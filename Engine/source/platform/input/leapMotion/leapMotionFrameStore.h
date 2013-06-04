// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LEAPMOTIONFRAMESTORE_H_
#define _LEAPMOTIONFRAMESTORE_H_

#include "platformWin32/platformWin32.h"
#include "Leap.h"

class SimGroup;

class LeapMotionFrameStore
{
public:
   // The maximum number of frames to keep
   static S32 smMaximumFramesStored;

   static SimGroup* smFrameGroup;

public:
   LeapMotionFrameStore();
   virtual ~LeapMotionFrameStore();

   static void staticInit();

   static bool isFrameGroupDefined() { return smFrameGroup != NULL; }
   static SimGroup* getFrameGroup() { return smFrameGroup; }

   S32 generateNewFrame(const Leap::Frame& frame, const F32& maxHandAxisRadius);

public:
   // For ManagedSingleton.
   static const char* getSingletonName() { return "LeapMotionFrameStore"; }   
};

/// Returns the LeapMotionFrameStore singleton.
#define LEAPMOTIONFS ManagedSingleton<LeapMotionFrameStore>::instance()

#endif   // _LEAPMOTIONFRAMESTORE_H_
