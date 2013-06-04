// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/buttons/guiRadioCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gui/core/guiCanvas.h"

IMPLEMENT_CONOBJECT(GuiRadioCtrl);

ConsoleDocClass( GuiRadioCtrl,
   "@brief A button based around the radio concept.\n\n"
   
   "GuiRadioCtrl's functionality is based around GuiButtonBaseCtrl's ButtonTypeRadio type.\n\n"

   "A button control with a radio box and a text label.\n"
   "This control is used in groups where multiple radio buttons\n"
   "present a range of options out of which one can be chosen.\n"
   "A radio button automatically signals its siblings when it is\n"
   "toggled on.\n\n"
   
   "@tsexample\n"
   "// Create a GuiCheckBoxCtrl that calls randomFunction with its current value when clicked.\n"
   "%radio = new GuiRadioCtrl()\n"
   "{\n"
   "   profile = \"GuiRadioProfile\";\n"
   "};\n"
   "@endtsexample\n\n"
   
   "@ingroup GuiButtons"
);

//-----------------------------------------------------------------------------

GuiRadioCtrl::GuiRadioCtrl()
{
   mButtonType = ButtonTypeRadio;
}

