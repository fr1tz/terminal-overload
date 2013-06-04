// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "unit/test.h"

using namespace UnitTesting;

CreateInteractiveTest(CheckPlatformAlerts, "Platform/Alerts")
{
   void run()
   {
      // Run through all the alert types.
      Platform::AlertOK("Test #1 - AlertOK", "This is a test of Platform::AlertOK. I am a blocking dialog with an OK button. Please hit OK to continue.");
      test(true, "AlertOK should return when the user clicks on it..."); // <-- gratuitous test point.
      
      bool res;
      
      res = Platform::AlertOKCancel("Test #2 - AlertOKCancel", "This is a test of Platform::alertOKCancel. I am a blocking dialog with an OK and a Cancel button. Please hit Cancel to continue.");
      test(res==false,"AlertOKCancel - Didn't get cancel. User error, or just bad code?");
      
      res = Platform::AlertOKCancel("Test #3 - AlertOKCancel", "This is a test of Platform::alertOKCancel. I am a blocking dialog with an OK and a Cancel button. Please hit OK to continue.");
      test(res==true,"AlertOKCancel - Didn't get ok. User error, or just bad code?");
      
      res = Platform::AlertRetry("Test #4 - AlertRetry", "This is a test of Platform::AlertRetry. I am a blocking dialog with an Retry and a Cancel button. Please hit Retry to continue.");
      test(res==true,"AlertRetry - Didn't get retry. User error, or just bad code?");

      res = Platform::AlertRetry("Test #5 - AlertRetry", "This is a test of Platform::AlertRetry. I am a blocking dialog with an Retry and a Cancel button. Please hit Cancel to continue.");
      test(res==false,"AlertRetry - Didn't get cancel. User error, or just bad code?");
   }
};