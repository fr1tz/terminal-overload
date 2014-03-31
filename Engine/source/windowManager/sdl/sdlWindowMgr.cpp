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

#include "windowManager/sdl/sdlWindowMgr.h"
#include "gfx/gfxDevice.h"
#include "core/util/journal/process.h"
#include "core/strings/unicode.h"

#include "SDL.h"

// ------------------------------------------------------------------------

void sdl_CloseSplashWindow(void* hinst);

#ifdef TORQUE_SDL

PlatformWindowManager * CreatePlatformWindowManager()
{
   return new SDLWindowManager();
}

#endif

// ------------------------------------------------------------------------

SDLWindowManager::SDLWindowManager()
{
   // Register in the process list.
   Process::notify(this, &SDLWindowManager::_process, PROCESS_INPUT_ORDER);

   // Init our list of allocated windows.
   mWindowListHead = NULL;

   // By default, we have no parent window.
   mParentWindow = NULL;

   mCurtainWindow = NULL;

   mOffscreenRender = false;

   buildMonitorsList();
}

SDLWindowManager::~SDLWindowManager()
{
   // Get ourselves off the process list.
   Process::remove(this, &SDLWindowManager::_process);

   // Kill all our windows first.
   while(mWindowListHead)
      // The destructors update the list, so this works just fine.
      delete mWindowListHead;
}

RectI SDLWindowManager::getPrimaryDesktopArea()
{
   // TODO SDL
   AssertFatal(0, "");
   return RectI(0,0,0,0);
}

Point2I SDLWindowManager::getDesktopResolution()
{
   SDL_DisplayMode mode;
   SDL_GetDesktopDisplayMode(0, &mode);

   // Return Resolution
   return Point2I(mode.w, mode.h);
}

S32 SDLWindowManager::getDesktopBitDepth()
{
   // Return Bits per Pixel
   SDL_DisplayMode mode;
   SDL_GetDesktopDisplayMode(0, &mode);
   int bbp;
   unsigned int r,g,b,a;
   SDL_PixelFormatEnumToMasks(mode.format, &bbp, &r, &g, &b, &a);
   return bbp;
}

void SDLWindowManager::buildMonitorsList()
{
   // TODO SDL
}

S32 SDLWindowManager::findFirstMatchingMonitor(const char* name)
{
   /// TODO SDL
   AssertFatal(0, "");

   return 0;
}

U32 SDLWindowManager::getMonitorCount()
{
   // TODO SDL
   AssertFatal(0, "");
   return 1;
}

const char* SDLWindowManager::getMonitorName(U32 index)
{
   // TODO SDL
   AssertFatal(0, "");

   return "Monitor";
}

RectI SDLWindowManager::getMonitorRect(U32 index)
{
   // TODO SDL
   AssertFatal(0, "");

   return RectI(0, 0, 0,0 );
}

void SDLWindowManager::getMonitorRegions(Vector<RectI> &regions)
{
   // TODO SDL
   AssertFatal(0, "");
}

void SDLWindowManager::getWindows(VectorPtr<PlatformWindow*> &windows)
{
   SDLWindow *win = mWindowListHead;
   while(win)
   {
      windows.push_back(win);
      win = win->mNextWindow;
   }
}

PlatformWindow *SDLWindowManager::createWindow(GFXDevice *device, const GFXVideoMode &mode)
{
   // Do the allocation.
   SDLWindow *window = new SDLWindow();   

   window->mWindowHandle = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.resolution.x, mode.resolution.y,  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   window->mWindowId = SDL_GetWindowID( window->mWindowHandle );
   window->mOwningManager = this;
   mWindowMap[ window->mWindowId ] = window;

   if(device)
   {
      window->mDevice = device;
      window->mTarget = device->allocWindowTarget(window);
      AssertISV(window->mTarget, "SDLWindowManager::createWindow - failed to get a window target back from the device.");
   }
   else
   {
      Con::warnf("SDLWindowManager::createWindow - created a window with no device!");
   }

   linkWindow(window);

   return window;
}


void SDLWindowManager::setParentWindow(void* newParent)
{
   
}

void* SDLWindowManager::getParentWindow()
{
   return NULL;
}

void SDLWindowManager::_process()
{
   SDL_Event evt;
   while( SDL_PollEvent(&evt) )
   {      
      switch(evt.type)
      {
          case SDL_QUIT:
          {
             SDLWindow *window = static_cast<SDLWindow*>( getFirstWindow() );
             if(window)
               window->appEvent.trigger( window->getWindowId(), WindowClose );
             break;
          }

         case SDL_KEYDOWN:
         case SDL_KEYUP:
         {
            SDLWindow *window = mWindowMap[evt.key.windowID];
            if(window)
               window->_processSDLEvent(evt);
            break;
         }

         case SDL_MOUSEMOTION:
         {
            SDLWindow *window = mWindowMap[evt.motion.windowID];
            if(window)
               window->_processSDLEvent(evt);
            break;
         }

         case SDL_MOUSEBUTTONDOWN:
         case SDL_MOUSEBUTTONUP:
         {
            SDLWindow *window = mWindowMap[evt.button.windowID];
            if(window)
               window->_processSDLEvent(evt);
            break;
         }

         case SDL_TEXTINPUT:
         {
            SDLWindow *window = mWindowMap[evt.text.windowID];
            if(window)
               window->_processSDLEvent(evt);
            break;
         }

         case SDL_WINDOWEVENT:
         {
            SDLWindow *window = mWindowMap[evt.window.windowID];
            if(window)
               window->_processSDLEvent(evt);
            break;
         }

         default:
         {
            Con::printf("Event: %d", evt.type);
         }
      }
   }

}

PlatformWindow * SDLWindowManager::getWindowById( WindowId id )
{
   // Walk the list and find the matching id, if any.
   SDLWindow *win = mWindowListHead;
   while(win)
   {
      if(win->getWindowId() == id)
         return win;

      win = win->mNextWindow;
   }

   return NULL; 
}

PlatformWindow * SDLWindowManager::getFirstWindow()
{
   return mWindowListHead != NULL ? mWindowListHead : NULL;
}

PlatformWindow* SDLWindowManager::getFocusedWindow()
{
   SDLWindow* window = mWindowListHead;
   while( window )
   {
      if( window->isFocused() )
         return window;

      window = window->mNextWindow;
   }

   return NULL;
}

void SDLWindowManager::linkWindow( SDLWindow *w )
{
   w->mNextWindow = mWindowListHead;
   mWindowListHead = w;
}

void SDLWindowManager::unlinkWindow( SDLWindow *w )
{
   SDLWindow **walk = &mWindowListHead;
   while(*walk)
   {
      if(*walk != w)
      {
         // Advance to next item in list.
         walk = &(*walk)->mNextWindow;
         continue;
      }

      // Got a match - unlink and return.
      *walk = (*walk)->mNextWindow;
      return;
   }
}

void SDLWindowManager::_processCmdLineArgs( const S32 argc, const char **argv )
{
   // TODO SDL
}

void SDLWindowManager::lowerCurtain()
{
   if(mCurtainWindow)
      return;

   // TODO SDL
}

void SDLWindowManager::raiseCurtain()
{
   if(!mCurtainWindow)
      return;

   // TODO SDL
}


AFTER_MODULE_INIT(gfx)
{
   int res = SDL_Init(SDL_INIT_EVERYTHING);
   AssertFatal(res != -1, "SDL init error");
}