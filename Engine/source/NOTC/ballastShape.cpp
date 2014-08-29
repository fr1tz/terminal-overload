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
#include "NOTC/fx/multiNodeLaserBeam.h"

#include "NOTC/ballastShape.h"

extern void wireCube(F32 size,Point3F pos);

static const U32 sgAllowedDynamicTypes = 0xffffff;

//----------------------------------------------------------------------------

namespace {
   F32 snapFloat(F32 val, F32 snap)
   {
      if(snap == 0.f)
         return(val);

      F32 a = mFmod(val, snap);

      if(mFabs(a) > (snap / 2))
         val < 0.f ? val -= snap : val += snap;

      return(val - a);
   }
}

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

   groundConnectionBeamOne   = NULL;
   groundConnectionBeamOneId = 0;
   groundConnectionBeamQuad   = NULL;
   groundConnectionBeamQuadId = 0;
}

bool BallastShapeData::preload(bool server, String &errorStr)
{
   if(!Parent::preload(server, errorStr))
      return false;

   if(mShape)
   {
      levelSequence = mShape->findSequence("level");
   }

   if(!server)
   {
      if(!groundConnectionBeamOne && groundConnectionBeamOneId != 0)
         if(Sim::findObject(groundConnectionBeamOneId, groundConnectionBeamOne) == false)
            Con::errorf(ConsoleLogEntry::General, "BallastShapeData::preload: Invalid packet, bad datablockId(groundConnectionBeamOne): %d", groundConnectionBeamOneId);
      if(!groundConnectionBeamQuad && groundConnectionBeamQuadId != 0)
         if(Sim::findObject(groundConnectionBeamQuadId, groundConnectionBeamQuad) == false)
            Con::errorf(ConsoleLogEntry::General, "BallastShapeData::preload: Invalid packet, bad datablockId(groundConnectionBeamQuad): %d", groundConnectionBeamQuadId);
   }

	return true;
}

void BallastShapeData::initPersistFields()
{
   addField("noIndividualDamage",   TypeBool, Offset(noIndividualDamage,   BallastShapeData), "Deprecated\n\n @internal");

   addField("groundConnectionBeamOne", TYPEID< MultiNodeLaserBeamData >(), Offset(groundConnectionBeamOne, BallastShapeData),
      "@brief MultiNodeLaserBeam datablock used for straight-down ground connection beam.\n\n");
   addField("groundConnectionBeamQuad", TYPEID< MultiNodeLaserBeamData >(), Offset(groundConnectionBeamQuad, BallastShapeData),
      "@brief MultiNodeLaserBeam datablock used for ground connection beam quad.\n\n");

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

   if(stream->writeFlag(groundConnectionBeamOne != NULL))
      stream->writeRangedU32(groundConnectionBeamOne->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if(stream->writeFlag(groundConnectionBeamQuad != NULL))
      stream->writeRangedU32(groundConnectionBeamQuad->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);

   stream->write(dynamicTypeField);
}

void BallastShapeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   noIndividualDamage = stream->readFlag();

   if(stream->readFlag())
      groundConnectionBeamOneId = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if(stream->readFlag())
      groundConnectionBeamQuadId = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);

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

   mGroundConnectionBeamOne = NULL;
   for(U32 i = 0; i < 4; i++)
      mGroundConnectionBeamQuad[i] = NULL;
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

