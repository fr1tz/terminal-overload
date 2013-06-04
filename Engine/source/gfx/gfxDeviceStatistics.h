// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GFXDEVICESTATISTICS_H_
#define _GFXDEVICESTATISTICS_H_

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

// A class that hold a simple set of device stats.
class GFXDeviceStatistics
{
public:
   // Actual stats
   S32 mPolyCount;
   S32 mDrawCalls;
   S32 mRenderTargetChanges;

   GFXDeviceStatistics();

   void setPrefix(const String& prefix);

   /// Clear stats
   void clear();

   /// Copy from source (should just be a memcpy, but that may change later) used in 
   /// conjunction with end to get a subset of statistics.  For example, statistics
   /// for a particular render bin.
   void start(GFXDeviceStatistics * source);

   /// Used with start to get a subset of stats on a device.  Basically will do
   /// this->mPolyCount = source->mPolyCount - this->mPolyCount.  (Fancy!)
   void end(GFXDeviceStatistics * source);

   /// Exports the stats to the console
   void exportToConsole();
private:
   String vnPolyCount;
   String vnDrawCalls;
   String vnRenderTargetChanges;
};

#endif