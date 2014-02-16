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

#include "gfx/gl/tGL/tXGL.h"
#include <X11/extensions/xf86vmode.h>

#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"

#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLEnumTranslate.h"
#include "gfx/gl/gfxGLVertexBuffer.h"
#include "gfx/gl/gfxGLPrimitiveBuffer.h"
#include "gfx/gl/gfxGLTextureTarget.h"
#include "gfx/gl/gfxGLWindowTarget.h"
#include "gfx/gl/gfxGLTextureManager.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gl/gfxGLCubemap.h"
#include "gfx/gl/gfxGLCardProfiler.h"

#include "windowManager/x11/x11Window.h"
#include "platformX86UNIX/x86UNIXState.h"



extern void loadGLCore();
extern void loadGLExtensions(void* context);

void EnumerateVideoModes(Vector<GFXVideoMode>& outModes)
{
    // Enumerate all available resolutions:
	XF86VidModeModeInfo **modes;
	int numModes;
 
	Display* display = XOpenDisplay(0);
    AssertFatal(display, "Failed to connect to X Server");
	XF86VidModeGetAllModeLines(display, XDefaultScreen(display), &numModes, &modes);
    for( int i = 0; i < numModes; i++ )
    {
        GFXVideoMode vmAdd;
        vmAdd.bitDepth     = 32;
        vmAdd.fullScreen   = true;
        vmAdd.refreshRate  = 60;
        vmAdd.resolution.x = modes[i]->vdisplay;
        vmAdd.resolution.y = modes[i]->hdisplay;

        // Only add this resolution if it is not already in the list:
        bool alreadyInList = false;
        for (Vector<GFXVideoMode>::iterator iter = outModes.begin(); iter != outModes.end(); iter++)
        {
            if (vmAdd == *iter)
            {
                alreadyInList = true;
                break;
            }
        }
        
        if(!alreadyInList)
            outModes.push_back( vmAdd );
    }
	XFree(modes);
}

void GFXGLDevice::enumerateAdapters( Vector<GFXAdapter*> &adapterList )
{
    

    // Create a dummy window & openGL context so that gl functions can be used here
    AssertFatal(x86UNIXState->isXWindowsRunning(), "Can not enumerate OpenGL devices without a connection to the X Server");

    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, 0};
    Display* display = x86UNIXState->getDisplayPointer();
    XVisualInfo* vi = glXChooseVisual(display, 0,  att);
    GLXContext context = glXCreateContext(display, vi, NULL, GL_TRUE);

    Window rootWindow = DefaultRootWindow(display);
    XSetWindowAttributes windowAttributes;
    windowAttributes.colormap = XCreateColormap(display, rootWindow, vi->visual, AllocNone);
    windowAttributes.event_mask = ExposureMask | KeyPressMask;
    Window win = XCreateWindow(display, rootWindow, 0, 0, 1, 1, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &windowAttributes);  
    XMapWindow(display, win);

    glXMakeCurrent(display, win, context);

    // Add the GL renderer
    loadGLCore();
    loadGLExtensions(0);
    
    GFXAdapter *toAdd = new GFXAdapter;
    toAdd->mIndex = 0;
    
    const char* renderer = (const char*) glGetString( GL_RENDERER );
    AssertFatal( renderer != NULL, "GL_RENDERER returned NULL!" );
    
    if (renderer)
    {
        dStrcpy(toAdd->mName, renderer);
        dStrncat(toAdd->mName, " OpenGL", GFXAdapter::MaxAdapterNameLen);
    }
    else
        dStrcpy(toAdd->mName, "OpenGL");
    
    toAdd->mType = OpenGL;
    toAdd->mShaderModel = 0.f;
    toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;
    
    // Enumerate all available resolutions:
    EnumerateVideoModes(toAdd->mAvailableModes);
    
    // Add to the list of available adapters.
    adapterList.push_back(toAdd);

    // Cleanup window & open gl context
    glXMakeCurrent(display, 0, NULL);
    glXDestroyContext(display, context);
    XDestroyWindow(display, win);
}

void GFXGLDevice::enumerateVideoModes() 
{
    mVideoModes.clear();
    EnumerateVideoModes(mVideoModes);
}

void GFXGLDevice::init( const GFXVideoMode &mode, PlatformWindow *window )
{
    AssertFatal(window, "GFXGLDevice::init - no window specified, can't init device without a window!");
    X11Window* x11Window = dynamic_cast<X11Window*>(window);
    AssertFatal(x11Window, "Window is not a valid X11Window object");

    // Create OpenGL context
    Display* display = x86UNIXState->getDisplayPointer();
    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, 0};   // TODO : get these from GFXVideoMode   
    XVisualInfo* vi = glXChooseVisual(display, 0,  att);
    GLXContext ctx = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, (GLXDrawable)x11Window->getWindowId(), ctx);
    mContext = ctx;
        
    loadGLCore();
    loadGLExtensions(0);
    
    // It is very important that extensions be loaded before we call initGLState()
    initGLState();
    
    mProjectionMatrix.identity();
    
    mInitialized = true;
    deviceInited();
}

bool GFXGLDevice::beginSceneInternal() 
{
    mCanCurrentlyRender = true;
   glGetError();
   return true;
}

U32 GFXGLDevice::getTotalVideoMemory()
{
   // CodeReview [ags 12/21/07] Figure out how to do this.
   return 0;
}

//------------------------------------------------------------------------------

GFXWindowTarget *GFXGLDevice::allocWindowTarget( PlatformWindow *window )
{
    AssertFatal(!mContext, "This GFXGLDevice is already assigned to a window");
    
    GFXGLWindowTarget* ggwt = 0;
    if( !mContext )
    {
        // no context, init the device now
        init(window->getVideoMode(), window);
        ggwt = new GFXGLWindowTarget(window, this);
        ggwt->registerResourceWithDevice(this);
        ggwt->mContext = mContext;
    }

    return ggwt;
}

GFXFence* GFXGLDevice::_createPlatformSpecificFence()
{
    return NULL;
}


//-----------------------------------------------------------------------------

void GFXGLWindowTarget::_WindowPresent()
{
   Display* display = x86UNIXState->getDisplayPointer();
   glXSwapBuffers(display, (Window)getWindow()->getWindowId());
}

void GFXGLWindowTarget::_teardownCurrentMode()
{
}

void GFXGLWindowTarget::_setupNewMode()
{
}
