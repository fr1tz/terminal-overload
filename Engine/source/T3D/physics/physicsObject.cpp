// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/physics/physicsObject.h"

#include "console/simEvents.h"
#include "console/simSet.h"


PhysicsObject::PhysicsObject()
   : mQueuedEvent( InvalidEventId )
{
}

PhysicsObject::~PhysicsObject()
{
   if ( mQueuedEvent != InvalidEventId )
      Sim::cancelEvent( mQueuedEvent );
}

void PhysicsObject::queueCallback( U32 ms, Delegate<void()> callback )
{
   // Cancel any existing event we may have pending.
   if ( mQueuedEvent != InvalidEventId )
      Sim::cancelEvent( mQueuedEvent );

   // Fire off a new event.
   SimDelegateEvent *event_ = new SimDelegateEvent();
   event_->mCallback = callback;
   event_->mEventId = &mQueuedEvent;
   mQueuedEvent = Sim::postEvent( Sim::getRootGroup(), event_, Sim::getCurrentTime() + ms );
}
