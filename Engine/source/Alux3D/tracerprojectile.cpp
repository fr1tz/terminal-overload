// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#include "dgl/dgl.h"
#include "sceneGraph/sceneState.h"
#include "sceneGraph/sceneGraph.h"
#include "console/consoleTypes.h"
#include "console/typeValidators.h"
#include "audio/audioDataBlock.h"
#include "core/bitStream.h"
#include "game/fx/explosion.h"
#include "game/shapeBase.h"
#include "game/player.h"
#include "ts/tsShapeInstance.h"
#include "game/tracerprojectile.h"
#include "audio/audio.h"
#include "math/mathUtils.h"
#include "math/mathIO.h"
#include "sim/netConnection.h"
#include "game/fx/particleEngine.h"
#include "game/fx/laserBeam.h"
#include "game/fx/fxLight.h"
#include "game/deflector.h"
#include "game/gameConnection.h"

IMPLEMENT_CO_DATABLOCK_V1(TracerProjectileData);
IMPLEMENT_CO_NETOBJECT_V1(TracerProjectile);

//--------------------------------------------------------------------------

IMPLEMENT_CO_SERVEREVENT_V1(CreateTracerEvent);

CreateTracerEvent::CreateTracerEvent()
{
	mGuaranteeType = Guaranteed;

	localId = 0;
	datablock = NULL;
	sourceId = -1;
	sourceSlot = -1;
	targetId = -1;
}

void CreateTracerEvent::pack(NetConnection* conn, BitStream* bstream)
{
	if(bstream->writeFlag(datablock))
	{
		bstream->writeRangedU32(datablock->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);

		bstream->writeInt(localId, 32);

		if(bstream->writeFlag(sourceId != -1))
			bstream->writeRangedU32(U32(sourceId), 0, NetConnection::MaxGhostCount);

		bstream->writeSignedInt(sourceSlot,4);

		if(bstream->writeFlag(targetId != -1))
			bstream->writeRangedU32(U32(targetId), 0, NetConnection::MaxGhostCount);

		mathWrite(*bstream, pos);
		mathWrite(*bstream, vel);
	}
}

void CreateTracerEvent::unpack(NetConnection* conn, BitStream* bstream)
{
	if(bstream->readFlag())
	{
		SimObject* ptr = NULL;
		U32 id = bstream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
		if(id != 0 && (ptr = Sim::findObject(id)))
			datablock = dynamic_cast<TracerProjectileData*>(ptr);

		localId = bstream->readInt(32);

		if(bstream->readFlag())
			sourceId = bstream->readRangedU32(0, NetConnection::MaxGhostCount);

		sourceSlot = bstream->readSignedInt(4);

		if(bstream->readFlag())
			targetId = bstream->readRangedU32(0, NetConnection::MaxGhostCount);

		mathRead(*bstream, &pos);
		mathRead(*bstream, &vel);
	}
}

void CreateTracerEvent::write(NetConnection* conn, BitStream* bstream)
{
	this->pack(conn, bstream);
}

void CreateTracerEvent::process(NetConnection* conn)
{
	if(!datablock)
		return;

	ShapeBase* source = NULL;
	if(sourceId != -1)
	{
		NetObject* pObj = conn->resolveObjectFromGhostIndex(sourceId);
		source = dynamic_cast<ShapeBase*>(pObj);
	}

	GameBase* target = NULL;
	if(targetId != -1)
	{
		NetObject* pObj = conn->resolveObjectFromGhostIndex(targetId);
		target = dynamic_cast<GameBase*>(pObj);
	}

	if(source)
		source->clientFiredTracer(conn, localId, sourceSlot, datablock, target, pos, vel);
}

//--------------------------------------------------------------------------
//
TracerProjectileData::TracerProjectileData()
{
	noFake = false;
	energyDrain = 0;
	posOffset.set(0, 0, 0);
	velOffset.set(0, 0);
}

//--------------------------------------------------------------------------

