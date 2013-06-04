// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMWIN32_H_
#define _PLATFORMWIN32_H_

// Sanity check for UNICODE
#ifdef TORQUE_UNICODE
#  ifndef UNICODE
#     error "ERROR: You must have UNICODE defined in your preprocessor settings (ie, /DUNICODE) if you have TORQUE_UNICODE enabled in torqueConfig.h!"
#  endif
#endif

#include <windows.h>
#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _MRECT_H_
#include "math/mRect.h"
#endif

#if defined(TORQUE_COMPILER_CODEWARRIOR)
#  include <ansi_prefix.win32.h>
#  include <stdio.h>
#  include <string.h>
#else
#  include <stdio.h>
#  include <string.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4996) // turn off "deprecation" warnings
#endif

#define NOMINMAX

// Hack to get a correct HWND instead of using global state.
extern HWND getWin32WindowHandle();

struct Win32PlatState
{
   FILE *log_fp;
   HINSTANCE hinstOpenGL;
   HINSTANCE hinstGLU;
   HINSTANCE hinstOpenAL;
   HWND appWindow;
   HDC appDC;
   HINSTANCE appInstance;
   HGLRC hGLRC;
   DWORD processId;
   bool renderThreadBlocked;
   S32 nMessagesPerFrame; ///< The max number of messages to dispatch per frame
   HMENU appMenu; ///< The menu bar for the window
#ifdef UNICODE
   //HIMC imeHandle;
#endif

   S32 desktopBitsPixel;
   S32 desktopWidth;
   S32 desktopHeight;
   S32 desktopClientWidth;
   S32 desktopClientHeight;
   U32 currentTime;
   
   // minimum time per frame
   U32 sleepTicks;
   // are we in the background?
   bool backgrounded;

   Win32PlatState();
};

extern Win32PlatState winState;

extern void setModifierKeys( S32 modKeys );

//-------------------------------------- Helper Functions

template< typename T >
inline void forwardslashT( T *str )
{
   while(*str)
   {
      if(*str == '\\')
         *str = '/';
      str++;
   }
}

inline void forwardslash( char* str )
{
   forwardslashT< char >( str );
}
inline void forwardslash( WCHAR* str )
{
   forwardslashT< WCHAR >( str );
}

template< typename T >
inline void backslashT( T *str )
{
   while(*str)
   {
      if(*str == '/')
         *str = '\\';
      str++;
   }
}

inline void backslash( char* str )
{
   backslashT< char >( str );
}
inline void backslash( WCHAR* str )
{
   backslashT< WCHAR >( str );
}

#endif //_PLATFORMWIN32_H_
