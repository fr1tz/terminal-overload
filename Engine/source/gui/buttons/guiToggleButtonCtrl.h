// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUITOGGLEBUTTONCTRL_H_
#define _GUITOGGLEBUTTONCTRL_H_

#ifndef _GUIBUTTONCTRL_H_
#include "gui/buttons/guiButtonCtrl.h"
#endif

class GuiToggleButtonCtrl : public GuiButtonCtrl
{
   typedef GuiButtonCtrl Parent;
public:
   DECLARE_CONOBJECT(GuiToggleButtonCtrl);
   GuiToggleButtonCtrl();

   virtual void onPreRender();
   void onRender(Point2I offset, const RectI &updateRect);
};

#endif //_GUITOGGLEBUTTONCTRL_H_
