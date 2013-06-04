// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function EUndoManager::onUndo( %this )
{
}

function EUndoManager::onRedo( %this )
{
}

function EUndoManager::onAddUndo( %this )
{
}

function EUndoManager::onRemoveUndo( %this )
{
}

function EUndoManager::onClear( %this )
{
}

function EUndoManager::updateUndoMenu( %this, %editMenu )
{
   // TODO: If we ever fix the TerrainEditor and WorldEditor
   // to have descriptive UndoAction names then we can change
   // the text as part of the menu update.
      
   %undoName = %this.getNextUndoName();
   %redoName = %this.getNextRedoName();
   
   %editMenu.setItemName( 0, "Undo " @ %undoName );
   %editMenu.setItemName( 1, "Redo " @ %redoName );
   
   %editMenu.enableItem( 0, %undoName !$= "" );
   %editMenu.enableItem( 1, %redoName !$= "" );
}


/// A helper for submitting a creation undo action.
function MECreateUndoAction::submit( %undoObject )
{
   // The instant group will try to add our
   // UndoAction if we don't disable it.   
   pushInstantGroup();
   
   // Create the undo action.     
   %action = new MECreateUndoAction()
   {
      actionName = "Create " @ %undoObject.getClassName();
   };
   
   // Restore the instant group.
   popInstantGroup();
   
   // Set the object to undo.
   %action.addObject( %undoObject );
   
   // Submit it.
   %action.addToManager( Editor.getUndoManager() );
}

function MECreateUndoAction::onUndone( %this )
{
   EWorldEditor.syncGui();
}

function MECreateUndoAction::onRedone( %this )
{
   EWorldEditor.syncGui();
}


/// A helper for submitting a delete undo action.
/// If %wordSeperated is not specified or is false it is assumed %deleteObjects
/// is tab sperated.
function MEDeleteUndoAction::submit( %deleteObjects, %wordSeperated )
{
   // The instant group will try to add our
   // UndoAction if we don't disable it.   
   pushInstantGroup();
   
   // Create the undo action.     
   %action = new MEDeleteUndoAction()
   {
      actionName = "Delete";
   };

   // Restore the instant group.
   popInstantGroup();
   
   // Add the deletion objects to the action which
   // will take care of properly deleting them.
   %deleteObjects = trim( %deleteObjects );   
   
   if ( %wordSeperated )
   {
      %count = getWordCount( %deleteObjects );
      for ( %i = 0; %i < %count; %i++ )
      {
         %object = getWord( %deleteObjects, %i );
         %action.deleteObject( %object );
      }
   }
   else
   {
      %count = getFieldCount( %deleteObjects );
      for ( %i = 0; %i < %count; %i++ )
      {
         %object = getField( %deleteObjects, %i );
         %action.deleteObject( %object );
      }
   }
   
   // Submit it.
   %action.addToManager( Editor.getUndoManager() );
}

function MEDeleteUndoAction::onUndone( %this )
{
   EWorldEditor.syncGui();
}

function MEDeleteUndoAction::onRedone( %this )
{
   EWorldEditor.syncGui();
}
