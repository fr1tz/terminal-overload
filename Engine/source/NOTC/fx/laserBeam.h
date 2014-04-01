// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#ifndef _LASERBEAM_H_
#define _LASERBEAM_H_

#ifndef _GAMEBASE_H_
#include "game/gameBase.h"
#endif

//-----
//
// LaserBeamData
//
//-----
class LaserBeamData : public GameBaseData
{
   typedef GameBaseData Parent;

  public:
   bool hasLine;
   ColorF lineStartColor;
   ColorF lineBetweenColor;
   ColorF lineEndColor;
	F32 lineWidth;

   bool hasInner;
   ColorF innerStartColor;
   ColorF innerBetweenColor;
   ColorF innerEndColor;
   F32    innerStartWidth;
   F32    innerBetweenWidth;
   F32    innerEndWidth;

   bool hasOuter;
   ColorF outerStartColor;
   ColorF outerBetweenColor;
   ColorF outerEndColor;
   F32    outerStartWidth;
   F32    outerBetweenWidth;
   F32    outerEndWidth;

   StringTableEntry	bitmap;
   StringTableEntry	crossBitmap;
   F32    bitmapWidth;
	F32    crossBitmapWidth;

   F32    betweenFactor;

   S32    blendMode;

   TextureHandle textureHandle;
   TextureHandle crossTextureHandle;

   // special flags, if set, all other options are ignored... -mg
   bool superMagicMonkeySpecialEffect;

  public:
   LaserBeamData();
   ~LaserBeamData();

   static void initPersistFields();
   bool onAdd();
   void packData(BitStream*);
   void unpackData(BitStream*);
   bool preload(bool server, char errorBuffer[256]);

   DECLARE_CONOBJECT(LaserBeamData);
};
DECLARE_CONSOLETYPE(LaserBeamData)

//-----
//
// LaserBeam
//
//-----
class LaserBeam : public GameBase
{
   typedef GameBase Parent;

  private:
   LaserBeamData* mDataBlock;

   // position...
   Point3F mStart;
   Point3F mBetween;
   Point3F mEnd;

   Point3F mSource;
   Point3F mVelocity;
   F32     mLength;

   // rendering...
   bool    mRender;
   bool    mFade;
   bool    mClip;
   PlaneF  mClipPlane;
   ColorF  mColor;

	// rendering-calculations...
	U32		mLastCalcTime;
	Point3F	mCrossVec;
	bool		mRenderCross;
	Point3F	mRenderCrossX,mRenderCrossY;

   // fading...
   F32     mOpacity; // when fading, store opacity of beam -mg
   U32     mFadeTime; // in ticks -mg

   void set_gl_color(const ColorF& color);

  public:
   LaserBeam();
   ~LaserBeam();

   // ConsoleObject...
   static void initPersistFields();
   static void consoleInit();

   // SimObject...
   bool onAdd();
   void onRemove();
 
   // SceneObject...
   bool prepRenderImage(SceneState*, const U32, const U32, const bool);
   void renderObject(SceneState*, SceneRenderImage*);

   // GameBase...
   void processTick(const Move*);
   void interpolateTick(F32);
   void advanceTime(F32);
   bool onNewDataBlock(GameBaseData* dptr);

   // LaserBeam...
   void setRender(bool _b);
   void update(Point3F _from, Point3F _to);
   void fadeAndDelete(U32 _fadeTime);
   void render( const Point3F* camPos );
   void setColor( const ColorF& color );
   void makeDisappear(const Point3F& src,
	   const Point3F& pos, const Point3F& vel, F32 len);

   DECLARE_CONOBJECT(LaserBeam);
};

//------
//
// MultiNodeLaserBeamData
//
//------
class MultiNodeLaserBeamData : public GameBaseData
{
   typedef GameBaseData Parent;

  public:
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

	bool	hasLine;
	ColorF lineColor;
	F32 lineWidth;

	bool hasInner;
	ColorF innerColor;
	F32    innerWidth;

	bool hasOuter;
	ColorF outerColor;
	F32    outerWidth;

	StringTableEntry bitmap;
	F32   bitmapWidth;

	S32   blendMode;

	S32	renderMode;

	F32 windCoefficient;

	S32 nodeMoveMode[3];
	F32 nodeMoveSpeed[3];
	F32 nodeMoveSpeedAdd[3];

	F32 nodeDistance;

	S32	fadeTime; // in MS

	TextureHandle textureHandle;

  public:
   MultiNodeLaserBeamData();
   ~MultiNodeLaserBeamData();

   static void initPersistFields();
	static void consoleInit();
   bool onAdd();
   void packData(BitStream*);
   void unpackData(BitStream*);
   bool preload(bool server, char errorBuffer[256]);

   DECLARE_CONOBJECT(MultiNodeLaserBeamData);
};
DECLARE_CONSOLETYPE(MultiNodeLaserBeamData)

//------
//
// MultiNodeLaserBeam
//
//------

class MultiNodeLaserBeam : public GameBase
{
   typedef GameBase Parent;

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
   bool prepRenderImage(SceneState*, const U32, const U32, const bool);
   void renderObject(SceneState*, SceneRenderImage*);

   // GameBase...
   void processTick(const Move*);
   void interpolateTick(F32);
   void advanceTime(F32);
   bool onNewDataBlock(GameBaseData* dptr);

   // MultiNodeLaserBeam...
   void setRender(bool b);
	void addNode(Point3F pos);
	bool addNodes(Point3F endpos);
	void setLastNodePos(Point3F pos);
	Point3F getLastNodePos();
	bool deleteLastNode();
   void fade();
   void render( const Point3F* camPos );
	void deleteOnFadeout() { mDeleteOnFadeout = true; };
	void smooth();
	void smoothDist(F32 dist);
	void smoothReverse();
	void smoothReverseDist(F32 dist);

   DECLARE_CONOBJECT(MultiNodeLaserBeam);
};


#endif // _LASERBEAM_H_

#endif // BORQUE_NEEDS_PORTING

