// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIPROGRESSCTRL_H_
#define _GUIPROGRESSCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _GUITEXTCTRL_H_
#include "gui/controls/guiTextCtrl.h"
#endif


class GuiProgressCtrl : public GuiTextCtrl
{
private:
   typedef GuiTextCtrl Parent;

   F32 mProgress;

public:
   //creation methods
   DECLARE_CONOBJECT(GuiProgressCtrl);
   DECLARE_CATEGORY( "Gui Values" );
   DECLARE_DESCRIPTION( "A control that display a horizontal progress bar.  The bar is\n"
      "rendered using as a filled rectangle (properties determined by profile)." );
   GuiProgressCtrl();

   //console related methods
   virtual const char *getScriptValue();
   virtual void setScriptValue(const char *value);

   void onPreRender();
   void onRender(Point2I offset, const RectI &updateRect);
};

#endif
