// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_BTCOLLISION_H_
#define _T3D_PHYSICS_BTCOLLISION_H_

#ifndef _T3D_PHYSICS_PHYSICSCOLLISION_H_
#include "T3D/physics/physicsCollision.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class btCollisionShape;
class btCompoundShape;
class btTriangleMesh;


class BtCollision : public PhysicsCollision
{
protected:

   /// The compound if we have more than one collision shape.
   btCompoundShape *mCompound;

   /// The concrete collision shapes.
   Vector<btCollisionShape*> mShapes;

   /// The local transform for the collision shape
   /// or identity if this is a compound.
   MatrixF mLocalXfm;

   /// If we have any triangle mesh collision shapes then
   /// we need to store the mesh data.
   Vector<btTriangleMesh*> mMeshInterfaces;

   /// Helper for adding shapes.
   void _addShape( btCollisionShape *shape, const MatrixF &localXfm );

public:

   BtCollision();
   virtual ~BtCollision();

   /// Return the Bullet collision shape.
   btCollisionShape* getShape();

   // The local transform used to offset the collsion
   // to its correct graphics position.
   const MatrixF& getLocalTransform() const { return mLocalXfm; }

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

#endif // _T3D_PHYSICS_BTCOLLISION_H_