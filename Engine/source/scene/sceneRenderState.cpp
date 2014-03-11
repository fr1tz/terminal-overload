// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/palette.h"
#include "scene/sceneRenderState.h"

#include "renderInstance/renderPassManager.h"
#include "math/util/matrixSet.h"



//-----------------------------------------------------------------------------

SceneRenderState::SceneRenderState( SceneManager* sceneManager,
                                    ScenePassType passType,
                                    const SceneCameraState& view,
                                    RenderPassManager* renderPass /* = NULL */,
                                    bool usePostEffects /* = true */ )
   :  mSceneManager( sceneManager ),
      mCullingState( sceneManager, view ),
      mRenderPass( renderPass ? renderPass : sceneManager->getDefaultRenderPass() ),
      mScenePassType( passType ),
      mRenderNonLightmappedMeshes( true ),
      mRenderLightmappedMeshes( true ),
      mUsePostEffects( usePostEffects ),
      mDisableAdvancedLightingBins( false ),
      mRenderArea( view.getFrustum().getBounds() ),
      mAmbientLightColor( sceneManager->getAmbientLightColor() ),
      mSceneRenderStyle( SRS_Standard ),
      mRenderField( 0 )
{
   // Setup the default parameters for the screen metrics methods.
   mDiffuseCameraTransform = view.getViewWorldMatrix();

   // The vector eye is the camera vector with its 
   // length normalized to 1 / zFar.
   getCameraTransform().getColumn( 1, &mVectorEye );
   mVectorEye.normalize( 1.0f / getFarPlane() );

   // TODO: What about ortho modes?  Is near plane ok
   // or do i need to remove it... maybe ortho has a near
   // plane of 1 and it just works out?

   const Frustum& frustum = view.getFrustum();
   const RectI& viewport = view.getViewport();

   mWorldToScreenScale.set(   ( frustum.getNearDist() * viewport.extent.x ) / ( frustum.getNearRight() - frustum.getNearLeft() ),
                              ( frustum.getNearDist() * viewport.extent.y ) / ( frustum.getNearTop() - frustum.getNearBottom() ) );

   // Assign shared matrix data to the render pass.

   mRenderPass->assignSharedXform( RenderPassManager::View, view.getWorldViewMatrix() );
   mRenderPass->assignSharedXform( RenderPassManager::Projection, view.getProjectionMatrix() );
}

//-----------------------------------------------------------------------------

SceneRenderState::~SceneRenderState()
{
}

//-----------------------------------------------------------------------------

const MatrixF& SceneRenderState::getWorldViewMatrix() const
{
   return getRenderPass()->getMatrixSet().getWorldToCamera();
}

//-----------------------------------------------------------------------------

const MatrixF& SceneRenderState::getProjectionMatrix() const
{
   return getRenderPass()->getMatrixSet().getCameraToScreen();
}

//-----------------------------------------------------------------------------

void SceneRenderState::renderObjects( SceneObject** objects, U32 numObjects )
{
   // Let the objects batch their stuff.

   PROFILE_START( SceneRenderState_prepRenderImages );
   for( U32 i = 0; i < numObjects; ++ i )
   {
      SceneObject* object = objects[ i ];
      Palette::active = object->getPalette();
      object->prepRenderImage( this );
      Palette::active.reset();
   }
   PROFILE_END();

   // Render what the objects have batched.

   getRenderPass()->renderPass( this );
}
