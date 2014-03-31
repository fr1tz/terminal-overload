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
#include "math/mMath.h"
#include "gfx/gfxStructs.h"

#include "windowManager/sdl/sdlWindow.h"
#include "windowManager/sdl/sdlWindowMgr.h"
#include "windowManager/sdl/sdlCursorController.h"
#include "platformSDL/sdlInput.h"
#include "platform/menus/popupMenu.h"
#include "platform/platformInput.h"

#include "gfx/gfxDevice.h"

#include "SDL.h"
#include "SDL_syswm.h"

#define SCREENSAVER_QUERY_DENY 0 // Disable screensaver

#ifndef IDI_ICON1 
#define IDI_ICON1 107
#endif

namespace 
{
   U32 getTorqueModFromSDL(U16 mod)
   {
      U32 ret = 0;

      if(mod & KMOD_LSHIFT)
         ret |= IM_LSHIFT;

      if(mod & KMOD_RSHIFT)
         ret |= IM_RSHIFT;

      if(mod & KMOD_LCTRL)
         ret |= IM_LCTRL;

      if(mod & KMOD_RCTRL)
         ret |= IM_RCTRL;

      if(mod & KMOD_LALT)
         ret |= IM_LALT;

      if(mod & KMOD_RALT)
         ret |= IM_RALT;

      return ret;
   }
}

SDLWindow::SDLWindow(): mMouseLockPosition(0,0),
mShouldLockMouse(false),
mMouseLocked(false),
mOwningManager(NULL),
mNextWindow(NULL),
mWindowHandle(NULL),
mOldParent(NULL),
mTarget(NULL),
mDevice(NULL),
mSuppressReset(false),
mMenuHandle(NULL),
mPosition(0,0)
{
	mCursorController = new SDLCursorController( this );

	mVideoMode.bitDepth = 32;
	mVideoMode.fullScreen = false;
	mVideoMode.refreshRate = 60;
	mVideoMode.resolution.set(800,600);
}

SDLWindow::~SDLWindow()
{
	// delete our sdl handle..
	SDL_DestroyWindow(mWindowHandle);

	// unlink ourselves from the window list...
	AssertFatal(mOwningManager, "SDLWindow::~SDLWindow - orphan window, cannot unlink!");
	mOwningManager->unlinkWindow(this);
}

GFXDevice * SDLWindow::getGFXDevice()
{
	return mDevice;
}

GFXWindowTarget * SDLWindow::getGFXTarget()
{
	return mTarget;
}

const GFXVideoMode & SDLWindow::getVideoMode()
{
	return mVideoMode;
}

void* SDLWindow::getSystemWindow(const WindowSystem system)
{
     SDL_SysWMinfo info;
     SDL_VERSION(&info.version);
     SDL_GetWindowWMInfo(mWindowHandle,&info);     

     if( system == WindowSystem_Windows && info.subsystem == SDL_SYSWM_WINDOWS)
        return info.info.win.window;

     return NULL;
}

void SDLWindow::setVideoMode( const GFXVideoMode &mode )
{
   mVideoMode = mode;
   mSuppressReset = true;

	// Set our window to have the right style based on the mode
   if(mode.fullScreen && !Platform::getWebDeployment() && !mOffscreenRender)
	{		
      setSize(mode.resolution);

      SDL_SetWindowFullscreen( mWindowHandle, SDL_WINDOW_FULLSCREEN);

      // When switching to Fullscreen, reset device after setting style
	   if(mTarget.isValid())
		   mTarget->resetMode();
	}
	else
	{
      // Reset device *first*, so that when we call setSize() and let it
	   // access the monitor settings, it won't end up with our fullscreen
	   // geometry that is just about to change.

	   if(mTarget.isValid())
		   mTarget->resetMode();

      if (!mOffscreenRender)
      {
		   SDL_SetWindowFullscreen( mWindowHandle, 0);
      }

      setSize(mode.resolution);
      centerWindow();
	}

	mSuppressReset = false;
}

bool SDLWindow::clearFullscreen()
{
	return true;
}

bool SDLWindow::isFullscreen()
{   
   U32 flags = SDL_GetWindowFlags( mWindowHandle );   
   if( flags & SDL_WINDOW_FULLSCREEN || flags & SDL_WINDOW_FULLSCREEN_DESKTOP )
      return true;

   return false;
}

