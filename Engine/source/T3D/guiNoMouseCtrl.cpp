// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/core/guiControl.h"

//------------------------------------------------------------------------------
class GuiNoMouseCtrl : public GuiControl
{
   typedef GuiControl Parent;
   public:

      // GuiControl
      bool pointInControl(const Point2I &)   { return(false); }
      DECLARE_CONOBJECT(GuiNoMouseCtrl);
      DECLARE_CATEGORY( "Gui Other" );
};
IMPLEMENT_CONOBJECT(GuiNoMouseCtrl);

ConsoleDocClass( GuiNoMouseCtrl,
				"@brief No known usage, possibly Legacy.\n\n"
				"Not used at all, internal until deprecated\n\n"
				"@internal");