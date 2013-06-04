// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/sceneCameraState.h"

#include "gfx/gfxDevice.h"


//-----------------------------------------------------------------------------

SceneCameraState::SceneCameraState( const RectI& viewport, const Frustum& frustum, const MatrixF& worldView, const MatrixF& projection )
   : mViewport( viewport ),
     mFrustum( frustum ),
     mWorldViewMatrix( worldView ),
     mProjectionMatrix( projection )
{
   mViewDirection = frustum.getTransform().getForwardVector();
}

//-----------------------------------------------------------------------------

SceneCameraState SceneCameraState::fromGFX()
{
   return fromGFXWithViewport( GFX->getViewport() );
}

//-----------------------------------------------------------------------------

SceneCameraState SceneCameraState::fromGFXWithViewport( const RectI& viewport )
{
   const MatrixF& world = GFX->getWorldMatrix();
   
   MatrixF camera = world;
   camera.inverse();

   Frustum frustum = GFX->getFrustum();
   frustum.setTransform( camera );

   return SceneCameraState(
      viewport,
      frustum,
      world,
      GFX->getProjectionMatrix()
   );
}
