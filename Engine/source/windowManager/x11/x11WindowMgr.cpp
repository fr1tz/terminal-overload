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

#include "windowManager/x11/x11WindowMgr.h"
#include "core/util/journal/process.h"
#include "platformX86UNIX/x86UNIXState.h"
#include "gfx/gfxStructs.h"
#include "gfx/gfxDevice.h"


// TODO LINUX X11 error handle
int X11ErrorHandle(Display *display, XErrorEvent *errorEvent)
{
    //AssertFatal(0, "X11ErrorHandle");
}

// ------------------------------------------------------------------------

PlatformWindowManager * CreatePlatformWindowManager()
{
   return new X11WindowManager();
}

// ------------------------------------------------------------------------

X11WindowManager::X11WindowManager()
{
    // Register in the process list.
    Process::notify(this, &X11WindowManager::_process, PROCESS_INPUT_ORDER);
    
    mWindowListHead = 0;
    mSplashWindow = 0;
    mSplashImage = 0;

    XSetErrorHandler(&X11ErrorHandle);
}

X11WindowManager::~X11WindowManager()
{
   // Get ourselves off the process list.
   Process::remove(this, &X11WindowManager::_process);

   while( mWindowListHead )
       delete mWindowListHead;
}

RectI X11WindowManager::getPrimaryDesktopArea()
{
   RectI res;

   AssertFatal(0, "Not Implemented");

   return res;
}

Point2I X11WindowManager::getDesktopResolution()
{
    Point2I res(0, 0);
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        res.x = DisplayWidth(display, DefaultScreen(display));
        res.y = DisplayHeight(display, DefaultScreen(display));
    }

   // Return Resolution
   return res;
}

S32 X11WindowManager::getDesktopBitDepth()
{
    int bpp = 0;
    if(x86UNIXState->isXWindowsRunning())
    {
        Display* display = x86UNIXState->getDisplayPointer();
        bpp = DefaultDepth(display, DefaultScreen(display));
    }
    
    // Return Bits per Pixel
    return bpp;
}

void X11WindowManager::getMonitorRegions(Vector<RectI> &regions)
{
   AssertFatal(0, "Not Implemented");
}

void X11WindowManager::getWindows(VectorPtr<PlatformWindow*> &windows)
{
   AssertFatal(0, "Not Implemented");
}

PlatformWindow *X11WindowManager::createWindow(GFXDevice *device, const GFXVideoMode &mode)
{
    // Create the window
    X11Window* newWindow = new X11Window(this);
    if( !newWindow->createWindow(0, 0, mode) )
        return 0;
    
    // Put the new window at the head of the list
    newWindow->mNextWindow = mWindowListHead;
    mWindowListHead = newWindow;

    // Bind the window to the graphics device
    newWindow->setGFXDevice(device);
    if(device)
    {
        newWindow->setGFXTarget(device->allocWindowTarget(newWindow));
    }

    // Show the window
    newWindow->show();

    // Center the window if not fullscreen
    if( !mode.fullScreen )
    {
        newWindow->centerWindow();
    }
    
    return newWindow;
}


void X11WindowManager::setParentWindow(void* newParent)
{
    AssertFatal(0, "Not Implemented");
}

void* X11WindowManager::getParentWindow()
{
    AssertFatal(0, "Not Implemented");
    return (void*)0;
}

void X11WindowManager::_process()
{
    X11Window* window = mWindowListHead;
    while( window )
    {
        window->update();

        window = window->mNextWindow;
    }    
}

PlatformWindow * X11WindowManager::getWindowById( WindowId id )
{
    AssertFatal(0, "Not Implemented");
    return NULL; 
}

PlatformWindow * X11WindowManager::getFirstWindow()
{
    return mWindowListHead != NULL ? mWindowListHead : NULL;
}

PlatformWindow* X11WindowManager::getFocusedWindow()
{ 
    X11Window* window = mWindowListHead;
    while( window )
    {
        if( window->isFocused() )
            return window;

        window = window->mNextWindow;
    }    
    return NULL;
}

void X11WindowManager::_processCmdLineArgs( const S32 argc, const char **argv )
{
}

void X11WindowManager::lowerCurtain()
{
    AssertFatal(0, "Not Implemented");
}

void X11WindowManager::raiseCurtain()
{
    AssertFatal(0, "Not Implemented");
}

bool X11WindowManager::removeWindow(X11Window* window)
{
    X11Window* next = mWindowListHead;
    X11Window* prev = 0;
    while( next )
    {
        if( next == window )
        {
            // Found the window in the list - Remove it
            if( next == mWindowListHead )
            {
                // Fix the head of the list
                mWindowListHead = mWindowListHead->mNextWindow;
            }
            else
            {
                // In the middle somewhere
                if( prev )
                    prev->mNextWindow = next->mNextWindow;
            }
            return true;
        }

        prev = next;
        next = next->mNextWindow;
    }

    // Didnt find the window to remove
    return false;
}

bool X11WindowManager::displaySplashWindow()
{
	return false; // TODO LINUX
#if 0
    if( !mSplashWindow )
    {
        // Load the splash image
        if( !mSplashImage )
        {
            mSplashImage = new X11Image();
            if( !mSplashImage->loadFile("art/gui/splash.bmp") )
            {
                delete mSplashImage;
                mSplashImage = 0;
            }
        }

        if( mSplashImage )
        {
            mSplashWindow = new X11Window(this);
            GFXVideoMode mode;
            mode.resolution = Point2I(mSplashImage->getWidth(), mSplashImage->getHeight());
            if ( !mSplashWindow->createWindow(0, 0, mode) )
            {
                delete mSplashWindow;
                delete mSplashImage;
                mSplashImage = 0;
                mSplashWindow = 0;
            }
            else
            {
                mSplashWindow->showSystemBar(false);
                mSplashWindow->centerWindow();
            }
        }
    }

    if( mSplashWindow )
    {
        // Show the window
        mSplashWindow->show();

        // Now set the image after it is visible
        mSplashWindow->setBackgroundImage(mSplashImage);
    }
    
    return (mSplashWindow != 0);
#endif
}

void X11WindowManager::closeSplashWindow()
{
    Con::printf("closeSplashWindow(0x%8.8x)", mSplashWindow);
    if( mSplashWindow )
    {
        delete mSplashWindow;
        mSplashWindow = 0;
    }

    if( mSplashImage )
    {
        delete mSplashImage;
        mSplashImage = 0;
    }
}