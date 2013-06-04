// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PHYSICS_PHYSICSUSERDATA_H_
#define _PHYSICS_PHYSICSUSERDATA_H_

#ifndef _SIGNAL_H_
#include "core/util/tSignal.h"
#endif

class PhysicsUserData;
class SceneObject;
class Point3F;
class PhysicsBody;


/// Signal used for contact reports.
///
/// @param us The physics user data for the signaling object.
/// @param them The other physics user data involved in the contact.
/// @param hitPoint The approximate position of the impact.
/// @param hitForce
///
/// @see PhysicsUserData
///
typedef Signal<void( PhysicsUserData *us,
                     PhysicsUserData *them,
                     const Point3F &hitPoint,
                     const Point3F &hitForce )> PhysicsContactSignal;


/// The base class for physics user data.
class PhysicsUserData
{
public:

   /// The constructor.
   PhysicsUserData()
      :  mObject( NULL ),
         mBody( NULL )
         #ifdef TORQUE_DEBUG
         , mTypeId( smTypeName )
         #endif
      {}

   /// The destructor.
   virtual ~PhysicsUserData() {}

   ///
   void setObject( SceneObject *object ) { mObject = object; }
   SceneObject* getObject() const { return mObject; }

   void setBody( PhysicsBody *body ) { mBody = body; }
   PhysicsBody* getBody() const { return mBody; }

   /// Helper method for casting a void pointer to a userdata pointer.
   static inline SceneObject* getObject( void *data )
   {
      PhysicsUserData *result = cast( data );
      return result ? result->getObject() : NULL;
   }

   PhysicsContactSignal& getContactSignal() { return mContactSignal; }

   /// Helper method for casting a void pointer to a userdata pointer.
   static inline PhysicsUserData* cast( void *data )
   {
      PhysicsUserData *result = (PhysicsUserData*)data;
      
      // If the typeid doesn't equal the value we assigned to it at
      // construction then this isn't a PhysicsUserData object.
      #ifdef TORQUE_DEBUG
      AssertFatal( !result || result->mTypeId == smTypeName,
          "PhysicsUserData::cast - The pointer is the wrong type!" );
      #endif

      return result;
   }

protected:

   #ifdef TORQUE_DEBUG

   /// The type string used to validate the void* cast.
   /// @see cast
   static const char *smTypeName;

   /// The type string assigned at construction used to
   /// validate the void* cast.
   /// @see cast
   const char *mTypeId;
   #endif

   PhysicsContactSignal mContactSignal;

   SceneObject *mObject;

   PhysicsBody *mBody;
};

#endif // _PHYSICS_PHYSICSUSERDATA_H_   