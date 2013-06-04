// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUICHECKBOXCTRL_H_
#define _GUICHECKBOXCTRL_H_

#ifndef _GUIBUTTONBASECTRL_H_
   #include "gui/buttons/guiButtonBaseCtrl.h"
#endif


/// A checkbox button.
class GuiCheckBoxCtrl : public GuiButtonBaseCtrl
{
   public:
   
      typedef GuiButtonBaseCtrl Parent;

   protected:

      S32 mIndent;
       
   public:
   
      GuiCheckBoxCtrl();
      
      S32 getIndent() const { return mIndent; }
      void setIndent( S32 value ) { mIndent = value; }

      void onRender( Point2I offset, const RectI &updateRect );
      bool onWake();

      void autoSize();

      DECLARE_CONOBJECT( GuiCheckBoxCtrl );
      DECLARE_DESCRIPTION( "A toggle button that displays a text label and an on/off checkbox." );
};

#endif //_GUI_CHECKBOX_CTRL_H
