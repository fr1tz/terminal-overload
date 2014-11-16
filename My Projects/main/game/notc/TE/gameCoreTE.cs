// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameCoreTE::onMissionLoaded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::onMissionLoaded");
   ETH::createTeams(%game);
   Parent::onMissionLoaded(%game);
}

function GameCoreTE::initGameVars(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::initGameVars");

   //-----------------------------------------------------------------------------
   // What kind of "player" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   // These override the values set in core/scripts/server/spawn.cs
   //-----------------------------------------------------------------------------
   
   // Leave $Game::defaultPlayerClass and $Game::defaultPlayerDataBlock as empty strings ("")
   // to spawn a the $Game::defaultCameraClass as the control object.
   $Game::defaultPlayerClass = "Etherform";
   $Game::defaultPlayerDataBlock = "FrmEtherform";
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
   %game.duration = 0;
   %game.endgameScore = 0;
   %game.endgamePause = 10;
   %game.allowCycling = true;   // Is mission cycling allowed?
}

function GameCoreTE::startGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::startGame");

   Parent::startGame(%game);
   ETH::startNewRound();
}

function GameCoreTE::endGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::endGame");

   parent::endGame(%game);
}

function GameCoreTE::onGameDurationEnd(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::onGameDurationEnd");

   parent::onGameDurationEnd(%game);
}

function GameCoreTE::prepareClient(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::prepareClient");

   Parent::prepareClient(%game, %client);
}

function GameCoreTE::onClientEnterGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::onClientEnterGame");

   Parent::onClientEnterGame(%game, %client);

   %team1playerCount = ETH::getTeamPlayerCount(1);
   %team2playerCount = ETH::getTeamPlayerCount(2);
   
   // Join team with less players.
   if(%team1playerCount > %team2playerCount)
      TE::joinTeam(%client, 2);
   else
      TE::joinTeam(%client, 1);
 
   if($Game::Duration)
   {
      %timeLeft = ($Game::StartTime + $Game::Duration) - $Sim::Time;
      commandToClient(%client, 'GameTimer', %timeLeft);
   }
}

function GameCoreTE::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::onClientLeaveGame");

   parent::onClientLeaveGame(%game, %client);

   TE::checkRoundEnd();
}

function GameCoreTE::queryClientSettings(%game, %client, %settings)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::queryClientSettings");

   Parent::queryClientSettings(%game, %client, %settings);
   
   %client.paletteColors[0] = "255 255 255 255";
   %client.paletteColors[1] = "255 255 255 255";
   
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor0");
   commandToClient(%client, 'XaNotcSettings1_Query', "PlayerColor1");
}

function GameCoreTE::processClientSettingsReply(%game, %client, %setting, %value)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::processClientSettingsReply");
   
   %status = "Ignored";
   
   echo(%client.authenticated);

   if(%setting $= "PlayerColor0")
   {
      if(!%client.authenticated)
      {
         %status = "Ignored for unauthenticated players";
      }
      else if(isValidPlayerColor(%value))
      {
         %client.paletteColors[0] = %value SPC "255";
         %status = "Ok";
      }
      else
         %status = "Invalid";

   }
   else if(%setting $= "PlayerColor1")
   {
      if(!%client.authenticated)
      {
         %status = "Ignored for unauthenticated players";
      }
      else if(isValidPlayerColor(%value))
      {
         %client.paletteColors[1] = %value SPC "255";
         %status = "Ok";
      }
      else
         %status = "Invalid";
   }

   commandToClient(%client, 'XaNotcSettings1_Confirmation', %setting, %status);
}

function GameCoreTE::clientRecordingDemo(%game, %client, %isRecording)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::clientRecordingDemo");
   
   if(!%isRecording)
      return;
      
   %client.zDemoRecordingSetupInProgress = true;
   TE::setupHud(%client);
   %client.control(%client.player);
   %client.zDemoRecordingSetupInProgress = false;
}

function GameCoreTE::updateClientPlayerList(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::updateClientPlayerList");
   Parent::updateClientPlayerList(%game, %client);
   ETH::updatePlayerList(%client);
}

function GameCoreTE::loadOut(%game, %player)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::loadOut");
   
   Parent::loadOut(%game, %player);
   
   %team = %player.client.team;
   %player.setTeamId(%team.teamId);
   %teamColorF = %team.color;
   %teamColorI = mFloatLength(getWord(%teamColorF, 0)*255, 0) SPC
                 mFloatLength(getWord(%teamColorF, 1)*255, 0) SPC
                 mFloatLength(getWord(%teamColorF, 2)*255, 0) SPC
                 255;
   echo(%teamColorF SPC "->" SPC %teamColorI);

   %player.paletteColors[0] = %teamColorI;
   %player.paletteColors[1] = %teamColorI;

   if(isObject(%player.light))
   {
      %colorI = %player.paletteColors[0];
      %colorF = getWord(%colorI, 0) / 255 SPC
                getWord(%colorI, 1) / 255 SPC
                getWord(%colorI, 2) / 255 SPC
                1;
      %player.light.color = %colorF;
   }

   // Setup ShapeBase HudInfo object team ID
   %player.zShapeBaseHudInfo.setDatasetType(0, $HudInfoDatasetType::TeamID);
   %player.zShapeBaseHudInfo.setDatasetIntField(0, %player.getTeamId());
   %player.zShapeBaseHudInfo.setDatasetType(1, $HudInfoDatasetType::Name);
   %player.zShapeBaseHudInfo.setDatasetStringField(1, %player.client.playerName);

   if(%player.getClassName() $= "Player" || %player.getClassName() $= "AiPlayer")
      TE::loadoutPlayer(%player);
   else if(%player.getClassName() $= "Etherform")
      TE::loadoutEtherform(%player);
}

function GameCoreTE::onUnitDestroyed(%game, %obj)
{
   echo(%game @"\c4 -> "@ %game.class @" -> GameCoreTE::onUnitDestroyed");
   
   if(%obj.zCalledOnUnitDestroyed)
      return;
      
   //echo(Game.roundSetup);
   if(Game.roundSetup || Game.roundSetup $= "")
      return;
      
   Parent::onUnitDestroyed(%game, %obj);
     
   %client = %obj.client;
   if(isObject(%client) && %client.player == %obj)
   {
      ETH::switchToEtherform(%client);
   }
   
   TE::checkRoundEnd();
}

function GameCoreTE::clientAction(%game, %client, %nr)
{
   echo(%game @"\c4 -> "@ %game.class @" -> GameCoreTE::clientAction");

   %obj = %client.getControlObject();
   if(!isObject(%obj))
      return;

   %obj.getDataBlock().clientAction(%obj, %nr);
}

function GameCoreTE::etherformManifest(%game, %obj)
{
   echo(%game @"\c4 -> "@ %game.class @" -> GameCoreTE::etherformManifest");
   
   %client = %obj.client;
   
   if(!isObject(%client))
      return;
      
   if(%obj.getClassName() !$= "Etherform")
      return;
      
   %client.BeepMsg("You can not re-manifest in this game mode!");
     return;
}

function GameCoreTE::suicide(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::suicide");
   ETH::switchToEtherform(%client);
   TE::checkRoundEnd();
}

function GameCoreTE::F(%game, %client, %nr)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreTE::F");
   if(%nr >= 1 && %nr <= 2)
   {
      TE::joinTeam(%client, %nr);
   }
}

  

