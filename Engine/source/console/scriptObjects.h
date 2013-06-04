// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCRIPTOBJECTS_H_
#define _SCRIPTOBJECTS_H_

#ifndef _CONSOLEINTERNAL_H_
#include "console/consoleInternal.h"
#endif

#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif

//-----------------------------------------------------------------------------
// ScriptObject
//-----------------------------------------------------------------------------

class ScriptObject : public SimObject
{
   typedef SimObject Parent;

public:
   ScriptObject();
   bool onAdd();
   void onRemove();

   DECLARE_CONOBJECT(ScriptObject);

   DECLARE_CALLBACK(void, onAdd, (SimObjectId ID) );
   DECLARE_CALLBACK(void, onRemove, (SimObjectId ID));
};

//-----------------------------------------------------------------------------
// ScriptTickObject
//-----------------------------------------------------------------------------

class ScriptTickObject : public ScriptObject, public virtual ITickable
{
   typedef ScriptObject Parent;

protected:
   bool mCallOnAdvanceTime;

public:
   ScriptTickObject();
   static void initPersistFields();
   bool onAdd();
   void onRemove();

   virtual void interpolateTick( F32 delta );
   virtual void processTick();
   virtual void advanceTime( F32 timeDelta );

   DECLARE_CONOBJECT(ScriptTickObject);

   DECLARE_CALLBACK(void, onInterpolateTick, (F32 delta) );
   DECLARE_CALLBACK(void, onProcessTick, () );
   DECLARE_CALLBACK(void, onAdvanceTime, (F32 timeDelta) );
};

//-----------------------------------------------------------------------------
// ScriptGroup
//-----------------------------------------------------------------------------

class ScriptGroup : public SimGroup
{
   typedef SimGroup Parent;
   
public:
   ScriptGroup();
   bool onAdd();
   void onRemove();

   DECLARE_CONOBJECT(ScriptGroup);

   DECLARE_CALLBACK(void, onAdd, (SimObjectId ID) );
   DECLARE_CALLBACK(void, onRemove, (SimObjectId ID));
};

#endif