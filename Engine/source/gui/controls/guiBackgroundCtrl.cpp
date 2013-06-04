// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/console.h"
#include "gui/controls/guiBackgroundCtrl.h"

IMPLEMENT_CONOBJECT(GuiBackgroundCtrl);

ConsoleDocClass( GuiBackgroundCtrl,
   "@brief Renders a background, so you can have a backdrop for your GUI.\n\n"

   "Deprecated\n\n"

   "@ingroup GuiImages\n"

   "@internal"
);

//--------------------------------------------------------------------------
GuiBackgroundCtrl::GuiBackgroundCtrl() : GuiControl()
{
   mDraw = false;
   mIsContainer = true;
}

//--------------------------------------------------------------------------
void GuiBackgroundCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   if ( mDraw )
      Parent::onRender( offset, updateRect );

   renderChildControls(offset, updateRect);
}


