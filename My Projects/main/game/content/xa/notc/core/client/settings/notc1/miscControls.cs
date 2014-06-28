// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$XaNotc1MiscMoveMap_RemapCount = 0;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Chat to Everyone";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_toggleMessageHud";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Message Hud PageUp";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_pageMessageHudUp";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Message Hud PageDown";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_pageMessageHudDown";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Resize Message Hud";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_resizeMessageHud";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Show Scores";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_showPlayerList";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Toggle Camera";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_toggleCamera";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Drop Camera at Player";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_dropCameraAtPlayer";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Drop Player at Camera";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_dropPlayerAtCamera";
$XaNotc1MiscMoveMap_RemapCount++;
$XaNotc1MiscMoveMap_RemapName[$XaNotc1MiscMoveMap_RemapCount] = "Bring up Options Dialog";
$XaNotc1MiscMoveMap_RemapCmd[$XaNotc1MiscMoveMap_RemapCount] = "XaNotc1MiscMoveMap_bringUpOptions";
$XaNotc1MiscMoveMap_RemapCount++;

function XaNotcSettings1_MiscControlsGui::onWake(%this)
{
   //echo("XaNotcSettings1_MiscControlsGui::onWake");
   
   if($InGuiEditor)
      return;

   %this-->MouseSensitivity.value = $pref::Input::LinkMouseSensitivity;
   %this.fillRemapList();
}

function XaNotcSettings1_MiscControlsGui::onSleep(%this)
{
   //echo("XaNotcSettings1_MiscControlsGui::onSleep");

   // write out the control config into the rw config file
   XaNotc1MiscMoveMap.save("notc/client/settings/XaNotc1MiscMoveMap.cs");
}

function XaNotcSettings1_MiscControlsGui::fillRemapList( %this )
{
   %remapList = %this-->RemapList;

	%remapList.clear();
   for ( %i = 0; %i < $XaNotc1MiscMoveMap_RemapCount; %i++ )
      %remapList.addRow( %i, XaNotcSettings1_MiscControls_buildFullMapString( %i ) );
}

function XaNotcSettings1_MiscControlsGui::doRemap( %this )
{
   %remapList = %this-->RemapList;

	%selId = %remapList.getSelectedId();
   %name = $XaNotc1MiscMoveMap_RemapName[%selId];

	XaNotcSettings1_Controls_RemapDlg-->OptRemapText.setValue( "Re-bind \"" @ %name @ "\" to..." );
	XaNotcSettings1_Controls_RemapInputCtrl.index = %selId;
   XaNotcSettings1_Controls_RemapInputCtrl.inputEventCallback = "XaNotcSettings1_MiscControls_onRemapCtrlInputEvent";
	Canvas.pushDialog(XaNotcSettings1_Controls_RemapDlg);
}

function XaNotcSettings1_MiscControls_onRemapCtrlInputEvent(%device, %action)
{
   //error( "** onInputEvent called - device = " @ %device @ ", action = " @ %action @ " **" );
   Canvas.popDialog(XaNotcSettings1_Controls_RemapDlg);
   
   %index = XaNotcSettings1_Controls_RemapInputCtrl.index;

   // Test for the reserved keystrokes:
   if ( %device $= "keyboard" )
   {
      // Cancel...
      if ( %action $= "escape" )
      {
         // Do nothing...
         return;
      }
   }

   %cmd  = $XaNotc1MiscMoveMap_RemapCmd[%index];
   %name = $XaNotc1MiscMoveMap_RemapName[%index];

   // Grab the friendly display name for this action
   // which we'll use when prompting the user below.
   %mapName = XaNotcSettings1_MiscControls_getMapDisplayName( %device, %action );

   // Get the current command this action is mapped to.
   %prevMap = XaNotc1MiscMoveMap.getCommand( %device, %action );

   // If nothing was mapped to the previous command
   // mapping then it's easy... just bind it.
   if ( %prevMap $= "" )
   {
      XaNotcSettings1_MiscControls_unbindExtraActions( %cmd, 1 );
      XaNotc1MiscMoveMap.bind( %device, %action, %cmd );
      optionsDlg-->RemapList.setRowById( %index, XaNotcSettings1_MiscControls_buildFullMapString( %index ) );
      return;
   }

   // If the previous command is the same as the
   // current then they hit the same input as what
   // was already assigned.
   if ( %prevMap $= %cmd )
   {
      XaNotcSettings1_MiscControls_unbindExtraActions( %cmd, 0 );
      XaNotc1MiscMoveMap.bind( %device, %action, %cmd );
      optionsDlg-->RemapList.setRowById( %index, XaNotcSettings1_MiscControls_buildFullMapString( %index ) );
      return;
   }

   // Look for the index of the previous mapping.
   %prevMapIndex = XaNotcSettings1_MiscControls_findRemapCmdIndex( %prevMap );

   // If we get a negative index then the previous
   // mapping was to an item that isn't included in
   // the mapping list... so we cannot unmap it.
   if ( %prevMapIndex == -1 )
   {
      MessageBoxOK( "Remap Failed", "\"" @ %mapName @ "\" is already bound to a non-remappable command!" );
      return;
   }

   // Setup the forced remapping callback command.
   %callback = "XaNotcSettings1_MiscControls_redoMapping(" @ %device @ ", \"" @ %action @ "\", \"" @
                              %cmd @ "\", " @ %prevMapIndex @ ", " @ %index @ ");";

   // Warn that we're about to remove the old mapping and
   // replace it with another.
   %prevCmdName = $XaNotc1MiscMoveMap_RemapName[%prevMapIndex];
   MessageBoxYesNo( "Warning",
      "\"" @ %mapName @ "\" is already bound to \""
      @ %prevCmdName @ "\"!\nDo you wish to replace this mapping?",
       %callback, "" );
}

