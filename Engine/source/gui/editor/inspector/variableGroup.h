// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_VARIABLEGROUP_H_
#define _GUI_INSPECTOR_VARIABLEGROUP_H_

#ifndef _GUI_INSPECTOR_GROUP_H_
#include "gui/editor/inspector/group.h"
#endif

// Forward refs
class GuiInspector;
class GuiInspectorField;

class GuiInspectorVariableGroup : public GuiInspectorGroup
{
public:

   typedef GuiInspectorGroup Parent;

   String mSearchString;

   GuiInspectorVariableGroup();
   virtual ~GuiInspectorVariableGroup();

   DECLARE_CONOBJECT(GuiInspectorVariableGroup);
   DECLARE_CATEGORY( "Gui Editor" );

   virtual GuiInspectorField* constructField( S32 fieldType );

   virtual bool inspectGroup();

protected:
};

#endif // _GUI_INSPECTOR_VARIABLEGROUP_H_
