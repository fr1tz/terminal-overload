// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#include "gui/shiny/guiTickCtrl.h"

IMPLEMENT_CONOBJECT( GuiTickCtrl );

ConsoleDocClass( GuiTickCtrl,
	"@brief Brief Description.\n\n"
	"This Gui Control is designed to be subclassed to let people create controls "
	"which want to receive update ticks at a constant interval. This class was "
	"created to be the Parent class of a control which used a DynamicTexture "
	"along with a VectorField to create warping effects much like the ones found "
	"in visualization displays for iTunes or Winamp. Those displays are updated "
	"at the framerate frequency. This works fine for those effects, however for "
	"an application of the same type of effects for things like Gui transitions "
	"the framerate-driven update frequency is not desirable because it does not "
	"allow the developer to be able to have any idea of a consistent user-experience.\n\n"

	"Enter the ITickable interface. This lets the Gui control, in this case, update "
	"the dynamic texture at a constant rate of once per tick, even though it gets "
	"rendered every frame, thus creating a framerate-independent update frequency "
	"so that the effects are at a consistent speed regardless of the specifics "
	"of the system the user is on. This means that the screen-transitions will "
	"occur in the same time on a machine getting 300fps in the Gui shell as a "
	"machine which gets 150fps in the Gui shell.\n\n"

	"@ingroup GuiUtil\n");

//------------------------------------------------------------------------------

static ConsoleDocFragment _setProcessTicks(
   "This will set this object to either be processing ticks or not.\n\n"
   "@param tick (optional) True or nothing to enable ticking, false otherwise.\n\n"
   "@tsexample\n"
   "// Turn off ticking for a control, like a MenuBar (declared previously)\n"
   "%sampleMenuBar.setProcessTicks(false);\n"
   "@endtsexample\n\n",
   "GuiTickCtrl",
   "void setProcessTicks( bool tick )"
);
ConsoleMethod( GuiTickCtrl, setProcessTicks, void, 2, 3, "( [tick = true] ) - This will set this object to either be processing ticks or not" )
{
   if( argc == 3 )
      object->setProcessTicks( dAtob( argv[2] ) );
   else
      object->setProcessTicks();
}