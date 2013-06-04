// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function initializeConvexEditor()
{
   echo(" % - Initializing Sketch Tool");
     
   exec( "./convexEditor.cs" );
   exec( "./convexEditorGui.gui" );
   exec( "./convexEditorToolbar.ed.gui" );
   exec( "./convexEditorGui.cs" );
   
   ConvexEditorGui.setVisible( false );  
   ConvexEditorOptionsWindow.setVisible( false );  
   ConvexEditorTreeWindow.setVisible( false ); 
   ConvexEditorToolbar.setVisible( false );
   
   EditorGui.add( ConvexEditorGui );
   EditorGui.add( ConvexEditorOptionsWindow );
   EditorGui.add( ConvexEditorTreeWindow );
   EditorGui.add( ConvexEditorToolbar );
      
   new ScriptObject( ConvexEditorPlugin )
   {
      superClass = "EditorPlugin";
      editorGui = ConvexEditorGui;
   };
      
   // Note that we use the WorldEditor's Toolbar.
   
   %map = new ActionMap();   
   %map.bindCmd( keyboard, "1", "ConvexEditorNoneModeBtn.performClick();", "" );  // Select
   %map.bindCmd( keyboard, "2", "ConvexEditorMoveModeBtn.performClick();", "" );  // Move
   %map.bindCmd( keyboard, "3", "ConvexEditorRotateModeBtn.performClick();", "" );// Rotate
   %map.bindCmd( keyboard, "4", "ConvexEditorScaleModeBtn.performClick();", "" ); // Scale      
   ConvexEditorPlugin.map = %map;   
   
   ConvexEditorPlugin.initSettings();
}

function ConvexEditorPlugin::onWorldEditorStartup( %this )
{
   // Add ourselves to the window menu.
   %accel = EditorGui.addToEditorsMenu( "Sketch Tool", "", ConvexEditorPlugin ); 
   
   // Add ourselves to the ToolsToolbar
   %tooltip = "Sketch Tool (" @ %accel @ ")";
   EditorGui.addToToolsToolbar( "ConvexEditorPlugin", "ConvexEditorPalette", expandFilename("tools/convexEditor/images/convex-editor-btn"), %tooltip );
   
   //connect editor windows
   GuiWindowCtrl::attach( ConvexEditorOptionsWindow, ConvexEditorTreeWindow);
   
   // Allocate our special menu.
   // It will be added/removed when this editor is activated/deactivated.
      
   if ( !isObject( ConvexActionsMenu ) )
   {
      singleton PopupMenu( ConvexActionsMenu )
      {
         superClass = "MenuBuilder";

         barTitle = "Sketch";
                                    
         Item[0] = "Hollow Selected Shape" TAB "" TAB "ConvexEditorGui.hollowSelection();";      
         item[1] = "Recenter Selected Shape" TAB "" TAB "ConvexEditorGui.recenterSelection();";
      };
   }
   
   %this.popupMenu = ConvexActionsMenu;
   
   exec( "./convexEditorSettingsTab.ed.gui" );
   ESettingsWindow.addTabPage( EConvexEditorSettingsPage );
}

function ConvexEditorPlugin::onActivated( %this )
{   
   %this.readSettings();
   
   EditorGui.bringToFront( ConvexEditorGui );
   ConvexEditorGui.setVisible( true );
   ConvexEditorToolbar.setVisible( true );
   ConvexEditorGui.makeFirstResponder( true ); 
   %this.map.push();   
   
   // Set the status bar here until all tool have been hooked up
   EditorGuiStatusBar.setInfo( "Sketch Tool." );
   EditorGuiStatusBar.setSelection( "" );
   
   // Add our menu.
   EditorGui.menuBar.insert( ConvexActionsMenu, EditorGui.menuBar.dynamicItemInsertPos );
   
   // Sync the pallete button state with the gizmo mode.
   %mode = GlobalGizmoProfile.mode;
   switch$ (%mode)
   {
      case "None":
         ConvexEditorNoneModeBtn.performClick();
      case "Move":
         ConvexEditorMoveModeBtn.performClick();
      case "Rotate":
         ConvexEditorRotateModeBtn.performClick();
      case "Scale":
         ConvexEditorScaleModeBtn.performClick();
   }

   Parent::onActivated( %this );
}

function ConvexEditorPlugin::onDeactivated( %this )
{    
   %this.writeSettings();
   
   ConvexEditorGui.setVisible( false );
   ConvexEditorOptionsWindow.setVisible( false );
   ConvexEditorTreeWindow.setVisible( false );
   ConvexEditorToolbar.setVisible( false );
   %this.map.pop();
   
   // Remove our menu.
   EditorGui.menuBar.remove( ConvexActionsMenu );

   Parent::onDeactivated( %this );
}

function ConvexEditorPlugin::onEditMenuSelect( %this, %editMenu )
{
   %hasSelection = false;
   
   if ( ConvexEditorGui.hasSelection() )
      %hasSelection = true;
            
   %editMenu.enableItem( 3, false ); // Cut
   %editMenu.enableItem( 4, false ); // Copy
   %editMenu.enableItem( 5, false ); // Paste  
   %editMenu.enableItem( 6, %hasSelection ); // Delete
   %editMenu.enableItem( 8, %hasSelection ); // Deselect     
}

function ConvexEditorPlugin::handleDelete( %this )
{
   ConvexEditorGui.handleDelete();
}

function ConvexEditorPlugin::handleDeselect( %this )
{
   ConvexEditorGui.handleDeselect();   
}

function ConvexEditorPlugin::handleCut( %this )
{
   //WorldEditorInspectorPlugin.handleCut();
}

function ConvexEditorPlugin::handleCopy( %this )
{
   //WorldEditorInspectorPlugin.handleCopy();
}

function ConvexEditorPlugin::handlePaste( %this )
{
   //WorldEditorInspectorPlugin.handlePaste();
}

function ConvexEditorPlugin::isDirty( %this )
{
   return ConvexEditorGui.isDirty;
}

function ConvexEditorPlugin::onSaveMission( %this, %missionFile )
{
   if( ConvexEditorGui.isDirty )
   {
      MissionGroup.save( %missionFile );
      ConvexEditorGui.isDirty = false;
   }
}

//-----------------------------------------------------------------------------
// Settings
//-----------------------------------------------------------------------------

function ConvexEditorPlugin::initSettings( %this )
{
   EditorSettings.beginGroup( "ConvexEditor", true );
   EditorSettings.setDefaultValue(  "MaterialName",         "Grid512_OrangeLines_Mat" );
   EditorSettings.endGroup();
}

function ConvexEditorPlugin::readSettings( %this )
{
   EditorSettings.beginGroup( "ConvexEditor", true );
   ConvexEditorGui.materialName         = EditorSettings.value("MaterialName");
   EditorSettings.endGroup();  
}

function ConvexEditorPlugin::writeSettings( %this )
{
   EditorSettings.beginGroup( "ConvexEditor", true );
   EditorSettings.setValue( "MaterialName",           ConvexEditorGui.materialName );
   EditorSettings.endGroup();
}