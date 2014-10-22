// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "component/simComponent.h"

class CachedInterfaceExampleComponent : public SimComponent
{
   typedef SimComponent Parent;

   ComponentProperty<U32> mMyId;
   static U32 smNumInstances;
   ComponentProperty<U32> *mpU32; // CodeReview [patw, 2, 17, 2007] Make ref objects when this is in Jugg

public:
   DECLARE_CONOBJECT( CachedInterfaceExampleComponent );

   CachedInterfaceExampleComponent() : mpU32( NULL )
   {
      mMyId = ( ( 1 << 24 ) | smNumInstances++ );
   }
   virtual ~CachedInterfaceExampleComponent()
   {
      smNumInstances--;
   }

public:
   //////////////////////////////////////////////////////////////////////////

   virtual void registerInterfaces( SimComponent *owner )
   {
      // Register a cached interface for this 
      owner->registerCachedInterface( NULL, "aU32", this, &mMyId );
   }

   //////////////////////////////////////////////////////////////////////////

   bool onComponentRegister( SimComponent *owner )
   {
      // Call up to the parent first
      if( !Parent::onComponentRegister( owner ) )
         return false;

      // We want to get an interface from another object in our containing component
      // to simulate component interdependency. 
      ComponentInterfaceList list;

      // Enumerate the interfaces on the owner, only ignore interfaces that this object owns
      if( !owner->getInterfaces( &list, NULL, "aU32", this, true ) )
         return false;

      // Sanity check before just assigning all willy-nilly
      for( ComponentInterfaceListIterator i = list.begin(); i != list.end(); i++ )
      {
         mpU32 = dynamic_cast<ComponentProperty<U32> *>( (*i) );

         if( mpU32 != NULL )
            return true;
      }

      return false;
   }

   //////////////////////////////////////////////////////////////////////////

   // CodeReview [patw, 2, 17, 2007] I'm going to make another lightweight interface
   // for this functionality later
   void unit_test()
   {
      EXPECT_TRUE( mpU32 != NULL )
         << "Pointer to dependent interface is NULL";
      if( mpU32 )
      {
         EXPECT_TRUE( *(*mpU32) & ( 1 << 24 ) )
            << "Pointer to interface data is bogus.";
         EXPECT_TRUE( *(*mpU32) != *mMyId )
            << "Two of me have the same ID, bad!";
      }
   }
};

IMPLEMENT_CONOBJECT( CachedInterfaceExampleComponent );
U32 CachedInterfaceExampleComponent::smNumInstances = 0;

ConsoleDocClass( CachedInterfaceExampleComponent,
				"@brief Legacy from older component system.\n\n"
				"Not intended for game development, for editors or internal use only.\n\n "
				"@internal");

TEST(SimComponent, Composition)
{
   SimComponent *testComponent = new SimComponent();
   CachedInterfaceExampleComponent *componentA = new CachedInterfaceExampleComponent();
   CachedInterfaceExampleComponent *componentB = new CachedInterfaceExampleComponent();

   // Register sub-components
   EXPECT_TRUE( componentA->registerObject() )
      << "Failed to register componentA";
   EXPECT_TRUE( componentB->registerObject() )
      << "Failed to register componentB";

   // Add the components
   EXPECT_TRUE( testComponent->addComponent( componentA ) )
      << "Failed to add component a to testComponent";
   EXPECT_TRUE( testComponent->addComponent( componentB ) )
      << "Failed to add component b to testComponent";

   EXPECT_EQ( componentA->getOwner(), testComponent )
      << "testComponent did not properly set the mOwner field of componentA to NULL.";
   EXPECT_EQ( componentB->getOwner(), testComponent )
      << "testComponent did not properly set the mOwner field of componentB to NULL.";

   // Register the object with the simulation, kicking off the interface registration
   ASSERT_TRUE( testComponent->registerObject() )
      << "Failed to register testComponent";

   {
      SCOPED_TRACE("componentA");
      componentA->unit_test();
   }
   {
      SCOPED_TRACE("componentB");
      componentB->unit_test();
   }

   testComponent->deleteObject();
};

#endif