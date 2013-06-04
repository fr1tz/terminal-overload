// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUICTRLARRAYCTRL_H_
#define _GUICTRLARRAYCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#include "gfx/gfxDevice.h"
#include "console/console.h"
#include "console/consoleTypes.h"

class GuiControlArrayControl : public GuiControl
{
private:
   typedef GuiControl Parent;

   bool mResizing;

   S32 mCols;
   Vector<S32> mColumnSizes;
   S32 mRowSize;
   S32 mRowSpacing;
   S32 mColSpacing;

public:
   GuiControlArrayControl();

   bool resize(const Point2I &newPosition, const Point2I &newExtent);

   bool onWake();
   void onSleep();
   void inspectPostApply();

   bool updateArray();

   void addObject(SimObject *obj);
   void removeObject(SimObject *obj);

   bool reOrder(SimObject* obj, SimObject* target = 0);

   static void initPersistFields();
   DECLARE_CONOBJECT(GuiControlArrayControl);
   DECLARE_CATEGORY( "Gui Containers" );
};

#endif