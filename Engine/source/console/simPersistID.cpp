// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simPersistID.h"
#include "console/simObject.h"
#include "core/util/tDictionary.h"
#include "core/util/safeDelete.h"


//#define DEBUG_SPEW


SimPersistID::LookupTableType* SimPersistID::smLookupTable;


//-----------------------------------------------------------------------------

SimPersistID::SimPersistID( SimObject* object )
   : mObject( object )
{
   AssertFatal( object, "SimPersistID::SimPersistID - got a NULL object!" );
   AssertFatal( !object->getPersistentId(), "SimPersistID::SimPersistID - object already has a persistent ID!" );
   
   mUUID.generate();
   smLookupTable->insertUnique( mUUID, this );
}

//-----------------------------------------------------------------------------

SimPersistID::SimPersistID( const Torque::UUID& uuid )
   : mUUID( uuid ),
     mObject( NULL )
{
   AssertFatal( !uuid.isNull(), "SimPersistID::SimPersistID - invalid UUID!" );
   smLookupTable->insertUnique( mUUID, this );
}

//-----------------------------------------------------------------------------

SimPersistID::~SimPersistID()
{
   smLookupTable->erase( getUUID() );
}

//-----------------------------------------------------------------------------

void SimPersistID::init()
{
   smLookupTable = new LookupTableType;
}

//-----------------------------------------------------------------------------

void SimPersistID::shutdown()
{
   SAFE_DELETE( smLookupTable );
}

//-----------------------------------------------------------------------------

SimPersistID* SimPersistID::create( SimObject* object )
{
   SimPersistID* pid = new SimPersistID( object );
   
   #ifdef DEBUG_SPEW
   Platform::outputDebugString( "[SimPersistID] Created new pid for object %i:%s (%s) with uuid '%s'",
      object->getId(), object->getClassName(), object->getName(),
      pid->getUUID().toString().c_str() );
   #endif
   
   return pid;
}

//-----------------------------------------------------------------------------

void SimPersistID::resolve( SimObject* object )
{
   AssertFatal( !mObject, "SimPersistID::resolve - PID is already resolved!" );
   mObject = object;
   
   #ifdef DEBUG_SPEW
   Platform::outputDebugString( "[SimPersistID] Resolving pid '%s' to %i:%s (%s)",
      getUUID().toString().c_str(),
      object->getId(), object->getClassName(), object->getName() );
   #endif
}

//-----------------------------------------------------------------------------

SimPersistID* SimPersistID::find( const Torque::UUID& uuid )
{
   AssertFatal( smLookupTable, "SimPersistID::find - system has not been initialized" );
   
   LookupTableType::Iterator iter = smLookupTable->find( uuid );
   if( iter != smLookupTable->end() )
      return iter->value;
      
   return NULL;
}

//-----------------------------------------------------------------------------

SimPersistID* SimPersistID::findOrCreate( const Torque::UUID& uuid )
{
   AssertFatal( smLookupTable, "SimPersistID::findOrCreate - system has not been initialized" );
   
   SimPersistID* pid = find( uuid );
   if( !pid )
   {      
      pid = new SimPersistID( uuid );

      #ifdef DEBUG_SPEW
      Platform::outputDebugString( "[SimPersistID] Created unresolved pid for UUID '%s'",
         uuid.toString().c_str() );
      #endif
   }
      
   return pid;
}
