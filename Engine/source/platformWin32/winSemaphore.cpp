// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformWin32/platformWin32.h"
#include "platform/threads/semaphore.h"

class PlatformSemaphore
{
public:
   HANDLE   *semaphore;

   PlatformSemaphore(S32 initialCount)
   {
      semaphore = new HANDLE;
      *semaphore = CreateSemaphore(0, initialCount, S32_MAX, 0);
   }

   ~PlatformSemaphore()
   {
      CloseHandle(*(HANDLE*)(semaphore));
      delete semaphore;
      semaphore = NULL;
   }
};

Semaphore::Semaphore(S32 initialCount)
{
   mData = new PlatformSemaphore(initialCount);
}

Semaphore::~Semaphore()
{
   AssertFatal(mData && mData->semaphore, "Semaphore::destroySemaphore: invalid semaphore");
   delete mData;
}

bool Semaphore::acquire(bool block, S32 timeoutMS)
{
   AssertFatal(mData && mData->semaphore, "Semaphore::acquireSemaphore: invalid semaphore");
   if(block)
   {
      WaitForSingleObject(*(HANDLE*)(mData->semaphore), timeoutMS != -1 ? timeoutMS : INFINITE );
      return(true);
   }
   else
   {
      DWORD result = WaitForSingleObject(*(HANDLE*)(mData->semaphore), 0);
      return(result == WAIT_OBJECT_0);
   }
}

void Semaphore::release()
{
   AssertFatal(mData && mData->semaphore, "Semaphore::releaseSemaphore: invalid semaphore");
   ReleaseSemaphore(*(HANDLE*)(mData->semaphore), 1, 0);
}
