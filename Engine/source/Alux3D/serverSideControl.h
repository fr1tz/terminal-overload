// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#ifndef _SERVERSIDECONTROL_H_
#define _SERVERSIDECONTROL_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif
#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif
#ifndef _GAMECONNECTION_H_
#include "game/gameConnection.h"
#endif

class ServerSideController : public SimObject
{
	typedef SimObject Parent;

public:
	ServerSideController();
	virtual Move getMove(ShapeBase* obj) = 0;
};

class HoverPodController : public ServerSideController
{
	typedef ServerSideController Parent;

	S32 mClientId;
	Point3F mDirection;

public:
	HoverPodController();
	Move getMove(ShapeBase* obj);
	DECLARE_CONOBJECT(HoverPodController);
	static void initPersistFields();
};

#endif // _SERVERSIDECONTROL_H_

#endif // BORQUE_NEEDS_PORTING
