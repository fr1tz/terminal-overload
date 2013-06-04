// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "macApplication.h"
#include "windowManager/mac/macWindow.h"
#include "windowManager/mac/macView.h"
#include "console/console.h"

@implementation macApplication

- (void)sendEvent:(NSEvent*)theEvent
{
   if([theEvent type] == NSKeyUp)
   {
      if([theEvent modifierFlags] & NSCommandKeyMask)
      {
         // These will normally be blocked, but we wants them!
         [[self delegate] keyUp:theEvent];
         return;
      }
   }
   
   MacWindow* window = [(GGMacView*)[self delegate] torqueWindow];
   if(window && window->isFullscreen())
   {
      switch([theEvent type])
      {
      case NSLeftMouseDown:
         [[self delegate] mouseDown:theEvent];
         return;
      case NSRightMouseDown:
         [[self delegate] rightMouseDown:theEvent];
         return;
      case NSLeftMouseUp:
         [[self delegate] mouseUp:theEvent];
         return;
      case NSRightMouseUp:
         [[self delegate] rightMouseUp:theEvent];
         return;
      case NSMouseMoved:
         [[self delegate] mouseMoved:theEvent];
         return;
      case NSLeftMouseDragged:
         [[self delegate] mouseDragged:theEvent];
         return;
      case NSRightMouseDragged:
         [[self delegate] rightMouseDragged:theEvent];
         return;
      case NSScrollWheel:
         [[self delegate] scrollWheel:theEvent];
         return;
      default:
         break;
      }
   }
   
   [super sendEvent:theEvent];
}

@end
