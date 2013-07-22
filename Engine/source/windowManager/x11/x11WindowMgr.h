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

#ifndef  _WINDOWMANAGER_X11_X11WINDOWMANAGER_
#define  _WINDOWMANAGER_X11_X11WINDOWMANAGER_

#include "windowManager/platformWindowMgr.h"
#include "windowManager/x11/x11Window.h"

/// Win32 implementation of the window manager interface.
class X11WindowManager : public PlatformWindowManager
{
    // A pointer to keep track of the splash window if one exits
    X11Window* mSplashWindow;
    X11Image* mSplashImage;

    // List of allocated windows.
    X11Window* mWindowListHead;

    // Callback for the process list.
    void _process();

public:
    X11WindowManager();
    virtual ~X11WindowManager();
    
    virtual RectI    getPrimaryDesktopArea();
    virtual S32      getDesktopBitDepth();
    virtual Point2I  getDesktopResolution();
    
    virtual void getMonitorRegions(Vector<RectI> &regions);
    virtual PlatformWindow *createWindow(GFXDevice *device, const GFXVideoMode &mode);
    virtual void getWindows(VectorPtr<PlatformWindow*> &windows);
    
    virtual void setParentWindow(void* newParent);
    virtual void* getParentWindow();
    
    virtual PlatformWindow *getWindowById(WindowId id);
    virtual PlatformWindow *getFirstWindow();
    virtual PlatformWindow* getFocusedWindow();
    
    virtual void lowerCurtain();
    virtual void raiseCurtain();
    
    virtual void _processCmdLineArgs(const S32 argc, const char **argv);
    
    bool removeWindow(X11Window* window);
    bool displaySplashWindow();
    void closeSplashWindow();
};

#endif