// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HEXAGONVOLUME_H_
#define _HEXAGONVOLUME_H_

#ifndef _CONCRETEPOLYLIST_H_
#include "collision/concretePolyList.h"
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

class HexagonGrid;

class HexagonVolumeData : public GameBaseData
{
	typedef GameBaseData Parent;

  public:
   StringTableEntry shapeName;
   Resource<TSShape> shape; 
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

class HexagonVolume : public GameBase
{
	typedef GameBase Parent;

	struct Hexagon
	{
		Point3I gridPos;
		U32 shapeNr;
	};

	static bool smRenderBounds;
	static U32 smBaseObjectMask;

	HexagonVolumeData* mDataBlock;

	HexagonGrid* mGrid;

	Vector<Hexagon> mHexagons; // Always empty on client
	struct HexMap
	{
		Point3I originGridPos;
		S32 width;
		S32 height;
		U32* elevation;
		U32* shapeNr;
	} mHexMap;

	TSShape* mServerShape; // Always NULL on client
	U32 mServerShapeId;
	U32 mServerShapeRevision;

	TSShapeInstance* mShapeInstance;
	ConcretePolyList mPolyList;

	bool mClientPerformRebuild;

	enum HexagonVolumeUpdateBits
	{
		TransformMask = Parent::NextFreeMask << 0,
		RebuildMask = Parent::NextFreeMask << 1,
		NextFreeMask  = Parent::NextFreeMask << 2
	};

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
	
	// GameBase
	bool onNewDataBlock(GameBaseData* dptr, bool reload);
	void processTick(const Move *move);

	// HexagonVolume
	void clearHexagons();
	bool addHexagon(Point3I gridPos, U32 shapeNr);
	bool removeHexagon(Point3I gridPos);
	bool rebuild();
	void clearHexMap();
	bool rebuildHexMap();
	bool rebuildMode2();
	void rebuildMode2MoveMeshVerts(TSMesh* mesh, Point3F vec);
	void rebuildMode2MergeMesh(TSMesh* dest, TSMesh* src);
	void rebuildMode3();
	void prepRenderImageMode0(SceneRenderState* state);
	void prepRenderImageMode1(SceneRenderState* state);
	void prepRenderImageMode2(SceneRenderState* state);
	void prepRenderImageMode3(SceneRenderState* state);
	void renderObjectBounds(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);
	void renderObjectMode3(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);
};

#endif // _HEXAGONVOLUME_H_