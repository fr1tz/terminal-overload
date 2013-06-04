// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_GROUP_H_
#define _GUI_INSPECTOR_GROUP_H_

#include "gui/core/guiCanvas.h"
#include "gui/controls/guiTextEditCtrl.h"
#include "gui/buttons/guiBitmapButtonCtrl.h"
#include "gui/containers/guiRolloutCtrl.h"

// Forward refs
class GuiInspector;
class GuiInspectorField;


/// The GuiInspectorGroup control is a helper control that the inspector
/// makes use of which houses a collapsible pane type control for separating
/// inspected objects fields into groups.  The content of the inspector is 
/// made up of zero or more GuiInspectorGroup controls inside of a GuiStackControl
///
class GuiInspectorGroup : public GuiRolloutCtrl
{
private:
   typedef GuiRolloutCtrl Parent;
public:
   // Members
   SimObjectPtr<GuiInspector>          mParent;
   Vector<GuiInspectorField*>          mChildren;
   GuiStackControl*                    mStack;
   Vector<GuiRolloutCtrl*>             mArrayCtrls;

   // Constructor/Destructor/Conobject Declaration
   GuiInspectorGroup();
   GuiInspectorGroup( const String& groupName, SimObjectPtr<GuiInspector> parent );
   virtual ~GuiInspectorGroup();
   
   DECLARE_CONOBJECT(GuiInspectorGroup);
   DECLARE_CATEGORY( "Gui Editor" );

   virtual GuiInspectorField* constructField( S32 fieldType );
   virtual GuiInspectorField* findField( const char *fieldName );

   // Publicly Accessible Information about this group
   const String& getGroupName() const { return mCaption; };
   SimObjectPtr<GuiInspector> getInspector() { return mParent; };

   bool onAdd();
   virtual bool inspectGroup();

   virtual void animateToContents();

   void clearFields();

   virtual bool updateFieldValue( StringTableEntry fieldName, const char *arrayIdx );
   virtual void updateAllFields();
   
   U32 getNumFields() const { return mChildren.size(); }

protected:
   // overridable method that creates our inner controls.
   virtual bool createContent();
   
   /// Determine the class that is a common ancestor to all inspected objects.
   AbstractClassRep* findCommonAncestorClass();
};

#endif // _GUI_INSPECTOR_GROUP_H_
