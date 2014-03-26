#include "windowManager/platformWindowMgr.h"
#include "windowManager/sdl/sdlWindow.h"

#include "SDL.h"

namespace
{   
   SDL_MessageBoxButtonData MBOkCancelData[2], MBRetryCancelData[2], MBSaveDontSaveData[2], MBSaveDontSaveCancelData[3];

   bool needInitMsgBox = true;

   void initMsgBox_ButtonData()
   {
      needInitMsgBox = false;

      SDL_MessageBoxButtonData MBOkButton;
      MBOkButton.text = "Ok";
      MBOkButton.buttonid = MROk;
      MBOkButton.flags = 0;
      
      SDL_MessageBoxButtonData MBCancelButton;
      MBCancelButton.text = "Cancel";
      MBCancelButton.buttonid = MRCancel;
      MBCancelButton.flags = 0;
      
      SDL_MessageBoxButtonData MBRetryButton;
      MBRetryButton.text = "Retry";
      MBRetryButton.buttonid = MROk;
      MBRetryButton.flags = 0;
      
      SDL_MessageBoxButtonData MBSaveButton;
      MBSaveButton.text = "Save";
      MBSaveButton.buttonid = MROk;
      MBSaveButton.flags = 0;
      
      SDL_MessageBoxButtonData MBDontSaveButton;
      MBDontSaveButton.text = "Don't Save";
      MBDontSaveButton.buttonid = MRRetry;
      MBDontSaveButton.flags = 0;

      MBOkCancelData[0] = MBOkButton;
      MBOkCancelData[1] = MBCancelButton;

      MBRetryCancelData[0] = MBRetryButton;
      MBRetryCancelData[1] = MBCancelButton;

      MBSaveDontSaveData[0] = MBSaveButton;
      MBSaveDontSaveData[1] = MBDontSaveButton;

      MBSaveDontSaveCancelData[0] = MBSaveButton;
      MBSaveDontSaveCancelData[1] = MBDontSaveButton;
      MBSaveDontSaveCancelData[2] = MBRetryButton;
   }
}

#ifdef TORQUE_SDL
S32 Platform::messageBox(const UTF8 *title, const UTF8 *message, MBButtons buttons, MBIcons icon)
{
   if(needInitMsgBox)
      initMsgBox_ButtonData();

   SDL_Window *window = WindowManager->getFirstWindow() ? SDL_GetWindowFromID( WindowManager->getFirstWindow()->getWindowId() ) : NULL;
   if(buttons == MBOk)
      return SDL_ShowSimpleMessageBox(0, title, message,  window );

   SDL_MessageBoxData boxData;
   boxData.title = title;
   boxData.message = message;
   boxData.window = window;
   boxData.flags = 0;
   boxData.colorScheme = NULL;
   boxData.buttons = NULL;
   boxData.numbuttons = 0;

   int res = MBOk;

   switch(buttons)
   {
      case MBOkCancel:
      {
         boxData.buttons = &MBOkCancelData[0];
         boxData.numbuttons = 2;
         break;
      }
      case MBRetryCancel:
      {
         boxData.buttons = &MBRetryCancelData[0];
         boxData.numbuttons = 2;
         break;
      }
      case MBSaveDontSave:
      {
         boxData.buttons = &MBSaveDontSaveData[0];
         boxData.numbuttons = 2;
         break;
      }
      case MBSaveDontSaveCancel:
      {
         boxData.buttons = &MBSaveDontSaveCancelData[0];
         boxData.numbuttons = 3;
         break;
      }
      default:
      {
         return MBOk;
      }
   }

   SDL_ShowMessageBox(&boxData, &res);
   return res;
}

//--------------------------------------
void Platform::AlertOK(const char *windowTitle, const char *message)
{
   SDL_ShowCursor(1);
   Platform::messageBox(windowTitle, message, MBOk );
}

//--------------------------------------
bool Platform::AlertOKCancel(const char *windowTitle, const char *message)
{
   SDL_ShowCursor(1);
   return MROk == Platform::messageBox(windowTitle, message, MBOkCancel );
}

//--------------------------------------
bool Platform::AlertRetry(const char *windowTitle, const char *message)
{
   SDL_ShowCursor(1);
   return MROk == Platform::messageBox(windowTitle, message, MBRetryCancel );
}
#endif