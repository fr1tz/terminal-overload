// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _UTIL_FPSTRACKER_H_
#define _UTIL_FPSTRACKER_H_

#include "platform/platform.h"

struct FPSTracker
{
   F32 fpsRealLast;
   F32 fpsReal;
   F32 fpsRealMin;
   F32 fpsRealMax;
   F32 fpsVirtualLast;
   F32 fpsVirtual;
   F32 fpsFrames;
   F32 fpsNext;
   F32 mUpdateInterval;

   FPSTracker();

   /// Resets the FPS variables
   void reset();

   /// Updates the FPS variables
   void update();
};

extern FPSTracker gFPS;

#endif