// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_VARIABLEFIELD_H_
#define _GUI_INSPECTOR_VARIABLEFIELD_H_

#ifndef _GUI_INSPECTOR_FIELD_H_
#include "gui/editor/inspector/field.h"
#endif

class GuiInspectorGroup;
class GuiInspector;


class GuiInspectorVariableField : public GuiInspectorField
{
   friend class GuiInspectorField;

public:

   typedef GuiInspectorField Parent;

   GuiInspectorVariableField();
   virtual ~GuiInspectorVariableField();

   DECLARE_CONOBJECT( GuiInspectorVariableField );
   DECLARE_CATEGORY( "Gui Editor" );

   virtual bool onAdd();


   virtual void setValue( const char* newValue );
   virtual const char* getValue() { return NULL; }
   virtual void updateValue();
   virtual void setData( const char* data, bool callbacks = true );
   virtual const char* getData( U32 inspectObjectIndex = 0 );
   virtual void updateData() {};

protected:

};

#endif // _GUI_INSPECTOR_VARIABLEFIELD_H_