void BallastShape::onRemove()
{
   scriptOnRemove();
   removeFromScene();

   if(mGroundConnectionBeamOne)
   {
      mGroundConnectionBeamOne->deleteObject();
      mGroundConnectionBeamOne = NULL;
   }

   for(U32 i = 0; i < 4; i++)
   {
      if(mGroundConnectionBeamQuad[i])
      {
         mGroundConnectionBeamQuad[i]->deleteObject();
         mGroundConnectionBeamQuad[i] = NULL;
      }
   }

   Parent::onRemove();
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

      if(mDataBlock->groundConnectionBeamOne)
      {
         if(mGroundConnectionBeamOne != NULL)
            mGroundConnectionBeamOne->deleteObject();
         mGroundConnectionBeamOne = new MultiNodeLaserBeam;
         mGroundConnectionBeamOne->setPalette(this->getPalette());
         mGroundConnectionBeamOne->onNewDataBlock(mDataBlock->groundConnectionBeamOne, false);
         if(!mGroundConnectionBeamOne->registerObject())
         {
            Con::warnf(ConsoleLogEntry::General, "Could not register mGroundConnectionBeamOne for class: %s", mDataBlock->getName());
            delete mGroundConnectionBeamOne;
            mGroundConnectionBeamOne = NULL;
         }
         else
         {
            mGroundConnectionBeamOne->setRender(false);
         }
      }

      if(mDataBlock->groundConnectionBeamQuad)
      {
         for(U32 i = 0; i < 4; i++)
         {
            if(mGroundConnectionBeamQuad[i] != NULL)
               mGroundConnectionBeamQuad[i]->deleteObject();
            mGroundConnectionBeamQuad[i] = new MultiNodeLaserBeam;
            mGroundConnectionBeamQuad[i]->setPalette(this->getPalette());
            mGroundConnectionBeamQuad[i]->onNewDataBlock(mDataBlock->groundConnectionBeamQuad, false);
            if(!mGroundConnectionBeamQuad[i]->registerObject())
            {
               Con::warnf( ConsoleLogEntry::General, "Could not register mGroundConnectionBeamQuad[%i] for class: %s", i, mDataBlock->getName());
               delete mGroundConnectionBeamQuad[i];
               mGroundConnectionBeamQuad[i] = NULL;
            }
            else
            {
               mGroundConnectionBeamQuad[i]->setRender(false);
            }
         }
      }
	}

   scriptOnNewDataBlock();
   return true;
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
   this->updateGroundConnectionBeams();
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

void BallastShape::updateGroundConnectionBeams()
{
   this->disableCollision();
   if(this->isMounted())
      mMount.object->disableCollision();

   this->updateGroundConnectionBeamOne();
   this->updateGroundConnectionBeamQuad();

   this->enableCollision();
   if(this->isMounted())
      mMount.object->enableCollision();
}

void BallastShape::updateGroundConnectionBeamOne()
{

}

void BallastShape::updateGroundConnectionBeamQuad()
{
   Point3F c = this->getRenderPosition();

   F32 gridSize = 4;

   Point3F gp[4];

   gp[0].x = snapFloat(c.x, gridSize);
   gp[0].y = snapFloat(c.y, gridSize);

   if(gp[0].x < c.x)
   {
      if(gp[0].y < c.y)
      {
         gp[1].x = gp[0].x + gridSize;
         gp[1].y = gp[0].y;
         gp[2].x = gp[0].x + gridSize;
         gp[2].y = gp[0].y + gridSize;
         gp[3].x = gp[0].x;
         gp[3].y = gp[0].y + gridSize;
      }
      else
      {
         gp[1].x = gp[0].x + gridSize;
         gp[1].y = gp[0].y;
         gp[2].x = gp[0].x + gridSize;
         gp[2].y = gp[0].y - gridSize;
         gp[3].x = gp[0].x;
         gp[3].y = gp[0].y - gridSize;
      }
   }
   else
   {
      if(gp[0].y < c.y)
      {
         gp[1].x = gp[0].x - gridSize;
         gp[1].y = gp[0].y;
         gp[2].x = gp[0].x - gridSize;
         gp[2].y = gp[0].y + gridSize;
         gp[3].x = gp[0].x;
         gp[3].y = gp[0].y + gridSize;
      }
      else
      {
         gp[1].x = gp[0].x - gridSize;
         gp[1].y = gp[0].y;
         gp[2].x = gp[0].x - gridSize;
         gp[2].y = gp[0].y - gridSize;
         gp[3].x = gp[0].x;
         gp[3].y = gp[0].y - gridSize;
      }
   }

   for(int i = 0; i < 4; i++)
   {
      if(mGroundConnectionBeamQuad[i])
      {
         RayInfo rInfo;
         Point3F start = gp[i]; start.z = mWorldBox.maxExtents.z;
         Point3F end = start; end.z = F32_MIN;
         if(gClientContainer.castRay(start, end, StaticObjectType, &rInfo))
         {
            mGroundConnectionBeamQuad[i]->clearNodes();
            mGroundConnectionBeamQuad[i]->addNode(c);
            mGroundConnectionBeamQuad[i]->addNodes(rInfo.point);
            mGroundConnectionBeamQuad[i]->setRender(true);
         }
         else
         {
            mGroundConnectionBeamQuad[i]->setRender(false);
         }
      }
   }   
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