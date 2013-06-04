// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "platform/threads/threadPool.h"
#include "console/console.h"
#include "core/util/tVector.h"

#ifndef TORQUE_SHIPPING

using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )

// Simple test that creates and verifies an array of numbers using
// thread pool work items.

CreateUnitTest( TestThreadPool, "Platform/ThreadPool/Simple" )
{
   enum { DEFAULT_NUM_ITEMS = 4000 };
   
   static Vector< U32 > results;
   
   struct TestItem : public ThreadPool::WorkItem
   {
         typedef ThreadPool::WorkItem Parent;
         
         U32 mIndex;
         
         TestItem( U32 index )
            : mIndex( index ) {}
      
      protected:
         virtual void execute()
         {
            results[ mIndex ] = mIndex;
         }
   };
   
   void run()
   {
      U32 numItems = Con::getIntVariable( "$testThreadPool::numValues", DEFAULT_NUM_ITEMS );
      ThreadPool* pool = &ThreadPool::GLOBAL();
      results.setSize( numItems );

      for( U32 i = 0; i < numItems; ++ i )
         results[ i ] = U32( -1 );
      
      for( U32 i = 0; i < numItems; ++ i )
      {
         ThreadSafeRef< TestItem > item( new TestItem( i ) );
         pool->queueWorkItem( item );
      }
      
      pool->flushWorkItems();
      
      for( U32 i = 0; i < numItems; ++ i )
         test( results[ i ] == i, "result mismatch" );
         
      results.clear();
   }
};

Vector< U32 > TestThreadPool::results( __FILE__, __LINE__ );

#endif // !TORQUE_SHIPPING
