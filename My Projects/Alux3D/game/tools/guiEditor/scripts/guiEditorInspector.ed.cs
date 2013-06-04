// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Core for the main Gui Editor inspector that shows the properties of
// the currently selected control.


//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::update( %this, %inspectTarget )
{
   %this.inspect( %inspectTarget );
}

//=============================================================================================
//    Event Handlers.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onInspectorFieldModified( %this, %object, %fieldName, %arrayIndex, %oldValue, %newValue )
{
   // The instant group will try to add our
   // UndoAction if we don't disable it.   
   pushInstantGroup();

   %nameOrClass = %object.getName();
   if ( %nameOrClass $= "" )
      %nameOrClass = %object.getClassname();
      
   %action = new InspectorFieldUndoAction()
   {
      actionName = %nameOrClass @ "." @ %fieldName @ " Change";
      
      objectId = %object.getId();
      fieldName = %fieldName;
      fieldValue = %oldValue;
      arrayIndex = %arrayIndex;
                  
      inspectorGui = %this;
   };
   
   // Restore the instant group.
   popInstantGroup();
         
   %action.addToManager( GuiEditor.getUndoManager() );
   
   GuiEditor.updateUndoMenu();
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onInspectorPreFieldModification( %this, %fieldName, %arrayIndex )
{
   pushInstantGroup();
   %undoManager = GuiEditor.getUndoManager();
   
   %numObjects = %this.getNumInspectObjects();
   if( %numObjects > 1 )
      %action = %undoManager.pushCompound( "Multiple Field Edit" );
      
   for( %i = 0; %i < %numObjects; %i ++ )
   {
      %object = %this.getInspectObject( %i );
      
      %nameOrClass = %object.getName();
      if( %nameOrClass $= "" )
         %nameOrClass = %object.getClassname();

      %undo = new InspectorFieldUndoAction()
      {
         actionName = %nameOrClass @ "." @ %fieldName @ " Change";

         objectId = %object.getId();
         fieldName = %fieldName;
         fieldValue = %object.getFieldValue( %fieldName, %arrayIndex );
         arrayIndex = %arrayIndex;

         inspectorGui = %this;
      };
      
      if( %numObjects > 1 )
         %undo.addToManager( %undoManager );
      else
      {
         %action = %undo;
         break;
      }
   }
      
   %this.currentFieldEditAction = %action;
   popInstantGroup();
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onInspectorPostFieldModification( %this )
{
   if( %this.currentFieldEditAction.isMemberOfClass( "CompoundUndoAction" ) )
   {
      // Finish multiple field edit.
      GuiEditor.getUndoManager().popCompound();
   }
   else
   {
      // Queue single field undo.
      %this.currentFieldEditAction.addToManager( GuiEditor.getUndoManager() );
   }
   
   %this.currentFieldEditAction = "";
   GuiEditor.updateUndoMenu();
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onInspectorDiscardFieldModification( %this )
{
   %this.currentFieldEditAction.undo();
   
   if( %this.currentFieldEditAction.isMemberOfClass( "CompoundUndoAction" ) )
   {
      // Multiple field editor.  Pop and discard.
      GuiEditor.getUndoManager().popCompound( true );
   }
   else
   {
      // Single field edit.  Just kill undo action.
      %this.currentFieldEditAction.delete();
   }
   
   %this.currentFieldEditAction = "";
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onFieldSelected( %this, %fieldName, %fieldTypeStr, %fieldDoc )
{
   GuiEditorFieldInfo.setText( "<font:ArialBold:14>" @ %fieldName @ "<font:ArialItalic:14> (" @ %fieldTypeStr @ ") " NL "<font:Arial:14>" @ %fieldDoc );
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onBeginCompoundEdit( %this )
{
   GuiEditor.getUndoManager().pushCompound( "Multiple Field Edits" );
}

//---------------------------------------------------------------------------------------------

function GuiEditorInspectFields::onEndCompoundEdit( %this )
{
   GuiEditor.getUndoManager().popCompound();
}
