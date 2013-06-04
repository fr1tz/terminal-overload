// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSBODY_H_
#define _T3D_PHYSICS_PHYSICSBODY_H_

#ifndef _T3D_PHYSICSCOMMON_H_
#include "T3D/physics/physicsCommon.h"
#endif
#ifndef _T3D_PHYSICS_PHYSICSOBJECT_H_
#include "T3D/physics/physicsObject.h"
#endif

class PhysicsCollision;
class SceneObject;


/// Simple physics object that represents a single rigid body.
class PhysicsBody : public PhysicsObject
{
public:

   virtual ~PhysicsBody() {}

   enum
   {
      /// Marks the body as a trigger object which is only used
      /// to get collision events and not get collision response.
      BF_TRIGGER = BIT( 0 ),

      /// The body is kinematic and assumed to be moved by 
      /// the game code via transforms.
      BF_KINEMATIC = BIT( 1 ),

      /// The body responds to contacts but does not push forces into others.
      BF_DEBRIS = BIT( 2 )
   };

   /// Initialize the body with a collision shape 
   /// and basic physics properties.
   virtual bool init(   PhysicsCollision *shape, 
                        F32 mass,
                        U32 bodyFlags,
                        SceneObject *obj, 
                        PhysicsWorld *world ) = 0;

   /// Returns true if the object is a dynamic rigid body 
   /// animated by the physics simulation.
   ///
   /// Kinematics are not considered to be dynamic.
   ///
   virtual bool isDynamic() const = 0;

   /// Returns the collision shape used to create the body.
   virtual PhysicsCollision* getColShape() = 0;

   ///
   virtual void setSleepThreshold( F32 linear, F32 angular ) = 0;

   ///
   virtual void setDamping( F32 linear, F32 angular ) = 0;

   ///
   virtual void getState( PhysicsState *outState ) = 0;

   ///
   virtual F32 getMass() const = 0;

   ///
   virtual Point3F getCMassPosition() const = 0;

   ///
   virtual void setLinVelocity( const Point3F &vel ) = 0;

   ///
   virtual void setAngVelocity( const Point3F &vel ) = 0;

   ///
   virtual Point3F getLinVelocity() const = 0;

   ///
   virtual Point3F getAngVelocity() const = 0;

   ///
   virtual void setSleeping( bool sleeping ) = 0;

   ///
   virtual void setMaterial(  F32 restitution,
                              F32 friction, 
                              F32 staticFriction ) = 0;

   ///
   virtual void applyCorrection( const MatrixF &xfm ) = 0;

   ///
   virtual void applyImpulse( const Point3F &origin, const Point3F &force ) = 0;
};


#endif // _T3D_PHYSICS_PHYSICSBODY_H_