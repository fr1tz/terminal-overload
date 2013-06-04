// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _APP_MAINLOOP_H_
#define _APP_MAINLOOP_H_

#include "platform/platform.h"

/// Support class to simplify the process of writing a main loop for Torque apps.
class StandardMainLoop
{
public:
   /// Initialize core libraries and call registered init functions
   static void init();

   /// Pass command line arguments to registered functions and main.cs
   static bool handleCommandLine(S32 argc, const char **argv);

   /// A standard mainloop implementation.
   static bool doMainLoop();

   /// Shut down the core libraries and call registered shutdown fucntions.
   static void shutdown();

   static void setRestart( bool restart );
   static bool requiresRestart();

private:
   /// Handle "pre shutdown" tasks like notifying scripts BEFORE we delete
   /// stuff from under them.
   static void preShutdown();
};

#endif