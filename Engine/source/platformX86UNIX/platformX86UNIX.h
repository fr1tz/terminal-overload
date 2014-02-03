// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMX86UNIX_H_
#define _PLATFORMX86UNIX_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _EVENT_H_
#include "platform/input/event.h"
#endif

#include <stdio.h>
#include <string.h>

// these will be used to construct the user preference directory where
// created files will be stored (~/PREF_DIR_ROOT/PREF_DIR_GAME_NAME)
#define PREF_DIR_ROOT ".garagegames"
#define PREF_DIR_GAME_NAME "torqueDemo"

// event codes for custom SDL events
const S32 TORQUE_SETVIDEOMODE = 1;

extern bool GL_EXT_Init( void );

extern void PlatformBlitInit( void );

// Process Control functions
void Cleanup(bool minimal=false);
void ImmediateShutdown(S32 exitCode, S32 signalNum = 0);
void ProcessControlInit();
bool AcquireProcessMutex(const char *mutexName);

// Utility functions
// Convert a string to lowercase in place
char *strtolwr(char* str);

void DisplayErrorAlert(const char* errMsg, bool showSDLError = true);

// Just like strstr, except case insensitive
// (Found this function at http://www.codeguru.com/string/stristr.html)
extern const char *stristr(const char *szStringToBeSearched, const char *szSubstringToSearchFor);

extern "C"
{
   // x86UNIX doesn't have a way to automatically get the executable file name
   void setExePathName(const char* exePathName);
}
#endif