IMPLEMENT_CONSOLETYPE(TracerProjectileData)
IMPLEMENT_GETDATATYPE(TracerProjectileData)
IMPLEMENT_SETDATATYPE(TracerProjectileData)

void TracerProjectileData::initPersistFields()
{
	Parent::initPersistFields();

	addField("noFake",      TypeBool,    Offset(noFake, TracerProjectileData));
	addField("energyDrain", TypeS32,     Offset(energyDrain, TracerProjectileData));
	addField("posOffset",	TypePoint3F, Offset(posOffset, TracerProjectileData));
	addField("velOffset",	TypePoint2F, Offset(velOffset, TracerProjectileData));
}

//--------------------------------------------------------------------------

bool TracerProjectileData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   return true;
}


bool TracerProjectileData::preload(bool server, char errorBuffer[256])
{
   if (Parent::preload(server, errorBuffer) == false)
      return false;

   return true;
}

//--------------------------------------------------------------------------

void TracerProjectileData::packData(BitStream* stream)
{
   Parent::packData(stream);

   stream->writeFlag(noFake);

   stream->write(energyDrain);

   stream->write(posOffset.x);
   stream->write(posOffset.y);
   stream->write(posOffset.z);

   stream->write(velOffset.x);
   stream->write(velOffset.y);
}

void TracerProjectileData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   noFake = stream->readFlag();

   stream->read(&energyDrain);

   stream->read(&posOffset.x);
   stream->read(&posOffset.y);
   stream->read(&posOffset.z);

   stream->read(&velOffset.x);
   stream->read(&velOffset.y);
}


//--------------------------------------------------------------------------

TracerProjectile::TracerProjectile(bool onClient, bool isFake)
{
	mFake.conn     = NULL;
	mFake.id       = 0;

	mIsFake = isFake;
	
	mNetFlags.clear();
	if(onClient)
	{
		mNetFlags.set(IsGhost);
	}
	else
	{
		mNetFlags.set(Ghostable);
	}
}

TracerProjectile::~TracerProjectile()
{

}

void TracerProjectile::onDeleteNotify(SimObject* obj)
{
	Parent::onDeleteNotify(obj);
}

//--------------------------------------------------------------------------

void TracerProjectile::initPersistFields()
{
   Parent::initPersistFields();
}

void TracerProjectile::consoleInit()
{
	Parent::consoleInit();
}


//--------------------------------------------------------------------------

bool TracerProjectile::onAdd()
{
	//Con::printf("TracerProjectile::onAdd(): [%s] [%s] target: %x", isGhost() ? "CLNT" : "SRVR", mIsFake ? "FAKE" : "NON-FAKE", mTarget);

	if(mIsFake)
	{
		AssertFatal(isClientObject(), "A fake TracerProjectile on the server? - Someone fucked up!");

		//Con::printf("TracerProjectile::onAdd() fake @ %u", Platform::getVirtualMilliseconds());

		mInitialPosition = mCurrPosition;
		mCurrDeltaBase = mCurrPosition;
		mCurrBackDelta = -mCurrVelocity;

		// notify server of our presence...
		CreateTracerEvent* event = new CreateTracerEvent();
		event->datablock  = mDataBlock;
		event->localId    = mDataBlock->noFake ? 0 : this->getId();
		event->sourceId   = mSourceObject ? mSourceObject->getNetIndex() : -1;
		event->sourceSlot = mSourceObjectSlot;
		event->targetId   = mTarget ? mTarget->getNetIndex() : -1;
		event->pos        = mCurrPosition;
		event->vel        = mCurrVelocity;

		GameConnection::getConnectionToServer()->postNetEvent(event);

		if(mDataBlock->noFake)
			return false;
	} 
	else
	{
		//Con::printf("TracerProjectile::onAdd() non-fake @ %u", Platform::getVirtualMilliseconds());
	}

	if(!Parent::onAdd())
		return false;	
     
	return true;
}


