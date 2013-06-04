// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _IINPUTDEVICE_H_
#define _IINPUTDEVICE_H_

#include "console/consoleTypes.h"

class IInputDevice
{
protected:
   /// Device name
   char mName[30];

   /// Device type
   U32 mDeviceType;

   /// Is the device enabled
   bool mEnabled;

public:
   inline const char* getDeviceName() const
   {
      return mName;
   }

   inline U32 getDeviceType() const
   {
      return mDeviceType;
   }

   inline bool isEnabled()
   {
      return mEnabled;
   }

   virtual bool process() = 0;
};

#endif
