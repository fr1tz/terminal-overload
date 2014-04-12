// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function gameSettingsChanged(%settings)
{
   //echo("gameSettingsChanged():" SPC %settings);
   commandToServer('GameSettingsChanged', %settings);
}

function gameSettingsAddEditor(%ctrl)
{
   //echo("gameSettingsAddEditor():" SPC %ctrl);
   
   if(!isObject(%ctrl))
      return;

   if(strstr($Client::GameSettingsEditors, %ctrl @ " ") != -1)
      return;

   $Client::GameSettingsEditors = $Client::GameSettingsEditors @ %ctrl @ " ";
}

function OptGameGui::onWake(%this)
{
   //echo("OptGameGui::onWake()");
   
   if($InGuiEditor)
      return;
   
   %this.updateEditorList();
   
   if(%this-->ContentContainer.getCount() == 0)
      OptGameEditorList.setFirstSelected();
}

function OptGameGui::setContent(%this, %ctrl)
{
   //echo("OptGameGui::setContent():" SPC %ctrl);

   if(%this.zContent $= %ctrl)
      return;

   // Clean content container.
   if(isObject(%this.zContent) && isObject(%this.zContentOriginalParent))
      %this.zContentOriginalParent.add(%this.zContent);
   %this-->ContentContainer.clear();

   %content = %ctrl;
   %contentOriginalParent = %ctrl.getParent();

   if(isObject(%content))
   {
      %this-->ContentContainer.add(%content);
      %content.setPosition(0, 0);
      %extent = %this-->ContentContainer.getExtent();
      %w = getWord(%extent, 0);
      %h = getWord(%extent, 1);
      %extent = %w-20 SPC %h;
      %content.setExtent(%extent);
      %this.zContent = %content;
      %this.zContentOriginalParent = %contentOriginalParent;
   }
}

function OptGameGui::updateEditorList(%this)
{
   //echo("OptGameGui::updateEditorList()");
   
   %popup = OptGameEditorList;
   %popup.clear();
   
   %numEditors = getWordCount($Client::GameSettingsEditors);
   for(%i = 0; %i < %numEditors; %i++)
   {
      %editor = getWord($Client::GameSettingsEditors, %i);
      %string = %editor.gameString;
      if(%string $= "")
         %string = %editor;
      %popup.add(%string, %editor.getId());
   }
}

function OptGameEditorList::onSelect( %this, %id, %text )
{
   //echo("OptGameEditorList::onSelect()");
   OptGameGui.setContent(%id);
}

