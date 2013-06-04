// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RAZERHYDRAFRAMESTORE_H_
#define _RAZERHYDRAFRAMESTORE_H_

#include "platform/types.h"
#include "sixense.h"

class SimGroup;

class RazerHydraFrameStore
{
public:
   // The maximum number of frames to keep
   static S32 smMaximumFramesStored;

   static SimGroup* smFrameGroup;

public:
   RazerHydraFrameStore();
   virtual ~RazerHydraFrameStore();

   static void staticInit();

   static bool isFrameGroupDefined() { return smFrameGroup != NULL; }
   static SimGroup* getFrameGroup() { return smFrameGroup; }

   S32 generateNewFrame(const sixenseAllControllerData& frame, const F32& maxAxisRadius);

public:
   // For ManagedSingleton.
   static const char* getSingletonName() { return "RazerHydraFrameStore"; }   
};

/// Returns the LeapMotionFrameStore singleton.
#define RAZERHYDRAFS ManagedSingleton<RazerHydraFrameStore>::instance()

#endif   // _RAZERHYDRAFRAMESTORE_H_
