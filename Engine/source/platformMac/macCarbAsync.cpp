// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <CoreServices/CoreServices.h>
#include "platform/async/asyncUpdate.h"


AsyncUpdateThread::AsyncUpdateThread( String name, AsyncUpdateList* updateList )
   : Parent( 0, 0, false, false ),
     mUpdateList( updateList ),
     mName( name )
{
   MPCreateEvent( ( MPEventID* ) &mUpdateEvent );
}

AsyncUpdateThread::~AsyncUpdateThread()
{
   MPDeleteEvent( *( ( MPEventID* ) &mUpdateEvent ) ) ;
}

void AsyncUpdateThread::_waitForEventAndReset()
{
   MPWaitForEvent( *( ( MPEventID* ) &mUpdateEvent ), NULL, kDurationForever ); 
}

void AsyncUpdateThread::triggerUpdate()
{
   MPSetEvent( *( ( MPEventID* ) &mUpdateEvent ), 1 );
}

AsyncPeriodicUpdateThread::AsyncPeriodicUpdateThread
      ( String name, AsyncUpdateList* updateList, U32 intervalMS )
   : Parent( name, updateList ),
     mIntervalMS( intervalMS )
{
}

AsyncPeriodicUpdateThread::~AsyncPeriodicUpdateThread()
{
}

void AsyncPeriodicUpdateThread::_waitForEventAndReset()
{
   MPWaitForEvent( *( ( MPEventID* ) &mUpdateEvent ), NULL, kDurationMillisecond * mIntervalMS );
}
