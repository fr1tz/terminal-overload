// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _UNITTESTCOMPONENTINTERFACE_H_
#define _UNITTESTCOMPONENTINTERFACE_H_

#include "unit/test.h"
#include "component/simComponent.h"
#include "component/componentInterface.h"

// This is commented out because I want to keep the explicit namespace referencing
// so that the multiple inheritances from UnitTest doesn't screw anyone up. It will
// also make for more readable code in the derived test-interfaces. -patw
//using namespace UnitTesting;

/// This is a class that will make it very easy for a component author to provide
/// unit testing functionality from within an instantiated component.
class UnitTestComponentInterface : public ComponentInterface, UnitTesting::UnitTest
{
   typedef ComponentInterface Parent;

private:
   StringTableEntry mName;
   UnitTesting::DynamicTestRegistration *mTestReg;

   // Constructors/Destructors
public:
   UnitTestComponentInterface( const char *name )
   {
      mName = StringTable->insert( name );

      mTestReg = new UnitTesting::DynamicTestRegistration( name, this );
   }

   virtual ~UnitTestComponentInterface()
   {
      delete mTestReg;
   }
   
   // ComponentInterface overrides
public:
   virtual bool isValid() const 
   { 
      return Parent::isValid() && ( mTestReg != NULL ); 
   }

   // UnitTest overrides
public:
   /// This is the only function you need to overwrite to add a unit test interface
   /// your component.
   virtual void run() = 0;
};

// Macros
#ifndef TORQUE_DEBUG
#  define DECLARE_UNITTEST_INTERFACE(x)
#  define CACHE_UNITTEST_INTERFACE(x)
#else
//-----------------------------------------------------------------------------
#  define DECLARE_UNITTEST_INTERFACE(x) \
      class x##_UnitTestInterface : public UnitTestComponentInterface \
      {\
         typedef UnitTestComponentInterface Parent; \
      public: \
         x##_UnitTestInterface() : UnitTestComponentInterface( #x ) {}; \
         virtual void run(); \
      } _##x##UnitTestInterface
//-----------------------------------------------------------------------------
#  define CACHE_UNITTEST_INTERFACE(x) registerCachedInterface( "unittest", #x, this, &_##x##UnitTestInterface )
#endif

#endif