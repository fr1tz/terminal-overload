// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/input/leapMotion/leapMotionFrameStore.h"
#include "platform/input/leapMotion/leapMotionFrame.h"
#include "core/module.h"
#include "console/simSet.h"
#include "console/consoleTypes.h"

MODULE_BEGIN( LeapMotionFrameStore )

   MODULE_INIT_AFTER( LeapMotionDevice )
   MODULE_INIT_AFTER( Sim )
   MODULE_SHUTDOWN_BEFORE( Sim )
   MODULE_SHUTDOWN_BEFORE( LeapMotionDevice )

   MODULE_INIT
   {
      LeapMotionFrameStore::staticInit();
      ManagedSingleton< LeapMotionFrameStore >::createSingleton();
   }
   
   MODULE_SHUTDOWN
   {
      ManagedSingleton< LeapMotionFrameStore >::deleteSingleton();
   }

MODULE_END;

S32 LeapMotionFrameStore::smMaximumFramesStored = 30;

SimGroup* LeapMotionFrameStore::smFrameGroup = NULL;

LeapMotionFrameStore::LeapMotionFrameStore()
{
   // Set up the SimGroup to store our frames
   smFrameGroup = new SimGroup();
   smFrameGroup->registerObject("LeapMotionFrameGroup");
   smFrameGroup->setNameChangeAllowed(false);
   Sim::getRootGroup()->addObject(smFrameGroup);
}

LeapMotionFrameStore::~LeapMotionFrameStore()
{
   if(smFrameGroup)
   {
      smFrameGroup->deleteObject();
      smFrameGroup = NULL;
   }
}

void LeapMotionFrameStore::staticInit()
{
   Con::addVariable("LeapMotion::MaximumFramesStored", TypeS32, &smMaximumFramesStored, 
      "@brief The maximum number of frames to keep when $LeapMotion::GenerateWholeFrameEvents is true.\n\n"
	   "@ingroup Game");
}

S32 LeapMotionFrameStore::generateNewFrame(const Leap::Frame& frame, const F32& maxHandAxisRadius)
{
   // Make sure our group has been created
   if(!smFrameGroup)
      return 0;

   // Either create a new frame object or pull one off the end
   S32 frameID = 0;
   if(smFrameGroup->size() >= smMaximumFramesStored)
   {
      // Make the last frame the first and update
      LeapMotionFrame* frameObj = static_cast<LeapMotionFrame*>(smFrameGroup->last());
      smFrameGroup->bringObjectToFront(frameObj);
      frameObj->copyFromFrame(frame, maxHandAxisRadius);
      frameID = frameObj->getId();
   }
   else
   {
      // Create a new frame and add it to the front of the list
      LeapMotionFrame* frameObj = new LeapMotionFrame();
      frameObj->registerObject();
      smFrameGroup->addObject(frameObj);
      smFrameGroup->bringObjectToFront(frameObj);
      frameObj->copyFromFrame(frame, maxHandAxisRadius);
      frameID = frameObj->getId();
   }

   return frameID;
}
