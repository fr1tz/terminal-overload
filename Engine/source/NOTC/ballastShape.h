// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BALLASTSHAPE_H_
#define _BALLASTSHAPE_H_

#ifndef _SHAPEBASE_H_
#include "T3D/shapeBase.h"
#endif

class MultiNodeLaserBeamData;
class MultiNodeLaserBeam;

//----------------------------------------------------------------------------

struct BallastShapeData: public ShapeBaseData {
   typedef ShapeBaseData Parent;

  public:
   BallastShapeData();

   bool  noIndividualDamage;
   S32   dynamicTypeField;
   S32   levelEnergySlot;

   S32 levelSequence;

   MultiNodeLaserBeamData* groundConnectionBeamOne;
   S32                     groundConnectionBeamOneId;
   MultiNodeLaserBeamData* ceilingConnectionBeamOne;
   S32                     ceilingConnectionBeamOneId;
   MultiNodeLaserBeamData* groundConnectionBeamQuad;
   S32                     groundConnectionBeamQuadId;

   //
   DECLARE_CONOBJECT(BallastShapeData);
   bool preload(bool server, String &errorStr);
   static void initPersistFields();
   virtual void packData(BitStream* stream);
   virtual void unpackData(BitStream* stream);
};


//----------------------------------------------------------------------------

class BallastShape: public ShapeBase
{
   typedef ShapeBase Parent;

   BallastShapeData*  mDataBlock;
   bool              mPowered;

   TSThread* mLevelThread;

	F32 mLevel;

   MultiNodeLaserBeam* mGroundConnectionBeamOne;
   MultiNodeLaserBeam* mCeilingConnectionBeamOne;
   MultiNodeLaserBeam* mGroundConnectionBeamQuad[4];

   void onUnmount(ShapeBase* obj,S32 node);

protected:
   enum MaskBits {
      PositionMask = Parent::NextFreeMask,	  
		LevelMask    = Parent::NextFreeMask << 1,
      NextFreeMask = Parent::NextFreeMask << 2
   };

   void updateBeams();
   void updateGroundConnectionBeamOne();
   void updateCeilingConnectionBeamOne();
   void updateGroundConnectionBeamQuad();

public:
   DECLARE_CONOBJECT(BallastShape);

   BallastShape();
   ~BallastShape();

   bool onAdd();
   void onRemove();
   bool onNewDataBlock(GameBaseData *dptr, bool reload);

   void setFlickerTime(U32 time);

   void processTick(const Move *move);
   void interpolateTick(F32 delta);
   void setTransform(const MatrixF &mat);

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);

	// Level
	void setLevel(F32 amount);
	F32  getLevel() { return mLevel; }

   // power
   void setPowered(bool power)      {mPowered = power;}
   bool isPowered()                 {return(mPowered);}

   static void initPersistFields();   
};


#endif
