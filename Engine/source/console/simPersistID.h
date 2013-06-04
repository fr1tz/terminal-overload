// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMPERSISTID_H_
#define _SIMPERSISTID_H_

#ifndef _TORQUE_UUID_H_
   #include "core/util/uuid.h"
#endif
#ifndef _REFBASE_H_
   #include "core/util/refBase.h"
#endif


/// @file
/// Persistent IDs for SimObjects.


class SimObject;
template< typename, typename > class HashTable;


/// A globally unique persistent ID for a SimObject.
class SimPersistID : public StrongRefBase
{
   public:
   
      typedef void Parent;
      friend class SimObject;
      
   protected:
   
      typedef HashTable< Torque::UUID, SimPersistID* > LookupTableType;
   
      /// Reference to the SimObject.  Will be NULL for as long as the
      /// persistent ID is not resolved.
      SimObject* mObject;
   
      /// The UUID assigned to the object.  Never changes.
      Torque::UUID mUUID;
      
      /// Table of persistent object IDs.
      static LookupTableType* smLookupTable;

      /// Construct a new persistent ID for "object" by generating a fresh
      /// unique identifier.
      SimPersistID( SimObject* object );
      
      /// Construct a persistent ID stub for the given unique identifier.
      /// The stub remains not bound to any object until it is resolved.
      SimPersistID( const Torque::UUID& uuid );
      
      ///
      ~SimPersistID();
      
      /// Bind this unresolved PID to the given object.
      void resolve( SimObject* object );
      
      ///
      void unresolve() { mObject = NULL; }

      /// Create a persistent ID for the given object.
      static SimPersistID* create( SimObject* object );
         
   public:
   
      /// Initialize the persistent ID system.
      static void init();
      
      /// Uninitialize the persistent ID system.
      static void shutdown();
      
      /// Look up a persistent ID by its UUID.  Return NULL if no PID is bound to the given UUID.
      static SimPersistID* find( const Torque::UUID& uuid );

      /// Look up a persistent ID by its UUID.  If no PID is bound to the given UUID yet, create a
      /// new PID and bind it to the UUID.
      static SimPersistID* findOrCreate( const Torque::UUID& uuid );
      
      /// Find a SimObject by the UUID assigned to its PID.  Return NULL if either no PID is bound
      /// to the given UUID or if the PID bound to it is not yet resolved.
      static SimObject* findObjectByUUID( const Torque::UUID& uuid );
            
      /// Return the object that is bound to this PID.  If the PID has not yet been resolved,
      /// return NULL.
      SimObject* getObject() const { return mObject; }
      
      /// Return the UUID bound to this PID.
      const Torque::UUID& getUUID() const { return mUUID; }
};

#endif // !_SIMPERSISTID_H_
