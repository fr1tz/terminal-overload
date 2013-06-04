// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_VARIABLEINSPECTOR_H_
#define _GUI_VARIABLEINSPECTOR_H_

#ifndef _GUI_INSPECTOR_H_
#include "gui/editor/guiInspector.h"
#endif


class GuiVariableInspector : public GuiInspector
{
   typedef GuiInspector Parent;

public:

   GuiVariableInspector();
   virtual ~GuiVariableInspector();

   DECLARE_CONOBJECT( GuiVariableInspector );
   DECLARE_CATEGORY( "Gui Editor" );

   virtual void inspectObject( SimObject *object ) {}

   virtual void loadVars( String searchString );


protected:

};

#endif // _GUI_VARIABLEINSPECTOR_H_