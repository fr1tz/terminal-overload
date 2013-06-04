// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef UNIT_UNITTESTING_H
#define UNIT_UNITTESTING_H

#ifndef _PLATFORMINTRINSICS_H_
#  include "platform/platformIntrinsics.h"
#endif


namespace UnitTesting {

//-----------------------------------------------------------------------------

struct UnitMargin
{
static void Push(int margin);
static void Pop();
static int Current();
};

void UnitPrint(const char* msg);


//-----------------------------------------------------------------------------

class UnitTest {
   int _testCount;
   int _failureCount;
   int _warningCount;

   bool _lastTestResult;

public:
   UnitTest();
   virtual ~UnitTest() {};

   /// Test an assertion and note if it has failed.
   bool test(bool a,const char* msg) {
      dFetchAndAdd( _testCount, 1 );
      if (!a)
         fail(msg);
      _lastTestResult = a;
      return a;
   }

   /// Report a failture condition.
   void fail(const char* msg);

   /// Report a warning
   void warn(const char* msg);

   int getTestCount() const { return _testCount; }
   int getFailureCount() const { return _failureCount; }
   int getWarningCount() const { return _warningCount; }
   bool lastTestPassed() const { return _lastTestResult; }

   /// Implement this with the specific test.
   virtual void run() = 0;
};


//-----------------------------------------------------------------------------

class TestRegistry
{
   friend class DynamicTestRegistration; // Bless me, Father, for I have sinned, but this is damn cool

   static TestRegistry *_list;
   TestRegistry *_next;

   const char *_name;
   const char *_className;
   bool _isInteractive;

public:
   TestRegistry(const char* name, bool interactive, const char *className);
   virtual ~TestRegistry() {}
   static TestRegistry* getFirst() { return _list; }
   TestRegistry* getNext() { return _next; }
   const char* getName() { return _name; }
   const bool isInteractive()  { return _isInteractive; }
   virtual UnitTest* newTest() = 0;
};

template<class T>
class TestRegistration: public TestRegistry
{
public:
   virtual ~TestRegistration() 
   {
   }

   TestRegistration(const char* name, bool interactive, const char *className)
      : TestRegistry(name, interactive, className) 
   {
   }

   virtual UnitTest* newTest() 
   { 
      return new T; 
   }
};

class DynamicTestRegistration : public TestRegistry
{

   UnitTest *mUnitTest;

public:
   DynamicTestRegistration( const char *name, UnitTest *test );

   virtual ~DynamicTestRegistration();

   virtual UnitTest *newTest() { return mUnitTest; }
};


//-----------------------------------------------------------------------------

class TestRun {
   int _testCount;
   int _subCount;
   int _failureCount;
   int _warningCount;
   void test(TestRegistry* reg);
public:
   TestRun();
   void printStats();
   bool test(const char* module, bool skipInteractive = false);
};

#define CreateUnitTest(Class,Name) \
   class Class; \
   static UnitTesting::TestRegistration<Class> _UnitTester##Class (Name, false, #Class); \
   class Class : public UnitTesting::UnitTest

#define CreateInteractiveTest(Class,Name) \
   class Class; \
   static UnitTesting::TestRegistration<Class> _UnitTester##Class (Name, true, #Class); \
   class Class : public UnitTesting::UnitTest

} // Namespace

#endif
