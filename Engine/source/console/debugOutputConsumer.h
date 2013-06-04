// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _DEBUGOUTPUTCONSUMER_H_
#define _DEBUGOUTPUTCONSUMER_H_

#include "platform/platform.h"

//#define TORQUE_LOCBUILD

#if !defined(TORQUE_DEBUG) && defined(TORQUE_OS_XENON) && !defined(TORQUE_LOCBUILD)
#define DISABLE_DEBUG_SPEW
#endif

#include "console/console.h"

namespace DebugOutputConsumer
{
   extern bool debugOutputEnabled;

   void init();
   void destroy();
   void logCallback( U32 level, const char *consoleLine );

   void enableDebugOutput( bool enable = true );
};

#endif