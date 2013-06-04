// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "windowManager/platformWindow.h"


//-----------------------------------------------------------------------------

void PlatformWindow::setFullscreen( const bool fullscreen )
{
   // Notify listeners that we will acquire the screen
   if(fullscreen && !Journal::IsDispatching())
      appEvent.trigger(getWindowId(),GainScreen);

   // Do platform specific fullscreen code
   _setFullscreen(fullscreen);

   // Notify listeners that we released the screen
   if(!fullscreen && !Journal::IsDispatching())
      appEvent.trigger(getWindowId(),LoseScreen);
}

//-----------------------------------------------------------------------------

bool PlatformWindow::shouldNotTranslate( U32 modifiers, U32 keyCode ) const
{
   if( mWindowInputGenerator )
      return mWindowInputGenerator->wantAsKeyboardEvent( modifiers, keyCode );
   else
      return false;
}
