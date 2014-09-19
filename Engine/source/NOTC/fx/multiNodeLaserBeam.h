// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MULTINODELASERBEAM_H_
#define _MULTINODELASERBEAM_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

class MultiNodeLaserBeamData : public GameBaseData
{
   typedef GameBaseData Parent;

  public:
   enum Constants {
      NumLanes = 3
   };

	enum RenderMode {
		FaceViewer,
		Horizontal,
		Vertical
	};

	enum NodeMoveMode {
		None,
		ConstantSpeed,
		DynamicSpeed
	};

   String materialString[NumLanes];
   BaseMatInstance*  materialInst[NumLanes];
   F32 width[NumLanes];

	S32	renderMode;

	F32 windCoefficient;

	S32 nodeMoveMode[3];
	F32 nodeMoveSpeed[3];
	F32 nodeMoveSpeedAdd[3];

	F32 nodeDistance;

	S32 fadeTime; // in MS

  public:
   MultiNodeLaserBeamData();
   ~MultiNodeLaserBeamData();

   static void initPersistFields();
	static void consoleInit();
   bool onAdd();
   void packData(BitStream*);
   void unpackData(BitStream*);
   bool preload(bool server, String &errorStr);

   DECLARE_CONOBJECT(MultiNodeLaserBeamData);
};

class MultiNodeLaserBeam : public GameBase
{
   typedef GameBase Parent;

 public:
   typedef GFXVertexPCT VertexType;

  private:
   MultiNodeLaserBeamData* mDataBlock;

   // rendering...
   bool    mRender;
   bool    mFade;
   int     mFadeMode;

	struct LaserBeamNode
	{
		Point3F pos;
		Point3F vel;
		F32     alpha;
	};

	Vector<LaserBeamNode> mNodes;

	U32 mCurrTick;
	bool mDeleteOnFadeout;

	// rendering-calculations...
	U32		mLastCalcTime;
	Point3F	mCrossVec;

   struct RenderData {
      GFXVertexBufferHandle<VertexType> vertBuf;
      GFXPrimitiveBufferHandle primBuf;
      U32 numVerts;
      U32 numPrims;
      GFXPrimitiveType primType;
   };

   RenderData mRenderData[MultiNodeLaserBeamData::NumLanes]; 

  public:
   MultiNodeLaserBeam();
   ~MultiNodeLaserBeam();

   // ConsoleObject...
   static void initPersistFields();
   static void consoleInit();

   // SimObject...
   bool onAdd();
   void onRemove();
 
   // SceneObject...
   void prepRenderImage(SceneRenderState *state);

   // GameBase...
   void processTick(const Move*);
   void interpolateTick(F32);
   void advanceTime(F32);
   bool onNewDataBlock(GameBaseData* dptr, bool reload);

   // MultiNodeLaserBeam...
   void updateRenderData(const Point3F& camPos, U32 lane);
   void setRender(bool b);
   void clearNodes();
	void addNode(Point3F pos);
	bool addNodes(Point3F endpos);
	void setFirstNodePos(Point3F pos);
	Point3F getFirstNodePos();
	void setLastNodePos(Point3F pos);
	Point3F getLastNodePos();
	bool deleteLastNode();
   void fade();
	void deleteOnFadeout() { mDeleteOnFadeout = true; };
	void smooth();
	void smoothDist(F32 dist);
	void smoothReverse();
	void smoothReverseDist(F32 dist);
   void setFadeout(F32 alpha);

   DECLARE_CONOBJECT(MultiNodeLaserBeam);
};

#endif // _MULTINODELASERBEAM_H_
