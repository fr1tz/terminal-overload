// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BLOBSHADOW_H_
#define _BLOBSHADOW_H_

#include "collision/depthSortList.h"
#include "scene/sceneObject.h"
#include "ts/tsShapeInstance.h"
#include "lighting/common/shadowBase.h"

class ShapeBase;
class LightInfo;

class BlobShadow : public ShadowBase
{
   F32 mRadius;
   F32 mInvShadowDistance;
   MatrixF mLightToWorld;
   MatrixF mWorldToLight;

   Vector<DepthSortList::Poly> mPartition;
   Vector<Point3F> mPartitionVerts;
   GFXVertexBufferHandle<GFXVertexPCT> mShadowBuffer;

   static U32 smShadowMask;

   static DepthSortList smDepthSortList;
   static GFXTexHandle smGenericShadowTexture;
   static F32 smGenericRadiusSkew;
   static S32 smGenericShadowDim;

   U32 mLastRenderTime;

   static void collisionCallback(SceneObject*,void *);

private:
   SceneObject* mParentObject;
   ShapeBase* mShapeBase;
   LightInfo* mParentLight;
   TSShapeInstance* mShapeInstance;
   GFXStateBlockRef mShadowSB;
   F32 mDepthBias;

   void setupStateBlocks();
   void setLightMatrices(const Point3F & lightDir, const Point3F & pos);
   void buildPartition(const Point3F & p, const Point3F & lightDir, F32 radius, F32 shadowLen);
public:

   BlobShadow(SceneObject* parentobject, LightInfo* light, TSShapeInstance* shapeinstance);
   ~BlobShadow();

   void setRadius(F32 radius);
   void setRadius(TSShapeInstance *, const Point3F & scale);

   bool prepare(const Point3F & pos, Point3F lightDir, F32 shadowLen);

   bool shouldRender(F32 camDist);

   void update( const SceneRenderState *state ) {}
   void render( F32 camDist, const TSRenderState &rdata );
   U32 getLastRenderTime() const { return mLastRenderTime; }

   static void generateGenericShadowBitmap(S32 dim);
   static void deleteGenericShadowBitmap();
};

#endif