function XaNotcSettings1_MiscControls_getMapDisplayName( %device, %action )
{
	if ( %device $= "keyboard" )
		return( %action );
	else if ( strstr( %device, "mouse" ) != -1 )
	{
		// Substitute "mouse" for "button" in the action string:
		%pos = strstr( %action, "button" );
		if ( %pos != -1 )
		{
			%mods = getSubStr( %action, 0, %pos );
			%object = getSubStr( %action, %pos, 1000 );
			%instance = getSubStr( %object, strlen( "button" ), 1000 );
			return( %mods @ "mouse" @ ( %instance + 1 ) );
		}
		else
			error( "Mouse input object other than button passed to getDisplayMapName!" );
	}
	else if ( strstr( %device, "joystick" ) != -1 )
	{
		// Substitute "joystick" for "button" in the action string:
		%pos = strstr( %action, "button" );
		if ( %pos != -1 )
		{
			%mods = getSubStr( %action, 0, %pos );
			%object = getSubStr( %action, %pos, 1000 );
			%instance = getSubStr( %object, strlen( "button" ), 1000 );
			return( %mods @ "joystick" @ ( %instance + 1 ) );
		}
		else
	   {
	      %pos = strstr( %action, "pov" );
         if ( %pos != -1 )
         {
            %wordCount = getWordCount( %action );
            %mods = %wordCount > 1 ? getWords( %action, 0, %wordCount - 2 ) @ " " : "";
            %object = getWord( %action, %wordCount - 1 );
            switch$ ( %object )
            {
               case "upov":   %object = "POV1 up";
               case "dpov":   %object = "POV1 down";
               case "lpov":   %object = "POV1 left";
               case "rpov":   %object = "POV1 right";
               case "upov2":  %object = "POV2 up";
               case "dpov2":  %object = "POV2 down";
               case "lpov2":  %object = "POV2 left";
               case "rpov2":  %object = "POV2 right";
               default:       %object = "??";
            }
            return( %mods @ %object );
         }
         else
            error( "Unsupported Joystick input object passed to getDisplayMapName!" );
      }
	}

	return( "??" );
}

function XaNotcSettings1_MiscControls_buildFullMapString( %index )
{
   %name       = $XaNotc1MiscMoveMap_RemapName[%index];
   %cmd        = $XaNotc1MiscMoveMap_RemapCmd[%index];

   %temp = XaNotc1MiscMoveMap.getBinding( %cmd );
   if ( %temp $= "" )
      return %name TAB "";

   %mapString = "";

   %count = getFieldCount( %temp );
   for ( %i = 0; %i < %count; %i += 2 )
   {
      if ( %mapString !$= "" )
         %mapString = %mapString @ ", ";

      %device = getField( %temp, %i + 0 );
      %object = getField( %temp, %i + 1 );
      %mapString = %mapString @ XaNotcSettings1_MiscControls_getMapDisplayName( %device, %object );
   }

   return %name TAB %mapString;
}

function XaNotcSettings1_MiscControls_redoMapping( %device, %action, %cmd, %oldIndex, %newIndex )
{
	//%actionMap.bind( %device, %action, $XaNotc1MiscMoveMap_RemapCmd[%newIndex] );
	XaNotc1MiscMoveMap.bind( %device, %action, %cmd );

   %remapList = XaNotcSettings1_MiscControlsGui-->RemapList;
	%remapList.setRowById( %oldIndex, XaNotcSettings1_MiscControls_buildFullMapString( %oldIndex ) );
	%remapList.setRowById( %newIndex, XaNotcSettings1_MiscControls_buildFullMapString( %newIndex ) );
}

function XaNotcSettings1_MiscControls_findRemapCmdIndex( %command )
{
	for ( %i = 0; %i < $XaNotc1MiscMoveMap_RemapCount; %i++ )
	{
		if ( %command $= $XaNotc1MiscMoveMap_RemapCmd[%i] )
			return( %i );
	}
	return( -1 );
}

/// This unbinds actions beyond %count associated to the
/// particular XaNotc1MiscMoveMap %commmand.
function XaNotcSettings1_MiscControls_unbindExtraActions( %command, %count )
{
   %temp = XaNotc1MiscMoveMap.getBinding( %command );
   if ( %temp $= "" )
      return;

   %count = getFieldCount( %temp ) - ( %count * 2 );
   for ( %i = 0; %i < %count; %i += 2 )
   {
      %device = getField( %temp, %i + 0 );
      %action = getField( %temp, %i + 1 );

      XaNotc1MiscMoveMap.unbind( %device, %action );
   }
}

function XaNotcSettings1_MiscControls_restoreDefaultMappings()
{
   XaNotc1MiscMoveMap.delete();
   exec("notc/client/settings/XaNotc1MiscMoveMap.cs");
   optionsDlg.fillRemapList();
}

function XaNotcSettings1_MiscControls_MouseSetSensitivity(%value)
{
   $pref::Input::LinkMouseSensitivity = %value;
}

