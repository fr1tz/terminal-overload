// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HUDINFO_H_
#define _HUDINFO_H_

#ifndef _NETOBJECT_H_
#include "sim/netObject.h"
#endif
#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif
#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

class NetConnection;

class HudInfo : public NetObject, public virtual ITickable
{
	typedef NetObject Parent;

   S32              mType;
   StringTableEntry mString;
   SceneObject*     mObject;
	Point3F          mPosition;

   S32              mAge;

 public:
   enum MaskBits
	{
		TypeMask     = BIT(0),
		StringMask   = BIT(1),
      ObjectMask   = BIT(2),
		PositionMask = BIT(3)
   };

	HudInfo();
	~HudInfo();

	// ConsoleObject
	static void consoleInit();
	static void initPersistFields();

   // SimObject
	bool onAdd();
	void onRemove();
	void onDeleteNotify(SimObject* obj);

	// NetObject
	F32 getUpdatePriority(CameraScopeQuery* focusObject, U32 updateMask, S32 updateSkips);
	U32 packUpdate(NetConnection*, U32, BitStream*);
	void unpackUpdate(NetConnection*, BitStream*);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   // HudInfo
   void setType(S32 type);
   void setString(StringTableEntry string);
   void setObject(SceneObject* obj);
   void setPosition(const Point3F& pos);
   S32 getType() { return mType; }
   StringTableEntry getString() { return mString; }
   SceneObject* getObject() { return mObject; }
	Point3F getPosition() { return mObject ? mObject->getPosition() : mPosition; }
   S32 getAge() { return mAge; }

	DECLARE_CONOBJECT(HudInfo);
};

#endif // _HUDINFO_H_

