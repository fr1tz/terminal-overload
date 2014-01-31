// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#pragma once

#include "np_pluginbase.h"

// Windows specific NP plugin interface for handling platform window integration with Torque 3D
class NPWebGamePlugin
{
public:

   NPWebGamePlugin(NPP aInstance);
   ~NPWebGamePlugin();

   // very simple interface based on browser window opening/closing
   NPBool	Open(NPWindow* aWindow);
   void	   Close();
   NPBool	IsOpen();

   // plugin instance
   NPP	   mInstance;
   bool     mOpen;

   static NPWebGamePlugin* sInstance;

   // Browser platform native window handle
   HWND mHwnd;
   LONG_PTR mOriginalWinProc;

};


