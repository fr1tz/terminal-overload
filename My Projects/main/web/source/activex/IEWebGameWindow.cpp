// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "StdAfx.h"
#include <shlobj.h>
#include "IEWebGameWindow.h"
#include "../common/webCommon.h"


// We hook the keyboard at application level so we TAB, Backspace, other accelerator combos 
// are captured and don't cause us grief
static HHOOK hHook = NULL;

// Hook procedure for WH_GETMESSAGE hook type.
LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
   // If this is a keystrokes message, translate it in controls'
   LPMSG lpMsg = (LPMSG) lParam;
   if( (nCode >= 0) &&
      PM_REMOVE == wParam &&
      (lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST) )
   {
      if (torque_directmessage)
      {         
         // call directly into the Torque 3D message queue, bypassing the windows event queue 
         // as we're hooking into the application level processing, this would cause a hang
         torque_directmessage(lpMsg->message, lpMsg->wParam, lpMsg->lParam);

         // The value returned from this hookproc is ignored, and it cannot
         // be used to tell Windows the message has been handled. To avoid
         // further processing, convert the message to WM_NULL before
         // returning.
         lpMsg->message = WM_NULL;
         lpMsg->lParam = 0L;
         lpMsg->wParam = 0;
      }
   }

   // Passes the hook information to the next hook procedure in
   // the current hook chain.
   return ::CallNextHookEx(hHook, nCode, wParam, lParam);
}




WebGameWindow::WebGameWindow(void)
{
   mTimer = false;   
   mInitialized = false;
}

WebGameWindow::~WebGameWindow(void)
{
   //handling threads in event callbacks (onDestroy for instance) seems to cause loads of problems (deadlocks, etc)
   if (mInitialized)
      WebCommon::ShutdownTorque3D();
}

// we use a timer to update the Torque 3D game loop (tick) and handle rendering
VOID CALLBACK MyTimerProc( 
                          HWND hwnd,        // handle to window for timer messages 
                          UINT message,     // WM_TIMER message 
                          UINT idTimer,     // timer identifier 
                          DWORD dwTime)     // current system time 
{ 
   static bool reentrant = false;

   if (!reentrant)
   {
      reentrant = true;
      torque_enginetick();
      reentrant = false;
   }
} 

LRESULT 
WebGameWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

   bHandled = TRUE;

   // check that the domain we're loading the plugin from is allowed
   if (!checkDomain())
   {
      return -1;
   }

   // load up the Torque 3D shared library and initialize it
   if (!WebCommon::InitTorque3D(this->m_hWnd))
   {
      return -1;
   }

   mTimer = true;
   mInitialized = true;

   // fire up timer for ticking Torque 3D update
   SetTimer( 1,            // timer identifier 
      1,                    // 1 millisecond
      (TIMERPROC) MyTimerProc); // timer callback 

   hHook = ::SetWindowsHookEx(
      WH_GETMESSAGE,
      GetMessageProc,
      WebCommon::gPluginModule,
      GetCurrentThreadId());

   return 0;
}

//------------------------------------------------------------------------------
/**
*/
LRESULT 
WebGameWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   // let the default handler run
   bHandled = FALSE;

   // kill update timer
   if (mTimer)
      KillTimer( 1); 
   mTimer = false;

   if (hHook)
      ::UnhookWindowsHookEx (hHook);

   hHook = NULL;

   return 0;
}

//------------------------------------------------------------------------------
/**
*/

LRESULT 
WebGameWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   // let the default handler run
   bHandled = FALSE;

   // resize the Torque 3D child window depending on our browser's parent window
   if (mInitialized && torque_resizewindow)
   {
      int width = (int) LOWORD( lParam );
      int height = (int) HIWORD( lParam );
      torque_resizewindow(width,height);
   }
   return 0;
}


//------------------------------------------------------------------------------
/**
*/
LRESULT
WebGameWindow::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   return MA_ACTIVATE;
}

