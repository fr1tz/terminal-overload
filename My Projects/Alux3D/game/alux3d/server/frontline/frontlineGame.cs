// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// FrontlineGame
// ----------------------------------------------------------------------------
// Depends on methods found in base/gameCore.cs.  Those added here are specific
// to this game type and/or over-ride the "default" game functionaliy.
// ----------------------------------------------------------------------------

function FrontlineGame::onMissionLoaded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onMissionLoaded");

   $Server::MissionType = "Frontline";
   
   // SimSet for unfinished physical soil tiles
   %game.unfinishedSoilTileSet = new SimSet();
   MissionCleanup.add(%game.unfinishedSoilTileSet);

   // SimSet for soil volumes that need to rebuild their geometry
   %game.soilVolumeDirtySet = new SimSet();
   MissionCleanup.add(%game.soilVolumeDirtySet);

   // SimSet for the meta soil worker
   %game.metaSoilWorkerSet = new SimSet();
   MissionCleanup.add(%game.metaSoilWorkerSet);
   
   Parent::onMissionLoaded(%game);
}

function FrontlineGame::initGameVars(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::initGameVars");

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
   $Game::defaultPlayerDataBlock = "DefaultPlayerData";
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
   %game.duration = 30 * 60;
   %game.endgameScore = 20;
   %game.endgamePause = 10;
   %game.allowCycling = false;   // Is mission cycling allowed?
}

function FrontlineGame::startGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::startGame");

   Parent::startGame(%game);
}

function FrontlineGame::endGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::endGame");

   Parent::endGame(%game);
}

function FrontlineGame::onGameDurationEnd(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onGameDurationEnd");

   Parent::onGameDurationEnd(%game);
}

function FrontlineGame::onClientEnterGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onClientEnterGame");

   parent::onClientEnterGame(%game, %client);
}

function FrontlineGame::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onClientLeaveGame");

   parent::onClientLeaveGame(%game, %client);

}


