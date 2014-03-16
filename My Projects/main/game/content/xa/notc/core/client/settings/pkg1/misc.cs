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

function XaNotcSettings1_MiscGui::onWake(%this)
{
   //echo("XaNotcSettings1_MiscGui::onWake");
   
   if($InGuiEditor)
      return;

}

function XaNotcSettings1_MiscGui::onSleep(%this)
{
   //echo("XaNotcSettings1_MiscGui::onSleep");

}

function XaNotcSettings1_Misc_PlayerColor0::onAction(%this)
{
   $Pref::NOTC1::PlayerColor0 = %this.PickColor;
   %this.ToolTip = "Color:" SPC %this.PickColor;
}

function XaNotcSettings1_Misc_PlayerColor1::onAction(%this)
{
   $Pref::NOTC1::PlayerColor1 = %this.PickColor;
   %this.ToolTip = "Color:" SPC %this.PickColor;
}

function XaNotcSettings1_Misc_Update(%element)
{
   //echo(%element);
   if(%element $= "DefaultFov")
      setDefaultFov($Pref::NOTC1::DefaultFov);
}



