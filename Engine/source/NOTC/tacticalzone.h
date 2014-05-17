// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TACTICALZONE_H_
#define _TACTICALZONE_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _MBOX_H_
#include "math/mBox.h"
#endif
#ifndef _EARLYOUTPOLYLIST_H_
#include "collision/earlyOutPolyList.h"
#endif
#ifndef _CLIPPEDPOLYLIST_H_
#include "collision/clippedPolyList.h"
#endif
#ifndef _TEXTUREDPOLYLIST_H_
#include "collision/texturedPolyList.h"
#endif
#ifndef _H_TRIGGER
#include "T3D/trigger.h"
#endif

class Convex;

#if 0
class TacticalZoneFaceRenderImage : public SceneRenderImage
{
  public:
   U32 face;
};
#endif

class TacticalZoneData: public GameBaseData
{
   typedef GameBaseData Parent;

  public:	
	enum { 
		MaxColors = 16,
		MaxColorsBits = 4
	};

	S32 tickPeriodMS;
	S32 colorChangeTimeMS;

	ColorF colors[MaxColors];

	StringTableEntry texture;
	StringTableEntry borderTexture;

   TacticalZoneData();
   DECLARE_CONOBJECT(TacticalZoneData);
   bool onAdd();
   static void initPersistFields();
   virtual void packData  (BitStream* stream);
   virtual void unpackData(BitStream* stream);
   virtual bool preload(bool server, String &errorStr);
};

class TacticalZone : public GameBase
{
   typedef GameBase Parent;
   TacticalZoneData*      mDataBlock;

	struct Face {
		Point3F center;
		PlaneF  plane;
	};

 public:

	enum RenderMode {
		None,
		BordersOnly,
		Full
	};

	enum UpdateMasks {
		ColorMask        = Parent::NextFreeMask,
		EditorMask       = Parent::NextFreeMask << 1,	
		Color1Mask       = Parent::NextFreeMask << 2,
		Color2Mask       = Parent::NextFreeMask << 3,
		FactorMask       = Parent::NextFreeMask << 4,
		FlashColor1Mask  = Parent::NextFreeMask << 5,
		FlashColor2Mask  = Parent::NextFreeMask << 6,
		FlashFactorMask  = Parent::NextFreeMask << 7,
		FlashMask        = Parent::NextFreeMask << 8,
		NextFreeMask     = Parent::NextFreeMask << 9
	};

 private:
	static S32  sRenderMode;
	static bool sRenderTerrainDebug;

   EarlyOutPolyList  mClippedList;
   Vector<GameBase*> mObjects;

	bool  mIgnoreRayCast;

	U32	mLastThink;
	U32	mCurrTick;

	ColorF mCurrColor;

	U8     mColor1;
	U8     mColor2;
	F32    mFactor;

	U8     mFlashColor1;
	U8     mFlashColor2;
	F32    mFlashFactor;

	F32 mBorderWidth[6];

	//
	// render stuff...
	//

	bool mShowOnMinimap;
	bool mRenderInteriors;
	bool mRenderTerrain;
	bool mRenderTerrainGrid;

	Point3F mCameraPos;
	bool mDebugMode;
	bool mClientComputePolys;
	Point3F mPoints[8]; // in world transform
	Face mFaces[6]; // in world transform
	PlaneF mBorderClippingPlanes[6];
	TexturedPolyList mBorderPolys[6];
	TexturedPolyList mInteriorPolys;
	TexturedPolyList mTerrainPolys; 

	typedef Vector<TexturedPolyList::Vertex> VertexList;

	VertexList mTerrainGridVertexList;
	VertexList mRaisedTerrainGridVertexList;
	VertexList mRenderTerrainGridVertexList;

	Vector<U32> mTerrainGridVertices;
	Vector<U32> mTerrainGridLines;
	Vector<U32> mRenderTerrainGridLines;

	void computePolys();
	void clearGrid();

  protected:
   bool onAdd();
   void onRemove();
   void onDeleteNotify(SimObject*);
   bool onNewDataBlock(GameBaseData* dptr, bool reload);
   void inspectPostApply();
   void onEditorEnable();
   void onEditorDisable();

   bool testObject(GameBase* enter);
   void processTick(const Move *move);
   void advanceTime(F32 dt);

   Convex* mConvexList;
   void buildConvex(const Box3F& box, Convex* convex);

   // Rendering
  protected:
	void updateFogCoords(TexturedPolyList& polyList, const Point3F& camPos);
	void prepRenderImage(SceneRenderState *state);
   void render(ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat);
#if 0
	void renderObject     ( SceneState *state, SceneRenderImage *image);
	void renderDebug(TacticalZoneFaceRenderImage* image);
	void renderInteriorPolyList(TexturedPolyList& polyList);
	void renderBorderPolyList(TexturedPolyList& polyList);
	void renderTerrainPolyList(TexturedPolyList& polyList);
	void renderTerrainGridLines(VertexList& vertexList);	
#endif

  public:
   void setTransform(const MatrixF &mat);

   TacticalZone();
   ~TacticalZone();

	void computeGrid();

	bool showOnMinimap() { return mShowOnMinimap; }
	bool renderInteriors() { return mRenderInteriors; }
	bool renderTerrain() { return mRenderTerrain; }

	void   setColor(U8 color1, U8 color2, F32 f);
	void   flash(U8 color1, U8 color2, F32 f);
	ColorF getZoneColor();
	ColorF getRenderColor();

   void      potentialEnterObject(GameBase*);
   U32       getNumTacticalZoneObjects() const;
   GameBase* getObject(const U32);

	bool castRay(const Point3F& start, const Point3F& end, RayInfo* info);

   DECLARE_CONOBJECT(TacticalZone);
   static void initPersistFields();
   static void consoleInit();

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream* stream);
   void unpackUpdate(NetConnection *conn,           BitStream* stream);

 private:
	static void objectFound(SceneObject* obj, void* key);
};

inline U32 TacticalZone::getNumTacticalZoneObjects() const
{
   return mObjects.size();
}

inline GameBase* TacticalZone::getObject(const U32 index)
{
   AssertFatal(index < getNumTacticalZoneObjects(), "Error, out of range object index");

   return mObjects[index];
}

#endif // _TACTICALZONE_H_
