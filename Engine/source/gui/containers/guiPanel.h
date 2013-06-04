// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GUI_PANEL_H_
#define _GUI_PANEL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif
#ifndef _GUITICKCTRL_H_
#include "gui/shiny/guiTickCtrl.h"
#endif
#ifndef _GUICONTAINER_H_
#include "gui/containers/guiContainer.h"
#endif


/// The GuiPanel panel is a container that when opaque will
/// draw a left to right gradient using its profile fill and
/// fill highlight colors.
///
/// @addtogroup gui_container_group Containers
///
/// @ingroup gui_group Gui System
/// @{
class GuiPanel : public GuiContainer
{
private:
   typedef GuiContainer Parent;

public:
   // Constructor/Destructor/ConObject Declaration
   GuiPanel();
   virtual ~GuiPanel();

   DECLARE_CONOBJECT(GuiPanel);

   // GuiControl
   void onRender(Point2I offset, const RectI &updateRect);
   void setVisible(bool value) { Parent::setVisible(value); setUpdateLayout( updateParent ); }
};
/// @}

#endif // _GUI_PANEL_H_