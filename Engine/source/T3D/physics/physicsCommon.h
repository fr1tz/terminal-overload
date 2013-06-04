// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICSCOMMON_H_
#define _T3D_PHYSICSCOMMON_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MQUAT_H_
#include "math/mQuat.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif
#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif


/// Helper structure which defines the state of a single physics body.
struct PhysicsState
{
   /// Constructor.
   PhysicsState()
      :  position( Point3F::Zero ),
         momentum( Point3F::Zero ),
         orientation( QuatF::Identity ),
         angularMomentum( Point3F::Zero ),
         linVelocity( Point3F::Zero ),
         angVelocity( Point3F::Zero ),
         sleeping( false )
   {
   }

   /// The primary physics state.
   // @{

   /// The position of the body.
   Point3F position;
  
   /// The momentum in kilogram meters per second.
   Point3F momentum;

   /// The orientation of the body.
   QuatF orientation;

   /// The angular momentum.
   Point3F angularMomentum; 

   /// Is true if the shape is asleep.
   bool sleeping;

   // @}

   /// The secondary physics state derived from the primary state.
   /// @{

   /// The linear velocity derived from the momentum.
   Point3F linVelocity;

   /// 
   Point3F angVelocity;

   /*
   Vector velocity;                ///< velocity in meters per second (calculated from momentum).
   Quaternion spin;                ///< quaternion rate of change in orientation.
   Vector angularVelocity;         ///< angular velocity (calculated from angularMomentum).
   Matrix bodyToWorld;             ///< body to world coordinates matrix.
   Matrix worldToBody;             ///< world to body coordinates matrix.
   */

   /// @}


   /// Interpolates between two physics states leaving the 
   /// result in this physics state.
	inline PhysicsState& interpolate( const PhysicsState &a, const PhysicsState &b, F32 t )
	{
      F32 inverseT = 1.0f - t;
		position = a.position*inverseT + b.position*t;
		momentum = a.momentum*inverseT + b.momentum*t;
		orientation.interpolate( a.orientation, b.orientation, t );
		angularMomentum = a.angularMomentum*inverseT + b.angularMomentum*t;

      // Recalculate the velocities
      //linVelocity = 
      //angVelocity

		return *this;
	}

   /// Helper builds the transform from the state.
   inline MatrixF getTransform() const
   {
      MatrixF xfm;
      orientation.setMatrix( &xfm );
      xfm.setPosition( position );
      return xfm;
   }

};


/// The event type passed to the physics reset signal.
/// @see PhysicsPlugin::getPhysicsResetSignal().
enum PhysicsResetEvent
{
   PhysicsResetEvent_Store,
   PhysicsResetEvent_Restore
};

/// The signal for system wide physics events.
/// @see PhysicsPlugin
typedef Signal<void(PhysicsResetEvent reset)> PhysicsResetSignal;

class PhysicsCollision;

/// A strong reference to a physics collision shape.
typedef StrongRefPtr<PhysicsCollision> PhysicsCollisionRef;

#endif // _T3D_PHYSICSCOMMON_H_