// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "core/util/journal/process.h"

FIXTURE(Process)
{
public:
   U32 remainingTicks;
   void notification()
   {
      if(remainingTicks == 0)
         Process::requestShutdown();
      remainingTicks--;
   }
};

TEST_FIX(Process, BasicAPI)
{
   // We'll run 30 ticks, then quit.
   remainingTicks = 30;

   // Register with the process list.
   Process::notify(this, &ProcessFixture::notification);

   // And do 30 notifies, making sure we end on the 30th.
   for(S32 i = 0; i < 30; i++)
   {
      EXPECT_TRUE(Process::processEvents())
         << "Should quit after 30 ProcessEvents() calls - not before!";
   }

   EXPECT_FALSE(Process::processEvents())
      << "Should quit after the 30th ProcessEvent() call!";

   Process::remove(this, &ProcessFixture::notification);
};

#endif