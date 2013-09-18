// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHAPERENDERVOLUME_H_
#define _SHAPERENDERVOLUME_H_

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

class ShapeRenderVolumeData : public GameBaseData
{
	typedef GameBaseData Parent;

  public:
	S32 mode;
	U32 objectMask;

	ShapeRenderVolumeData();
   
	DECLARE_CONOBJECT(ShapeRenderVolumeData);

	bool onAdd();
	static void initPersistFields();
	virtual void packData  (BitStream* stream);
	virtual void unpackData(BitStream* stream);
};

class ShapeRenderVolume : public GameBase
{
	typedef GameBase Parent;

	static bool smRenderBounds;
	static U32 smBaseObjectMask;

	ShapeRenderVolumeData* mDataBlock;

	bool mGeometryDirty;
	U32 mServerObjectCount; // Transmitted from server
	U32 mGeometryDirtyTicks; // For how many ticks has the
	                         // geometry been dirty?

	TSShape* mShape;
	TSShapeInstance* mShapeInstance;
	Vector<ShapeBase*> mObjects;
	ConcretePolyList mPolyList;

	enum ShapeRenderVolumeUpdateBits
	{
		TransformMask = Parent::NextFreeMask << 0,
		RebuildMask = Parent::NextFreeMask << 1,
		NextFreeMask  = Parent::NextFreeMask << 2
	};

  public:
	ShapeRenderVolume();
	~ShapeRenderVolume();

	// SimObject
	DECLARE_CONOBJECT(ShapeRenderVolume);
	static void consoleInit();
	static void initPersistFields();
	bool onAdd();
	void onRemove();
	void onDeleteNotify(SimObject*);
	void inspectPostApply();

	// NetObject
	U32  packUpdate(NetConnection* conn, U32 mask, BitStream* stream);
	void unpackUpdate(NetConnection *conn, BitStream* stream);

	// SceneObject
	void setTransform(const MatrixF &mat);
	void prepRenderImage(SceneRenderState* state);
	
	// GameBase
	bool onNewDataBlock(GameBaseData* dptr, bool reload);
	void processTick(const Move *move);

	// ShapeRenderVolume
	static void findCallback(SceneObject* obj, void* key);
	bool clientRebuildCheck();
	void rebuild();
	void rebuildMode2();
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

#endif // _SHAPERENDERVOLUME_H_