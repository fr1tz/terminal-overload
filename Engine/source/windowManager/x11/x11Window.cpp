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

#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>

#include "windowManager/x11/x11Window.h"
#include "windowManager/x11/x11WindowMgr.h"
#include "windowManager/x11/x11CursorController.h"
#include "platformX86UNIX/x86UNIXState.h"


const long defaultX11EventMask = 0
    | KeyPressMask
    | KeyReleaseMask
    | ButtonPressMask
    | ButtonReleaseMask
    | EnterWindowMask
    | LeaveWindowMask
    | PointerMotionMask
    | PointerMotionHintMask
    | Button1MotionMask
    | Button2MotionMask
    | Button3MotionMask
    | Button4MotionMask
    | Button5MotionMask
    | ButtonMotionMask
    | KeymapStateMask
    | ExposureMask
    | VisibilityChangeMask
    | StructureNotifyMask
    //| ResizeRedirectMask
    | SubstructureNotifyMask
    //| SubstructureRedirectMask
    | FocusChangeMask
    //| PropertyChangeMask
    | ColormapChangeMask;

X11Window::X11Window(X11WindowManager* owner)
{
    mCursorController = new X11CursorController( this );
    mOwningManager = owner;

    mNextWindow = 0;

    mWindowID = 0;
    mVisible = false;
    mMouseLocked = false;
    mHasFocus = false;

}

X11Window::~X11Window()
{
    cleanup();
    mOwningManager->removeWindow(this);
}

const GFXVideoMode & X11Window::getVideoMode()
{
	return mVideoMode;
}

void X11Window::setVideoMode( const GFXVideoMode &mode )
{
    _setFullscreen(mode.fullScreen);
    setSize(mode.resolution);
    mVideoMode = mode;
}

bool X11Window::clearFullscreen()
{
    AssertFatal(0, "Not Implemented");
	return true;
}

bool X11Window::isFullscreen()
{
	return mVideoMode.fullScreen;
}

void X11Window::_setFullscreen(const bool fullscreen)
{
    if( fullscreen != mVideoMode.fullScreen )
    {
        Display* display = x86UNIXState->getDisplayPointer();
        Atom wm_state = XInternAtom(display, "_NET_WM_STATE", fullscreen ? False : True);
        Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", fullscreen ? False : True);

        XEvent xev;
        memset(&xev, 0, sizeof(xev));
        xev.type = ClientMessage;
        xev.xclient.window = mWindowID;
        xev.xclient.message_type = wm_state;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = 1;
        xev.xclient.data.l[1] = fullscreen;
        xev.xclient.data.l[2] = 0;
        XSendEvent (display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
        XFlush(display);
        mVideoMode.fullScreen = fullscreen;
    }
}

bool X11Window::setCaption( const char *cap )
{
    if( !mWindowID )
        return false;

    if( !x86UNIXState->isXWindowsRunning() )
        return false;

    Display* display = x86UNIXState->getDisplayPointer();
    XStoreName(display, mWindowID, cap);
	return true;
}

const char * X11Window::getCaption()
{
    if( !mWindowID )
        return 0;

    if( !x86UNIXState->isXWindowsRunning() )
        return 0;

    Display* display = x86UNIXState->getDisplayPointer();

    char* tempName;
    XFetchName(display, mWindowID, &tempName);

    const char* caption = StringTable->insert(tempName);
    XFree(tempName);

	return caption;
}

void X11Window::setFocus()
{
    AssertFatal(0, "Not Implemented");
}

void X11Window::setClientExtent( const Point2I newExtent )
{
    AssertFatal(0, "Not Implemented");
}

const Point2I X11Window::getClientExtent()
{
    Point2I clientExtent(0, 0);
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        XWindowAttributes attributes;
        XGetWindowAttributes(display, mWindowID, &attributes);
        clientExtent.x = attributes.width;
        clientExtent.y = attributes.height;
    }

	return clientExtent;
}

void X11Window::setBounds( const RectI &newBounds )
{
    AssertFatal(0, "Not Implemented");
}

const RectI X11Window::getBounds() const
{
    AssertFatal(0, "Not Implemented");

	// Return as a Torque RectI
	return RectI(0,0,0,0);
}

