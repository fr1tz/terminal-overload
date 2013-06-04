// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/async/asyncUpdate.h"
#include "core/stream/tStream.h"


//-----------------------------------------------------------------------------
//    AsyncUpdateList implementation.
//-----------------------------------------------------------------------------

void AsyncUpdateList::process( S32 timeOut )
{
   U32 endTime = 0;
   if( timeOut != -1 )
      endTime = Platform::getRealMilliseconds() + timeOut;

   // Flush the process list.

   IPolled* ptr;
   IPolled* firstProcessedPtr = 0;

   while( mUpdateList.tryPopFront( ptr ) )
   {
      if( ptr == firstProcessedPtr )
      {
         // We've wrapped around.  Stop.

         mUpdateList.pushFront( ptr );
         break;
      }

      if( ptr->update() )
      {
         mUpdateList.pushBack( ptr );

         if( !firstProcessedPtr )
            firstProcessedPtr = ptr;
      }

      // Stop if we have exceeded our processing time budget.

      if( timeOut != -1
          && Platform::getRealMilliseconds() >= endTime )
         break;
   }
}

//--------------------------------------------------------------------------
//    AsyncUpdateThread implementation.
//--------------------------------------------------------------------------

void AsyncUpdateThread::run( void* )
{
   _setName( getName() );

   while( !checkForStop() )
   {
      _waitForEventAndReset();
      
      if( !checkForStop() )
         mUpdateList->process();
   }
}
