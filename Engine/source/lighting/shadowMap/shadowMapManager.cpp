// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/shadowMap/shadowMapManager.h"

#include "lighting/shadowMap/shadowMapPass.h"
#include "lighting/shadowMap/lightShadowMap.h"
#include "materials/materialManager.h"
#include "lighting/lightManager.h"
#include "core/util/safeDelete.h"
#include "scene/sceneRenderState.h"
#include "gfx/gfxTextureManager.h"
#include "core/module.h"
#include "console/consoleTypes.h"


GFX_ImplementTextureProfile(ShadowMapTexProfile,
                            GFXTextureProfile::DiffuseMap, 
                            GFXTextureProfile::PreserveSize | GFXTextureProfile::Dynamic , 
                            GFXTextureProfile::None);


MODULE_BEGIN( ShadowMapManager )

   MODULE_INIT
   {
      ManagedSingleton< ShadowMapManager >::createSingleton();
   }
   
   MODULE_SHUTDOWN
   {
      ManagedSingleton< ShadowMapManager >::deleteSingleton();
   }

MODULE_END;


AFTER_MODULE_INIT( Sim )
{
   Con::addVariable( "$pref::Shadows::textureScalar",	
      TypeF32, &LightShadowMap::smShadowTexScalar,
      "@brief Used to scale the shadow texture sizes.\n"
      "This can reduce the shadow quality and texture memory overhead or increase them.\n"
      "@ingroup AdvancedLighting\n" );
   Con::NotifyDelegate callabck( &LightShadowMap::releaseAllTextures );
   Con::addVariableNotify( "$pref::Shadows::textureScalar", callabck );

   Con::addVariable( "$pref::Shadows::disable", 
      TypeBool, &ShadowMapPass::smDisableShadowsPref,
      "Used to disable all shadow rendering.\n"
      "@ingroup AdvancedLighting\n" );

   Con::addVariable( "$Shadows::disable", 
      TypeBool, &ShadowMapPass::smDisableShadowsEditor,
      "Used by the editor to disable all shadow rendering.\n"
      "@ingroup AdvancedLighting\n" );

   Con::NotifyDelegate shadowCallback( &ShadowMapManager::updateShadowDisable );
   Con::addVariableNotify( "$pref::Shadows::disable", shadowCallback );
   Con::addVariableNotify( "$Shadows::disable", shadowCallback );
}

Signal<void(void)> ShadowMapManager::smShadowDeactivateSignal;


ShadowMapManager::ShadowMapManager() 
:  mShadowMapPass(NULL), 
   mCurrentShadowMap(NULL),
   mIsActive(false)
{
}

ShadowMapManager::~ShadowMapManager()
{
}

void ShadowMapManager::setLightShadowMapForLight( LightInfo *light )
{
   ShadowMapParams *params = light->getExtended<ShadowMapParams>();
   if ( params )
      mCurrentShadowMap = params->getShadowMap();
   else 
      mCurrentShadowMap = NULL;
}

void ShadowMapManager::activate()
{
   ShadowManager::activate();

   if (!getSceneManager())
   {
      Con::errorf("This world has no scene manager!  Shadow manager not activating!");
      return;
   }

   mShadowMapPass = new ShadowMapPass(LIGHTMGR, this);

   getSceneManager()->getPreRenderSignal().notify( this, &ShadowMapManager::_onPreRender, 0.01f );
   GFXTextureManager::addEventDelegate( this, &ShadowMapManager::_onTextureEvent );

   mIsActive = true;
}

void ShadowMapManager::deactivate()
{
   GFXTextureManager::removeEventDelegate( this, &ShadowMapManager::_onTextureEvent );
   getSceneManager()->getPreRenderSignal().remove( this, &ShadowMapManager::_onPreRender );

   SAFE_DELETE(mShadowMapPass);
   mTapRotationTex = NULL;

   // Clean up our shadow texture memory.
   LightShadowMap::releaseAllTextures();
   TEXMGR->cleanupPool();

   mIsActive = false;

   ShadowManager::deactivate();
}

void ShadowMapManager::_onPreRender( SceneManager *sg, const SceneRenderState *state )
{
   if ( mShadowMapPass && state->isDiffusePass() )
      mShadowMapPass->render( sg, state, (U32)-1 );
}

void ShadowMapManager::_onTextureEvent( GFXTexCallbackCode code )
{
   if ( code == GFXZombify )
      mTapRotationTex = NULL;
}

GFXTextureObject* ShadowMapManager::getTapRotationTex()
{
   if ( mTapRotationTex.isValid() )
      return mTapRotationTex;

   mTapRotationTex.set( 64, 64, GFXFormatR8G8B8A8, &ShadowMapTexProfile, 
                        "ShadowMapManager::getTapRotationTex" );

   GFXLockedRect *rect = mTapRotationTex.lock();
   U8 *f = rect->bits;
   F32 angle;
   for( U32 i = 0; i < 64*64; i++, f += 4 )
   {         
      // We only pack the rotations into the red
      // and green channels... the rest are empty.
      angle = M_2PI_F * gRandGen.randF();
      f[0] = U8_MAX * ( ( 1.0f + mSin( angle ) ) * 0.5f );
      f[1] = U8_MAX * ( ( 1.0f + mCos( angle ) ) * 0.5f );
      f[2] = 0;
      f[3] = 0;
   }

   mTapRotationTex.unlock();

   return mTapRotationTex;
}

void ShadowMapManager::updateShadowDisable()
{
   bool disable = false;

   if ( ShadowMapPass::smDisableShadowsEditor || ShadowMapPass::smDisableShadowsPref )
      disable = true;

   if ( disable != ShadowMapPass::smDisableShadows)
   {
      ShadowMapPass::smDisableShadows = disable;
      smShadowDeactivateSignal.trigger();
   }
}