void SDLWindow::_setFullscreen(const bool fullscreen)
{
	if( isFullscreen() )
		return;

	if(fullscreen && !mOffscreenRender)
	{
		Con::printf("SDLWindow::setFullscreen (full) enter");
		SDL_SetWindowFullscreen( mWindowHandle, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		Con::printf("SDLWindow::setFullscreen (windowed) enter");
      if (!mOffscreenRender)
      {
	      SDL_SetWindowFullscreen( mWindowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
      }

      setSize(mVideoMode.resolution);

	}
	Con::printf("SDLWindow::setFullscreen exit");   
}

bool SDLWindow::setCaption( const char *cap )
{
   SDL_SetWindowTitle(mWindowHandle, cap);
	return true;
}

const char * SDLWindow::getCaption()
{
   return StringTable->insert( SDL_GetWindowTitle(mWindowHandle) );
}

void SDLWindow::setFocus()
{
   SDL_SetWindowGrab( mWindowHandle, SDL_TRUE );
}

void SDLWindow::setClientExtent( const Point2I newExtent )
{
	Point2I oldExtent = getClientExtent();
	if (oldExtent == newExtent)
		return;   

   SDL_SetWindowSize(mWindowHandle, newExtent.x, newExtent.y);
}

const Point2I SDLWindow::getClientExtent()
{
	// Fetch Client Rect from Windows
   Point2I size;
	SDL_GetWindowSize(mWindowHandle, &size.x, &size.y);

	return size;
}

void SDLWindow::setBounds( const RectI &newBounds )
{
	// TODO SDL
}

const RectI SDLWindow::getBounds() const
{
	// TODO SDL
	return RectI(0, 0, 0, 0);   
}

void SDLWindow::setPosition( const Point2I newPosition )
{
	SDL_SetWindowPosition( mWindowHandle, newPosition.x, newPosition.y );
}

const Point2I SDLWindow::getPosition()
{
	Point2I position;
	SDL_GetWindowPosition( mWindowHandle, &position.x, &position.y );

	// Return position
	return position;
}

Point2I SDLWindow::clientToScreen( const Point2I& pos )
{
   Point2I position;
   SDL_GetWindowPosition( mWindowHandle, &position.x, &position.y );
   return pos + position;
}

Point2I SDLWindow::screenToClient( const Point2I& pos )
{
   Point2I position;
   SDL_GetWindowPosition( mWindowHandle, &position.x, &position.y );
   return pos - position;
}

void SDLWindow::centerWindow()
{
   int sizeX, sizeY;
   SDL_GetWindowSize(mWindowHandle, &sizeX, &sizeY);

   SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
   
   U32 posX = (mode.w/2) - (sizeX/2);
   U32 posY = (mode.h/2) - (sizeY/2);

   SDL_SetWindowPosition( mWindowHandle, posX, posY);
}

bool SDLWindow::setSize( const Point2I &newSize )
{
   SDL_SetWindowSize(mWindowHandle, newSize.x, newSize.y);

   // Let GFX get an update about the new resolution
   if (mTarget.isValid())
		mTarget->resetMode();

	InvalidateRect( NULL, NULL, true );

	return true;
}

bool SDLWindow::isOpen()
{
	return mWindowHandle;
}

bool SDLWindow::isVisible()
{
	// Is the window open and visible, ie. not minimized?
	if(!mWindowHandle)
		return false;

   if (mOffscreenRender)
      return true;

   U32 flags = SDL_GetWindowFlags( mWindowHandle );   
   if( flags & SDL_WINDOW_SHOWN)
      return true;

	return false;
}

bool SDLWindow::isFocused()
{
   if (mOffscreenRender)
      return true;

   U32 flags = SDL_GetWindowFlags( mWindowHandle );   
   if( flags & SDL_WINDOW_INPUT_FOCUS || flags & SDL_WINDOW_INPUT_GRABBED || flags & SDL_WINDOW_MOUSE_FOCUS )
      return true;

	return true;
}

bool SDLWindow::isMinimized()
{
   if (mOffscreenRender)
      return false;

   U32 flags = SDL_GetWindowFlags( mWindowHandle );   
   if( flags & SDL_WINDOW_MINIMIZED)
      return true;

    return false;
}

bool SDLWindow::isMaximized()
{
   if (mOffscreenRender)
      return true;

   U32 flags = SDL_GetWindowFlags( mWindowHandle );   
   if( flags & SDL_WINDOW_MAXIMIZED)
      return true;

    return false;
}

WindowId SDLWindow::getWindowId()
{
	return mWindowId;
}

void SDLWindow::minimize()
{
   if (mOffscreenRender)
      return;

	SDL_MinimizeWindow( mWindowHandle );
}

void SDLWindow::maximize()
{
   if (mOffscreenRender)
      return;

	SDL_MaximizeWindow( mWindowHandle );
}

void SDLWindow::restore()
{
   if (mOffscreenRender)
      return;

	SDL_RestoreWindow( mWindowHandle );
}

void SDLWindow::hide()
{
   if (mOffscreenRender)
      return;

	SDL_HideWindow( mWindowHandle );
}

void SDLWindow::show()
{
   if (mOffscreenRender)
      return;

	SDL_RaiseWindow( mWindowHandle );
}

void SDLWindow::close()
{
	delete this;
}

void SDLWindow::defaultRender()
{
	// TODO SDL
}

void SDLWindow::_triggerMouseLocationNotify()
{
   int winX, winY;
   SDL_GetMouseState(&winX, &winY);
   if(!mMouseLocked)
      mouseEvent.trigger(getWindowId(), 0, winX, winY, false);
   else
      mouseEvent.trigger(getWindowId(), 0, winX-(mVideoMode.resolution.x/2), winY-(mVideoMode.resolution.y/2), true);
}

void SDLWindow::_triggerMouseButtonNotify(const SDL_Event& event)
{
   S32 action = (event.type == SDL_MOUSEBUTTONDOWN) ? SI_MAKE : SI_BREAK;
   S32 button = -1;

   switch (event.button.button)
   {
      case SDL_BUTTON_LEFT:
         button = 0;
         break;
      case SDL_BUTTON_RIGHT:
         button = 1;
         break;
      case SDL_BUTTON_MIDDLE:
         button = 2;
         break;
      default:
         return;
   }
   
   buttonEvent.trigger(getWindowId(), 0, action, button );
}

void SDLWindow::_triggerKeyNotify(const SDL_Event& evt)
{
   U32 inputAction = IA_MAKE;
   SDL_Keysym tKey = evt.key.keysym;

   if(evt.type == SDL_KEYUP)
   {
      inputAction = IA_BREAK;
   }

   if(evt.key.repeat)
   {
      inputAction = IA_REPEAT;
   }

   U32 modifiers = getTorqueModFromSDL(evt.key.keysym.mod);

   if(tKey.scancode)
   {
      keyEvent.trigger(getWindowId(), modifiers, inputAction, KeyMapSDL::getTorqueScanCodeFromSDL(tKey.scancode) );
      //Con::printf("Key %d : %d", tKey.sym, inputAction);
   }
}

void SDLWindow::_triggerTextNotify(const SDL_Event& evt)
{
   for(int i = 0; i < 32; ++i)
   {
      if(!evt.text.text[i])
         break;

      charEvent.trigger(getWindowId(), 0, evt.text.text[i] );
      //Con::printf("Char %d : %d", printable, inputAction);
   }
}

void SDLWindow::_processSDLEvent(SDL_Event &evt)
{
   switch(evt.type)
   {        
      case SDL_KEYDOWN:
      case SDL_KEYUP:
      {
         _triggerKeyNotify(evt);
         break;
      }

      case SDL_TEXTINPUT:
      {         
         _triggerTextNotify(evt);
         break;
      }

      case SDL_MOUSEMOTION:
      {
         _triggerMouseLocationNotify();
         break;
      }

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      {
         appEvent.trigger(getWindowId(), GainFocus);
         _triggerMouseLocationNotify();
         _triggerMouseButtonNotify(evt);
         
         break;
      }

      case SDL_WINDOWEVENT:
      {
         switch( evt.window.event )
         {
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_RESIZED:
            {
               int width, height;
               SDL_GetWindowSize( mWindowHandle, &width, &height );
               mVideoMode.resolution.set( width, height );
               getGFXTarget()->resetMode();
               break;
            }

            default:
               break;
         }
      }
   }

}

//-----------------------------------------------------------------------------
// Mouse Locking
//-----------------------------------------------------------------------------

void SDLWindow::setMouseLocked( bool enable )
{
   if (mOffscreenRender)
      return;

	mMouseLocked = enable;
   SDL_GetMouseState(&mMouseLockPosition.x, &mMouseLockPosition.y);
}

const UTF16 *SDLWindow::getWindowClassName()
{
   // TODO SDL
	return L"WindowClassName";
}

const UTF16 *SDLWindow::getCurtainWindowClassName()
{
   // TODO SDL
	return L"CurtainWindowClassName";
}