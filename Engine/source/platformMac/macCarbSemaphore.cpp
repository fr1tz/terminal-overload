// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <CoreServices/CoreServices.h>
#include "platform/platform.h"
#include "platform/threads/semaphore.h"

class PlatformSemaphore
{
public:
   MPSemaphoreID mSemaphore;

   PlatformSemaphore(S32 initialCount)
   {
      OSStatus err = MPCreateSemaphore(S32_MAX - 1, initialCount, &mSemaphore);
      AssertFatal(err == noErr, "Failed to allocate semaphore!");
   }

   ~PlatformSemaphore()
   {
      OSStatus err = MPDeleteSemaphore(mSemaphore);
      AssertFatal(err == noErr, "Failed to destroy semaphore!");
   }
};

Semaphore::Semaphore(S32 initialCount)
{
   mData = new PlatformSemaphore(initialCount);
}

Semaphore::~Semaphore()
{
   AssertFatal(mData && mData->mSemaphore, "Semaphore::destroySemaphore: invalid semaphore");
   delete mData;
}

bool Semaphore::acquire( bool block, S32 timeoutMS )
{
   AssertFatal(mData && mData->mSemaphore, "Semaphore::acquireSemaphore: invalid semaphore");
   OSStatus err = MPWaitOnSemaphore(mData->mSemaphore, block ? ( timeoutMS == -1 ? kDurationForever : timeoutMS ) : kDurationImmediate);
   return(err == noErr);
}

void Semaphore::release()
{
   AssertFatal(mData && mData->mSemaphore, "Semaphore::releaseSemaphore: invalid semaphore");
   OSStatus err = MPSignalSemaphore(mData->mSemaphore);
   AssertFatal(err == noErr, "Failed to release semaphore!");
}
