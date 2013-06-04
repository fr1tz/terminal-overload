// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/debugOutputConsumer.h"

namespace DebugOutputConsumer
{
#ifndef DISABLE_DEBUG_SPEW
bool debugOutputEnabled = true;
#else
bool debugOutputEnabled = false;
#endif


void init()
{
   Con::addConsumer( DebugOutputConsumer::logCallback );
}

void destroy()
{
   Con::removeConsumer( DebugOutputConsumer::logCallback );
}

void logCallback( U32 level, const char *consoleLine )
{
   TORQUE_UNUSED(level);
   if( debugOutputEnabled )
   {
      Platform::outputDebugString( "%s", consoleLine );
   }
}

}
