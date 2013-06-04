// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSOBJECT_H_
#define _T3D_PHYSICS_PHYSICSOBJECT_H_

#ifndef _PHYSICS_PHYSICSUSERDATA_H_
#include "T3D/physics/physicsUserData.h"
#endif
#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif
#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif

class PhysicsWorld;
class MatrixF;
class Point3F;
class Box3F;


///
class PhysicsObject : public WeakRefBase 
{
public:
   
   virtual ~PhysicsObject();

   /// Returns the physics world this object is a member of.
   virtual PhysicsWorld* getWorld() = 0;

   /// Sets the transform on the physics object.
   ///
   /// For static objects this is only intended to be used for
   /// for infrequent changes when editing the mission.
   ///
   virtual void setTransform( const MatrixF &transform ) = 0;

   /// Returns the transform of the physics body at 
   /// the last processed simulation tick.
   virtual MatrixF& getTransform( MatrixF *outMatrix ) = 0;

   /// Returns the world aligned bounding box containing the PhysicsObject.
   virtual Box3F getWorldBounds() = 0;

   /// 
   void queueCallback( U32 ms, Delegate<void()> callback );

   const PhysicsUserData& getUserData() const { return mUserData; }

   PhysicsUserData& getUserData() { return mUserData; }

   /// Set false to skip simulation of this object or temporarily remove
   /// it from the physics simulation. Implementation is PhysicsPlugin specific.
   virtual void setSimulationEnabled( bool enabled ) = 0;
   virtual bool isSimulationEnabled() = 0;

protected:

   /// You shouldn't be creating this object directly.
   PhysicsObject();

   /// The user data object assigned to this object.
   PhysicsUserData mUserData;

   /// The last queued callback event.
   /// @see queueCallback
   U32 mQueuedEvent;
};

#endif // _T3D_PHYSICS_PHYSICSOBJECT_H_