// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$XaNotcSettings1_RemapCount = 0;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Forward";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "moveforward";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Backward";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "movebackward";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Strafe Left";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "moveleft";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Strafe Right";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "moveright";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Turn Left";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "turnLeft";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Turn Right";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "turnRight";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Look Up";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "panUp";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Look Down";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "panDown";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Jump";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "jump";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Fire Weapon";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "mouseFire";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Adjust Zoom";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "setZoomFov";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Toggle Zoom";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "toggleZoom";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Free Look";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "toggleFreeLook";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Switch 1st/3rd";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "toggleFirstPerson";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Chat to Everyone";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "toggleMessageHud";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Message Hud PageUp";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "pageMessageHudUp";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Message Hud PageDown";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "pageMessageHudDown";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Resize Message Hud";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "resizeMessageHud";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Show Scores";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "showPlayerList";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Animation - Wave";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "celebrationWave";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Animation - Salute";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "celebrationSalute";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Suicide";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "suicide";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Toggle Camera";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "toggleCamera";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Drop Camera at Player";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "dropCameraAtPlayer";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Drop Player at Camera";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "dropPlayerAtCamera";
$XaNotcSettings1_RemapCount++;
$XaNotcSettings1_RemapName[$XaNotcSettings1_RemapCount] = "Bring up Options Dialog";
$XaNotcSettings1_RemapCmd[$XaNotcSettings1_RemapCount] = "bringUpOptions";
$XaNotcSettings1_RemapCount++;

function XaNotcSettings1_ControlsGui::onWake(%this)
{
   //echo("XaNotcSettings1_ControlsGui::onWake");
   
   if($InGuiEditor)
      return;

   %this-->MouseSensitivity.value = $pref::Input::LinkMouseSensitivity;
   %this.fillRemapList();
}

function XaNotcSettings1_ControlsGui::onSleep(%this)
{
   //echo("XaNotcSettings1_ControlsGui::onSleep");

   // write out the control config into the rw config file
   XaNotc1CatMoveMap.save("notc/client/settings/notc1controls.cs");
}

function XaNotcSettings1_ControlsGui::fillRemapList( %this )
{
   %remapList = %this-->RemapList;

	%remapList.clear();
   for ( %i = 0; %i < $XaNotcSettings1_RemapCount; %i++ )
      %remapList.addRow( %i, XaNotcSettings1_Controls_buildFullMapString( %i ) );
}

function XaNotcSettings1_ControlsGui::doRemap( %this )
{
   %remapList = %this-->RemapList;

	%selId = %remapList.getSelectedId();
   %name = $XaNotcSettings1_RemapName[%selId];

	XaNotcSettings1_Controls_RemapDlg-->OptRemapText.setValue( "Re-bind \"" @ %name @ "\" to..." );
	XaNotcSettings1_Controls_RemapInputCtrl.index = %selId;
	Canvas.pushDialog( XaNotcSettings1_Controls_RemapDlg );
}

