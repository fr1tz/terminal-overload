// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUITEXTEDITSLIDERCTRL_H_
#define _GUITEXTEDITSLIDERCTRL_H_

#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif
#ifndef _GUITEXTEDITCTRL_H_
#include "gui/controls/guiTextEditCtrl.h"
#endif

class GuiTextEditSliderCtrl : public GuiTextEditCtrl
{
   typedef GuiTextEditCtrl Parent;

public:

   enum CtrlArea
   {
      None,
      Slider,
      ArrowUp,
      ArrowDown
   };

   GuiTextEditSliderCtrl();
   ~GuiTextEditSliderCtrl();

   DECLARE_CONOBJECT(GuiTextEditSliderCtrl);
   DECLARE_CATEGORY( "Gui Values" );
   DECLARE_DESCRIPTION( "A text that shows a numeric value and up/down arrows to\n"
      "increase/decrease the value." );

   static void initPersistFields();

   virtual void getText(char *dest);  // dest must be of size
                                      // StructDes::MAX_STRING_LEN + 1

   virtual void setText(const char *txt);

   void setValue();
   void checkRange();
   void checkIncValue();
   void timeInc(U32 elapseTime);

   virtual bool onKeyDown(const GuiEvent &event);
   virtual void onMouseDown(const GuiEvent &event);
   virtual void onMouseDragged(const GuiEvent &event);
   virtual void onMouseUp(const GuiEvent &event);
   virtual bool onMouseWheelUp(const GuiEvent &event);
   virtual bool onMouseWheelDown(const GuiEvent &event);

   virtual void onPreRender();
   virtual void onRender(Point2I offset, const RectI &updateRect);

protected:

   Point2F mRange;
   F32 mIncAmount;
   F32 mValue;
   F32 mIncCounter;
   F32 mMulInc;
   StringTableEntry mFormat;
   U32 mMouseDownTime;
   bool mFocusOnMouseWheel;

   CtrlArea mTextAreaHit;
};

#endif //_GUITEXTEDITSLIDERCTRL_H_
