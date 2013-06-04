// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIBACKGROUNDCTRL_H_
#define _GUIBACKGROUNDCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

/// Renders a background, so you can have a backdrop for your GUI.
class GuiBackgroundCtrl : public GuiControl
{
private:
   typedef GuiControl Parent;

public:
   bool  mDraw;

   //creation methods
   DECLARE_CONOBJECT(GuiBackgroundCtrl);
   DECLARE_CATEGORY( "Gui Containers" );
   
   GuiBackgroundCtrl();

   void onRender(Point2I offset, const RectI &updateRect);
};

#endif
