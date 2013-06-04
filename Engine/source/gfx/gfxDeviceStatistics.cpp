// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gfx/gfxDeviceStatistics.h"
#include "platform/platform.h"
#include "console/console.h"

GFXDeviceStatistics::GFXDeviceStatistics()
{
   clear();   
}

void GFXDeviceStatistics::setPrefix(const String& prefix)
{
   // This is a bit silly, but we don't want to construct these
   // strings every frame.
   vnPolyCount = prefix + "polyCount";
   vnDrawCalls = prefix + "drawCalls";
   vnRenderTargetChanges = prefix + "renderTargetChanges";
}

/// Clear stats
void GFXDeviceStatistics::clear()
{
   mPolyCount = 0;
   mDrawCalls = 0;
   mRenderTargetChanges = 0;
}

/// Copy from source (should just be a memcpy, but that may change later) used in 
/// conjunction with end to get a subset of statistics.  For example, statistics
/// for a particular render bin.
void GFXDeviceStatistics::start(GFXDeviceStatistics * source)
{
   mPolyCount = source->mPolyCount;
   mDrawCalls = source->mDrawCalls;
   mRenderTargetChanges = source->mRenderTargetChanges;
}

/// Used with start to get a subset of stats on a device.  Basically will do
/// this->mPolyCount = source->mPolyCount - this->mPolyCount.  (Fancy!)
void GFXDeviceStatistics::end(GFXDeviceStatistics * source)
{
   mPolyCount = source->mPolyCount - mPolyCount;
   mDrawCalls = source->mDrawCalls - mDrawCalls;
   mRenderTargetChanges = source->mRenderTargetChanges - mRenderTargetChanges;   
}

/// Exports the stats to the console
void GFXDeviceStatistics::exportToConsole()
{
   Con::setIntVariable(vnPolyCount, mPolyCount);
   Con::setIntVariable(vnDrawCalls, mDrawCalls);
   Con::setIntVariable(vnRenderTargetChanges, mRenderTargetChanges);
}