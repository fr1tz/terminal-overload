// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "component/moreAdvancedComponent.h"
#include "unit/test.h"

// unitTest_runTests("Component/MoreAdvancedComponent");

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_CONOBJECT(MoreAdvancedComponent);

ConsoleDocClass( MoreAdvancedComponent,
				"@brief This is a slightly more advanced component which will be used to demonstrate "
				"components which are dependent on other components.\n\n"
				"Not intended for game development, for editors or internal use only.\n\n "
				"@internal");

bool MoreAdvancedComponent::onComponentRegister( SimComponent *owner )
{
   if( !Parent::onComponentRegister( owner ) )
      return false;

   // This will return the first interface of type SimpleComponent that is cached
   // on the parent object. 
   mSCInterface = owner->getInterface<SimpleComponentInterface>();

   // If we can't find this interface, our component can't function, so false
   // will be returned, and this will signify, to the top-level component, that it
   // should fail the onAdd call.
   return ( mSCInterface != NULL );
}

bool MoreAdvancedComponent::testDependentInterface()
{
   // These two requirements must be met in order for the test to proceed, so
   // lets check them.
   if( mSCInterface == NULL || !mSCInterface->isValid() )
      return false;

   return mSCInterface->isFortyTwo( 42 );
}

//////////////////////////////////////////////////////////////////////////

using namespace UnitTesting;

CreateUnitTest(MoreAdvancedComponentTest, "Component/MoreAdvancedComponent")
{
   void run()
   {
      // Create component instances and compose them.
      SimComponent *parentComponent = new SimComponent();
      SimpleComponent *simpleComponent = new SimpleComponent();
      MoreAdvancedComponent *moreAdvComponent = new MoreAdvancedComponent();
      // CodeReview note that the interface pointer isn't initialized in a ctor
      //  on the components, so it's bad memory against which you might
      //  be checking in testDependentInterface [3/3/2007 justind]
      parentComponent->addComponent( simpleComponent );
      parentComponent->addComponent( moreAdvComponent );

      simpleComponent->registerObject();
      moreAdvComponent->registerObject();

      // Put a break-point here, follow the onAdd call, and observe the order in
      // which the SimComponent::onAdd function executes. You will see the interfaces
      // get cached, and the dependent interface query being made.
      parentComponent->registerObject();

      // If the MoreAdvancedComponent found an interface, than the parentComponent
      // should have returned true, from onAdd, and should therefore be registered
      // properly with the Sim
      test( parentComponent->isProperlyAdded(), "Parent component not properly added!" );

      // Now lets test the interface. You can step through this, as well.
      test( moreAdvComponent->testDependentInterface(), "Dependent interface test failed." ); 

      // CodeReview is there a reason we can't just delete the parentComponent here? [3/3/2007 justind]
      //
      // Clean up
      parentComponent->removeComponent( simpleComponent );
      parentComponent->removeComponent( moreAdvComponent );

      parentComponent->deleteObject();
      moreAdvComponent->deleteObject();
      simpleComponent->deleteObject();
   }
};