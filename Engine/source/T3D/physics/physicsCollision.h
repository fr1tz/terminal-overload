// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSCOLLISION_H_
#define _T3D_PHYSICS_PHYSICSCOLLISION_H_

#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif

class Point3F;
class MatrixF;
class PlaneF;


/// The shared collision representation for a instance of a 
/// static or dynamic physics body.
///
/// Note that making very big convex primitives can cause bad
/// queries and collisions in some physics providers.
///
/// @see PhysicsBody
///
class PhysicsCollision : public StrongRefBase
{
public:

   /// Add an infinite plane to the collision shape.
   ///
   /// This shape is assumed to be static in some physics
   /// providers and will at times be faked with a large box.
   ///
   virtual void addPlane( const PlaneF &plane ) = 0;

   /// Add a box to the collision shape.
   virtual void addBox( const Point3F &halfWidth,
                        const MatrixF &localXfm ) = 0;

   /// Add a sphere to the collision shape.
   virtual void addSphere( F32 radius,
                           const MatrixF &localXfm ) = 0;

   /// Add a Y axis capsule to the collision shape.
   virtual void addCapsule(   F32 radius,
                              F32 height,
                              const MatrixF &localXfm ) = 0;

   /// Add a point cloud convex hull to the collision shape.
   virtual bool addConvex( const Point3F *points, 
                           U32 count,
                           const MatrixF &localXfm ) = 0;

   /// Add a triangle mesh to the collision shape.
   virtual bool addTriangleMesh( const Point3F *vert,
                                 U32 vertCount,
                                 const U32 *index,
                                 U32 triCount,
                                 const MatrixF &localXfm ) = 0;

   /// Add a heightfield to the collision shape.
   virtual bool addHeightfield(  const U16 *heights,
                                 const bool *holes,
                                 U32 blockSize,
                                 F32 metersPerSample,
                                 const MatrixF &localXfm ) = 0;
};

#endif // _T3D_PHYSICS_PHYSICSCOLLISION_H_