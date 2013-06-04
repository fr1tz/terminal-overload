// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSFORCE_H_
#define _T3D_PHYSICS_PHYSICSFORCE_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _T3D_PHYSICSCOMMON_H_
#include "T3D/physics/physicsCommon.h"
#endif
#ifndef _T3D_PHYSICS_PHYSICSOBJECT_H_
#include "T3D/physics/physicsObject.h"
#endif

class PhysicsBody;
class PhysicsWorld;


/// A physics force controller used for gameplay effects.
class PhysicsForce : public SceneObject
{
   typedef SceneObject Parent;

public:

   PhysicsForce();
   virtual ~PhysicsForce();

   DECLARE_CONOBJECT( PhysicsForce );

   // SimObject
   static void initPersistFields();
   bool onAdd();
   void onRemove();   
   
   // SceneObject
   void onMount( SceneObject *obj, S32 node );
   void onUnmount( SceneObject *obj, S32 node );

   // ProcessObject
   void processTick( const Move *move );

   ///
   void attach( const Point3F &start, const Point3F &direction, F32 maxDist );

   ///
   void detach( const Point3F &force = Point3F::Zero );

   ///
   bool isAttached() const { return mBody != NULL; }

protected:

   void _preTick();

   ///
   PhysicsWorld *mWorld;

   F32 mForce;

   ///
   bool mPhysicsTick;

   ///
   WeakRefPtr<PhysicsBody> mBody;

};


#endif // _T3D_PHYSICS_PHYSICSFORCE_H_