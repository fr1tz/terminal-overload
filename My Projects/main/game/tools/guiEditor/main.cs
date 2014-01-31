// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function initializeGuiEditor()
{
   echo( " % - Initializing Gui Editor" );
   
   // GUIs.
   
   exec( "./gui/guiEditor.ed.gui" );
   exec( "./gui/guiEditorNewGuiDialog.ed.gui" );
   exec( "./gui/guiEditorPrefsDlg.ed.gui" );
   exec( "./gui/guiEditorSelectDlg.ed.gui" );
   exec( "./gui/EditorChooseGUI.ed.gui" );
   
   // Scripts.

   exec( "./scripts/guiEditor.ed.cs" );
   exec( "./scripts/guiEditorTreeView.ed.cs" );
   exec( "./scripts/guiEditorInspector.ed.cs" );
   exec( "./scripts/guiEditorProfiles.ed.cs" );
   exec( "./scripts/guiEditorGroup.ed.cs" );
   exec( "./scripts/guiEditorUndo.ed.cs" );
   exec( "./scripts/guiEditorCanvas.ed.cs" );
   exec( "./scripts/guiEditorContentList.ed.cs" );
   exec( "./scripts/guiEditorStatusBar.ed.cs" );
   exec( "./scripts/guiEditorToolbox.ed.cs" );
   exec( "./scripts/guiEditorSelectDlg.ed.cs" );
   
   exec( "./scripts/guiEditorNewGuiDialog.ed.cs" );
   exec( "./scripts/fileDialogs.ed.cs" );
   exec( "./scripts/guiEditorPrefsDlg.ed.cs" );
   exec( "./scripts/EditorChooseGUI.ed.cs" );
}

function destroyGuiEditor()
{
}
