// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIBUBBLETEXTCTRL_H_
#define _GUIBUBBLETEXTCTRL_H_

#ifndef _GUITEXTCTRL_H_
#include "gui/controls/guiTextCtrl.h"
#endif
#ifndef _GUIMLTEXTCTRL_H_
#include "gui/controls/guiMLTextCtrl.h"
#endif

/// A single-line text control that displays its text in a multi-line popup when
/// clicked.
class GuiBubbleTextCtrl : public GuiTextCtrl
{
   private:
   
      typedef GuiTextCtrl Parent;

  protected:
      bool mInAction;
      GuiControl *mDlg;
      GuiControl *mPopup;
      GuiMLTextCtrl *mMLText;

      void popBubble();

  public:
  
      DECLARE_CONOBJECT(GuiBubbleTextCtrl);
      DECLARE_DESCRIPTION( "A single-line text control that displays its text in a multi-line\n"
         "popup when clicked." );

      GuiBubbleTextCtrl() { mInAction = false; }

      virtual void onMouseDown(const GuiEvent &event);
};

#endif /* _GUI_BUBBLE_TEXT_CONTROL_H_ */
