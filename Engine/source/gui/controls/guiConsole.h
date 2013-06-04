// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUICONSOLE_H_
#define _GUICONSOLE_H_

#ifndef _GUIARRAYCTRL_H_
#include "gui/core/guiArrayCtrl.h"
#endif

#ifndef _CONSOLE_LOGGER_H_
#include "console/consoleLogger.h"
#endif


class GuiConsole : public GuiArrayCtrl
{
   private:
      typedef GuiArrayCtrl Parent;

      Resource<GFont> mFont;

      S32 getMaxWidth(S32 startIndex, S32 endIndex);

   protected:

      /// @name Callbacks
      /// @{

      DECLARE_CALLBACK( void, onMessageSelected, ( ConsoleLogEntry::Level level, const char* message ) );

      /// @}

      // GuiArrayCtrl.
      virtual void onCellSelected( Point2I cell );

   public:
      GuiConsole();
      DECLARE_CONOBJECT(GuiConsole);
      DECLARE_CATEGORY( "Gui Editor" );
      DECLARE_DESCRIPTION( "Control that displays the console log text." );

      // GuiArrayCtrl.
      virtual bool onWake();
      virtual void onPreRender();
      virtual void onRenderCell(Point2I offset, Point2I cell, bool selected, bool mouseOver);
};

#endif
