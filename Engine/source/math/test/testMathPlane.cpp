// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "math/mPlane.h"
#include "math/mRandom.h"


#ifndef TORQUE_SHIPPING

using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )
#define XTEST( t, x ) t->test( ( x ), "FAIL: " #x )

CreateUnitTest( TestMathPlane, "Math/Plane" )
{
   static F32 randF()
   {
      return gRandGen.randF( -1.f, 1.f );
   }

   void test_whichSide()
   {
      for( U32 i = 0; i < 100; ++ i )
      {
         Point3F position( randF(), randF(), randF() );
         Point3F normal( randF(), randF(), randF() );

         PlaneF p1( position, normal );

         TEST( p1.whichSide( position + normal ) == PlaneF::Front );
         TEST( p1.whichSide( position + ( - normal ) ) == PlaneF::Back );
         TEST( p1.whichSide( position ) == PlaneF::On );
      }
   }

   void test_distToPlane()
   {
      for( U32 i = 0; i < 100; ++ i )
      {
         Point3F position( randF(), randF(), randF() );
         Point3F normal( randF(), randF(), randF() );

         PlaneF p1( position, normal );

         TEST( mIsEqual( p1.distToPlane( position + normal ), normal.len() ) );
         TEST( mIsEqual( p1.distToPlane( position + ( - normal ) ), - normal.len() ) );
         TEST( mIsZero( p1.distToPlane( position ) ) );
      }
   }

   void run()
   {
      test_whichSide();
      test_distToPlane();
   }
};

#endif // !TORQUE_SHIPPING
