// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MACVIEW_H_
#define _MACVIEW_H_

#import <Cocoa/Cocoa.h>
#include "windowManager/mac/macWindow.h"

/// GGMacView handles displaying content and responding to user input.
@interface GGMacView : NSOpenGLView
{
   MacWindow* mTorqueWindow;
   U32 mLastMods;
   bool mHandledAsCharEvent;
}
- (void)setTorqueWindow:(MacWindow*)theWindow;
- (MacWindow*)torqueWindow;

/// @name Inherited Mouse Input methods
/// @{
- (void)mouseDown:(NSEvent *)theEvent;
- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)rightMouseDragged:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)rightMouseUp:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)scrollWheel:(NSEvent *)theEvent;
/// @}

/// @name Inherited Keyboard Input methods
/// @{
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
/// @}

/// @name Keyboard Input Common Code
/// @{
- (void)rawKeyUpDown:(NSEvent *)theEvent keyDown:(BOOL)isKeyDown;
/// @}

/// @name Mouse Input Common Code
/// @{
- (void)mouseUpDown:(NSEvent *)theEvent mouseDown:(BOOL)isMouseDown;
- (void)mouseMotion:(NSEvent *)theEvent;
/// @}

- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (BOOL)resignFirstResponder;


@end

#endif
