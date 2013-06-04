// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/threads/mutex.h"
#include "platformWin32/platformWin32.h"
#include "core/util/safeDelete.h"

//-----------------------------------------------------------------------------
// Mutex Data
//-----------------------------------------------------------------------------

struct PlatformMutexData
{
   CRITICAL_SECTION mCriticalSection;
};

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------

Mutex::Mutex()
{
   mData = new PlatformMutexData;
   InitializeCriticalSection( &mData->mCriticalSection );
}

Mutex::~Mutex()
{
   AssertFatal( TryEnterCriticalSection( &mData->mCriticalSection ), "Mutex::~Mutex - Critical section is locked!" );
   DeleteCriticalSection( &mData->mCriticalSection );
   SAFE_DELETE( mData );
}

//-----------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------

bool Mutex::lock( bool block )
{
   AssertFatal( mData, "Mutex::lock - No data!" );

   if( !block )
      return TryEnterCriticalSection( &mData->mCriticalSection );
   else
   {
      EnterCriticalSection( &mData->mCriticalSection );
      return true;
   }
}

void Mutex::unlock()
{
   AssertFatal( mData, "Mutex::unlock - No data!" );
   LeaveCriticalSection( &mData->mCriticalSection );
}
