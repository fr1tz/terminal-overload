// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIRADIOCTRL_H_
#define _GUIRADIOCTRL_H_

#ifndef _GUICHECKBOXCTRLL_H_
#include "gui/buttons/guiCheckBoxCtrl.h"
#endif

// the radio button renders exactly the same as the check box
// the only difference is it sends messages to its siblings to
// turn themselves off.

class GuiRadioCtrl : public GuiCheckBoxCtrl
{
   typedef GuiCheckBoxCtrl Parent;

public:
   DECLARE_CONOBJECT(GuiRadioCtrl);
   DECLARE_DESCRIPTION( "A button control with a radio box and a text label.\n"
                        "This control is used in groups where multiple radio buttons\n"
                        "present a range of options out of which one can be chosen.\n"
                        "A radio button automatically signals its siblings when it is\n"
                        "toggled on." );
   GuiRadioCtrl();
};

#endif //_GUI_RADIO_CTRL_H
