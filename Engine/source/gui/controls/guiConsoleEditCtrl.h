// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUICONSOLEEDITCTRL_H_
#define _GUICONSOLEEDITCTRL_H_

#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif
#ifndef _GUITEXTEDITCTRL_H_
#include "gui/controls/guiTextEditCtrl.h"
#endif
#ifndef _GUISCROLLCTRL_H_
#include "gui/containers/guiScrollCtrl.h"
#endif

class GuiConsoleEditCtrl : public GuiTextEditCtrl
{
private:
   typedef GuiTextEditCtrl Parent;

protected:
   bool mUseSiblingScroller;
   GuiScrollCtrl* mSiblingScroller;

public:
   GuiConsoleEditCtrl();
   
   DECLARE_CONOBJECT(GuiConsoleEditCtrl);
   DECLARE_CATEGORY( "Gui Editor" );

   static void initPersistFields();

   bool onKeyDown(const GuiEvent &event);
};

#endif //_GUI_TEXTEDIT_CTRL_H
