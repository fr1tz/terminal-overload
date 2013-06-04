// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "unit/test.h"
#include "core/threadStatic.h"
#include "math/mRandom.h"
#include "platform/profiler.h"

using namespace UnitTesting;

//-----------------------------------------------------------------------------
// This unit test will blow up without thread static support
#if defined(TORQUE_ENABLE_THREAD_STATICS) && defined(TORQUE_ENABLE_PROFILER)

// Declare a test thread static
DITTS( U32, gInstancedStaticFoo, 42 );
static U32 gTrueStaticFoo = 42;

CreateUnitTest( TestThreadStaticPerformance, "Core/ThreadStaticPerformance" )
{
   void run()
   {
      // Bail if the profiler is turned on right now
      if( !test( !gProfiler->isEnabled(), "Profiler is currently enabled, test cannot continue" ) )
         return;

      // Spawn an instance
      TorqueThreadStaticListHandle testInstance = _TorqueThreadStaticReg::spawnThreadStaticsInstance();

      static const dsize_t TEST_SIZE = 100000;

      // What we are going to do in this test is to test some U32 static
      // performance. The test will be run TEST_SIZE times, and so first create
      // an array of values to standardize the tests on.
      U32 testValue[TEST_SIZE];

      for( int i = 0; i < TEST_SIZE; i++ )
         testValue[i] = gRandGen.randI();

      // Reset the profiler, tell it to dump to console when done
      gProfiler->dumpToConsole();
      gProfiler->enable( true );

      // Value array is initialized, so lets put the foo's through the paces
      PROFILE_START(ThreadStaticPerf_TrueStaticAssign);
      for( int i = 0; i < TEST_SIZE; i++ )
         gTrueStaticFoo = testValue[i];
      PROFILE_END();

      PROFILE_START(ThreadStaticPerf_InstanceStaticAssign);
      for( int i = 0; i < TEST_SIZE; i++ )
         ATTS_( gInstancedStaticFoo, 1 ) = testValue[i];
      PROFILE_END();

      gProfiler->enable( false );

      // Clean up instance
      _TorqueThreadStaticReg::destroyInstance( testInstance );
   }
};

#endif // TORQUE_ENABLE_THREAD_STATICS