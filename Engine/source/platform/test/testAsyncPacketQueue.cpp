// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "platform/async/asyncPacketQueue.h"
#include "console/console.h"
#include "core/util/tVector.h"

#ifndef TORQUE_SHIPPING

using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )

CreateUnitTest( TestAsyncPacketQueue, "Platform/AsyncPacketQueue" )
{
   struct Packet
   {
      typedef void Parent;

      StringChar mChar;
      U32 mDuration;
      S32 mWriteIndex;
      U32 mWriteTime;

      Packet() {}
      Packet( StringChar ch, U32 duration )
         : mChar( ch ), mDuration( duration ), mWriteIndex( -2 ), mWriteTime( 0 ) {}
   };

   struct TimeSource
   {
      typedef void Parent;

      U32 mStartTime;

      TimeSource()
         : mStartTime( Platform::getRealMilliseconds() ) {}

      U32 getPosition()
      {
         return ( Platform::getRealMilliseconds() - mStartTime );
      }
   };

   struct Consumer : public IOutputStream< Packet* >
   {
      typedef IOutputStream< Packet* > Parent;

      U32 mIndex;

      Consumer()
         : mIndex( 0 ) {}

      virtual void write( Packet* const* packets, U32 num )
      {
         for( U32 i = 0; i < num; ++ i )
         {
            Packet* p = packets[ i ];

            Con::printf( "%c", p->mChar );

            p->mWriteTime = Platform::getRealMilliseconds();
            p->mWriteIndex = mIndex;
            mIndex ++;
         }
      }
   };

   void test1( bool dropPackets, U32 queueLength )
   {
      F32 factor = Con::getFloatVariable( "$testAsyncPacketQueue::timeFactor", 100.0f );
      String str = Con::getVariable( "$testAsyncPacketQueue::string" );
      if( str.isEmpty() )
         str = "This is a test string";

      Vector< Packet > packets;
      for( U32 i = 0; i < str.size(); ++ i )
         packets.push_back( Packet( str[ i ], U32( Platform::getRandom() * factor ) ) );

      U32 totalTime = 0;
      for( U32 i = 0; i < packets.size(); ++ i )
         totalTime += packets[ i ].mDuration;

      TimeSource timeSource;
      Consumer consumer;
      AsyncPacketQueue< Packet*, TimeSource* > queue( queueLength, &timeSource, &consumer, totalTime, dropPackets );

      U32 index = 0;
      while( !queue.isAtEnd() )
      {
         if( queue.needPacket()
             && index < packets.size() )
         {

            Packet* packet = &packets[ index ];
            index ++;

            queue.submitPacket( packet, packet->mDuration );
         }
      }

      U32 time = timeSource.mStartTime;
      S32 lastIndex = -1;
      for( U32 i = 0; i < packets.size(); ++ i )
      {
         TEST( ( packets[ i ].mWriteIndex == -2 && dropPackets ) // not written = dropped
               || packets[ i ].mWriteIndex == lastIndex + 1 );

         if( packets[ i ].mWriteIndex != -2 )
            lastIndex ++;

         if( queueLength == 1 )
            TEST( packets[ i ].mWriteTime >= time || dropPackets ); // start time okay

         time += packets[ i ].mDuration;
         if( dropPackets )
            TEST( packets[ i ].mWriteTime < time ); // end time okay (if not dropping)
      }
   }

   void run()
   {
      test1( false, 1 );
      test1( true, 1 );

      test1( false, 4 );
      test1( true, 4 );
   }
};

#endif // !TORQUE_SHIPPING
