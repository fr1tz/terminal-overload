// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

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
#include "T3D/gameBase/gameConnection.h"
#endif

class ShapeBase;

class ServerSideController : public SimObject
{
	typedef SimObject Parent;

public:
	ServerSideController();
	virtual Move getMove(ShapeBase* obj) = 0;
};

class SimpleServerSideController : public ServerSideController
{
	typedef ServerSideController Parent;

	Move mMove;
	bool mResetMove;

public:
	SimpleServerSideController();
	Move getMove(ShapeBase* obj);
	DECLARE_CONOBJECT(SimpleServerSideController);
	static void initPersistFields();
};

#if 0
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
#endif

#endif // _SERVERSIDECONTROL_H_
