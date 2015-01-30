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

function GameCoreDM::onMissionLoaded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onMissionLoaded");
   parent::onMissionLoaded(%game);
}

function GameCoreDM::initGameVars(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::initGameVars");

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

function GameCoreDM::startGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::startGame");

   parent::startGame(%game);
}

function GameCoreDM::endGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::endGame");

   parent::endGame(%game);
}

function GameCoreDM::onGameDurationEnd(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onGameDurationEnd");

   parent::onGameDurationEnd(%game);
}

function GameCoreDM::prepareClient(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::prepareClient");

   Parent::prepareClient(%game, %client);
   
   // Setup LoadingGui layers.
   %t[1] = "";
   %t[2] = "<just:center><color:FFFFFF><font:Quantico:18>" @
           "<spush><font:Quantico:32>DEATHMATCH<spop><br>" @
           "Destroy anything that moves";
   %t[3] = "";
   for(%i = 1; %i <= 3; %i++)
   {
      commandToClient(%client, '_XaNotcLoadingGui_SetLayer', %i, "", false);
   	%l = strlen(%t[%i]); %n = 0;
   	while(%n < %l)
   	{
   		%chunk = getSubStr(%t[%i], %n, 255);
         commandToClient(%client, '_XaNotcLoadingGui_SetLayer', %i, %chunk, true);
   		%n += 255;
   	}
   }
}

function GameCoreDM::onClientEnterGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onClientEnterGame");

   Parent::onClientEnterGame(%game, %client);
   
   if($Game::Duration)
   {
      %timeLeft = ($Game::StartTime + $Game::Duration) - $Sim::Time;
      commandToClient(%client, 'GameTimer', %timeLeft);
   }
   
   Game.preparePlayer(%client);
}

function GameCoreDM::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onClientLeaveGame");

   parent::onClientLeaveGame(%game, %client);

}

function GameCoreDM::queryClientSettings(%game, %client, %settings)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::queryClientSettings");

   Parent::queryClientSettings(%game, %client, %settings);
   
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor0");
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor1");
}

function GameCoreDM::processClientSettingsReply(%game, %client, %setting, %value)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::processClientSettingsReply");
   
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

function GameCoreDM::loadOut(%game, %player)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreDM::loadOut");
   
   Parent::loadOut(%game, %player);

   %player.clearWeaponCycle();
   %player.addToWeaponCycle(WpnMGL2);
   %player.addToWeaponCycle(WpnSMG2);
   %player.addToWeaponCycle(WpnSG1);
   %player.addToWeaponCycle(WpnSR1);
   %player.addToWeaponCycle(WpnMG2);
   //%player.addToWeaponCycle(WpnML1);

   %player.setInventory(ItemImpShield, 1);
   %player.setInventory(ItemEtherboard, 1);
   %player.setInventory(ItemLauncher, 1);
   %player.setInventory(ItemBounce, 1);
   %player.setInventory(ItemXJump, 1);
   
   %player.setInventory(ItemG1Launcher, 1);
   
   %player.setInventory(WpnSMG2, 1);
   %player.setInventory(WpnMGL2, 1);

   if (%player.getDatablock().mainWeapon.image !$= "")
      %player.mountImage(%player.getDatablock().mainWeapon.image, 0);
   else
      %player.mountImage(WpnBadgerImage, 0);
}

function GameCoreDM::onUnitDestroyed(%game, %obj)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onUnitDestroyed");
   
   Parent::onUnitDestroyed(%game, %obj);
   
   %client = %obj.client;
   if(isObject(%client) && %client.player == %obj)
      DM::onDeath(%client);
}

function GameCoreDM::clientAction(%game, %client, %nr)
{
   echo(%game @"\c4 -> "@ %game.class @" -> GameCoreDM::clientAction");

   %obj = %client.getControlObject();
   if(!isObject(%obj))
      return;

   %obj.getDataBlock().clientAction(%obj, %nr);
}
