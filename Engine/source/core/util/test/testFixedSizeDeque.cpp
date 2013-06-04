// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "core/util/tFixedSizeDeque.h"


using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )

CreateUnitTest( TestFixedSizeDeque, "Util/FixedSizeDeque" )
{
   void run()
   {
      enum { DEQUE_SIZE = 3 };
      FixedSizeDeque< U32 > deque( DEQUE_SIZE );

      TEST( deque.capacity() == DEQUE_SIZE );
      TEST( deque.size() == 0 );

      deque.pushFront( 1 );
      TEST( deque.capacity() == ( DEQUE_SIZE - 1 ) );
      TEST( deque.size() == 1 );
      TEST( !deque.isEmpty() );

      deque.pushBack( 2 );
      TEST( deque.capacity() == ( DEQUE_SIZE - 2 ) );
      TEST( deque.size() == 2 );

      TEST( deque.popFront() == 1 );
      TEST( deque.popFront() == 2 );
      TEST( deque.isEmpty() );
   }
};
