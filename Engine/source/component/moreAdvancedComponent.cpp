// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "component/moreAdvancedComponent.h"

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