void X11Window::setPosition( const Point2I newPosition )
{
    AssertFatal(0, "Not Implemented");
}

const Point2I X11Window::getPosition()
{
    AssertFatal(0, "Not Implemented");

	// Return position
	return Point2I(0,0);
}

Point2I X11Window::clientToScreen( const Point2I& pos )
{
    AssertFatal(0, "Not Implemented");
    return Point2I( 0, 0 );
}

Point2I X11Window::screenToClient( const Point2I& pos )
{
    AssertFatal(0, "Not Implemented");
    return Point2I( 0, 0 );
}

void X11Window::showSystemBar(bool show)
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        XSetWindowAttributes attributes;
        attributes.override_redirect = !show;
        XChangeWindowAttributes(display, mWindowID, CWOverrideRedirect, &attributes);
    }
}

void X11Window::centerWindow()
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();

        int screenWidth = DisplayWidth(display, DefaultScreen(display));
        int screenHeight = DisplayHeight(display, DefaultScreen(display));
        int windowX = (screenWidth - mVideoMode.resolution.x) / 2;
        int windowY = (screenHeight - mVideoMode.resolution.y) / 2;

        XMoveWindow(display, mWindowID, windowX, windowY);
    }
}

bool X11Window::setSize( const Point2I &newSize )
{
	if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();

        mVideoMode.resolution = newSize;
        XResizeWindow(display, mWindowID, newSize.x, newSize.y);
        return true;
    }
	return false;
}

bool X11Window::isOpen()
{
	return true;
}

bool X11Window::isVisible()
{
    if(x86UNIXState->isXWindowsRunning())
    {
        if( mWindowID )
            return mVisible;        // Maybe come up with some more elaborate check here??
    }
	return false;
}

bool X11Window::isFocused()
{
    return mHasFocus;
}

bool X11Window::isMinimized()
{
    AssertFatal(0, "Not Implemented");
    return false;
}

bool X11Window::isMaximized()
{
    AssertFatal(0, "Not Implemented");
    return false;
}

WindowId X11Window::getWindowId()
{
	return (WindowId)mWindowID;
}

void X11Window::minimize()
{
    AssertFatal(0, "Not Implemented");
}

void X11Window::maximize()
{
    AssertFatal(0, "Not Implemented");
}

void X11Window::restore()
{
    AssertFatal(0, "Not Implemented");
}

void X11Window::hide()
{
    AssertFatal(0, "Not Implemented");
}

void X11Window::show()
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();

        // Show the window
        XMapWindow(display, mWindowID);

        // Wait for the window to be visible
        XSelectInput(display, mWindowID, ExposureMask);
        while (1)
        {
            XEvent event;
            XNextEvent(display, &event);
            if( event.type == Expose )
                mVisible = true;
                break;
        }

        // Request all default events
        XSelectInput(display, mWindowID, defaultX11EventMask);
    }
}

void X11Window::close()
{
	AssertFatal(0, "Not Implemented");
}

void X11Window::defaultRender()
{
	AssertFatal(0, "Not Implemented");
}

void X11Window::setBackgroundImage(X11Image* image)
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        GC gc = XCreateGC(display, mWindowID, 0, NULL);
        XPutImage(display, mWindowID, gc, image->getXImage(), 0, 0, 0, 0, image->getWidth(), image->getHeight());
		XFlush(display);
    }
}

//-----------------------------------------------------------------------------
// Mouse Locking
//-----------------------------------------------------------------------------

void X11Window::setMouseLocked( bool enable )
{
    mMouseLocked = enable;
    setCursorVisible(!enable);
    if(enable)
        XWarpPointer(x86UNIXState->getDisplayPointer(), NULL, mWindowID, 0, 0, 0, 0, mVideoMode.resolution.x/2, mVideoMode.resolution.y/2);
}

const UTF16 *X11Window::getWindowClassName()
{
    AssertFatal(0, "Not Implemented");
	return 0;
}

const UTF16 *X11Window::getCurtainWindowClassName()
{
    AssertFatal(0, "Not Implemented");
	return 0;
}

void* X11Window::getPlatformDrawable() const
{
    AssertFatal(0, "Not Implemented");
    return 0;
}

