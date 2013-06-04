// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MACCURSORCONTROLLER_H_
#define _MACCURSORCONTROLLER_H_

#include "windowManager/platformCursorController.h"

class MacCursorController : public PlatformCursorController
{
public:
   MacCursorController(MacWindow* owner)
      : PlatformCursorController( ( PlatformWindow* ) owner )
   {
      pushCursor(PlatformCursorController::curArrow);
   }
   
   virtual void setCursorPosition(S32 x, S32 y);
   virtual void getCursorPosition(Point2I &point);
   virtual void setCursorVisible(bool visible);
   virtual bool isCursorVisible();
   
   virtual void setCursorShape(U32 cursorID);
   virtual void setCursorShape( const UTF8 *fileName, bool reload );
   
   virtual U32 getDoubleClickTime();
   virtual S32 getDoubleClickWidth();
   virtual S32 getDoubleClickHeight();
};

#endif
