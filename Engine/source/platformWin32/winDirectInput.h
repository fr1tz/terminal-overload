// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WINDIRECTINPUT_H_
#define _WINDIRECTINPUT_H_

#ifndef _PLATFORMWIN32_H_
#include "platformWin32/platformWin32.h"
#endif
#ifndef _PLATFORMINPUT_H_
#include "platform/platformInput.h"
#endif
#ifndef _WINDINPUTDEVICE_H_
#include "platformWin32/winDInputDevice.h"
#endif

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <xinput.h>

// XInput related definitions
typedef DWORD (WINAPI* FN_XInputGetState)(DWORD dwUserIndex, XINPUT_STATE* pState);
typedef DWORD (WINAPI* FN_XInputSetState)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);
#define XINPUT_MAX_CONTROLLERS 4  // XInput handles up to 4 controllers 
#define XINPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
struct XINPUT_CONTROLLER_STATE
{
    XINPUT_STATE    state;
    bool            bConnected;
};

//------------------------------------------------------------------------------
class DInputManager : public InputManager
{
   private:
      typedef SimGroup Parent;

      // XInput state
      HMODULE                 mXInputLib;
      FN_XInputGetState       mfnXInputGetState;
      FN_XInputSetState       mfnXInputSetState;
      XINPUT_CONTROLLER_STATE mXInputStateOld[XINPUT_MAX_CONTROLLERS];
      XINPUT_CONTROLLER_STATE mXInputStateNew[XINPUT_MAX_CONTROLLERS];
      U32                     mLastDisconnectTime[XINPUT_MAX_CONTROLLERS];
      bool                    mXInputStateReset;
      bool                    mXInputDeadZoneOn;

      /// Number of milliseconds to skip checking an xinput device if it was
      /// disconnected on last check.
      const static U32 csmDisconnectedSkipDelay = 250;

      HMODULE        mDInputLib;
      LPDIRECTINPUT8 mDInputInterface;

      static bool smJoystickEnabled;
      static bool smXInputEnabled;

      bool mJoystickActive;
      bool mXInputActive;

      void  enumerateDevices();

      static BOOL CALLBACK EnumDevicesProc( const DIDEVICEINSTANCE *pddi, LPVOID pvRef );

      bool acquire( U8 deviceType, U8 deviceID );
      void unacquire( U8 deviceType, U8 deviceID );

      // XInput worker functions
      void buildXInputEvent( U32 deviceInst, InputEventType objType, InputObjectInstances objInst, InputActionType action, F32 fValue );
      void fireXInputConnectEvent( S32 controllerID, bool condition, bool connected );
      void fireXInputMoveEvent( S32 controllerID, bool condition, InputObjectInstances objInst, F32 fValue );
      void fireXInputButtonEvent( S32 controllerID, bool forceFire, S32 button, InputObjectInstances objInst );
      void processXInput();

   public:
      DInputManager();

      bool enable();
      void disable();

      void onDeleteNotify( SimObject* object );
      bool onAdd();
      void onRemove();

      void process();

      // DirectInput functions:
      static void init();

      static bool enableJoystick();
      static void disableJoystick();
      static bool isJoystickEnabled();
      bool activateJoystick();
      void deactivateJoystick();
      bool isJoystickActive()       { return( mJoystickActive ); }

      static bool enableXInput();
      static void disableXInput();
      static bool isXInputEnabled();
      bool activateXInput();
      void deactivateXInput();
      bool isXInputActive()         { return( mXInputActive ); }
      void resetXInput()            { mXInputStateReset = true; }
      bool isXInputConnected(S32 controllerID);
      S32 getXInputState(S32 controllerID, S32 property, bool current);

      // Console interface:
      const char* getJoystickAxesString( U32 deviceID );

      bool rumble( const char *pDeviceName, F32 x, F32 y );
};

#endif  // _H_WINDIRECTINPUT_
