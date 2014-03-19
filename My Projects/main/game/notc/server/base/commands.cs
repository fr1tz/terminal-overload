// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdAction(%client, %nr)
{
   echo("serverCmdAction(): client" SPC %client SPC "action" SPC %nr);
   Game.clientAction(%client, %nr);
}

function serverCmdJoinTeam(%client, %nr)
{
   echo("serverCmdJoinTeam(): client" SPC %client SPC "action" SPC %nr);
   Game.joinTeam(%client, %nr);
}

// ----------------------------------------------------------------------------
// Settings
// ----------------------------------------------------------------------------

function serverCmdGameSettingsChanged(%client, %settings)
{
   //echo("serverCmdGameSettingsChanged(): client:" SPC %client SPC "settings:" SPC %settings);
   Game.queryClientSettings(%client, %settings);
}

function serverCmdXaNotcSettings1_Reply(%client, %setting, %value)
{
   //echo("serverCmdXaNotcSettings1_Reply(): client:" SPC %client SPC "setting:" SPC %setting SPC "value:" SPC %value);
   Game.processClientSettingsReply(%client, %setting, %value);
}

//-----------------------------------------------------------------------------
// Misc server commands avialable to clients
//-----------------------------------------------------------------------------

function serverCmdSuicide(%client)
{
   if (isObject(%client.player))
      %client.player.kill("Suicide");
}

function serverCmdPlayCel(%client,%anim)
{
   if (isObject(%client.player))
      %client.player.playCelAnimation(%anim);
}

function serverCmdTestAnimation(%client, %anim)
{
   if (isObject(%client.player))
      %client.player.playTestAnimation(%anim);
}

function serverCmdPlayDeath(%client)
{
   if (isObject(%client.player))
      %client.player.playDeathAnimation();
}

// ----------------------------------------------------------------------------
// Throw/Toss
// ----------------------------------------------------------------------------

function serverCmdThrow(%client, %data)
{
   %player = %client.player;
   if(!isObject(%player) || %player.getState() $= "Dead" || !$Game::Running)
      return;
   switch$ (%data)
   {
      case "Weapon":
         %item = (%player.getMountedImage($WeaponSlot) == 0) ? "" : %player.getMountedImage($WeaponSlot).item;
         if (%item !$="")
            %player.throw(%item);
      case "Ammo":
         %weapon = (%player.getMountedImage($WeaponSlot) == 0) ? "" : %player.getMountedImage($WeaponSlot);
         if (%weapon !$= "")
         {
            if(%weapon.ammo !$= "")
               %player.throw(%weapon.ammo);
         }
      default:
         if(%player.hasInventory(%data.getName()))
            %player.throw(%data);
   }
}

// ----------------------------------------------------------------------------
// Force game end and cycle
// Probably don't want this in a final game without some checks.  Anyone could
// restart a game.
// ----------------------------------------------------------------------------

function serverCmdFinishGame()
{
   cycleGame();
}

// ----------------------------------------------------------------------------
// Cycle weapons
// ----------------------------------------------------------------------------

function serverCmdCycleWeapon(%client, %direction)
{
   %client.getControlObject().cycleWeapon(%direction);
}

// ----------------------------------------------------------------------------
// Unmount current weapon
// ----------------------------------------------------------------------------

function serverCmdUnmountWeapon(%client)
{
   %client.getControlObject().unmountImage($WeaponSlot);
}


