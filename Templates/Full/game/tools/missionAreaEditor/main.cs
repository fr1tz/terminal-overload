// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function initializeMissionAreaEditor()
{
   echo(" % - Initializing Mission Area Editor");
     
   exec( "./missionAreaEditor.ed.cs" );
   exec( "./missionAreaEditorGui.ed.gui" );
   exec( "./missionAreaEditorGui.ed.cs" );
   
   // Add ourselves to EditorGui, where all the other tools reside
   MissionAreaEditorGui.setVisible( false );  
   MissionAreaEditorTerrainWindow.setVisible( false );
   MissionAreaEditorPropertiesWindow.setVisible( false );
   
   EditorGui.add( MissionAreaEditorGui );
   EditorGui.add( MissionAreaEditorTerrainWindow );
   EditorGui.add( MissionAreaEditorPropertiesWindow );
   
   new ScriptObject( MissionAreaEditorPlugin )
   {
      superClass = "EditorPlugin";
      editorGui = MissionAreaEditorGui;
   };

   MissionAreaEditorPlugin.initSettings();
}

function destroyMissionAreaEditor()
{
}

function MissionAreaEditorPlugin::onWorldEditorStartup( %this )
{    
    // Add ourselves to the window menu.
   %accel = EditorGui.addToEditorsMenu( "Mission Area Editor", "", MissionAreaEditorPlugin );   
   
   // Add ourselves to the ToolsToolbar
   %tooltip = "Mission Area Editor (" @ %accel @ ")";   
   EditorGui.addToToolsToolbar( "MissionAreaEditorPlugin", "MissionAreaEditorPalette", expandFilename("tools/missionAreaEditor/images/mission-area"), %tooltip );

   //connect editor windows   
   GuiWindowCtrl::attach( MissionAreaEditorPropertiesWindow, MissionAreaEditorTerrainWindow);
}

function MissionAreaEditorPlugin::onActivated( %this )
{
   %this.readSettings();
   
   EditorGui.bringToFront( MissionAreaEditorGui );
   
   MissionAreaEditorGui.setVisible(true);
   MissionAreaEditorGui.makeFirstResponder( true );
   
   MissionAreaEditorTerrainWindow.setVisible( true );
   MissionAreaEditorPropertiesWindow.setVisible( true );
   
   // Set the status bar here until all tool have been hooked up
   EditorGuiStatusBar.setInfo("Mission Area Editor.");
   EditorGuiStatusBar.setSelection("");
   
   // Allow the Gui to setup.
   MissionAreaEditorGui.onEditorActivated(); 
   
   Parent::onActivated(%this);
}

function MissionAreaEditorPlugin::onDeactivated( %this )
{
   %this.writeSettings();
   
   MissionAreaEditorGui.setVisible(false);
   MissionAreaEditorTerrainWindow.setVisible( false );
   MissionAreaEditorPropertiesWindow.setVisible( false );
   
   // Allow the Gui to cleanup.
   MissionAreaEditorGui.onEditorDeactivated(); 
   
   Parent::onDeactivated(%this);
}

//-----------------------------------------------------------------------------
// Settings
//-----------------------------------------------------------------------------

function MissionAreaEditorPlugin::initSettings( %this )
{
   EditorSettings.beginGroup( "MissionAreaEditor", true );
   
   EditorSettings.setDefaultValue(  "MissionBoundsColor",   "255 255 255" );
   
   EditorSettings.endGroup();
}

function MissionAreaEditorPlugin::readSettings( %this )
{
   EditorSettings.beginGroup( "MissionAreaEditor", true );
   
   MissionAreaEditorTerrainEditor.missionBoundsColor     = EditorSettings.value("MissionBoundsColor");
   
   EditorSettings.endGroup();  
}

function MissionAreaEditorPlugin::writeSettings( %this )
{
   EditorSettings.beginGroup( "MissionAreaEditor", true );
   
   EditorSettings.setValue( "MissionBoundsColor",     MissionAreaEditorTerrainEditor.missionBoundsColor );

   EditorSettings.endGroup();
}
