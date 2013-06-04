// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <Cocoa/Cocoa.h>
#include "app/mainLoop.h"
#include "platform/platformInput.h"
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>
#include "console/console.h"
#include "platform/threads/thread.h"

// TODO: let the mainLoop's sleep time happen via rescheduling the timer every run-through.
extern S32 sgTimeManagerProcessInterval;

@interface MainLoopTimerHandler : NSObject
{
   U32 argc;
   const char** argv;
   NSTimeInterval interval;
}
   +(id)startTimerWithintervalMs:(U32)intervalMs argc:(U32)_argc argv:(const char**)_argv;
   -(void)firstFire:(NSTimer*)theTimer;
   -(void)fireTimer:(NSTimer*)theTimer;
@end
@implementation MainLoopTimerHandler
   -(void)firstFire:(NSTimer*)theTimer
   {
      StandardMainLoop::init();
      StandardMainLoop::handleCommandLine(argc, argv);
      [NSTimer scheduledTimerWithTimeInterval:interval target:self selector:@selector(fireTimer:) userInfo:nil repeats:YES];
   }
   -(void)fireTimer:(NSTimer*)theTimer
   {
      if(!StandardMainLoop::doMainLoop())
      {
         StandardMainLoop::shutdown();
         [theTimer invalidate];
         [NSApp setDelegate:nil];
         [NSApp terminate:self];
      }
//      if(!mainLoop || !mainLoop->mainLoop())
//      {
//         // stop the timer from firing again
//         if(mainLoop)
//            mainLoop->shutdown();
//            
//         [theTimer invalidate];
//         [NSApp setDelegate:nil];
//         [NSApp terminate:self];
//      }
   }
   +(id)startTimerWithintervalMs:(U32)intervalMs argc:(U32)_argc argv:(const char**)_argv
   {
      MainLoopTimerHandler* handler = [[[MainLoopTimerHandler alloc] init] autorelease];
      handler->argc = _argc;
      handler->argv = _argv;
      handler->interval = intervalMs / 1000.0; // interval in milliseconds
      [NSTimer scheduledTimerWithTimeInterval:handler->interval target:handler selector:@selector(firstFire:) userInfo:nil repeats:NO];
      return handler;
   }
@end

#pragma mark -

#ifndef TORQUE_SHARED
//-----------------------------------------------------------------------------
// main() - the real one - this is the actual program entry point.
//-----------------------------------------------------------------------------
S32 main(S32 argc, const char **argv)
{   
   NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

   // get command line and text file args, filter them
      
   // now, we prepare to hand off execution to torque & macosx.
   U32 appReturn = 0;         
   printf("installing torque main loop timer\n");
   [MainLoopTimerHandler startTimerWithintervalMs:1 argc:argc argv:argv];
   printf("starting NSApplicationMain\n");
   appReturn = NSApplicationMain(argc, argv);
   printf("NSApplicationMain exited\n");
   
   // shut down the engine
   
   [pool release];

   return appReturn;
}

#endif

static NSApplication *app = NULL;
static NSAutoreleasePool* pool = NULL;

void torque_mac_engineinit(S32 argc, const char **argv)
{
   
   if (!Platform::getWebDeployment())
   {
      pool = [[NSAutoreleasePool alloc] init];
      app = [NSApplication sharedApplication];
   }
   
}

void torque_mac_enginetick()
{

   if (!Platform::getWebDeployment())
   {
          
      NSEvent *e = [app nextEventMatchingMask: NSAnyEventMask
                        untilDate: [NSDate distantPast] 
                        inMode: NSDefaultRunLoopMode
                        dequeue: YES];
      if (e)
         [app sendEvent: e];

   }
}

void torque_mac_engineshutdown()
{
   if (!Platform::getWebDeployment())
   {
      [pool release];
   }
}


extern "C" {

//-----------------------------------------------------------------------------
// torque_macmain() - entry point for application using bundle
//-----------------------------------------------------------------------------
S32 torque_macmain(S32 argc, const char **argv)
{   
   NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

   // get command line and text file args, filter them
      
   // now, we prepare to hand off execution to torque & macosx.
   U32 appReturn = 0;         
   printf("installing torque main loop timer\n");
   [MainLoopTimerHandler startTimerWithintervalMs:1 argc:argc argv:argv];
   printf("starting NSApplicationMain\n");
   appReturn = NSApplicationMain(argc, argv);
   printf("NSApplicationMain exited\n");
   
   // shut down the engine
   
   [pool release];

   return appReturn;
}

} // extern "C"



#pragma mark ---- Init funcs  ----
//------------------------------------------------------------------------------
void Platform::init()
{
   // Set the platform variable for the scripts
   Con::setVariable( "$platform", "macos" );

   Input::init();
}

//------------------------------------------------------------------------------
void Platform::shutdown()
{
   Input::destroy();
}
