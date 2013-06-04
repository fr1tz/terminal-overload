// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIDYNAMICCTRLARRAYCTRL_H_
#define _GUIDYNAMICCTRLARRAYCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#include "gfx/gfxDevice.h"
#include "console/console.h"
#include "console/consoleTypes.h"

class GuiDynamicCtrlArrayControl : public GuiControl
{
   typedef GuiControl Parent;

public:

   GuiDynamicCtrlArrayControl();
   virtual ~GuiDynamicCtrlArrayControl();

   DECLARE_CONOBJECT(GuiDynamicCtrlArrayControl);
   DECLARE_CATEGORY( "Gui Containers" );

   // ConsoleObject
   static void initPersistFields();

   // SimObject
   void inspectPostApply();

   // SimSet
   void addObject(SimObject *obj);

   // GuiControl
   bool resize(const Point2I &newPosition, const Point2I &newExtent);
   void childResized(GuiControl *child);

   // GuiDynamicCtrlArrayCtrl
   void refresh();

protected:

   S32 mCols;
   S32 mRows;
   S32 mRowSize;
   S32 mColSize;
   S32 mRowSpacing;
   S32 mColSpacing;
   bool mResizing;
   bool mSizeToChildren;
   bool mAutoCellSize;
   bool mFrozen;
   bool mDynamicSize;   
   bool mFillRowFirst;

   RectSpacingI mPadding;
};

#endif // _GUIDYNAMICCTRLARRAYCTRL_H_