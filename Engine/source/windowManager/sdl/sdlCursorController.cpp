//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include <tchar.h>
#include "core/strings/unicode.h"
#include "math/mMath.h"
#include "windowManager/sdl/sdlWindow.h"
#include "windowManager/sdl/sdlWindowMgr.h"
#include "windowManager/sdl/sdlCursorController.h"
#include "platform/platformInput.h"


U32 SDLCursorController::getDoubleClickTime()
{
   // TODO SDL
   return 500;
}
S32 SDLCursorController::getDoubleClickWidth()
{
   // TODO SDL
   return 32;
}
S32 SDLCursorController::getDoubleClickHeight()
{
   // TODO SDL
   return 32;
}

void SDLCursorController::setCursorPosition( S32 x, S32 y )
{
   // TODO SDL
}

void SDLCursorController::getCursorPosition( Point2I &point )
{
   // TODO SDL

   // Return 
   point.x = 0;
   point.y = 0;
}

void SDLCursorController::setCursorVisible( bool visible )
{
   // TODO SDL
}

bool SDLCursorController::isCursorVisible()
{
   // TODO SDL
   return true;
}

void SDLCursorController::setCursorShape(U32 cursorID)
{
   // TODO SDL
}


void SDLCursorController::setCursorShape( const UTF8 *fileName, bool reload )
{
   // TODO SDL
}
