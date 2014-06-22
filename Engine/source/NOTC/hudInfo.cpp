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

	mObject = NULL;
	mPosition.set(0, 0, 0);
   mAge = 0;

   for(U32 i = 0; i < NumDataSets; i++)
   {
      mDataSets[i].type = 0;
      mDataSets[i].stringField = StringTable->insert("");
      mDataSets[i].intField = 0;
      mDataSets[i].floatField = 0;
      mDataSets[i].boolField = false;
   }
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

   // Data sets
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(stream->writeFlag(mask & (DataSetMask<<i)))
      {
         if(stream->writeFlag(mDataSets[i].type != 0))
            stream->write(mDataSets[i].type);

         if(stream->writeFlag(!mDataSets[i].stringField.isEmpty()))
            stream->write(mDataSets[i].stringField);

         if(stream->writeFlag(mDataSets[i].intField != 0))
            stream->write(mDataSets[i].intField);

         if(stream->writeFlag(mDataSets[i].floatField != 0))
            stream->write(mDataSets[i].floatField);

         stream->writeFlag(mDataSets[i].boolField);
      }
   }

	return retMask;
}


void HudInfo::unpackUpdate(NetConnection* conn, BitStream* stream)
{
	Parent::unpackUpdate(conn, stream);

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

   // Data sets
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(stream->readFlag())
      {
         if(stream->readFlag())
            stream->read(&mDataSets[i].type);
         else
            mDataSets[i].type = 0;

         if(stream->readFlag())
            stream->read(&mDataSets[i].stringField);
         else
            mDataSets[i].stringField = "";

         if(stream->readFlag())
            stream->read(&mDataSets[i].intField);
         else
            mDataSets[i].intField = 0;

         if(stream->readFlag())
            stream->read(&mDataSets[i].floatField);
         else
            mDataSets[i].floatField = 0;

         mDataSets[i].boolField = stream->readFlag();
      }
   }
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

String HudInfo::getDataSetStringField(U32 dataSetType)
{
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(mDataSets[i].type == dataSetType)
         return mDataSets[i].stringField;
   }
   return String("");
}

S32 HudInfo::getDataSetIntField(U32 dataSetType)
{
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(mDataSets[i].type == dataSetType)
         return mDataSets[i].intField;
   }
   return 0;
}

F32 HudInfo::getDataSetFloatField(U32 dataSetType)
{
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(mDataSets[i].type == dataSetType)
         return mDataSets[i].floatField;
   }
   return 0;
}

bool HudInfo::getDataSetBoolField(U32 dataSetType)
{
   for(U32 i = 0; i < NumDataSets; i++)
   {
      if(mDataSets[i].type == dataSetType)
         return mDataSets[i].boolField;
   }
   return false;
}

//------------------------------------------------------------------------------

void HudInfo::setDataSetType(U32 dataSetIndex, U32 type)
{
   if(!this->isServerObject() || dataSetIndex > NumDataSets-1)
      return;
   mDataSets[dataSetIndex].type = type;
   this->setMaskBits(DataSetMask << dataSetIndex);
}

void HudInfo::setDataSetStringField(U32 dataSetIndex, String s)
{
   if(!this->isServerObject() || dataSetIndex > NumDataSets-1)
      return;
   mDataSets[dataSetIndex].stringField = s;
   this->setMaskBits(DataSetMask << dataSetIndex);
}

void HudInfo::setDataSetIntField(U32 dataSetIndex, S32 i)
{
   if(!this->isServerObject() || dataSetIndex > NumDataSets-1)
      return;
   mDataSets[dataSetIndex].intField = i;
   this->setMaskBits(DataSetMask << dataSetIndex);
}

void HudInfo::setDataSetFloatField(U32 dataSetIndex, F32 f)
{
   if(!this->isServerObject() || dataSetIndex > NumDataSets-1)
      return;
   mDataSets[dataSetIndex].floatField = f;
   this->setMaskBits(DataSetMask << dataSetIndex);
}

void HudInfo::setDataSetBoolField(U32 dataSetIndex, bool b)
{
   if(!this->isServerObject() || dataSetIndex > NumDataSets-1)
      return;
   mDataSets[dataSetIndex].boolField = b;
   this->setMaskBits(DataSetMask << dataSetIndex);
}

//------------------------------------------------------------------------------

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

DefineEngineMethod( HudInfo, setDataSetType, void, (U32 dataSetIndex, U32 type),,
   "@brief Sets the name of a data set.\n\n")
{
   object->setDataSetType(dataSetIndex, type);
}

DefineEngineMethod( HudInfo, setDataSetStringField, void, (U32 dataSetIndex, String s),,
   "@brief Sets the string field of a data set.\n\n")
{
   object->setDataSetStringField(dataSetIndex, s);
}

DefineEngineMethod( HudInfo, setDataSetIntField, void, (U32 dataSetIndex, S32 i),,
   "@brief Sets the int field of a data set.\n\n")
{
   object->setDataSetIntField(dataSetIndex, i);
}

DefineEngineMethod( HudInfo, setDataSetFloatField, void, (U32 dataSetIndex, F32 f),,
   "@brief Sets the float field of a data set.\n\n")
{
   object->setDataSetFloatField(dataSetIndex, f);
}

DefineEngineMethod( HudInfo, setDataSetBoolField, void, (U32 dataSetIndex, bool b),,
   "@brief Sets the bool field of a data set.\n\n")
{
   object->setDataSetBoolField(dataSetIndex, b);
}
