// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/console.h"
#include "platformX86UNIX/platformX86UNIX.h"
#include "platform/threads/mutex.h"
#include "core/util/safeDelete.h"

#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

struct PlatformMutexData
{
   pthread_mutex_t mutex;
};

Mutex::Mutex()
{
   mData = new PlatformMutexData;
   pthread_mutexattr_t attr;

   pthread_mutexattr_init(&attr);
   pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);

   pthread_mutex_init(&mData->mutex, &attr);
}

Mutex::~Mutex()
{
   AssertFatal(mData, "Mutex::destroyMutex: invalid mutex");
   pthread_mutex_destroy(&mData->mutex);
   SAFE_DELETE(mData);
}

bool Mutex::lock(bool block)
{
   if(mData == NULL)
      return false;
   if(block)
   {
	   return pthread_mutex_lock(&mData->mutex) == 0;
   }
   else
   {
	   return pthread_mutex_trylock(&mData->mutex) == 0;
   }
}

void Mutex::unlock()
{
   if(mData == NULL)
      return;
   pthread_mutex_unlock(&mData->mutex);
}
