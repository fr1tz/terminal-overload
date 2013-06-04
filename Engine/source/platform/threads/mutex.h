// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/types.h"
#include "platform/platformAssert.h"

#ifndef _PLATFORM_THREADS_MUTEX_H_
#define _PLATFORM_THREADS_MUTEX_H_

// Forward ref used by platform code
struct PlatformMutexData;

class Mutex
{
protected:
   PlatformMutexData *mData;

public:
   Mutex();
   virtual ~Mutex();

   virtual bool lock(bool block = true);
   virtual void unlock();

   // Old API so that we don't have to change a load of code
   static void *createMutex()
   {
      Mutex *mutex = new Mutex;
      return (void *)mutex;
   }

   static void destroyMutex(void *mutex)
   {
      Mutex *realMutex = reinterpret_cast<Mutex *>(mutex);
      delete realMutex;
   }

   static bool lockMutex(void *mutex, bool block = true)
   {
      Mutex *realMutex = reinterpret_cast<Mutex *>(mutex);
      return realMutex->lock(block);
   }

   static void unlockMutex(void *mutex)
   {
      Mutex *realMutex = reinterpret_cast<Mutex *>(mutex);
      realMutex->unlock();
   }
};

/// Helper for simplifying mutex locking code.
///
/// This class will automatically unlock a mutex that you've
/// locked through it, saving you from managing a lot of complex
/// exit cases. For instance:
///
/// @code
/// MutexHandle handle;
/// handle.lock(myMutex);
///
/// if(error1)
///   return; // Auto-unlocked by handle if we leave here - normally would
///           // leave the mutex locked, causing much pain later.
///
/// handle.unlock();
/// @endcode
class MutexHandle
{
private:
   void *mMutexPtr;

public:
   MutexHandle()
      : mMutexPtr(NULL)
   {
   }

   ~MutexHandle()
   {
      if(mMutexPtr)
         unlock();
   }

   bool lock(void *mutex, bool blocking=false)
   {
      AssertFatal(!mMutexPtr, "MutexHandle::lock - shouldn't be locking things twice!");

      bool ret = Mutex::lockMutex(mutex, blocking);

      if(ret)
      {
         // We succeeded, do book-keeping.
         mMutexPtr = mutex;
      }

      return ret;
   }

   void unlock()
   {
      if(mMutexPtr)
      {
         Mutex::unlockMutex(mMutexPtr);
         mMutexPtr = NULL;
      }
   }

};

#endif // _PLATFORM_THREADS_MUTEX_H_
