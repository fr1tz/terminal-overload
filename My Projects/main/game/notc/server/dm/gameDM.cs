// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// DeathmatchGame
// ----------------------------------------------------------------------------
// Depends on methods found in gameCore.cs.  Those added here are specific to
// this game type and/or over-ride the "default" game functionaliy.
//
// The desired Game Type must be added to each mission's LevelInfo object.
//   - gameType = "Deathmatch";
// If this information is missing then the GameCore will default to Deathmatch.
// ----------------------------------------------------------------------------

function DeathMatchGame::onMissionLoaded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::onMissionLoaded");

   $Server::MissionType = "Deathmatch";
   parent::onMissionLoaded(%game);
}

function DeathMatchGame::initGameVars(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::initGameVars");

   //-----------------------------------------------------------------------------
   // What kind of "player" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   // These override the values set in core/scripts/server/spawn.cs
   //-----------------------------------------------------------------------------
   
   // Leave $Game::defaultPlayerClass and $Game::defaultPlayerDataBlock as empty strings ("")
   // to spawn a the $Game::defaultCameraClass as the control object.
   $Game::defaultPlayerClass = "Player";
   $Game::defaultPlayerDataBlock = "FrmStandardcat";
   $Game::defaultPlayerSpawnGroups = "PlayerSpawnPoints PlayerDropPoints";

   //-----------------------------------------------------------------------------
   // What kind of "camera" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   // These override the values set in core/scripts/server/spawn.cs
   //-----------------------------------------------------------------------------
   $Game::defaultCameraClass = "Camera";
   $Game::defaultCameraDataBlock = "Observer";
   $Game::defaultCameraSpawnGroups = "CameraSpawnPoints PlayerSpawnPoints PlayerDropPoints";

   // Set the gameplay parameters
   %game.duration = 10 * 60;
   %game.endgameScore = 0;
   %game.endgamePause = 10;
   %game.allowCycling = true;   // Is mission cycling allowed?
}

function DeathMatchGame::startGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::startGame");

   parent::startGame(%game);
}

function DeathMatchGame::endGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::endGame");

   parent::endGame(%game);
}

function DeathMatchGame::onGameDurationEnd(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::onGameDurationEnd");

   parent::onGameDurationEnd(%game);
}

function DeathMatchGame::prepareClient(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::prepareClient");

   Parent::prepareClient(%game, %client);
   
   %files = "xa/notc/core/client/audio/Descriptions/v1/exec.cs" TAB
            "xa/notc/core/client/audio/Hearing/v1/exec.cs" TAB
            "xa/notc/core/client/gui/CatGui/v1/exec.cs" TAB
            "xa/notc/core/client/gui/ChatHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/GuiChanger/v1/exec.cs" TAB
            "xa/notc/core/client/gui/MiscHud/v1/exec.cs" TAB
            "xa/notc/core/client/misc/Commands/v1/exec.cs" TAB
            "xa/notc/core/client/postfx/ChromaticLens/v1/exec.cs" TAB
            "xa/notc/deathmatch/client/gui/EndGameGui/v1/exec.cs" TAB
            "xa/notc/deathmatch/client/gui/PlayerList/v1/exec.cs";

   %fieldCount = getFieldCount(%files);
   for(%i = 0; %i < %fieldCount; %i++)
   {
      %file = getField(%files, %i);
      commandToClient(%client, 'ExecContentScript', %file);
   }
}

function DeathMatchGame::onClientEnterGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::onClientEnterGame");

   Parent::onClientEnterGame(%game, %client);
   
   if($Game::Duration)
   {
      %timeLeft = ($Game::StartTime + $Game::Duration) - $Sim::Time;
      commandToClient(%client, 'GameTimer', %timeLeft);
   }
}

function DeathMatchGame::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::onClientLeaveGame");

   parent::onClientLeaveGame(%game, %client);

}

function DeathMatchGame::queryClientSettings(%game, %client, %settings)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::queryClientSettings");

   Parent::queryClientSettings(%game, %client, %settings);
   
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor0");
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor1");
}

function DeathMatchGame::processClientSettingsReply(%game, %client, %setting, %value)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::processClientSettingsReply");
   
   %status = "Ignored";
   
   if(%setting $= "PlayerColor0")
   {
      if(isValidPlayerColor(%value))
      {
         %client.paletteColors[0] = %value SPC "255";
         %status = "Ok";
      }
      else
         %status = "Invalid";
      
   }
   else if(%setting $= "PlayerColor1")
   {
      if(isValidPlayerColor(%value))
      {
         %client.paletteColors[1] = %value SPC "255";
         %status = "Ok";
      }
      else
         %status = "Invalid";
   }

   commandToClient(%client, 'XaNotcSettings1_Confirmation', %setting, %status);
}

function DeathMatchGame::loadOut(%game, %player)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::loadOut");
   
   Parent::loadOut(%game, %player);

   %player.clearWeaponCycle();
   %player.addToWeaponCycle(WpnSMG1);
   %player.addToWeaponCycle(WpnMGL1);
   %player.addToWeaponCycle(WpnSG1);
   %player.addToWeaponCycle(WpnSR1);
   %player.addToWeaponCycle(WpnMG1);
   //%player.addToWeaponCycle(WpnML1);

   %player.setInventory(ItemBallast, 1);
   %player.setInventory(ItemEtherboard, 1);
   %player.setInventory(WpnSMG, 1);

   if (%player.getDatablock().mainWeapon.image !$= "")
      %player.mountImage(%player.getDatablock().mainWeapon.image, 0);
   else
      %player.mountImage(WpnBadgerImage, 0);
}

function DeathMatchGame::clientAction(%game, %client, %nr)
{
   echo(%game @"\c4 -> "@ %game.class @" -> DeathMatchGame::clientAction");

   %obj = %client.getControlObject();
   if(!isObject(%obj))
      return;

   %obj.getDataBlock().clientAction(%obj, %nr);
}
