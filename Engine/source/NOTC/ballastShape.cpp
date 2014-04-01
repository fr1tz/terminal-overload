// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/engineAPI.h"
#include "core/dnet.h"
#include "core/stream/bitStream.h"
#include "app/game.h"
#include "math/mMath.h"
#include "console/simBase.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "T3D/gameBase/moveManager.h"
#include "ts/tsShapeInstance.h"
#include "math/mathIO.h"
#include "sim/netConnection.h"
#include "scene/sceneObjectLightingPlugin.h"

#include "NOTC/ballastShape.h"

extern void wireCube(F32 size,Point3F pos);

static const U32 sgAllowedDynamicTypes = 0xffffff;

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(BallastShapeData);

ConsoleDocClass( BallastShapeData,
	"@brief TODO.\n\n"

	"@ingroup gameObjects\n"
	"@ingroup Datablocks"
);

BallastShapeData::BallastShapeData()
{
   dynamicTypeField     = 0;

   shadowEnable = true;

   noIndividualDamage = false;
}

bool BallastShapeData::preload(bool server, String &errorStr)
{
   if(!Parent::preload(server, errorStr))
      return false;

   if(mShape)
   {
      levelSequence = mShape->findSequence("level");
   }

	return true;
}

void BallastShapeData::initPersistFields()
{
   addField("noIndividualDamage",   TypeBool, Offset(noIndividualDamage,   BallastShapeData), "Deprecated\n\n @internal");
   addField("dynamicType",          TypeS32,  Offset(dynamicTypeField,     BallastShapeData), 
      "@brief An integer value which, if speficied, is added to the value retured by getType().\n\n"
      "This allows you to extend the type mask for a BallastShape that uses this datablock.  Type masks "
      "are used for container queries, etc.");

   Parent::initPersistFields();
}

void BallastShapeData::packData(BitStream* stream)
{
   Parent::packData(stream);
   stream->writeFlag(noIndividualDamage);
   stream->write(dynamicTypeField);
}

void BallastShapeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   noIndividualDamage = stream->readFlag();
   stream->read(&dynamicTypeField);
}


//----------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(BallastShape);

ConsoleDocClass( BallastShape,
	"@brief TODO.\n\n"

	"@ingroup gameObjects\n"
	"@ingroup Datablocks"
);

BallastShape::BallastShape()
{
   //mTypeMask |= BallastShapeObjectType | StaticObjectType;
   mDataBlock = 0;
	mLevel = 0.0;
	mLevelThread = 0;
}

BallastShape::~BallastShape()
{
}


//----------------------------------------------------------------------------

void BallastShape::initPersistFields()
{
   Parent::initPersistFields();
}

bool BallastShape::onAdd()
{
   if(!Parent::onAdd() || !mDataBlock)
      return false;

   // We need to modify our type mask based on what our datablock says...
   mTypeMask |= (mDataBlock->dynamicTypeField & sgAllowedDynamicTypes);

   addToScene();

   if (isServerObject())
      scriptOnAdd();
   return true;
}

bool BallastShape::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<BallastShapeData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   // Mass thread is only needed on client.
   mLevelThread = 0;
   if(this->isGhost())
   {
      if(mDataBlock->levelSequence != -1)
      {
         mLevelThread = mShapeInstance->addThread();
         mShapeInstance->setSequence(mLevelThread, mDataBlock->levelSequence, 0);
      }
	}

   scriptOnNewDataBlock();
   return true;
}

void BallastShape::onRemove()
{
   scriptOnRemove();
   removeFromScene();
   Parent::onRemove();
}


//----------------------------------------------------------------------------

void BallastShape::processTick(const Move* move)
{
   Parent::processTick(move);

   // Image Triggers
   if (move && mDamageState == Enabled) {
      setImageTriggerState(0,move->trigger[0]);
      setImageTriggerState(1,move->trigger[1]);
   }

   if (isMounted()) {
      MatrixF mat;
      mMount.object->getMountTransform( mMount.node, mMount.xfm, &mat );
      Parent::setTransform(mat);
      Parent::setRenderTransform(mat);
   }
}

void BallastShape::interpolateTick(F32 delta)
{
   if (isMounted()) {
      MatrixF mat;
      mMount.object->getRenderMountTransform( delta, mMount.node, mMount.xfm, &mat );
      Parent::setRenderTransform(mat);
   }
}

void BallastShape::setTransform(const MatrixF& mat)
{
   Parent::setTransform(mat);
   setMaskBits(PositionMask);
}

void BallastShape::onUnmount(ShapeBase*,S32)
{
   // Make sure the client get's the final server pos.
   setMaskBits(PositionMask);
}


//----------------------------------------------------------------------------

U32 BallastShape::packUpdate(NetConnection *connection, U32 mask, BitStream *bstream)
{
   U32 retMask = Parent::packUpdate(connection,mask,bstream);
   if (bstream->writeFlag(mask & PositionMask | ExtendedInfoMask))
   {

      // Write the transform (do _not_ use writeAffineTransform.  Since this is a static
      //  object, the transform must be RIGHT THE *&)*$&^ ON or it will goof up the
      //  synchronization between the client and the server.
      mathWrite(*bstream,mObjToWorld);
      mathWrite(*bstream, mObjScale);
   }

   // powered?
   bstream->writeFlag(mPowered);

   if(bstream->writeFlag(mask & LevelMask))
   {
		bstream->write(mLevel);
	}

   if (mLightPlugin) 
   {
      retMask |= mLightPlugin->packUpdate(this, ExtendedInfoMask, connection, mask, bstream);
   }

   return retMask;
}

void BallastShape::unpackUpdate(NetConnection *connection, BitStream *bstream)
{
   Parent::unpackUpdate(connection,bstream);
   if (bstream->readFlag())
   {
      MatrixF mat;
      mathRead(*bstream,&mat);
      Parent::setTransform(mat);
      Parent::setRenderTransform(mat);

      VectorF scale;
      mathRead(*bstream, &scale);
      setScale(scale);
   }

   // powered?
   mPowered = bstream->readFlag();

	// Level
	if(bstream->readFlag())
	{
		F32 level;
		bstream->read(&level);
		this->setLevel(level);
	}

   if (mLightPlugin)
   {
      mLightPlugin->unpackUpdate(this, connection, bstream);
   }
}

//----------------------------------------------------------------------------

void BallastShape::setLevel(F32 amount)
{
	mLevel = amount;
	mMass = mDataBlock->mass * mLevel;
	setMaskBits(LevelMask);
	if(mLevelThread)
	{
		mShapeInstance->setPos(mLevelThread, 1-mLevel);
		mShapeInstance->animate();
	}
}

//----------------------------------------------------------------------------



DefineEngineMethod( BallastShape, setLevel, void, ( F32 amount ),,
   "@brief Set level of ballast.\n\n"
   "@param amount Level amount (0.0-0.1)\n\n" )
{
   object->setLevel(amount);
}

DefineEngineMethod( BallastShape, getLevel, F32, ( void ),,
	"@brief Returns current level of ballast (0.0-1.0).\n\n")
{
   return object->getLevel();
}