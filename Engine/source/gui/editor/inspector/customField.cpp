// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/editor/inspector/customField.h"
#include "gui/editor/guiInspector.h"

//-----------------------------------------------------------------------------
// GuiInspectorCustomField - Child class of GuiInspectorField 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( GuiInspectorCustomField );

ConsoleDocClass( GuiInspectorCustomField,
   "@brief A control that allows to edit the custom properties (text) of one or more SimObjects.\n\n"
   "Editor use only.\n\n"
   "@internal"
);

GuiInspectorCustomField::GuiInspectorCustomField( GuiInspector *inspector,
                                                    GuiInspectorGroup* parent, 
                                                    SimFieldDictionary::Entry* field )
{
   mInspector = inspector;
   mParent = parent;
   setBounds(0,0,100,20);   
}

GuiInspectorCustomField::GuiInspectorCustomField()
{
   mInspector = NULL;
   mParent = NULL;
}

void GuiInspectorCustomField::setData( const char* data, bool callbacks )
{
   mCustomValue = data;

   // Force our edit to update
   updateValue();
}

const char* GuiInspectorCustomField::getData( U32 inspectObjectIndex )
{
   return mCustomValue;
}

void GuiInspectorCustomField::updateValue()
{
   setValue( mCustomValue );
}

void GuiInspectorCustomField::setDoc( const char* doc )
{
   mDoc = StringTable->insert( doc, true );
}

void GuiInspectorCustomField::setToolTip( StringTableEntry data )
{
   static StringTableEntry sTooltipProfile = StringTable->insert( "tooltipProfile" );
   static StringTableEntry sHoverTime = StringTable->insert( "hovertime" );
   static StringTableEntry sTooltip = StringTable->insert( "tooltip" );
   
   mEdit->setDataField( sTooltipProfile, NULL, "GuiToolTipProfile" );
   mEdit->setDataField( sHoverTime, NULL, "1000" );
   mEdit->setDataField( sTooltip, NULL, data );
}

bool GuiInspectorCustomField::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   return true;
}

void GuiInspectorCustomField::setInspectorField( AbstractClassRep::Field *field, 
                                                  StringTableEntry caption, 
                                                  const char*arrayIndex ) 
{
   // Override the base just to be sure it doesn't get called.
   // We don't use an AbstractClassRep::Field...

//    mField = field; 
//    mCaption = StringTable->EmptyString();
//    mRenameCtrl->setText( getFieldName() );
}

GuiControl* GuiInspectorCustomField::constructEditControl()
{
   GuiControl* retCtrl = new GuiTextCtrl();

   static StringTableEntry sProfile = StringTable->insert( "profile" );
   retCtrl->setDataField( sProfile, NULL, "GuiInspectorTextEditProfile" );

   // Register the object
   retCtrl->registerObject();

   return retCtrl;
}

void GuiInspectorCustomField::setValue( const char* newValue )
{
   GuiTextCtrl *ctrl = dynamic_cast<GuiTextCtrl*>( mEdit );
   if( ctrl != NULL )
      ctrl->setText( newValue );
}

void GuiInspectorCustomField::_executeSelectedCallback()
{
   Con::executef( mInspector, "onFieldSelected", mCaption, ConsoleBaseType::getType(TypeCaseString)->getTypeName(), mDoc );
}
