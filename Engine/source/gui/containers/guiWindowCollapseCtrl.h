// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIWINDOWCOLLAPSECTRL_H_
#define _GUIWINDOWCOLLAPSECTRL_H_

#ifndef _GUIWINDOWCTRL_H_
   #include "gui/containers/guiWindowCtrl.h"
#endif


/// @addtogroup gui_container_group Containers
///
/// Legacy control.  Use GuiWindowCtrl with canCollapse=true.
///
/// @deprecated Functionality moved into GuiWindowCtrl.
///
/// @ingroup gui_group Gui System
/// @{
class GuiWindowCollapseCtrl : public GuiWindowCtrl
{
	public:

		typedef GuiWindowCtrl Parent;

      GuiWindowCollapseCtrl();

      DECLARE_CONOBJECT(GuiWindowCollapseCtrl);
      DECLARE_DESCRIPTION( "Legacy control.  Use GuiWindowCtrl with canCollapse=true." );
};
/// @}

#endif //_GUI_WINDOWCOLLAPSE_CTRL_H
