// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/shadowMap/paraboloidLightShadowMap.h"
#include "lighting/common/lightMapParams.h"
#include "lighting/shadowMap/shadowMapManager.h"
#include "math/mathUtils.h"
#include "scene/sceneManager.h"
#include "scene/sceneRenderState.h"
//#include "scene/sceneReflectPass.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/util/gfxFrustumSaver.h"
#include "renderInstance/renderPassManager.h"
#include "materials/materialDefinition.h"
#include "gui/controls/guiBitmapCtrl.h"

ParaboloidLightShadowMap::ParaboloidLightShadowMap( LightInfo *light )
   :  Parent( light ),
      mShadowMapScale( 1, 1 ),
      mShadowMapOffset( 0, 0 )
{   
}

ParaboloidLightShadowMap::~ParaboloidLightShadowMap()
{
   releaseTextures();
}

ShadowType ParaboloidLightShadowMap::getShadowType() const
{
   const ShadowMapParams *params = mLight->getExtended<ShadowMapParams>();
   return params->shadowType;
}

void ParaboloidLightShadowMap::setShaderParameters(GFXShaderConstBuffer* params, LightingShaderConstants* lsc)
{
   if ( lsc->mTapRotationTexSC->isValid() )
      GFX->setTexture( lsc->mTapRotationTexSC->getSamplerRegister(), 
                        SHADOWMGR->getTapRotationTex() );

   ShadowMapParams *p = mLight->getExtended<ShadowMapParams>();
   if ( lsc->mLightParamsSC->isValid() )
   {
      Point4F lightParams( mLight->getRange().x, p->overDarkFactor.x, 0.0f, 0.0f);
      params->set( lsc->mLightParamsSC, lightParams );
   }

   // Atlasing parameters (only used in the dual case, set here to use same shaders)
   params->setSafe( lsc->mAtlasScaleSC, mShadowMapScale );
   params->setSafe( lsc->mAtlasXOffsetSC, mShadowMapOffset );

   // The softness is a factor of the texel size.
   params->setSafe( lsc->mShadowSoftnessConst, p->shadowSoftness * ( 1.0f / mTexSize ) );
}

void ParaboloidLightShadowMap::_render(   RenderPassManager* renderPass,
                                          const SceneRenderState *diffuseState )
{
   PROFILE_SCOPE(ParaboloidLightShadowMap_render);

   const LightMapParams *lmParams = mLight->getExtended<LightMapParams>();
   const bool bUseLightmappedGeometry = lmParams ? !lmParams->representedInLightmap || lmParams->includeLightmappedGeometryInShadow : true;

   const U32 texSize = getBestTexSize();

   if (  mShadowMapTex.isNull() || 
         mTexSize != texSize )
   {
      mTexSize = texSize;

      mShadowMapTex.set(   mTexSize, mTexSize, 
                           ShadowMapFormat, &ShadowMapProfile, 
                           "ParaboloidLightShadowMap" );
   }

   GFXFrustumSaver frustSaver;
   GFXTransformSaver saver;
   
   // Render the shadowmap!
   GFX->pushActiveRenderTarget();

   // Calc matrix and set up visible distance
   mWorldToLightProj = mLight->getTransform();
   mWorldToLightProj.inverse();
   GFX->setWorldMatrix(mWorldToLightProj);

   const F32 &lightRadius = mLight->getRange().x;
   GFX->setOrtho(-lightRadius, lightRadius, -lightRadius, lightRadius, 1.0f, lightRadius, true);

   // Set up target
   mTarget->attachTexture( GFXTextureTarget::Color0, mShadowMapTex );
   mTarget->attachTexture( GFXTextureTarget::DepthStencil, 
      _getDepthTarget( mShadowMapTex->getWidth(), mShadowMapTex->getHeight() ) );
   GFX->setActiveRenderTarget(mTarget);
   GFX->clear(GFXClearTarget | GFXClearStencil | GFXClearZBuffer, ColorI(255,255,255,255), 1.0f, 0);

   // Create scene state, prep it
   SceneManager* sceneManager = diffuseState->getSceneManager();
   
   SceneRenderState shadowRenderState
   (
      sceneManager,
      SPT_Shadow,
      SceneCameraState::fromGFXWithViewport( diffuseState->getViewport() ),
      renderPass
   );

   shadowRenderState.getMaterialDelegate().bind( this, &LightShadowMap::getShadowMaterial );
   shadowRenderState.renderNonLightmappedMeshes( true );
   shadowRenderState.renderLightmappedMeshes( bUseLightmappedGeometry );
   shadowRenderState.setDiffuseCameraTransform( diffuseState->getCameraTransform() );
   shadowRenderState.setWorldToScreenScale( diffuseState->getWorldToScreenScale() );

   sceneManager->renderSceneNoLights( &shadowRenderState, SHADOW_TYPEMASK );

   _debugRender( &shadowRenderState );
 
   mTarget->resolve();
   GFX->popActiveRenderTarget();   
}