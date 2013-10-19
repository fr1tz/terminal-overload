// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HEXAGONVOLUME_H_
#define _HEXAGONVOLUME_H_

#ifndef _CONCRETEPOLYLIST_H_
#include "collision/concretePolyList.h"
#endif
#ifndef _CONVEX_H_
#include "collision/convex.h"
#endif
#ifndef _MBOX_H_
#include "math/mBox.h"
#endif
#ifndef _SHAPEBASE_H_
#include "T3D/shapeBase.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef _TSSHAPECACHE_H_
#include "Alux3d/tsShapeCache.h"
#endif
#ifndef _HEXAGONVOLUMECOLLISIONSHAPE_H_
#include "hexagonVolumeCollisionShape.h"
#endif

class Grid;

//--------------------------------------------------------------------------

class HexagonVolumeData : public GameBaseData
{
	typedef GameBaseData Parent;

  public:
	enum {
		MaxShapes = 4
	};

   StringTableEntry renderShapeName[MaxShapes];
   Resource<TSShape> renderShape[MaxShapes]; 
	TSShapeInstance* renderShapeInstance[MaxShapes];
	StaticShapeData* collisionShapeData[MaxShapes];
	S32 collisionShapeDataID[MaxShapes];

	S32 mode;
	U32 objectMask;

	HexagonVolumeData();
   
	DECLARE_CONOBJECT(HexagonVolumeData);

	bool onAdd();
	bool preload(bool server, String &errorStr);
	static void initPersistFields();
	virtual void packData  (BitStream* stream);
	virtual void unpackData(BitStream* stream);
};

//--------------------------------------------------------------------------

class HexagonVolumeHexConvex : public Convex
{
   friend class HexagonVolume;

   typedef Convex Parent;

	HexagonVolume* pHexagonVolume;
   U32 hullId;
   U32 idx;

 public:
   HexagonVolumeHexConvex() { mType = HexagonVolumeHexConvexType; }

   Point3F support(const VectorF& v) const;
   void getFeatures(const MatrixF& mat,const VectorF& n, ConvexFeature* cf);
   void getPolyList(AbstractPolyList* list);
};

//--------------------------------------------------------------------------

class HexagonVolume : public GameBase
{
	friend class HexagonVolumeHexConvex;

	typedef GameBase Parent;

	static bool smRenderBounds;
	static U32 smBaseObjectMask;

	struct HexMap
	{
		struct Hex
		{
			Point3I serverGridPos; // Not networked
			U32 shapeNr;
			U32 elevation;
			U32 amount;
			Vector<HexagonVolumeCollisionShape*> col;
		};

		Point3I originGridPos;
		S32 width;
		S32 height;
		Hex* hexArray;

		Point3I indexToGrid(U32 idx) {
			Point3I mapPos;
			mapPos.y = idx / this->width;
			mapPos.x = idx - (mapPos.y*this->width);
			mapPos.z = this->hexArray[idx].elevation;
			Point3I gridPos;
			gridPos.x = this->originGridPos.x + mapPos.x;
			gridPos.y = this->originGridPos.y + mapPos.y;
			gridPos.z = this->originGridPos.z + mapPos.z;
			return gridPos;
		};

		S32 gridToIndex(Point3I gridPos) {
			Point2I mapPos;
			mapPos.x = gridPos.x - this->originGridPos.x;
			mapPos.y = gridPos.y - this->originGridPos.y;
			U32 idx = (mapPos.y*this->width) + mapPos.x;
			return idx;
		};
	};
	
	struct RebuildProcess
	{
		enum State
		{
			Ready,
			Start,
			CollisionStart,
			CollisionProcess,
			CollisionFinish,
			RenderStart,
			RenderProcess,
			RenderFinish
		} state;
		bool useCachedShape;
		TSShape* shape;
		TSMesh* mesh;
		U32 idx;
		U32 x;
	};

	enum HexagonVolumeUpdateBits
	{
		TransformMask = Parent::NextFreeMask << 0,
		InitMask      = Parent::NextFreeMask << 1,
		RebuildMask   = Parent::NextFreeMask << 2,
		NextFreeMask  = Parent::NextFreeMask << 3
	};

	HexagonVolumeData* mDataBlock;

	Grid* mGrid;
	HexMap mHexMap;

	RebuildProcess mRebuild;
	bool mClientStartRebuild;

	U32 mServerShapeId;
	U32 mServerShapeRevision;

	TSShapeInstance* mShapeInstance;
	ConcretePolyList mPolyList;
	HexagonVolumeHexConvex mConvex;

  public:
	HexagonVolume();
	~HexagonVolume();

	// SimObject
	DECLARE_CONOBJECT(HexagonVolume);
	static void consoleInit();
	static void initPersistFields();
	bool onAdd();
	void onRemove();
	void onDeleteNotify(SimObject*);
	void inspectPostApply();

	// NetObject
	void onServerObjectDeleted();
	U32  packUpdate(NetConnection* conn, U32 mask, BitStream* stream);
	void unpackUpdate(NetConnection *conn, BitStream* stream);

	// SceneObject
	void setTransform(const MatrixF &mat);
	void prepRenderImage(SceneRenderState* state);
   bool buildPolyList(PolyListContext context, AbstractPolyList* polyList, const Box3F &box, const SphereF& sphere);
   void buildConvex(const Box3F& box, Convex* convex);
   bool castRay(const Point3F &start, const Point3F &end, RayInfo* info);
   bool castRayRendered(const Point3F &start, const Point3F &end, RayInfo* info);
	
	// GameBase
	bool onNewDataBlock(GameBaseData* dptr, bool reload);
	void processTick(const Move *move);

	// HexagonVolume
 private:
	void initHexMap(const Point3I& originGridPos, S32 width, S32 height);
	void freeHexMap();
	bool startRebuild();
	void rebuildMode2Start();
	void rebuildMode2CollisionStart();
	void rebuildMode2CollisionProcess();
	void rebuildMode2CollisionFinish();
	void rebuildMode2RenderStart();
	void rebuildMode2RenderProcess();
	void rebuildMode2RenderFinish();
	void rebuildMode2Done();
	void rebuildMode2MoveMeshVerts(TSMesh* mesh, Point3F vec);
	void rebuildMode2MergeMesh(TSMesh* dest, TSMesh* src);
	void rebuildMode3();
	void prepRenderImageMode0(SceneRenderState* state);
	void prepRenderImageMode1(SceneRenderState* state);
	void prepRenderImageMode2(SceneRenderState* state);
	void prepRenderImageMode3(SceneRenderState* state);
 public:
	void renderObjectBounds(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);
	void renderObjectConvex(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);
	void renderObjectPolyList(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);
	// Script interface...
	bool sInit();
	S32  sGetHexagonAmount(Point2I gridPos2D);
	S32  sGetHexagonElevation(Point2I gridPos2D);
	S32  sGetHexagonShapeNr(Point2I gridPos2D);
	bool sSetHexagon(Point3I gridPos, U32 shapeNr, U32 amount);
	bool sAddHexagon(Point3I gridPos, U32 shapeNr);
	bool sRemoveHexagon(Point3I gridPos);
	bool sRebuild();
};

#endif // _HEXAGONVOLUME_H_