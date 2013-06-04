// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/iTickable.h"

// The statics
U32 ITickable::smLastTick = 0;
U32 ITickable::smLastTime = 0;
U32 ITickable::smLastDelta = 0;

U32 ITickable::smTickShift = 5;
U32 ITickable::smTickMs = ( 1 << smTickShift );
F32 ITickable::smTickSec = ( F32( ITickable::smTickMs ) / 1000.f );
U32 ITickable::smTickMask = ( smTickMs - 1 );

//------------------------------------------------------------------------------

ITickable::ITickable() : mProcessTick( true )
{
   getProcessList().push_back( this );
}

//------------------------------------------------------------------------------

ITickable::~ITickable()
{
   for( ProcessListIterator i = getProcessList().begin(); i != getProcessList().end(); i++ )
   {
      if( (*i) == this )
      {
         getProcessList().erase( i );
         return;
      }
   }
}

//------------------------------------------------------------------------------

void ITickable::init( const U32 tickShift )
{
    // Sanity!
    AssertFatal( tickShift == 0 || tickShift <= 31, "ITickable::init() - Invalid 'tickShift' parameter!" );

    // Calculate tick constants.
    smTickShift = tickShift;
    smTickMs = ( 1 << smTickShift );
    smTickSec = ( F32( smTickMs ) / 1000.f );
    smTickMask = ( smTickMs - 1 );
}

//------------------------------------------------------------------------------

Vector<ITickable *>& ITickable::getProcessList()
{
   // This helps to avoid the static initialization order fiasco
   static Vector<ITickable *> smProcessList( __FILE__, __LINE__ ); ///< List of tick controls
   return smProcessList;
}

//------------------------------------------------------------------------------

bool ITickable::advanceTime( U32 timeDelta )
{
   U32 targetTime = smLastTime + timeDelta;
   U32 targetTick = ( targetTime + smTickMask ) & ~smTickMask;
   U32 tickCount = ( targetTick - smLastTick ) >> smTickShift;

   // Advance objects
   if( tickCount )
      for( ; smLastTick != targetTick; smLastTick += smTickMs )
         for( ProcessListIterator i = getProcessList().begin(); i != getProcessList().end(); i++ )
            if( (*i)->isProcessingTicks() )
               (*i)->processTick();

   smLastDelta = ( smTickMs - ( targetTime & smTickMask ) ) & smTickMask;
   F32 dt = smLastDelta / F32( smTickMs );

   // Now interpolate objects that want ticks
   for( ProcessListIterator i = getProcessList().begin(); i != getProcessList().end(); i++ )
      if( (*i)->isProcessingTicks() )
         (*i)->interpolateTick( dt );


   // Inform ALL objects that time was advanced
   dt = F32( timeDelta ) / 1000.f;
   for( ProcessListIterator i = getProcessList().begin(); i != getProcessList().end(); i++ )
      (*i)->advanceTime( dt );

   smLastTime = targetTime;

   return tickCount != 0;
}
