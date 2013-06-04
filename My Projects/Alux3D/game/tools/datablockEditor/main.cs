// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//---------------------------------------------------------------------------------------------

function initializeDatablockEditor()
{
   echo( " - Initializing Datablock Editor" );
   
   exec("./datablockEditor.cs");
   exec("./datablockEditorUndo.cs");
   exec("./DatablockEditorTreeWindow.ed.gui");
   exec("./DatablockEditorInspectorWindow.ed.gui");
   exec("./DatablockEditorCreatePrompt.ed.gui");
   
   // Add ourselves to EditorGui, where all the other tools reside
   DatablockEditorInspectorWindow.setVisible( false );
   DatablockEditorTreeWindow.setVisible( false );
   
   EditorGui.add( DatablockEditorInspectorWindow );
   EditorGui.add( DatablockEditorTreeWindow );
   
   new ScriptObject( DatablockEditorPlugin )
   {
      superClass = "WorldEditorPlugin";
      editorGui = EWorldEditor;
   };
      
   new SimSet( UnlistedDatablocks );
   
   // create our persistence manager
   DatablockEditorPlugin.PM = new PersistenceManager();
   
   %map = new ActionMap();
   %map.bindCmd( keyboard, "backspace", "DatablockEditorPlugin.onDeleteKey();", "" );
   %map.bindCmd( keyboard, "delete", "DatablockEditorPlugin.onDeleteKey();", "" );  
   DatablockEditorPlugin.map = %map;
   
   DatablockEditorPlugin.initSettings();
}

//---------------------------------------------------------------------------------------------

function destroyDatablockEditor()
{
}
