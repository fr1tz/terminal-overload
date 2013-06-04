// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_DYNAMICGROUP_H_
#define _GUI_INSPECTOR_DYNAMICGROUP_H_

#include "gui/editor/inspector/group.h"

#include "console/simFieldDictionary.h"


class GuiInspectorDynamicGroup : public GuiInspectorGroup
{
private:
   typedef GuiInspectorGroup Parent;
   GuiControl* mAddCtrl;


public:
   DECLARE_CONOBJECT(GuiInspectorDynamicGroup);
   GuiInspectorDynamicGroup() { /*mNeedScroll=false;*/ };
   GuiInspectorDynamicGroup( StringTableEntry groupName, SimObjectPtr<GuiInspector> parent )
      : GuiInspectorGroup( groupName, parent) { /*mNeedScroll=false;*/};

   //-----------------------------------------------------------------------------
   // inspectGroup is overridden in GuiInspectorDynamicGroup to inspect an 
   // objects FieldDictionary (dynamic fields) instead of regular persistent
   // fields.
   bool inspectGroup();
   virtual void updateAllFields();

   // For scriptable dynamic field additions
   void addDynamicField();

   // Clear our fields (delete them)
   void clearFields();

   // Find an already existent field by name in the dictionary
   virtual SimFieldDictionary::Entry* findDynamicFieldInDictionary( StringTableEntry fieldName );
protected:
   // create our inner controls when we add
   virtual bool createContent();

};

#endif // _GUI_INSPECTOR_DYNAMICGROUP_H_
