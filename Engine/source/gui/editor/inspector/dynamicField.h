// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_DYNAMICFIELD_H_
#define _GUI_INSPECTOR_DYNAMICFIELD_H_

#include "console/simFieldDictionary.h"
#include "gui/editor/inspector/field.h"


class GuiInspectorDynamicField : public GuiInspectorField
{
   typedef GuiInspectorField Parent;   

public:

   GuiInspectorDynamicField( GuiInspector *inspector, GuiInspectorGroup* parent, SimFieldDictionary::Entry* field );
   GuiInspectorDynamicField() {};
   ~GuiInspectorDynamicField() {};

   DECLARE_CONOBJECT( GuiInspectorDynamicField );

   virtual void             setData( const char* data, bool callbacks = true );
   virtual const char*      getData( U32 inspectObjectIndex = 0 );
   virtual StringTableEntry getFieldName() { return ( mDynField != NULL ) ? mDynField->slotName : StringTable->insert( "" ); }
   virtual StringTableEntry getRawFieldName() { return getFieldName(); }

   virtual bool onAdd();

   void renameField( const char* newFieldName );
   GuiControl* constructRenameControl();

   virtual bool updateRects();
   virtual void setInspectorField( AbstractClassRep::Field *field, 
                                   StringTableEntry caption = NULL,
                                   const char *arrayIndex = NULL );

protected:

   virtual void _executeSelectedCallback();

protected:

   /// Dynamic field dictionary entry for first target object only.
   SimFieldDictionary::Entry* mDynField;
   
   SimObjectPtr<GuiTextEditCtrl> mRenameCtrl;
   GuiBitmapButtonCtrl*          mDeleteButton;
   RectI                         mDeleteRect;
   RectI                         mValueRect;
};

#endif // _GUI_INSPECTOR_DYNAMICFIELD_H_
