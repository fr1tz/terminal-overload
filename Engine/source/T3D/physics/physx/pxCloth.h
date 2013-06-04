// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PXCLOTH_H_
#define _PXCLOTH_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _PHYSX_H_
#include "T3D/physics/physx/px.h"
#endif
#ifndef _T3D_PHYSICS_PHYSICSPLUGIN_H_
#include "T3D/physics/physicsPlugin.h"
#endif

class Material;
class BaseMatInstance;
class PxWorld;
class NxScene;
class NxClothMesh;
class NxCloth;


class PxCloth : public GameBase
{
   typedef GameBase Parent;

   enum MaskBits 
   {
      TransformMask  = Parent::NextFreeMask << 0,
      ClothMask      = Parent::NextFreeMask << 1,
      MaterialMask   = Parent::NextFreeMask << 3,
      NextFreeMask   = Parent::NextFreeMask << 4
   };  

public:

   PxCloth();
   virtual ~PxCloth();

   DECLARE_CONOBJECT( PxCloth );      

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();
   virtual void inspectPostApply();
   void onPhysicsReset( PhysicsResetEvent reset );

   // NetObject
   virtual U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   virtual void unpackUpdate( NetConnection *conn, BitStream *stream );

   // SceneObject
   virtual void setTransform( const MatrixF &mat );
   virtual void setScale( const VectorF &scale );
   virtual void prepRenderImage( SceneRenderState *state );

   // GameBase
   virtual bool onNewDataBlock( GameBaseData *dptr, bool reload );
   virtual void processTick( const Move *move );
   virtual void interpolateTick( F32 delta );

protected:

   PxWorld *mWorld;

   NxScene *mScene;

   /// Cooked cloth collision mesh.
   NxClothMesh *mClothMesh;

   /// The cloth actor used 
   NxCloth *mCloth;

   NxMeshData mReceiveBuffers;

   bool mBendingEnabled;
   bool mDampingEnabled;
   bool mTriangleCollisionEnabled;
   bool mSelfCollisionEnabled;

   F32 mDensity;
   F32 mThickness;
   F32 mFriction;
   F32 mBendingStiffness;
   F32 mStretchingStiffness;
   F32 mDampingCoefficient;
   F32 mCollisionResponseCoefficient;
   F32 mAttachmentResponseCoefficient;

   U32 mAttachmentMask;

   static EnumTable mAttachmentFlagTable;

   String mMaterialName;
   SimObjectPtr<Material> mMaterial;
   BaseMatInstance *mMatInst;

   String lookupName;

   /// The output verts from the PhysX simulation.
   GFXVertexPNTT *mVertexRenderBuffer;

   /// The output indices from the PhysX simulation.
   U16 *mIndexRenderBuffer;

   U32 mMaxVertices;
   U32 mMaxIndices;

   /// The number of indices in the cloth which
   /// is updated by the PhysX simulation.
   U32 mNumIndices;

   /// The number of verts in the cloth which
   /// is updated by the PhysX simulation.
   U32 mNumVertices;

   U32 mMeshDirtyFlags;
   bool mIsVBDirty;

   GFXPrimitiveBufferHandle mPrimBuffer;
   GFXVertexBufferHandle<GFXVertexPNTT> mVB;

   Point2I mPatchVerts; 
   Point2F mPatchSize;

   MatrixF mResetXfm;

   void _initMaterial();

   void _releaseMesh();
   void _releaseCloth();

   bool _createClothPatch();

   void _recreateCloth( const MatrixF &transform );

   void _updateClothProperties();

   void _initClothMesh();
   void _initReceiveBuffers();
   void _setupAttachments();

   void _updateStaticCloth();

   void _updateVBIB();
};

#endif // _PXCLOTH_H_