void TracerProjectile::onRemove()
{
	// delete lasertrails & emitters
	// immediately if we're a fake...
	if(mIsFake)
	{
		for( S32 i = 0; i < NUM_LASERTRAILS; i++ )
		{
			if(mLaserTrailList[i])
			{
				mLaserTrailList[i]->deleteObject();
				mLaserTrailList[i] = NULL;
			}
		}

		if(mParticleEmitter)
		{
			mParticleEmitter->deleteObject();
			mParticleEmitter = NULL;
		}

		if(mParticleWaterEmitter)
		{
			mParticleWaterEmitter->deleteObject();
			mParticleWaterEmitter = NULL;
		}
	}

	Parent::onRemove();
}


bool TracerProjectile::onNewDataBlock(GameBaseData* dptr)
{
   mDataBlock = dynamic_cast<TracerProjectileData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr))
      return false;

   return true;
}


//----------------------------------------------------------------------------

void TracerProjectile::processTick(const Move* move)
{
	Parent::processTick(move);
}


void TracerProjectile::advanceTime(F32 dt)
{
   Parent::advanceTime(dt);
}

void TracerProjectile::interpolateTick(F32 delta)
{
   Parent::interpolateTick(delta);
}

//--------------------------------------------------------------------------

U32 TracerProjectile::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);

	if(stream->writeFlag(mask & GameBase::InitialUpdateMask))
   {
		if(stream->writeFlag(mFake.conn == con))
		{
			// send fake-ghost-replacement info...
			stream->writeInt(mFake.id, 32);
		}
   }

   return retMask;
}

void TracerProjectile::unpackUpdate(NetConnection* con, BitStream* stream)
{
   Parent::unpackUpdate(con, stream);

   if(stream->readFlag())
   {
		if(stream->readFlag())
		{
			// read fake-ghost-replacement info...
			mFake.id = stream->readInt(32);				
		}
   }
}

//--------------------------------------------------------------------------

class ObjectDeleteEvent : public SimEvent
{
public:
   void process(SimObject *object)
   {
      object->deleteObject();
   }
};

//--------------------------------------------------------------------------

bool TracerProjectile::prepRenderImage(SceneState* state, const U32 stateKey,
                                       const U32 startZone, const bool modifyBaseState)
{
	bool render = true;

	// if we're about to render for the first time...
	if(mRenderCount == 0)
	{
		if(mFake.id != 0) // if this projectile replaces a fake one...
		{
			// find the fake ghost...
			TracerProjectile* prj = NULL;
			SimObject* obj = NULL;
			if(Sim::findObject(mFake.id, obj))
				prj = dynamic_cast<TracerProjectile*>(obj);

			if(prj)
			{
				if(prj->mHidden)
					render = true;
				else if(prj->mCurrTick < 2)
					render = false;
				else
				{
					prj->mHidden = true;
					Sim::postEvent(prj, new ObjectDeleteEvent, Sim::getCurrentTime());
					mFake.id = 0;
					render = true;
				}
			}
			else
				render = true;

		}
	}

	if(render)
		return Parent::prepRenderImage(state, stateKey, startZone, modifyBaseState);
	else
		return false;
}

//--------------------------------------------------------------------------

void TracerProjectile::onCollision(const Point3F& p, const Point3F& n, SceneObject* obj)
{
	if(mIsFake)
	{
		mHidden = true;
		Sim::postEvent(this, new ObjectDeleteEvent, Sim::getCurrentTime());
	}
	else
		Parent::onCollision(p, n, obj);
}

void TracerProjectile::explode(const Point3F& p, const Point3F& n, const U32 collideType, bool nodecal)
{
	if(mIsFake)
	{
		mHidden = true;
		Sim::postEvent(this, new ObjectDeleteEvent, Sim::getCurrentTime());
	}
	else
		Parent::explode(p, n, collideType, nodecal);
}

#endif // BORQUE_NEEDS_PORTING