// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function DecalEditorGui::createAction(%this, %class, %desc)
{
   pushInstantGroup();
   %action = new UndoScriptAction()
   {
      class = %class;
      superClass = BaseDecalEdAction;
      actionName = %desc;
      tree = DecalEditorTreeView;
   };
   popInstantGroup();
   return %action;
}

function DecalEditorGui::doAction(%this, %action)
{
   if (%action.doit())
      %action.addToManager(Editor.getUndoManager());
}

function BaseDecalEdAction::redo(%this)
{
   // Default redo action is the same as the doit action
   %this.doit();
}

function BaseDecalEdAction::undo(%this)
{
}

//------------------------------------------------------------------------------
// Edit node
function DecalEditorGui::doEditNodeDetails(%this, %instanceId, %transformData, %gizmo)
{
   %action = %this.createAction(ActionEditNodeDetails, "Edit Decal Transform");
   %action.instanceId = %instanceId;
   %action.newTransformData = %transformData;
   
   if( %gizmo )
      %action.oldTransformData = %this.gizmoDetails;
   else
      %action.oldTransformData = %this.getDecalTransform(%instanceId);
   
   %this.doAction(%action);
}

function ActionEditNodeDetails::doit(%this)
{
   %count = getWordCount(%this.newTransformData);
   if(%this.instanceId !$= "" && %count == 7)
   {
      DecalEditorGui.editDecalDetails( %this.instanceId, %this.newTransformData );
      DecalEditorGui.syncNodeDetails();
      DecalEditorGui.selectDecal( %this.instanceId );
      return true;
   }
   return false;
}

function ActionEditNodeDetails::undo(%this)
{
   %count = getWordCount(%this.oldTransformData);
   if(%this.instanceId !$= "" && %count == 7)
   {
      DecalEditorGui.editDecalDetails( %this.instanceId, %this.oldTransformData );
      DecalEditorGui.syncNodeDetails();
      DecalEditorGui.selectDecal( %this.instanceId );
   }
}

//------------------------------------------------------------------------------
// Delete Decal Datablocks

// This functionality solely depends on the undo/redo datablock callbacks in 
// source.

function DecalEditorGui::redoDeleteDecalDatablock( %this, %datablock )
{
   // Remove the object from file and place a filter
   if( %datablock.getFilename() !$= "" )
   {
      DecalPMan.removeDirty( %datablock );
      DecalPMan.removeObjectFromFile( %datablock );  
   }
   
   DecalDataList.addFilteredItem( %datablock );
}

function DecalEditorGui::undoDeleteDecalDatablock( %this, %datablock )
{
   // Replace the object in file and remove the filter
   %filename = %datablock.getFilename();
   if( %datablock.getFilename() !$= "" )
   {
      DecalPMan.setDirty( %datablock, %filename );
      DecalPMan.saveDirty();
   }
   
   DecalDataList.removeFilteredItem( %datablock );
}
