// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platformTLS.h"
#include "platformWin32/platformWin32.h"
#include "core/util/safeDelete.h"

#define TORQUE_ALLOC_STORAGE(member, cls, data) \
   AssertFatal(sizeof(cls) <= sizeof(data), avar("Error, storage for %s must be %d bytes.", #cls, sizeof(cls))); \
   member = (cls *) data; \
   constructInPlace(member)

//-----------------------------------------------------------------------------

struct PlatformThreadStorage
{
   DWORD mTlsIndex;
};

//-----------------------------------------------------------------------------

ThreadStorage::ThreadStorage()
{
   TORQUE_ALLOC_STORAGE(mThreadStorage, PlatformThreadStorage, mStorage);
   mThreadStorage->mTlsIndex = TlsAlloc();
}

ThreadStorage::~ThreadStorage()
{
   TlsFree(mThreadStorage->mTlsIndex);
   destructInPlace(mThreadStorage);
}

void *ThreadStorage::get()
{
   return TlsGetValue(mThreadStorage->mTlsIndex);
}

void ThreadStorage::set(void *value)
{
   TlsSetValue(mThreadStorage->mTlsIndex, value);
}

/* POSIX IMPLEMENTATION LOOKS LIKE THIS:

class PlatformThreadStorage
{
pthread_key_t mThreadKey;
};

ThreadStorage::ThreadStorage()
{
TORQUE_ALLOC_STORAGE(mThreadStorage, PlatformThreadStorage, mStorage);
pthread_key_create(&mThreadStorage->mThreadKey, NULL);
}

ThreadStorage::~ThreadStorage()
{
pthread_key_delete(mThreadStorage->mThreadKey);
}

void *ThreadStorage::get()
{
return pthread_getspecific(mThreadStorage->mThreadKey);
}

void ThreadStorage::set(void *value)
{
pthread_setspecific(mThreadStorage->mThreadKey, value);
}
*/