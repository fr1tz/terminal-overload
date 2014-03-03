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

#include "windowManager/x11/x11CursorController.h"
#include "windowManager/x11/x11Window.h"
#include "platformX86UNIX/x86UNIXState.h"

#include <X11/cursorfont.h>

inline X11Window* X11CursorController::getX11WindowOwner() const
{
    return static_cast<X11Window*>(mOwner);
}

X11CursorController::X11CursorController( PlatformWindow *owner ) :  PlatformCursorController( owner )
{
    AssertFatal(dynamic_cast<X11Window*>(mOwner), "X11CursorController::X11CursorController window owner not X11Window.");

    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();

        // Setup a blank cursor so we can hide the cursor
        static char data[1] = {0};
        Cursor cursor;
        XColor dummy;
        dummy.red = dummy.green = dummy.blue = 0;
        Pixmap blank = XCreateBitmapFromData(display, DefaultRootWindow(display), data, 1, 1);
        mBlankCursor = XCreatePixmapCursor(display, blank, blank, &dummy, &dummy, 0, 0);
        XFreePixmap(display, blank);

       pushCursor( PlatformCursorController::curArrow );

    }
    mVisible = true;
};

X11CursorController::~X11CursorController()
{
}

U32 X11CursorController::getDoubleClickTime()
{
    return 500;
}

S32 X11CursorController::getDoubleClickWidth()
{
    return 4;
}

S32 X11CursorController::getDoubleClickHeight()
{
    return 4;
}

void X11CursorController::setCursorPosition( S32 x, S32 y )
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        XWarpPointer(display, None, getX11WindowOwner()->getWindowId(), 0, 0, 0, 0, x, y);
    }
}

void X11CursorController::getCursorPosition( Point2I &point )
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        Window root, child;
        int rootX, rootY, winX, winY;
        U32 mask;
        XQueryPointer(display, getX11WindowOwner()->getWindowId(), &root, &child, &rootX, &rootY, &winX, &winY, &mask);
        point.x = rootX;
        point.y = rootY;
    }
}

void X11CursorController::setCursorVisible( bool visible )
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        mVisible = visible;
        if( visible )
        {
            XUndefineCursor(display, getX11WindowOwner()->getWindowId());
        }
        else
        {
            XDefineCursor(display, getX11WindowOwner()->getWindowId(), mBlankCursor);
        }
    }
}

bool X11CursorController::isCursorVisible()
{
    return mVisible;
}


static struct { U32 id; U32 fontCursorID; } sgCursorShapeMap[]=
{
   { PlatformCursorController::curArrow,       XC_arrow },
   { PlatformCursorController::curWait,        XC_watch },
   { PlatformCursorController::curPlus,        XC_crosshair },
   { PlatformCursorController::curResizeVert,  XC_sb_v_double_arrow },
   { PlatformCursorController::curResizeHorz,  XC_sb_h_double_arrow },
   { PlatformCursorController::curResizeAll,   XC_fleur },
   { PlatformCursorController::curIBeam,       XC_xterm },
   { PlatformCursorController::curResizeNESW,  XC_sizing },
   { PlatformCursorController::curResizeNWSE,  XC_sizing },
   { PlatformCursorController::curHand,        XC_hand2 },
   { 0,                             0 },
};

void X11CursorController::setCursorShape(U32 cursorID)
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        U32 fontCursorID = 0;
        for( int i = 0; sgCursorShapeMap[i].fontCursorID != 0; i++ )
        {
            if(cursorID == sgCursorShapeMap[i].id)
            {
                fontCursorID = sgCursorShapeMap[i].fontCursorID;
                break;
            }
        }
        if( fontCursorID )
        {
            XDefineCursor(display, getX11WindowOwner()->getWindowId(), XCreateFontCursor(display, fontCursorID));
        }
    }
}

void X11CursorController::setCursorShape( const UTF8 *fileName, bool reload )
{
    AssertFatal(0, "Not Implemented");
}
