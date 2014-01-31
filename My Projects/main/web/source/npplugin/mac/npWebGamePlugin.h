// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#pragma once

#include "../../common/webCommon.h"

class NPWebGamePlugin
{
public:

   NPWebGamePlugin(NPP aInstance);
   ~NPWebGamePlugin();

   NPBool	Open(NPWindow* aWindow);
   void	   Close();
   NPBool	IsOpen();

   NPP	 mInstance;
   bool  mOpen;

   static NPWebGamePlugin* sInstance;
};


