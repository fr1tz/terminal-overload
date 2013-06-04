// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "core/util/journal/process.h"
#include "core/util/safeDelete.h"

using namespace UnitTesting;

CreateUnitTest(TestingProcess, "Journal/Process")
{
   // How many ticks remaining?
   U32 _remainingTicks;

   // Callback for process list.
   void process()
   {
      if(_remainingTicks==0)
         Process::requestShutdown();

      _remainingTicks--;
   }

   void run()
   {
      // We'll run 30 ticks, then quit.
      _remainingTicks = 30;

      // Register with the process list.
      Process::notify(this, &TestingProcess::process);

      // And do 30 notifies, making sure we end on the 30th.
      for(S32 i=0; i<30; i++)
         test(Process::processEvents(), "Should quit after 30 ProcessEvents() calls - not before!");
      test(!Process::processEvents(), "Should quit after the 30th ProcessEvent() call!");
   }
};