// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "unit/memoryTester.h"

using namespace UnitTesting;

void MemoryTester::mark()
{

}

bool MemoryTester::check()
{
   //UnitTesting::UnitPrint("MemoryTester::check - unavailable w/o TORQUE_DEBUG_GUARD defined!");
   return true;
}
