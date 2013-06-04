// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GUIRECTHANDLES_H_
#define _GUIRECTHANDLES_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

class GuiRectHandles : public GuiControl
{
private:
   typedef GuiControl Parent;

protected:
   RectF    mHandleRect;
   S32      mHandleSize;
   bool     mUseCustomColor;
   ColorI   mHandleColor;
   S32      mHitHandle;    // 0 = none, 1-8 = clockwise circle starting upper left, 9 = centre
   Point2I  mHitPoint;

public:
   DECLARE_CONOBJECT(GuiRectHandles);
   DECLARE_CATEGORY( "Gui Other" );
   DECLARE_DESCRIPTION( "Draws a box with handles for the user to manipulate.");

   GuiRectHandles();
   virtual ~GuiRectHandles();

   static void initPersistFields();

   virtual void onMouseUp(const GuiEvent &event);
   virtual void onMouseDown(const GuiEvent &event);
   virtual void onMouseDragged(const GuiEvent &event);

   virtual void onRender(Point2I offset, const RectI &updateRect);
};

#endif
