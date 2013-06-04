// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//---------------------------------------------------------------------------------------------

function DatablockEditorPlugin::createUndo( %this, %class, %desc )
{
   pushInstantGroup();
   %action = new UndoScriptAction()
   {
      class = %class;
      superClass = BaseDatablockEdAction;
      actionName = %desc;
      editor = DatablockEditorPlugin;
      treeview = DatablockEditorTree;
      inspector = DatablockEditorInspector;
   };
   popInstantGroup();
   return %action;
}

//---------------------------------------------------------------------------------------------

function DatablockEditorPlugin::submitUndo( %this, %action )
{
   %action.addToManager( Editor.getUndoManager() );
}

//=============================================================================================
//    BaseDatablockEdAction.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function BaseDatablockEdAction::redo( %this )
{
}

//---------------------------------------------------------------------------------------------

function BaseDatablockEdAction::undo( %this )
{
}

//=============================================================================================
//    ActionCreateDatablock.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function ActionCreateDatablock::redo( %this )
{
   %db = %this.db;
   
   %db.name = %this.dbName;
   
   %this.editor.PM.setDirty( %db, %this.fname );
   %this.editor.addExistingItem( %db );
   %this.editor.selectDatablock( %db );
   %this.editor.flagInspectorAsDirty( true );
   
   UnlistedDatablocks.remove( %id );
}

//---------------------------------------------------------------------------------------------

function ActionCreateDatablock::undo( %this )
{
   %db = %this.db;
      
   %itemId = %this.treeview.findItemByName( %db.name );
   if( !%itemId )
      %itemId = %this.treeview.findItemByName( %db.name @ " *" );
   
   %this.treeview.removeItem( %itemId );
   %this.editor.resetSelectedDatablock();
   %this.editor.PM.removeDirty( %db );

   %this.dbName = %db.name;
   %db.name = "";
   
   UnlistedDatablocks.add( %this.db );
}

//=============================================================================================
//    ActionDeleteDatablock.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function ActionDeleteDatablock::redo( %this )
{
   %db = %this.db;
      
   %itemId = %this.treeview.findItemByName( %db.name );
   if( !%itemId )
      %itemId = %this.treeview.findItemByName( %db.name @ " *" );
      
   // Remove from tree and file.
      
   %this.treeview.removeItem( %db );
   %this.editor.resetSelectedDatablock();
   if( %db.getFileName() !$= "" )
      %this.editor.PM.removeObjectFromFile( %db );
   
   // Unassign name.

   %this.dbName = %db.name;
   %db.name = "";
   
   // Add to unlisted.
   
   UnlistedDatablocks.add( %db );
}

//---------------------------------------------------------------------------------------------

function ActionDeleteDatablock::undo( %this )
{
   %db = %this.db;
   
   // Restore name.
   
   %db.name = %this.dbName;
   
   // Add to tree and select.
   
   %this.editor.addExistingItem( %db, true );
   %this.editor.selectDatablock( %db );
   
   // Mark as dirty.
   
   %this.editor.PM.setDirty( %db, %this.fname );
   %this.editor.syncDirtyState();
   
   // Remove from unlisted.
   
   UnlistedDatablocks.remove( %id );
}
