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
mPosition(0,0),
mFullscreen(false)
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
	bool needCurtain = (mVideoMode.fullScreen != mode.fullScreen);

	if(needCurtain)
   {
		Con::errorf("SDLWindow::setVideoMode - invoking curtain");
      mOwningManager->lowerCurtain();
   }

	mVideoMode = mode;
	mSuppressReset = true;

   // Can't switch to fullscreen while a child of another window
   if(mode.fullScreen && !Platform::getWebDeployment() && mOwningManager->getParentWindow())
   {
      mOldParent = (SDL_Window*)mOwningManager->getParentWindow();
      mOwningManager->setParentWindow(NULL);
   }
   else if(!mode.fullScreen && mOldParent)
   {
      mOwningManager->setParentWindow(mOldParent);
      mOldParent = NULL;
   }

	// Set our window to have the right style based on the mode
   if(mode.fullScreen && !Platform::getWebDeployment() && !mOffscreenRender)
	{		
      SDL_SetWindowFullscreen( mWindowHandle, SDL_WINDOW_FULLSCREEN);

      // TODO SDL 
      // Clear the menu bar from the window for full screen
      /*HMENU menu = GetMenu(mWindowHandle);
      if(menu)
      {
         SetMenu(mWindowHandle, NULL);
      }*/

      // When switching to Fullscreen, reset device after setting style
	   if(mTarget.isValid())
		   mTarget->resetMode();

      mFullscreen = true;
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

         // Put back the menu bar, if any
         if(mMenuHandle)
         {
            // TODO SDL
            //SetMenu(mWindowHandle, mMenuHandle);
         }
      }

      // Make sure we're the correct resolution for web deployment
      if (!Platform::getWebDeployment() || !mOwningManager->getParentWindow() || mOffscreenRender)
      {
         setSize(mode.resolution);
      }
      else
      {
         HWND parentWin = (HWND)mOwningManager->getParentWindow();
         RECT windowRect;
         GetClientRect(parentWin, &windowRect);
         Point2I res(windowRect.right-windowRect.left, windowRect.bottom-windowRect.top);
         if (res.x == 0 || res.y == 0)
         {
            // Must be too early in the window set up to obtain the parent's size.
            setSize(mode.resolution);
         }
         else
         {
            setSize(res);
         }
      }

      if (!mOffscreenRender)
      {
		   // We have to force Win32 to update the window frame and make the window
		   // visible and no longer topmost - this code might be possible to simplify.
		   // TODO SDL
      }

      mFullscreen = false;
	}

	mSuppressReset = false;

	if(needCurtain)
		mOwningManager->raiseCurtain();

   // TODO SDL
	//SetForegroundWindow(mWindowHandle);
}

bool SDLWindow::clearFullscreen()
{
	return true;
}

bool SDLWindow::isFullscreen()
{   
	return mFullscreen;
}

void SDLWindow::_setFullscreen(const bool fullscreen)
{
	if (fullscreen == mFullscreen)
		return;

	mFullscreen = fullscreen;
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
   // TODO SDL FOCUS
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
   // TODO SDL
   AssertFatal(0, "");
   return pos;
}

Point2I SDLWindow::screenToClient( const Point2I& pos )
{
   // TODO SDL
   AssertFatal(0, "");
   return pos;
}

void SDLWindow::centerWindow()
{
	// TODO SDL
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
	return true;
}

bool SDLWindow::isVisible()
{
	// Is the window open and visible, ie. not minimized?

	if(!mWindowHandle)
		return false;

   if (mOffscreenRender)
      return true;

   // TODO SDL
	return true;
}

bool SDLWindow::isFocused()
{

   if (mOffscreenRender)
      return true;

   // TODO SDL
	return true;
}

bool SDLWindow::isMinimized()
{
   if (mOffscreenRender)
      return false;

    // TODO SDL

    return false;
}

bool SDLWindow::isMaximized()
{
   if (mOffscreenRender)
      return true;

    // TODO SDL

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

	// TODO SDL
   AssertFatal(0, "");
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
         
   U32 modifiers = 0;
   SDL_Keysym tKey = evt.key.keysym;

   if(evt.type == SDL_KEYUP)
   {
      inputAction = IA_BREAK;
   }

   if(evt.key.repeat)
   {
      inputAction = IA_REPEAT;
   }

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
   }

}

//-----------------------------------------------------------------------------
// Accelerators
//-----------------------------------------------------------------------------

void SDLWindow::addAccelerator(Accelerator &accel)
{
	// TODO SDL
   AssertFatal(0, "");
}

void SDLWindow::removeAccelerator(Accelerator &accel)
{
	// TODO SDL
   AssertFatal(0, "");
}

//-----------------------------------------------------------------------------

bool SDLWindow::isAccelerator(const InputEventInfo &info)
{
	// TODO SDL
   AssertFatal(0, "");
	return false;
}

//-----------------------------------------------------------------------------

void SDLWindow::addAccelerators(AcceleratorList &list)
{
	// TODO SDL
}

void SDLWindow::removeAccelerators(AcceleratorList &list)
{
	// TODO SDL
}

//-----------------------------------------------------------------------------
// Mouse Locking
//-----------------------------------------------------------------------------

void SDLWindow::setMouseLocked( bool enable )
{

   if (mOffscreenRender)
      return;

	// TODO SDL
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