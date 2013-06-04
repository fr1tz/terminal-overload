// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_CUSTOMFIELD_H_
#define _GUI_INSPECTOR_CUSTOMFIELD_H_

#include "console/simFieldDictionary.h"
#include "gui/editor/inspector/field.h"

class GuiInspectorCustomField : public GuiInspectorField
{
   typedef GuiInspectorField Parent;   

public:

   GuiInspectorCustomField( GuiInspector *inspector, GuiInspectorGroup* parent, SimFieldDictionary::Entry* field );
   GuiInspectorCustomField();
   ~GuiInspectorCustomField() {};

   DECLARE_CONOBJECT( GuiInspectorCustomField );

   virtual void             setData( const char* data, bool callbacks = true );
   virtual const char*      getData( U32 inspectObjectIndex = 0 );
   virtual void             updateValue();
   virtual StringTableEntry getFieldName() { return StringTable->EmptyString(); }

   virtual void setDoc( const char* doc );
   virtual void setToolTip( StringTableEntry data );

   virtual bool onAdd();

   virtual void setInspectorField( AbstractClassRep::Field *field, 
                                   StringTableEntry caption = NULL,
                                   const char *arrayIndex = NULL );
   
   virtual GuiControl* constructEditControl();

   virtual void setValue( const char* newValue );

protected:

   virtual void _executeSelectedCallback();

protected:

   String mCustomValue;
   StringTableEntry mDoc;
};

#endif // _GUI_INSPECTOR_DYNAMICFIELD_H_
