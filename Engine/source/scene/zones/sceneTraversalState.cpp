// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/zones/sceneTraversalState.h"

#include "scene/sceneManager.h"
#include "scene/culling/sceneCullingState.h"
#include "scene/culling/sceneCullingVolume.h"
#include "scene/zones/sceneZoneSpaceManager.h"


//-----------------------------------------------------------------------------

SceneTraversalState::SceneTraversalState( SceneCullingState* cullingState )
   : mCullingState( cullingState ),
     mTraversedArea( 0.f )
{
   VECTOR_SET_ASSOCIATION( mZoneStack );
   VECTOR_SET_ASSOCIATION( mCullingVolumeStack );

   // Push the polyhedron of the root frustum onto the traversal
   // stack as the current culling volume.

   pushCullingVolume( cullingState->getRootVolume() );
}

//-----------------------------------------------------------------------------

SceneZoneSpace* SceneTraversalState::getZoneFromStack( U32 depth )
{
   SceneZoneSpaceManager* zoneManager = getCullingState()->getSceneManager()->getZoneManager();
   U32 zoneId = getZoneIdFromStack( depth );

   return zoneManager->getZoneOwner( zoneId );
}

//-----------------------------------------------------------------------------

void SceneTraversalState::pushCullingVolume( const SceneCullingVolume& volume )
{
   mCullingVolumeStack.push_back( volume );
}

//-----------------------------------------------------------------------------

void SceneTraversalState::popCullingVolume()
{
   AssertFatal( mCullingVolumeStack.size() > 1, "SceneTraversalState::popCullingVolume - Must not pop root volume" );
   mCullingVolumeStack.pop_back();
}
