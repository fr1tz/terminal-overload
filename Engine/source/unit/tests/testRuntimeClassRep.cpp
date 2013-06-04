// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/runtimeClassRep.h"
#include "unit/test.h"

using namespace UnitTesting;

//-----------------------------------------------------------------------------

class RuntimeRegisteredSimObject : public SimObject
{
   typedef SimObject Parent;

protected:
   bool mFoo;

public:
   RuntimeRegisteredSimObject() : mFoo( false ) {};

   DECLARE_RUNTIME_CONOBJECT(RuntimeRegisteredSimObject);

   static void initPersistFields();
};

IMPLEMENT_RUNTIME_CONOBJECT(RuntimeRegisteredSimObject);

void RuntimeRegisteredSimObject::initPersistFields()
{
   addField( "fooField", TypeBool, Offset( mFoo, RuntimeRegisteredSimObject ) );
}

//-----------------------------------------------------------------------------

CreateUnitTest( RuntimeClassRepUnitTest, "Console/RuntimeClassRep" )
{
   void run()
   {
      // First test to make sure that the test class is not registered (don't know how it could be, but that's programming for you)
      test( !RuntimeRegisteredSimObject::dynRTClassRep.isRegistered(), "RuntimeRegisteredSimObject class was already registered with the console" );

      // This should not be able to find the class, and return null (this may AssertWarn as well)
      ConsoleObject *conobj = ConsoleObject::create( "RuntimeRegisteredSimObject" );
      test( conobj == NULL, "AbstractClassRep returned non-NULL value! That is really bad!" );

      // Register with console system
      RuntimeRegisteredSimObject::dynRTClassRep.consoleRegister();

      // Make sure that the object knows it's registered
      test( RuntimeRegisteredSimObject::dynRTClassRep.isRegistered(), "RuntimeRegisteredSimObject class failed console registration" );

      // Now try again to create the instance
      conobj = ConsoleObject::create( "RuntimeRegisteredSimObject" );
      test( conobj != NULL, "AbstractClassRep::create method failed!" );

      // Cast the instance, and test it
      RuntimeRegisteredSimObject *rtinst = dynamic_cast<RuntimeRegisteredSimObject *>( conobj );
      test( rtinst != NULL, "Casting failed for some reason" );

      // Register it
      rtinst->registerObject( "_utRRTestObject" );
      test( rtinst->isProperlyAdded(), "registerObject failed on test object" );

      // Now execute some script on it
      Con::evaluate( "_utRRTestObject.fooField = true;" );

      // Test to make sure field worked
      test( dAtob( rtinst->getDataField( StringTable->insert( "fooField" ), NULL ) ), "Script test failed!" );

      // BALETED
      rtinst->deleteObject();

      // Unregister the class
      RuntimeRegisteredSimObject::dynRTClassRep.consoleUnRegister();

      // And make sure we can't create another one
      conobj = ConsoleObject::create( "RuntimeRegisteredSimObject" );
      test( conobj == NULL, "Unregistration of type failed" );
   }
};