bool X11Window::createWindow(int x, int y, const GFXVideoMode &mode, Window parent)
{
    if(x86UNIXState->isXWindowsRunning())
    {
        // Cleanup any existing window
        cleanup();

        // Set the parent
        setParent(parent);

        // Create a new window
        Display* display = x86UNIXState->getDisplayPointer();
        mWindowID = XCreateSimpleWindow(display, mParent, x, y, mode.resolution.x, mode.resolution.y, 0, BlackPixel(display, DefaultScreen(display)), WhitePixel(display, DefaultScreen(display)));

        XWindowAttributes attributes;
        XGetWindowAttributes(display, mWindowID, &attributes);
        mVideoMode = mode;
        mVideoMode.resolution.x = attributes.width;
        mVideoMode.resolution.y = attributes.height;
        mVideoMode.bitDepth = attributes.depth;
    }

    return (mWindowID != 0);
}

void X11Window::cleanup()
{
    if( mWindowID != 0 )
    {
        Display* display = x86UNIXState->getDisplayPointer();
        XDestroyWindow(display, mWindowID);
        mWindowID = 0;
    }
}

void X11Window::setParent(Window parent)
{
    // Get display & parent
    Display* display = x86UNIXState->getDisplayPointer();
    if( parent )
        mParent = parent;
    else
        mParent = DefaultRootWindow(display);       // No parent specified, use the default root window as the parent
}

void X11Window::triggerMouseLocationNotify()
{
    // Get the cursor position in this window
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        Window root, child;
        int rootX, rootY, winX, winY;
        U32 mask;
        XQueryPointer(display, mWindowID, &root, &child, &rootX, &rootY, &winX, &winY, &mask);

        if(!mMouseLocked)
            mouseEvent.trigger(getWindowId(), 0, winX, winY, false);
        else
            mouseEvent.trigger(getWindowId(), 0, winX-(mVideoMode.resolution.x/2), winY-(mVideoMode.resolution.y/2), true);
    }
}

S32 TranslateOSKeyCode(XKeyEvent* evt);
S16 TranslateOSString(XKeyEvent* evt);
U32 TranslateModifiersToWindowManagerInput(XKeyEvent* evt);
U32 TranslateMouseButton_X11ToTorque(XButtonEvent* evt);


struct KeyRepeatCheckData
{
    XEvent *event;
    bool found;
};

static Bool X11_KeyRepeatCheckIfEvent(Display *display, XEvent *chkev,
    XPointer arg)
{
    struct KeyRepeatCheckData *d = (struct KeyRepeatCheckData *) arg;
    if (chkev->type == KeyPress &&
        chkev->xkey.keycode == d->event->xkey.keycode &&
        chkev->xkey.time - d->event->xkey.time < 2)
        d->found = true;
    return false;
}

//From SDL2, thx :D
/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
static bool X11_KeyRepeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    struct KeyRepeatCheckData d;
    d.event = event;
    d.found = false;
    if (XPending(display))
        XCheckIfEvent(display, &dummyev, X11_KeyRepeatCheckIfEvent,
            (XPointer) &d);
    return d.found;
}

