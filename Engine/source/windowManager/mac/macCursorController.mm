// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <Carbon/Carbon.h>
#include <Cocoa/Cocoa.h>
#include "windowManager/mac/macWindow.h"
#include "windowManager/mac/macCursorController.h"

void MacCursorController::setCursorPosition(S32 x, S32 y)
{
   MacWindow* macWindow = dynamic_cast<MacWindow*>(mOwner);
   if(!macWindow || !macWindow->isVisible())
      return;
      
   CGPoint pt = { x, y };
   CGWarpMouseCursorPosition(pt);
   
   macWindow->_skipAnotherMouseEvent();
}

void MacCursorController::getCursorPosition( Point2I &point )
{
   NSPoint pos = [NSEvent mouseLocation];
   point.x = pos.x;
   point.y = pos.y;
   
   //what does this do?? comment??
   
   MacWindow* macWindow = static_cast<MacWindow*>(mOwner);
   
   CGRect bounds = macWindow->getDisplayBounds();
   CGRect mainbounds = macWindow->getMainDisplayBounds();
   F32 offsetY = mainbounds.size.height - (bounds.size.height + bounds.origin.y);
   point.y = bounds.size.height + offsetY - point.y;
}

void MacCursorController::setCursorVisible(bool visible)
{
   visible ? [NSCursor unhide] : [NSCursor hide];
}

bool MacCursorController::isCursorVisible()
{
   return CGCursorIsVisible();
}

// a repository of custom cursors.
@interface TorqueCursors : NSObject { }
+(NSCursor*)resizeAll;
+(NSCursor*)resizeNWSE;
+(NSCursor*)resizeNESW;
@end
@implementation TorqueCursors
+(NSCursor*)resizeAll
{
   static NSCursor* cur = nil;
   if(!cur)
      cur = [[NSCursor alloc] initWithImage:[NSImage imageNamed:@"resizeAll"] hotSpot:NSMakePoint(8, 8)];
   return cur;
}
+(NSCursor*)resizeNWSE
{
   static NSCursor* cur = nil;
   if(!cur)
      cur = [[NSCursor alloc] initWithImage:[NSImage imageNamed:@"resizeNWSE"] hotSpot:NSMakePoint(8, 8)];
   return cur;
}
+(NSCursor*)resizeNESW
{
   static NSCursor* cur = nil;
   if(!cur)
      cur = [[NSCursor alloc] initWithImage:[NSImage imageNamed:@"resizeNESW"] hotSpot:NSMakePoint(8, 8)];
   return cur;
}
@end

void MacCursorController::setCursorShape(U32 cursorID)
{
   NSCursor *cur;
   switch(cursorID)
   {
      case PlatformCursorController::curArrow:
         [[NSCursor arrowCursor] set];
         break;
      case PlatformCursorController::curWait:
         // hack: black-sheep carbon call
         SetThemeCursor(kThemeWatchCursor);
         break;
      case PlatformCursorController::curPlus:
         [[NSCursor crosshairCursor] set];
         break;
      case PlatformCursorController::curResizeVert:
         [[NSCursor resizeLeftRightCursor] set];
         break;
      case PlatformCursorController::curIBeam:
         [[NSCursor IBeamCursor] set];
         break;
      case PlatformCursorController::curResizeAll:
         cur = [TorqueCursors resizeAll];
         [cur set];
         break;
      case PlatformCursorController::curResizeNESW:
         [[TorqueCursors resizeNESW] set];
         break;
      case PlatformCursorController::curResizeNWSE:
         [[TorqueCursors resizeNWSE] set];
         break;
      case PlatformCursorController::curResizeHorz:
         [[NSCursor resizeUpDownCursor] set];
      break;
   }
}

void MacCursorController::setCursorShape( const UTF8 *fileName, bool reload )
{
   //TODO: this is untested code
   
   NSString* strFileName = [ NSString stringWithUTF8String: fileName ];
   
   // Load image file.
   
   NSImage* image = [ NSImage alloc ];
   if( [ image initWithContentsOfFile: strFileName ] == nil )
      return;

   // Allocate cursor.
   
   NSCursor* cursor = [ NSCursor alloc ];
   [ cursor initWithImage: image hotSpot: NSMakePoint( 0.5, 0.5 ) ];
}

U32 MacCursorController::getDoubleClickTime()
{
   return GetDblTime() / 60.0f * 1000.0f;
}

S32 MacCursorController::getDoubleClickWidth()
{
   // This is an arbitrary value.
   return 10;
}

S32 MacCursorController::getDoubleClickHeight()
{
   return getDoubleClickWidth();
}

