// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "platform/platformInput.h"
#include "console/console.h"

#include "platformX86UNIX/platformX86UNIX.h"
#include "platformX86UNIX/x86UNIXStdConsole.h"
#include "platformX86UNIX/x86UNIXState.h"

extern void InitWindowingSystem();

//------------------------------------------------------------------------------
void Platform::init()
{
   StdConsole::create();
   stdConsole->enable(true);

   // init process control stuff
   ProcessControlInit();

   Con::printf("Initializing platform...");

   // Set the platform variable for the scripts
   Con::setVariable( "$platform", "x86UNIX" );
#if defined(__linux__)
   Con::setVariable( "$platformUnixType", "Linux" );
#elif defined(__OpenBSD__)
   Con::setVariable( "$platformUnixType", "OpenBSD" );
#else
   Con::setVariable( "$platformUnixType", "Unknown" );
#endif

   Input::init();

   //installRedBookDevices();

#ifndef TORQUE_DEDICATED
   // if we're not dedicated do more initialization
   InitWindowingSystem();
#endif
}

//------------------------------------------------------------------------------
void Platform::shutdown()
{
   Cleanup();
}

//------------------------------------------------------------------------------


extern "C"
{
   bool torque_engineinit(int argc, const char **argv);
   int  torque_enginetick();
   S32  torque_getreturnstatus();
   bool torque_engineshutdown();

   int torque_unixmain(int argc, const char **argv)
   {
     if (!torque_engineinit(argc, argv))
         return 1;

     while(torque_enginetick())
     {

     }

     torque_engineshutdown();

     return torque_getreturnstatus();

   }
}

extern S32 TorqueMain(S32 argc, const char **argv);

#if !defined(TORQUE_SHARED)
int main(int argc, const char **argv)
{
   return TorqueMain(argc, argv);
}
#endif
