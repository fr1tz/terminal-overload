// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformX86UNIX/platformX86UNIX.h"
#include "platform/threads/semaphore.h"
// Instead of that mess that was here before, lets use the SDL lib to deal
// with the semaphores.

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

struct PlatformSemaphore
{
   SDL_sem *semaphore;

   PlatformSemaphore(S32 initialCount)
   {
       semaphore = SDL_CreateSemaphore(initialCount);
       AssertFatal(semaphore, "PlatformSemaphore constructor - Failed to create SDL Semaphore.");
   }

   ~PlatformSemaphore()
   {
       SDL_DestroySemaphore(semaphore);
   }
};

Semaphore::Semaphore(S32 initialCount)
{
  mData = new PlatformSemaphore(initialCount);
}

Semaphore::~Semaphore()
{
  AssertFatal(mData, "Semaphore destructor - Invalid semaphore.");
  delete mData;
}

bool Semaphore::acquire(bool block, S32 timeoutMS)
{
   AssertFatal(mData && mData->semaphore, "Semaphore::acquire - Invalid semaphore.");
   if (block)
   {
      // Semaphore acquiring is different from the MacOS/Win realization because SDL_SemWaitTimeout() with "infinite" timeout can be too heavy on some platforms.
      // (see "man SDL_SemWaitTimeout(3)" for more info)
      // "man" states to avoid the use of SDL_SemWaitTimeout at all, but at current stage this looks like a valid and working solution, so keeping it this way.
      // [bank / Feb-2010]
      if (timeoutMS == -1)
      {
         if (SDL_SemWait(mData->semaphore) < 0)
            AssertFatal(false, "Semaphore::acquie - Wait failed.");
      }
      else
      {
         if (SDL_SemWaitTimeout(mData->semaphore, timeoutMS) < 0)
            AssertFatal(false, "Semaphore::acquie - Wait with timeout failed.");
      }
      return (true);
   }
   else
   {
      int res = SDL_SemTryWait(mData->semaphore);
      return (res == 0);
   }
}

void Semaphore::release()
{
   AssertFatal(mData, "Semaphore::releaseSemaphore - Invalid semaphore.");
   SDL_SemPost(mData->semaphore);
}
