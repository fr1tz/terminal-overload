// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PXCOLLISION_H_
#define _T3D_PHYSICS_PXCOLLISION_H_

#ifndef _T3D_PHYSICS_PHYSICSCOLLISION_H_
#include "T3D/physics/physicsCollision.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class NxShapeDesc;


class PxCollision : public PhysicsCollision
{
protected:

   /// The collision representation.
   Vector<NxShapeDesc*> mColShapes;

   /// Helper for adding shapes.
   //void _addShape( btCollisionShape *shape, const MatrixF &localXfm );

public:

   PxCollision();
   virtual ~PxCollision();

   /// Return the PhysX shape descriptions.
   const Vector<NxShapeDesc*>& getShapes() const { return mColShapes; }

   // PhysicsCollision
   virtual void addPlane( const PlaneF &plane );
   virtual void addBox( const Point3F &halfWidth,
                        const MatrixF &localXfm );
   virtual void addSphere( F32 radius,
                           const MatrixF &localXfm );
   virtual void addCapsule(   F32 radius,
                              F32 height,
                              const MatrixF &localXfm );
   virtual bool addConvex( const Point3F *points, 
                           U32 count,
                           const MatrixF &localXfm );
   virtual bool addTriangleMesh( const Point3F *vert,
                                 U32 vertCount,
                                 const U32 *index,
                                 U32 triCount,
                                 const MatrixF &localXfm );
   virtual bool addHeightfield(  const U16 *heights,
                                 const bool *holes,
                                 U32 blockSize,
                                 F32 metersPerSample,
                                 const MatrixF &localXfm );
};

#endif // _T3D_PHYSICS_PXCOLLISION_H_