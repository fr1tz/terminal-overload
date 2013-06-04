// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "unit/test.h"
#include "unit/memoryTester.h"
#include "core/util/tVector.h"

using namespace UnitTesting;

CreateUnitTest(TestVectorAllocate, "Types/Vector")
{
   void run()
   {
      MemoryTester m;
      m.mark();

      Vector<S32> *vector = new Vector<S32>;
      for(S32 i=0; i<1000; i++)
         vector->push_back(10000 + i);

      // Erase the first element, 500 times.
      for(S32 i=0; i<500; i++)
         vector->erase(U32(0));

      vector->compact();

      test(vector->size() == 500, "Vector was unexpectedly short!");

      delete vector;

      test(m.check(), "Vector allocation test leaked memory!");
   }
};