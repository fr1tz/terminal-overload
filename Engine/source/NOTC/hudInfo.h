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

   enum Constants {
      NumDataSets = 8
   };

   SceneObject*     mObject;
	Point3F          mPosition;
   S32              mAge;

   struct DataSet {
      U32 type;
      String stringField;
      S32 intField;
      F32 floatField;
      bool boolField;      
   } mDataSets[NumDataSets];

 public:
   enum MaskBits
	{
      ObjectMask   = BIT(0),
		PositionMask = BIT(1),
      DataSetMask  = BIT(2)
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
   SceneObject* getObject() { return mObject; }
	Point3F getPosition() { return mObject ? mObject->getPosition() : mPosition; }
   S32 getAge() { return mAge; }
   // Data set access
   String getDataSetStringField(U32 dataSetType);
   S32 getDataSetIntField(U32 dataSetType);
   F32 getDataSetFloatField(U32 dataSetType);
   bool getDataSetBoolField(U32 dataSetType);
   // Data set manipulation (server-side only)
   void setDataSetType(U32 dataSetIndex, U32 type);
   void setDataSetStringField(U32 dataSetIndex, String s);
   void setDataSetIntField(U32 dataSetIndex, S32 i);
   void setDataSetFloatField(U32 dataSetIndex, F32 f);
   void setDataSetBoolField(U32 dataSetIndex, bool b);
   //
   void setObject(SceneObject* obj);
   void setPosition(const Point3F& pos);

	DECLARE_CONOBJECT(HudInfo);
};

#endif // _HUDINFO_H_

