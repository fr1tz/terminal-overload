// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "console/simObject.h"


using namespace UnitTesting;


// Test to ensure that all console classes in the system are default-constructible.

CreateUnitTest( TestDefaultConstruction, "Console/DefaultConstruction" )
{
   void run()
   {
      for( AbstractClassRep* classRep = AbstractClassRep::getClassList();
           classRep != NULL;
           classRep = classRep->getNextClass() )
      {
         // Create object.
         
         ConsoleObject* object = classRep->create();
         test( object, avar( "AbstractClassRep::create failed for class '%s'", classRep->getClassName() ) );
         if( !object )
            continue;
         
         // Make sure it's a SimObject.
         
         SimObject* simObject = dynamic_cast< SimObject* >( object );
         if( !simObject )
         {
            SAFE_DELETE( object );
            continue;
         }
         
         // Register the object.
         
         bool result = simObject->registerObject();
         test( result, avar( "registerObject failed for object of class '%s'", classRep->getClassName() ) );
         
         if( result )
            simObject->deleteObject();
         else
            SAFE_DELETE( simObject );
      }
   }
};
