// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIEASEVIEWCTRL_H_
#define _GUIEASEVIEWCTRL_H_

#ifndef _GUICONTROL_H_
   #include "gui/core/guiControl.h"
#endif
#ifndef _MEASE_H_
   #include "math/mEase.h"
#endif


/// Control to visualize an EaseF.
class GuiEaseViewCtrl : public GuiControl
{
   public:
   
      typedef GuiControl Parent;

   protected:

      EaseF mEase;         // ease we are visualizing
      ColorF mAxisColor;   // color to draw axis in
      ColorF mEaseColor;   // color to draw ease in
      F32 mEaseWidth;      // width of lines
   
   public:
   
      GuiEaseViewCtrl();

      bool onWake();
      void onSleep();

      void onRender( Point2I, const RectI &);
      static void initPersistFields();
      
      DECLARE_CONOBJECT( GuiEaseViewCtrl );
      DECLARE_CATEGORY( "Gui Editor" );
      DECLARE_DESCRIPTION( "Control that display an EaseF curve." );
};

#endif // !_GUIEASEVIEWCTRL_H_
