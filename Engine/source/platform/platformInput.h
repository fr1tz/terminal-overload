// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMINPUT_H_
#define _PLATFORMINPUT_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#include "platform/input/event.h"

//------------------------------------------------------------------------------
U8 TranslateOSKeyCode( U8 vcode );
U8 TranslateKeyCodeToOS(U8 keycode);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class InputDevice : public SimObject
{
protected:
   char mName[30];

public:
   struct ObjInfo
   {
      InputEventType      mType;
      InputObjectInstances  mInst;
      S32   mMin, mMax;
   };

   inline const char* getDeviceName()
   {
      return mName;
   }

   virtual bool process() = 0;
};

//------------------------------------------------------------------------------

class InputManager : public SimGroup
{
protected:
   bool  mEnabled;

public:
   inline bool  isEnabled()
   {
      return mEnabled;
   }

   virtual bool enable() = 0;
   virtual void disable() = 0;
   virtual void process() = 0;
};

enum KEY_STATE
{
   STATE_LOWER,
   STATE_UPPER,
   STATE_GOOFY
};

//------------------------------------------------------------------------------
class Input
{
protected:
   static InputManager* smManager;

   static bool smActive;

   /// Current modifier keys.
   static U8 smModifierKeys;

   static bool smLastKeyboardActivated;
   static bool smLastMouseActivated;
   static bool smLastJoystickActivated;

public:
   static void init();
   static void destroy();

   static bool enable();
   static void disable();

   static void activate();
   static void deactivate();

   static U16  getAscii( U16 keyCode, KEY_STATE keyState );
   static U16  getKeyCode( U16 asciiCode );

   static bool isEnabled();
   static bool isActive();

   static void process();

   static InputManager* getManager();

   static U8 getModifierKeys() {return smModifierKeys;}
   static void setModifierKeys(U8 mod) {smModifierKeys = mod;}
#ifdef LOG_INPUT
   static void log( const char* format, ... );
#endif

#ifdef TORQUE_OS_XENON
   static S32 getLockedController();
#endif

   /// Global input routing JournaledSignal; post input events here for
   /// processing.
   static InputEvent smInputEvent;
};

#endif // _H_PLATFORMINPUT_
