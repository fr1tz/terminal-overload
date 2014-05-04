// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "NOTC/hudInfo.h"

#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "core/stream/bitStream.h"
#include "math/mathIO.h"
#include "T3D/gameBase/gameConnection.h"

IMPLEMENT_CO_NETOBJECT_V1(HudInfo);

HudInfo::HudInfo()
{
   mNetFlags.set(Ghostable);

   mType = 0;
   mString = StringTable->insert("");
	mObject = NULL;
	mPosition.set(0, 0, 0);

   mAge = 0;
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

	// Add to HudInfo set
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

	if(obj == mObject)
		mObject = NULL;
}


//------------------------------------------------------------------------------

F32 HudInfo::getUpdatePriority(CameraScopeQuery*, U32 updateMask, S32 updateSkips)
{
   return F32(updateSkips) * 0.5;
}

U32 HudInfo::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
	U32 retMask = Parent::packUpdate(conn, mask, stream);

	S32 ghostId = mObject ? conn->getGhostIndex(mObject) : -1;

   if(stream->writeFlag(mask & TypeMask))
      stream->write(mType);

   if(stream->writeFlag((mask & StringMask) && mString))
      stream->writeString(mString);

   bool writeGhostId = false;
   if(mask & ObjectMask)
   {
      if(ghostId == -1)     
         retMask |= ObjectMask; // No ghost, try again later.
      else
         writeGhostId = true;
   }
   if(stream->writeFlag(writeGhostId))
      stream->writeRangedU32(U32(ghostId), 0, NetConnection::MaxGhostCount);

   bool writePosition = (mask & PositionMask) && (mObject == NULL || ghostId == -1);
   if(stream->writeFlag(writePosition))
      mathWrite(*stream, mObject ? mObject->getPosition() : mPosition);

	return retMask;
}


void HudInfo::unpackUpdate(NetConnection* conn, BitStream* stream)
{
	Parent::unpackUpdate(conn, stream);

   if(stream->readFlag())
      stream->read(&mType);

   if(stream->readFlag())
      mString = stream->readSTString();

   if(stream->readFlag())
   {
      SceneObject* obj = NULL;
		S32 ghostId = stream->readRangedU32(0, NetConnection::MaxGhostCount);
		NetObject* pObject = conn->resolveGhost(ghostId);
		if(pObject != NULL)
			obj = dynamic_cast<SceneObject*>(pObject);
      this->setObject(obj);
   }

   if(stream->readFlag())
      mathRead(*stream, &mPosition);
}

//------------------------------------------------------------------------------

void HudInfo::processTick()
{
   mAge++;

   if(this->isServerObject() && mObject)
      if(mObject->getPosition() != mPosition)
         this->setMaskBits(PositionMask);

}

//------------------------------------------------------------------------------

void HudInfo::setType(S32 type)
{
   mType = type;
   this->setMaskBits(TypeMask);
}

void HudInfo::setString(StringTableEntry string)
{
   mString = string;
   this->setMaskBits(StringMask);
}

void HudInfo::setObject(SceneObject* obj)
{
   if(mObject)
      this->clearNotify(mObject);

   mObject = obj;

   if(mObject)
      this->deleteNotify(mObject);

   this->setMaskBits(ObjectMask);
}

void HudInfo::setPosition(const Point3F& pos)
{
   if(mObject)
      return;
   mPosition = pos;
   this->setMaskBits(PositionMask);
}

//------------------------------------------------------------------------------

DefineEngineMethod( HudInfo, setType, void, (S32 type),,
   "@brief Sets the arbitrary type number for this object.\n\n"
   "@param type The arbitrary type number\n\n")
{
   object->setType(type);
}

DefineEngineMethod( HudInfo, getType, S32, (),,
   "@brief Returns the arbitrary type number for this object.\n\n")
{
   return object->getType();
}

DefineEngineMethod( HudInfo, setString, void, (const char* string),,
   "@brief Sets the arbitrary string for this object.\n\n"
   "@param string The arbitrary string\n\n")
{
   object->setString(string);
}

DefineEngineMethod( HudInfo, getString, const char*, (),,
   "@brief Returns the arbitrary string for this object.\n\n")
{
   return object->getString();
}

DefineEngineMethod( HudInfo, setObject, void, (SceneObject* obj),,
   "@brief Sets the object that is linked to this object.\n\n"
   "@param shape The ShapeBase object\n\n")
{
   object->setObject(obj);
}

DefineEngineMethod( HudInfo, getObject, SceneObject*, (),,
   "@brief Returns the object this is linked to this object.\n\n")
{
   return object->getObject();
}

DefineEngineMethod( HudInfo, setPosition, void, (Point3F pos),,
   "@brief Sets the object's position.\n\n"
   "@param pos The position\n\n")
{
   object->setPosition(pos);
}

DefineEngineMethod( HudInfo, getPosition, Point3F, (),,
   "@brief Returns the object's position.\n\n")
{
   return object->getPosition();
}
