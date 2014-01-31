// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
   
function MissionAreaEditorGui::onEditorActivated( %this )
{
   EWorldEditor.clearSelection();
   
   %ma = getMissionAreaServerObject();
   EWorldEditor.selectObject( %ma );
   EWorldEditor.syncGui();
   MissionAreaEditorTerrainEditor.updateTerrain();
   %this.setSelectedMissionArea( %ma );
   %this.onMissionAreaSelected( %this.getSelectedMissionArea() );   
}

function MissionAreaEditorGui::onEditorDeactivated( %this )
{
}

function MissionAreaEditorGui::onMissionAreaSelected( %this, %missionArea )
{
   %this.missionArea = %missionArea;
   MissionAreaEditorTerrainEditor.setMissionArea( %missionArea );
   MissionAreaInspector.inspect( %missionArea );  
}

//-----------------------------------------------------------------------------

function MissionAreaEditorTerrainEditor::onMissionAreaModified( %this )
{
   MissionAreaInspector.refresh();
}

function MissionAreaEditorTerrainEditor::onUndo( %this )
{
   MissionAreaInspector.refresh();
}

//-----------------------------------------------------------------------------

function MissionAreaInspector::inspect( %this, %obj )
{
   %name = "";
   if ( isObject( %obj ) )
      %name = %obj.getName();   
   else
      MissionAreaFieldInfoControl.setText( "" );
   
   //RiverInspectorNameEdit.setValue( %name );
   Parent::inspect( %this, %obj );  
}

function MissionAreaInspector::onInspectorFieldModified( %this, %object, %fieldName, %arrayIndex, %oldValue, %newValue )
{
   // Same work to do as for the regular WorldEditor Inspector.
   Inspector::onInspectorFieldModified( %this, %object, %fieldName, %arrayIndex, %oldValue, %newValue );   
}

function MissionAreaInspector::onFieldSelected( %this, %fieldName, %fieldTypeStr, %fieldDoc )
{
   MissionAreaFieldInfoControl.setText( "<font:ArialBold:14>" @ %fieldName @ "<font:ArialItalic:14> (" @ %fieldTypeStr @ ") " NL "<font:Arial:14>" @ %fieldDoc );
}
