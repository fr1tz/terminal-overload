// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "util/fpsTracker.h"
#include "console/console.h"

FPSTracker gFPS;

FPSTracker::FPSTracker()
{
   mUpdateInterval = 0.25f;
   reset();
}

void FPSTracker::reset()
{
   fpsNext         = (F32)Platform::getRealMilliseconds()/1000.0f + mUpdateInterval;

   fpsRealLast       = 0.0f;
   fpsReal           = 0.0f;
   fpsRealMin        = 0.000001f; // Avoid division by zero.
   fpsRealMax        = 1.0f;
   fpsVirtualLast    = 0.0f;
   fpsVirtual        = 0.0f;
   fpsFrames         = 0;
}

void FPSTracker::update()
{
   const float alpha  = 0.07f;
   F32 realSeconds    = (F32)Platform::getRealMilliseconds()/1000.0f;
   F32 virtualSeconds = (F32)Platform::getVirtualMilliseconds()/1000.0f;

   fpsFrames++;
   if (fpsFrames > 1)
   {
      fpsReal    = fpsReal*(1.0-alpha) + (realSeconds-fpsRealLast)*alpha;
      fpsVirtual = fpsVirtual*(1.0-alpha) + (virtualSeconds-fpsVirtualLast)*alpha;

      if( fpsFrames > 10 ) // Wait a few frames before updating these.
      {
         // Update min/max.  This is a bit counter-intuitive, as the comparisons are
         // inversed because these are all one-over-x values.

         if( fpsReal > fpsRealMin )
            fpsRealMin = fpsReal;
         if( fpsReal < fpsRealMax )
            fpsRealMax = fpsReal;
      }
   }

   fpsRealLast    = realSeconds;
   fpsVirtualLast = virtualSeconds;

   // update variables every few frames
   F32 update = fpsRealLast - fpsNext;
   if (update > 0.5f)
   {
      Con::setVariable( "fps::real",      avar( "%4.1f", 1.0f / fpsReal ) );
      Con::setVariable( "fps::realMin",   avar( "%4.1f", 1.0f / fpsRealMin ) );
      Con::setVariable( "fps::realMax",   avar( "%4.1f", 1.0f / fpsRealMax ) );
      Con::setVariable( "fps::virtual",   avar( "%4.1f", 1.0f / fpsVirtual ) );

      if (update > mUpdateInterval)
         fpsNext  = fpsRealLast + mUpdateInterval;
      else
         fpsNext += mUpdateInterval;
   }
}

ConsoleFunction( resetFPSTracker, void, 1, 1, "()"
   "@brief Reset FPS stats (fps::)\n\n"
   "@ingroup Game")
{
   gFPS.reset();
}
