// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// For VS2005.
#define _WIN32_WINNT 0x501
#ifndef TORQUE_OS_XENON
#include "platformWin32/platformWin32.h"
#endif
#include "platform/async/asyncUpdate.h"


AsyncUpdateThread::AsyncUpdateThread( String name, AsyncUpdateList* updateList )
   : Parent( 0, 0, false, false ),
     mUpdateList( updateList ),
     mName( name )
{
   // Create an auto-reset event in non-signaled state.
   mUpdateEvent = CreateEvent( NULL, false, false, NULL );
}

AsyncUpdateThread::~AsyncUpdateThread()
{
   CloseHandle( ( HANDLE ) mUpdateEvent );
}

void AsyncUpdateThread::_waitForEventAndReset()
{
   WaitForSingleObject( ( HANDLE ) mUpdateEvent, INFINITE );
}

void AsyncUpdateThread::triggerUpdate()
{
   SetEvent( ( HANDLE ) mUpdateEvent );
}

AsyncPeriodicUpdateThread::AsyncPeriodicUpdateThread( String name,
                                                      AsyncUpdateList* updateList,
                                                      U32 intervalMS )
   : Parent( name, updateList )
{
   mUpdateTimer = CreateWaitableTimer( NULL, FALSE, NULL );

   // This is a bit contrived.  The 'dueTime' is in 100 nanosecond intervals
   // and relative if it is negative.  The period is in milliseconds.

   LARGE_INTEGER deltaTime;
   deltaTime.QuadPart = - LONGLONG( intervalMS * 10 /* micro */ * 1000 /* milli */ );

   SetWaitableTimer( ( HANDLE ) mUpdateTimer, &deltaTime, intervalMS, NULL, NULL, FALSE );
}

AsyncPeriodicUpdateThread::~AsyncPeriodicUpdateThread()
{
   CloseHandle( ( HANDLE ) mUpdateTimer );
}

void AsyncPeriodicUpdateThread::_waitForEventAndReset()
{
   HANDLE handles[ 2 ];
   
   handles[ 0 ] = ( HANDLE ) mUpdateEvent;
   handles[ 1 ] = ( HANDLE ) mUpdateTimer;

   WaitForMultipleObjects( 2, handles, FALSE, INFINITE );
}
