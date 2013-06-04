// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PHYSICSEVENTS_H_
#define _PHYSICSEVENTS_H_

#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

class SceneObject;
class SceneContainer;


/// When this NetEvent is processed on the client-side it 
/// applies a radial impulse to objects in the physics 
/// simulation.
class RadialImpulseEvent : public NetEvent
{
   typedef NetEvent Parent;

protected:

   struct ImpulseInfo
   {
      Point3F pos;
      F32 radius;
      F32 magnitude;
   };

   Point3F mPosition;
   F32 mRadius;
   F32 mMagnitude;

   static void _impulseCallback( SceneObject *obj, void *key );

public:

   RadialImpulseEvent();      
   RadialImpulseEvent( const Point3F &pos, F32 radius, F32 magnitude );
   ~RadialImpulseEvent();   

   virtual void pack( NetConnection* /*ps*/, BitStream *bstream );   
   virtual void write( NetConnection*, BitStream *bstream );   
   virtual void unpack( NetConnection *ps, BitStream *bstream );   
   virtual void process(NetConnection *);
   
   static void impulse( SceneContainer *con, const Point3F &position, F32 radius, F32 magnitude );

   DECLARE_CONOBJECT( RadialImpulseEvent );
};


#endif // _PHYSICSEVENTS_H_