void X11Window::update()
{
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();

        const long keyMasks = KeyPressMask | KeyReleaseMask;
        const long buttonMasks = ButtonPressMask | ButtonReleaseMask;
        const long mouseMasks = PointerMotionMask | PointerMotionHintMask | ButtonMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask;
        long eventMask = defaultX11EventMask;

        XEvent evt;
        while( XCheckWindowEvent(display, mWindowID, eventMask, &evt) )
        {
            bool repeatKey = false;
            switch( evt.type )
            {
                default:
                case NoEventMask:
                    Con::printf("event type: %d", evt.type);
                    break;
                case KeyPress:
                case KeyRelease:
                {
                    U32 inputAction = IA_MAKE;
                    U32 modifiers = TranslateModifiersToWindowManagerInput(&evt.xkey);
                    U8 tKey = TranslateOSKeyCode(&evt.xkey);

                    if(evt.type == KeyRelease)
                    {
                        inputAction = IA_BREAK;

                        if(X11_KeyRepeat(display, &evt))
                            inputAction = IA_REPEAT;
                    }

                    if(tKey)
                    {
                        keyEvent.trigger(getWindowId(), modifiers, inputAction, tKey);
                        //Con::printf("Key %d : %d", tKey, inputAction);
                    }

                     if(evt.type == KeyPress)
                     {
                         S16 ascii = TranslateOSString(&evt.xkey);
                         if(ascii)
                         {
                            //Con::printf("Char %d : %d", ascii, inputAction);
                            charEvent.trigger(getWindowId(), modifiers, ascii);
                         }
                     }
                     break;
                }
                case ButtonPress:
                    // Clicking in the window should set focus here
                    appEvent.trigger(getWindowId(), GainFocus);

                    // Make sure our mouse position is up to date
                    triggerMouseLocationNotify();

                    // Trigger the click
                    buttonEvent.trigger(getWindowId(), 0, IA_MAKE,
                                        TranslateMouseButton_X11ToTorque(&evt.xbutton) );

                    break;
                case ButtonRelease:
                    // Make sure mouse position is up to date
                    triggerMouseLocationNotify();

                    // Release the mouse button
                    buttonEvent.trigger(getWindowId(), 0, IA_BREAK,
                                        TranslateMouseButton_X11ToTorque(&evt.xbutton) );

                    break;
                case MotionNotify:
                    triggerMouseLocationNotify();
                    break;
                case EnterNotify:
                    //Con::printf("EnterNotify");
                    break;
                case LeaveNotify:
                    //Con::printf("LeaveNotify");
                    break;
                case FocusIn:
                    appEvent.trigger(getWindowId(), GainFocus);
                    mHasFocus = true;
                    break;
                case FocusOut:
			        appEvent.trigger(getWindowId(), LoseFocus);
			        mHasFocus = false;
                    break;
                case KeymapNotify:
                    //Con::printf("KeymapNotify");
                    break;
                case Expose:
                    //Con::printf("Expose");
                    break;
                case GraphicsExpose:
                    //Con::printf("GraphicsExpose");
                    break;
                case NoExpose:
                    //Con::printf("NoExpose");
                    break;
                case VisibilityNotify:
                    //Con::printf("VisibilityNotify");
                    break;
                case CreateNotify:
                    //Con::printf("CreateNotify");
                    break;
                case DestroyNotify:
                    //Con::printf("DestroyNotify");
                    break;
                case UnmapNotify:
                    //Con::printf("UnmapNotify");
                    break;
                case MapNotify:
                    //Con::printf("MapNotify");
                    break;
                case MapRequest:
                    //Con::printf("MapRequest");
                    break;
                case ReparentNotify:
                    //Con::printf("ReparentNotify");
                    break;
                case ConfigureNotify:
                    //Con::printf("ConfigureNotify");
                    if (mTarget.isValid()
                        && (mVideoMode.resolution.x != evt.xconfigure.width || mVideoMode.resolution.y != evt.xconfigure.height) )
                    {
                        mVideoMode.resolution.set(evt.xconfigure.width, evt.xconfigure.height);
                    }
                    break;
                case ConfigureRequest:
                    //Con::printf("ConfigureRequest");
                    break;
                case GravityNotify:
                    //Con::printf("GravityNotify");
                    break;
                case ResizeRequest:
                    //Con::printf("ResizeRequest");
                    break;
                case CirculateNotify:
                    //Con::printf("CirculateNotify");
                    break;
                case CirculateRequest:
                    //Con::printf("CirculateRequest");
                    break;
                case PropertyNotify:
                    //Con::printf("PropertyNotify");
                    break;
                case SelectionClear:
                    //Con::printf("SelectionClear");
                    break;
                case SelectionRequest:
                    //Con::printf("SelectionRequest");
                    break;
                case SelectionNotify:
                    //Con::printf("SelectionNotify");
                    break;
                case ColormapNotify:
                    //Con::printf("ColormapNotify");
                    break;
                case ClientMessage:
                    //Con::printf("ClientMessage");
                    break;
                case MappingNotify:
                    //Con::printf("MappingNotify");
                    break;
            }
        }

        if(mMouseLocked && mHasFocus)
            XWarpPointer(display, NULL, mWindowID, 0, 0, 0, 0, mVideoMode.resolution.x/2, mVideoMode.resolution.y/2);
    }
}