function XaNotcSettings1_Controls_RemapInputCtrl::onInputEvent( %this, %device, %action )
{
   //error( "** onInputEvent called - device = " @ %device @ ", action = " @ %action @ " **" );
   Canvas.popDialog(XaNotcSettings1_Controls_RemapDlg);

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

   %cmd  = $XaNotcSettings1_RemapCmd[%this.index];
   %name = $XaNotcSettings1_RemapName[%this.index];

   // Grab the friendly display name for this action
   // which we'll use when prompting the user below.
   %mapName = XaNotcSettings1_Controls_getMapDisplayName( %device, %action );

   // Get the current command this action is mapped to.
   %prevMap = XaNotc1CatMoveMap.getCommand( %device, %action );

   // If nothing was mapped to the previous command
   // mapping then it's easy... just bind it.
   if ( %prevMap $= "" )
   {
      XaNotcSettings1_Controls_unbindExtraActions( %cmd, 1 );
      XaNotc1CatMoveMap.bind( %device, %action, %cmd );
      optionsDlg-->RemapList.setRowById( %this.index, XaNotcSettings1_Controls_buildFullMapString( %this.index ) );
      return;
   }

   // If the previous command is the same as the
   // current then they hit the same input as what
   // was already assigned.
   if ( %prevMap $= %cmd )
   {
      XaNotcSettings1_Controls_unbindExtraActions( %cmd, 0 );
      XaNotc1CatMoveMap.bind( %device, %action, %cmd );
      optionsDlg-->RemapList.setRowById( %this.index, XaNotcSettings1_Controls_buildFullMapString( %this.index ) );
      return;
   }

   // Look for the index of the previous mapping.
   %prevMapIndex = XaNotcSettings1_Controls_findRemapCmdIndex( %prevMap );

   // If we get a negative index then the previous
   // mapping was to an item that isn't included in
   // the mapping list... so we cannot unmap it.
   if ( %prevMapIndex == -1 )
   {
      MessageBoxOK( "Remap Failed", "\"" @ %mapName @ "\" is already bound to a non-remappable command!" );
      return;
   }

   // Setup the forced remapping callback command.
   %callback = "XaNotcSettings1_Controls_redoMapping(" @ %device @ ", \"" @ %action @ "\", \"" @
                              %cmd @ "\", " @ %prevMapIndex @ ", " @ %this.index @ ");";

   // Warn that we're about to remove the old mapping and
   // replace it with another.
   %prevCmdName = $XaNotcSettings1_RemapName[%prevMapIndex];
   MessageBoxYesNo( "Warning",
      "\"" @ %mapName @ "\" is already bound to \""
      @ %prevCmdName @ "\"!\nDo you wish to replace this mapping?",
       %callback, "" );
}

function XaNotcSettings1_Controls_getMapDisplayName( %device, %action )
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

function XaNotcSettings1_Controls_buildFullMapString( %index )
{
   %name       = $XaNotcSettings1_RemapName[%index];
   %cmd        = $XaNotcSettings1_RemapCmd[%index];

   %temp = XaNotc1CatMoveMap.getBinding( %cmd );
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
      %mapString = %mapString @ XaNotcSettings1_Controls_getMapDisplayName( %device, %object );
   }

   return %name TAB %mapString;
}

function XaNotcSettings1_Controls_redoMapping( %device, %action, %cmd, %oldIndex, %newIndex )
{
	//%actionMap.bind( %device, %action, $XaNotcSettings1_RemapCmd[%newIndex] );
	XaNotc1CatMoveMap.bind( %device, %action, %cmd );

   %remapList = XaNotcSettings1_ControlsGui-->RemapList;
	%remapList.setRowById( %oldIndex, XaNotcSettings1_Controls_buildFullMapString( %oldIndex ) );
	%remapList.setRowById( %newIndex, XaNotcSettings1_Controls_buildFullMapString( %newIndex ) );
}

function XaNotcSettings1_Controls_findRemapCmdIndex( %command )
{
	for ( %i = 0; %i < $XaNotcSettings1_RemapCount; %i++ )
	{
		if ( %command $= $XaNotcSettings1_RemapCmd[%i] )
			return( %i );
	}
	return( -1 );
}

/// This unbinds actions beyond %count associated to the
/// particular XaNotc1CatMoveMap %commmand.
function XaNotcSettings1_Controls_unbindExtraActions( %command, %count )
{
   %temp = XaNotc1CatMoveMap.getBinding( %command );
   if ( %temp $= "" )
      return;

   %count = getFieldCount( %temp ) - ( %count * 2 );
   for ( %i = 0; %i < %count; %i += 2 )
   {
      %device = getField( %temp, %i + 0 );
      %action = getField( %temp, %i + 1 );

      XaNotc1CatMoveMap.unbind( %device, %action );
   }
}

function XaNotcSettings1_Controls_restoreDefaultMappings()
{
   XaNotc1CatMoveMap.delete();
   exec("notc/client/settings/notc1controls.cs");
   optionsDlg.fillRemapList();
}

function XaNotcSettings1_Controls_MouseSetSensitivity(%value)
{
   $pref::Input::LinkMouseSensitivity = %value;
}

