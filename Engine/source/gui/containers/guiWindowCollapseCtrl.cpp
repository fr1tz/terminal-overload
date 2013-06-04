// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/containers/guiWindowCollapseCtrl.h"

IMPLEMENT_CONOBJECT( GuiWindowCollapseCtrl );

ConsoleDocClass( GuiWindowCollapseCtrl,
   "@deprecated Use GuiWindowCtrl with GuiWindowCtrl::canCollapse = true.\n\n"
   "@internal"
);


//-----------------------------------------------------------------------------

GuiWindowCollapseCtrl::GuiWindowCollapseCtrl()
{
   mCanCollapse = true;
}
