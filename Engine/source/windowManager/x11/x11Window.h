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

#ifndef  _WINDOWMANAGER_X11_X11WINDOW_
#define  _WINDOWMANAGER_X11_X11WINDOW_

#include <X11/Xlib.h>
#include "windowManager/platformWindow.h"
#include "windowManager/x11/x11Image.h"

#include "gfx/gfxStructs.h"
#include "gfx/gfxTarget.h"

class X11WindowManager;

/// Implementation of a window on Win32.
class X11Window : public PlatformWindow
{
public:
    X11WindowManager* mOwningManager;

    X11Window* mNextWindow;

    Window mParent;
    Window mWindowID;

    bool mHasFocus;
    bool mMouseLocked;
    bool mShouldLockMouse;
    bool mVisible;

    GFXVideoMode mVideoMode;
    GFXDevice* mDevice;
    GFXWindowTargetRef mTarget;

public:
    X11Window(X11WindowManager* owner);
    virtual ~X11Window();

    virtual GFXDevice *getGFXDevice()           { return mDevice; }
    void setGFXDevice(GFXDevice* device)        { mDevice = device; }
    virtual GFXWindowTarget *getGFXTarget()     { return mTarget; }
    void setGFXTarget(GFXWindowTarget* target)  { mTarget = target; }

    virtual void setVideoMode(const GFXVideoMode &mode);
    virtual const GFXVideoMode &getVideoMode();
    virtual bool clearFullscreen();
    virtual bool isFullscreen();
    virtual void _setFullscreen(const bool fullscreen);

    virtual bool setCaption(const char *cap);
    virtual const char *getCaption();

    // Window Client Area Extent
    virtual void setClientExtent( const Point2I newExtent );
    virtual const Point2I getClientExtent();

    // Window Bounds
    virtual void setBounds(const RectI &newBounds);
    virtual const RectI getBounds() const;

    // Window Position
    virtual void setPosition( const Point2I newPosition );
    virtual const Point2I getPosition();
    virtual void centerWindow();
    virtual bool setSize(const Point2I &newSize);

    // Coordinate space conversion.
    virtual Point2I clientToScreen( const Point2I& pos );
    virtual Point2I screenToClient( const Point2I& pos );

    virtual bool isOpen();
    virtual bool isVisible();
    virtual bool isFocused();
    virtual bool isMinimized();
    virtual bool isMaximized();

    virtual void minimize();
    virtual void maximize();
    virtual void hide();
    virtual void show();
    virtual void close();
    virtual void restore();
    virtual void setFocus();
    void showSystemBar(bool show);
    void setBackgroundImage(X11Image* image);

    virtual void setMouseLocked(bool enable);
    virtual bool isMouseLocked() const { return mMouseLocked; };
    virtual bool shouldLockMouse() const { return mShouldLockMouse; };

    virtual WindowId getWindowId();

    virtual PlatformWindow * getNextWindow() const
    {
        return mNextWindow;
    }

    /// Provide a simple GDI-based render for when the game is not rendering.
    virtual void defaultRender();

    /// Return the class name for the windows we create with this class.
    static const UTF16 *getWindowClassName();

    /// Return the class name for the curtain window class.
    static const UTF16 *getCurtainWindowClassName();

    /// Return the platform specific object needed to create or attach an
    /// accelerated graohics drawing context on or to the window
    virtual void* getPlatformDrawable() const;

    bool createWindow(int x, int y, const GFXVideoMode &mode, Window parent = 0);

    void update();

private:
    void cleanup();
    void setParent(Window parent);
    void triggerMouseLocationNotify();
};
#endif
