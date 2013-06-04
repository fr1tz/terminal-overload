// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "math/mPolyhedron.h"


#ifndef TORQUE_SHIPPING

using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )
#define XTEST( t, x ) t->test( ( x ), "FAIL: " #x )


CreateUnitTest( TestMathPolyhedronBuildFromPlanes, "Math/Polyhedron/BuildFromPlanes" )
{
   void test_unitCube()
   {
      Vector< PlaneF > planes;

      // Build planes for a unit cube centered at the origin.
      // Note that the normals must be facing inwards.

      planes.push_back( PlaneF( Point3F( -0.5f, 0.f, 0.f ), Point3F( 1.f, 0.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.5f, 0.f, 0.f ), Point3F( -1.f, 0.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, -0.5f, 0.f ), Point3F( 0.f, 1.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.5f, 0.f ), Point3F( 0.f, -1.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.f, -0.5f ), Point3F( 0.f, 0.f, 1.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.f, 0.5f ), Point3F( 0.f, 0.f, -1.f ) ) );

      // Turn it into a polyhedron.

      Polyhedron polyhedron;
      polyhedron.buildFromPlanes(
         PlaneSetF( planes.address(), planes.size() )
      );

      // Check if we got a cube back.

      TEST( polyhedron.getNumPoints() == 8 );
      TEST( polyhedron.getNumPlanes() == 6 );
      TEST( polyhedron.getNumEdges() == 12 );
   }

   void test_extraPlane()
   {
      Vector< PlaneF > planes;

      // Build planes for a unit cube centered at the origin.
      // Note that the normals must be facing inwards.

      planes.push_back( PlaneF( Point3F( -0.5f, 0.f, 0.f ), Point3F( 1.f, 0.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.5f, 0.f, 0.f ), Point3F( -1.f, 0.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, -0.5f, 0.f ), Point3F( 0.f, 1.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.5f, 0.f ), Point3F( 0.f, -1.f, 0.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.f, -0.5f ), Point3F( 0.f, 0.f, 1.f ) ) );
      planes.push_back( PlaneF( Point3F( 0.f, 0.f, 0.5f ), Point3F( 0.f, 0.f, -1.f ) ) );

      // Add extra plane that doesn't contribute a new edge.

      planes.push_back( PlaneF( Point3F( 0.5f, 0.5f, 0.5f ), Point3F( -1.f, -1.f, -1.f ) ) );

      // Turn it into a polyhedron.

      Polyhedron polyhedron;
      polyhedron.buildFromPlanes(
         PlaneSetF( planes.address(), planes.size() )
      );

      // Check if we got a cube back.

      TEST( polyhedron.getNumPoints() == 8 );
      TEST( polyhedron.getNumPlanes() == 6 );
      TEST( polyhedron.getNumEdges() == 12 );
   }

   void run()
   {
      test_unitCube();
      //test_extraPlane();
   }
};

#endif // !TORQUE_SHIPPING
