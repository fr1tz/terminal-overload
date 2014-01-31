// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Dialog for creating new GUIs.  Allows to enter an object name and
// select a GuiControl class to use for the toplevel object.


//---------------------------------------------------------------------------------------------

function GuiEditorNewGuiDialog::init( %this, %guiName, %guiClass )
{
   %this-->nameField.setValue( %guiName );
   
   // Initialize the class dropdown if we haven't already.
   
   %classDropdown = %this-->classDropdown;
   if( !%classDropdown.size() )
   {
      %classes = enumerateConsoleClassesByCategory( "Gui" );
      %count = getFieldCount( %classes );
      
      for( %i = 0; %i < %count; %i ++ )
      {
         %className = getField( %classes, %i );
         if( GuiEditor.isFilteredClass( %className )
             || !isMemberOfClass( %className, "GuiControl" ) )
            continue;
            
         %classDropdown.add( %className, 0 );
      }
      
      %classDropdown.sort();
   }
   
   %classDropdown.setText( "GuiControl" );
}

//=============================================================================================
//    Event Handlers.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEditorNewGuiDialog::onWake( %this )
{
   // Center the dialog.

   %root = %this.getRoot();
   %this.setPosition( %root.extent.x / 2 - %this.extent.x / 2, %root.extent.y / 2 - %this.extent.y / 2 );
}

//---------------------------------------------------------------------------------------------

function GuiEditorNewGuiDialog::onOK( %this )
{
   %name = %this-->nameField.getValue();
   %class = %this-->classDropdown.getText();

   // Make sure we don't clash with an existing object.
   // If there's an existing GUIControl with the name, ask to replace.
   // If there's an existing non-GUIControl with the name, or the name is invalid, refuse to create.

   if( isObject( %name ) && %name.isMemberOfClass( "GuiControl" ) )
   {
      if( MessageBox( "Warning", "Replace the existing control '" @ %name @ "'?", "OkCancel", "Question" ) == $MROk )
         %name.delete();
      else
         return;
   }

   if( Editor::validateObjectName( %name, false ) )
   {
      %this.getRoot().popDialog( %this );
      %obj = eval("return new " @ %class @ "(" @ %name @ ");");
      
      // Make sure we have no association with a filename.
      %obj.setFileName( "" );
      
      GuiEditContent(%obj);
   }
}

//---------------------------------------------------------------------------------------------

function GuiEditorNewGuiDialog::onCancel( %this )
{
   %this.getRoot().popDialog( %this );
}
