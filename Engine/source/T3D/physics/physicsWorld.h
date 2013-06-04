// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSWORLD_H_
#define _T3D_PHYSICS_PHYSICSWORLD_H_

#ifndef _SIGNAL_H_
#include "core/util/tSignal.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif

class ProcessList;
class Point3F;
struct RayInfo;
class SceneRenderState;
class PhysicsBody;



class PhysicsWorld
{
protected:

   Signal<void()> mStaticChangedSignal;

   Signal<void()> mUpdateSignal;

   /// The current gravity force.
   Point3F mGravity;

public:

   /// The constructor.
   PhysicsWorld();

   /// The destructor.
   virtual ~PhysicsWorld() {};

   /// 
   Signal<void()>& getUpdateSignal() { return mUpdateSignal; }

   // Called when a static body in the scene has been removed.
   Signal<void()>& getStaticChangedSignal() { return mStaticChangedSignal; }
   
   /// Overloaded to do debug drawing.
   ///
   /// It is assumed the GFX state is setup prior to this call for
   /// rendering in world space.
   ///
   virtual void onDebugDraw( const SceneRenderState *state ) = 0;

   /// Prepare the physics world for use.
   virtual bool initWorld( bool isServer, ProcessList *processList ) = 0;

   /// Tears down the physics world destroying any existing
   /// bodies, joints, and controllers.
   virtual void destroyWorld() = 0;

   ///
   virtual void reset() = 0;

   /// Returns true if the physics world is active and simulating.
   virtual bool isEnabled() const = 0;

   /// Returns the active gravity force.
   const Point3F& getGravity() const { return mGravity; }

   /// An abstract way to raycast into any type of PhysicsWorld, in a way 
   /// that mirrors a Torque-style raycast.  
   //
   /// This method is not fully developed or very sophisticated. For example, 
   /// there is no system of collision groups or raycast masks, which could 
   /// be very complex to write in a PhysicsPlugin-Abstract way...
   //
   // Optional forceAmt parameter will also apply a force to hit objects.
   virtual bool castRay( const Point3F &startPnt, const Point3F &endPnt, RayInfo *ri, const Point3F &impulse ) = 0;


   ///
   enum BodyType
   {
      BT_Static     = BIT( 0 ),
      BT_Dynamic    = BIT( 1 ),
      BT_Player     = BIT( 2 ),

      BT_All = BT_Static | BT_Dynamic | BT_Player
   };

   ///
   virtual PhysicsBody* castRay( const Point3F &start, const Point3F &end, U32 bodyTypes = BT_All ) = 0;

   virtual void explosion( const Point3F &pos, F32 radius, F32 forceMagnitude ) = 0;
};


#endif // _T3D_PHYSICS_PHYSICSWORLD_H_