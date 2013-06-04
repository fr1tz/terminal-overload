// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef  _WIN32_CURSORCONTROLLER_H_
#define  _WIN32_CURSORCONTROLLER_H_

#include <windows.h>
#include "windowManager/platformCursorController.h"

class Win32CursorController : public PlatformCursorController
{
public:
   Win32CursorController( PlatformWindow *owner ) :
      PlatformCursorController( owner )
   {
      pushCursor( PlatformCursorController::curArrow );
   };

   virtual void setCursorPosition( S32 x, S32 y );
   virtual void getCursorPosition( Point2I &point );
   virtual void setCursorVisible( bool visible );
   virtual bool isCursorVisible();

   void setCursorShape( U32 cursorID );
   void setCursorShape( const UTF8 *fileName, bool reload );

   U32 getDoubleClickTime();
   S32 getDoubleClickWidth();
   S32 getDoubleClickHeight();
};


#endif
