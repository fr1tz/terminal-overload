// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/physics/physicsWorld.h"


PhysicsWorld::PhysicsWorld()
   : mGravity( 0, 0, -20.0f ) // NOTE: This matches the gravity used for player objects.
{
}
