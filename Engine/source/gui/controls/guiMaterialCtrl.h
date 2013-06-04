// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIMATERIALCTRL_H_
#define _GUIMATERIALCTRL_H_

#ifndef _GUICONTAINER_H_
#include "gui/containers/guiContainer.h"
#endif

class BaseMatInstance;


///
class GuiMaterialCtrl : public GuiContainer
{
private:
   typedef GuiContainer Parent;

protected:

   String mMaterialName;

   BaseMatInstance *mMaterialInst;

   static bool _setMaterial( void *object, const char *index, const char *data );

public:

   GuiMaterialCtrl();

   // ConsoleObject
   static void initPersistFields();
   void inspectPostApply();
   
   DECLARE_CONOBJECT(GuiMaterialCtrl);
   DECLARE_CATEGORY( "Gui Editor" );

   // GuiControl
   bool onWake();
   void onSleep();

   bool setMaterial( const String &materialName );

   void onRender( Point2I offset, const RectI &updateRect );
};

#endif // _GUIMATERIALCTRL_H_
