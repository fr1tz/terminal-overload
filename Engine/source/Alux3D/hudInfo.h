// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#ifndef HUDINFO_H
#define HUDINFO_H

#ifndef _NETOBJECT_H_
#include "sim/netObject.h"
#endif

class ShapeBase;
class NetConnection;

class HudInfo : public NetObject
{
	typedef NetObject Parent;

	// vector of net connections that need to be notified
	// that they have a ghost of our shape...
	Vector<NetConnection*> mShapeGhostNotifyConnections;

	bool             mActive;

    ShapeBaseData*   mDatablock;
	S32              mDatablockId;

	ShapeBase*       mShape;
   StringTableEntry mShapeName;
	S32              mTeamId;
	Point3F          mPos;

	NetConnection*   mControllingClient; // only used on server
	S32              mControlSlot;

 public:
   enum MaskBits
	{
		InitialUpdateMask    = BIT(0),
		ShapeNameMask        = BIT(1),
		TeamIdMask           = BIT(2),
		PositionMask         = BIT(3),
		ControlMask          = BIT(4),
   };

	HudInfo(ShapeBase* shape = NULL);
	~HudInfo();

	// ConsoleObject...
	static void consoleInit();
	static void initPersistFields();

   // SimObject...      
	bool onAdd();
	void onRemove();
	void onDeleteNotify(SimObject* obj);

	// NetObject...
	F32 getUpdatePriority(CameraScopeQuery* focusObject, U32 updateMask, S32 updateSkips);
	U32 packUpdate(NetConnection*, U32, BitStream*);
	void unpackUpdate(NetConnection*, BitStream*);

	void setActive(bool active) { mActive = active; }
	bool isActive() { return mActive; }
	ShapeBaseData*   datablock() { return mDatablock; }
	ShapeBase*       shape()     { return mShape; }
	StringTableEntry shapeName() { return mShape ? mShape->getShapeName() : mShapeName; }
	S32              teamId()    { return mShape ? mShape->getTeamId() : mTeamId; }
	Point3F          pos()       { return mShape ? mShape->getPosition() : mPos; }
	void markAsControlled(NetConnection* conn, U32 slot);
	S32  underControl() { return mControlSlot; }

	DECLARE_CONOBJECT(HudInfo);
};

#endif // HUDINFO_H

#endif // BORQUE_NEEDS_PORTING
