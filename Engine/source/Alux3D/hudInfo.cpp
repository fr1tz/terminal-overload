// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#include "console/consoleTypes.h"
#include "dgl/dgl.h"
#include "core/bitStream.h"
#include "math/mathIO.h"
#include "math/mathUtils.h"
#include "game/gameConnection.h"
#include "sceneGraph/sceneGraph.h"
#include "shapeBase.h"
#include "hudInfo.h"

IMPLEMENT_CO_NETOBJECT_V1(HudInfo);

HudInfo::HudInfo(ShapeBase* shape)
{
	mActive = true;

	mDatablock = shape ? (ShapeBaseData*)shape->getDataBlock() : NULL;
	mDatablockId = 0;

	mShape = shape;
	mShapeName = StringTable->insert("");
	mTeamId = 0;
	mPos.set(0, 0, 0);

	mControllingClient = NULL;
	mControlSlot = 0;
}


HudInfo::~HudInfo()
{
/*
   delete mGroundShapeInstance;
   mGroundShapeInstance = NULL;
*/
}

void HudInfo::initPersistFields()
{
	Parent::initPersistFields();

/*
	addField("teamId", TypeS32,		Offset(mTeamId, HudInfo));
	addField("name", TypeString, Offset(mName,HudInfo));  
*/
}

void HudInfo::consoleInit()
{
/*
	Con::addCommand("HudInfo", "updateClients", cUpdateClients, "obj.updateClients()", 2, 2);
	Con::addCommand("HudInfo", "updateGroundShape", cUpdateGroundShape, "obj.updateClients()", 2, 2);
*/
}

//------------------------------------------------------------------------------

bool HudInfo::onAdd()
{
	if(!Parent::onAdd()) return(false);

    if(!mDatablock && mDatablockId != 0)
      if(Sim::findObject(mDatablockId, mDatablock) == false)
         Con::errorf(ConsoleLogEntry::General, "HudInfo::onAdd: Invalid packet, bad datablockId(mDatablock): %d", mDatablockId);

	// add to HudInfo set...
	if(isServerObject())
		Sim::getServerHudInfoSet()->addObject(this);
	else
		Sim::getClientHudInfoSet()->addObject(this);

	return true;
}

void HudInfo::onRemove()
{
	// remove from HudInfo set...
	if(isServerObject())
		Sim::getServerHudInfoSet()->removeObject(this);
	else
		Sim::getClientHudInfoSet()->removeObject(this);

	Parent::onRemove();
}

void HudInfo::onDeleteNotify(SimObject* obj)
{
	Parent::onDeleteNotify(obj);

	if(obj == mShape)
		mShape = NULL;

	for(U32 i = 0; i < mShapeGhostNotifyConnections.size(); i++)
      if(mShapeGhostNotifyConnections[i] == obj)
         mShapeGhostNotifyConnections.erase(i);
}


//------------------------------------------------------------------------------

F32 HudInfo::getUpdatePriority(CameraScopeQuery*, U32 updateMask, S32 updateSkips)
{
   return F32(updateSkips) * 0.5;
}

U32 HudInfo::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
	U32 retMask = Parent::packUpdate(conn, mask, stream);

	if( stream->writeFlag(mask & InitialUpdateMask) )
		stream->writeRangedU32(mDatablock->getId(), DataBlockObjectIdFirst,  DataBlockObjectIdLast);

	S32 ghostId = mShape ? conn->getGhostIndex(mShape) : -1;
	if(stream->writeFlag(ghostId == -1))
	{
		// no ghost...
		const char* name = mShape ? mShape->getShapeName() : mShapeName;
		if( stream->writeFlag(mask & ShapeNameMask && name) )
			stream->writeString(name);

		if( stream->writeFlag(mask & TeamIdMask) )
			stream->writeInt(mShape ? mShape->getTeamId() : mTeamId, 2);

		if( stream->writeFlag(mask & PositionMask) )
			mathWrite(*stream, mShape ? mShape->getPosition() : mPos);
	}
	else
		stream->writeRangedU32(U32(ghostId), 0, NetConnection::MaxGhostCount);

	// control info...
	if( stream->writeFlag(mask & ControlMask) )
	{
		if(conn == mControllingClient)
		{
			stream->writeSignedInt(mControlSlot, 3);
		}
		else
		{
			if(mControllingClient)
				stream->writeSignedInt(0, 3);
			else
				stream->writeSignedInt(-1, 3);
		}
	}

	return retMask;
}


void HudInfo::unpackUpdate(NetConnection* conn, BitStream* stream)
{
	Parent::unpackUpdate(conn, stream);

    if(stream->readFlag())
        mDatablockId = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);

	if( stream->readFlag() )
	{
		if( stream->readFlag() )
			mShapeName = stream->readSTString();

		if( stream->readFlag() )
			mTeamId = stream->readInt(2);

		if( stream->readFlag() )
			mathRead(*stream, &mPos);
	}
	else
	{
		S32 ghostId = stream->readRangedU32(0, NetConnection::MaxGhostCount);
		NetObject* pObject = conn->resolveGhost(ghostId);
		if(pObject != NULL)
		{
			ShapeBase* shape = dynamic_cast<ShapeBase*>(pObject);
			if(shape != mShape)
			{
				if(mShape)
					clearNotify(mShape);

				mShape = shape;

				mShapeName = mShape->getShapeName();
				mTeamId = mShape->getTeamId();
				mPos = mShape->getPosition();

				deleteNotify(mShape);
			}
		}
	}

	if( stream->readFlag() )
		mControlSlot = stream->readSignedInt(3);
}

//------------------------------------------------------------------------------

void HudInfo::markAsControlled(NetConnection* conn, U32 slot)
{
	mControllingClient = conn;
	mControlSlot = (S32)slot;
	this->setMaskBits(ControlMask);
}

//------------------------------------------------------------------------------

ConsoleMethod( HudInfo, setActive, void, 3, 3, "(bool active)")
{
	object->setActive(dAtob(argv[2]));
}

ConsoleMethod( HudInfo, isActive, bool, 2, 2, "()")
{
	return object->isActive();
}

ConsoleMethod( HudInfo, markAsControlled, void, 4, 4, "")
{
	NetConnection* client;
	if(Sim::findObject(argv[2],client))
	{
		S32 slot = dAtoi(argv[3]);
		object->markAsControlled(client, slot);
	}
	else
	{
		object->markAsControlled(NULL, 0);
	}
}

#endif // BORQUE_NEEDS_PORTING