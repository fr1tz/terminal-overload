// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::initGameVars(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::initGameVars");

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
   $Game::defaultPlayerDataBlock = "FrmLight";
   $Game::defaultPlayerSpawnGroups = "PlayerDropPoints";

   //-----------------------------------------------------------------------------
   // What kind of "camera" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   // These override the values set in core/scripts/server/spawn.cs
   //-----------------------------------------------------------------------------
   $Game::defaultCameraClass = "Camera";
   $Game::defaultCameraDataBlock = "Observer";
   $Game::defaultCameraSpawnGroups = "PlayerDropPoints";

   // Set the gameplay parameters
   %game.duration = 30 * 60;
   %game.endgameScore = 20;
   %game.endgamePause = 10;
   %game.allowCycling = false;   // Is mission cycling allowed?
   
   %game.form[0] = FrmLight;
   %game.form[1] = FrmParrot;
   %game.form[2] = FrmBumblebeeStatic;
   %game.form[3] = FrmCrate;
   %game.form[4] = FrmSoldier;
   %game.form[5] = FrmPillar;
   %game.form[6] = FrmHoverpod;
   %game.form[7] = FrmHovercycle;
   %game.formCount = 7;
   %game.weapon[1] = WpnBadgerImage;
   %game.weapon[2] = WpnStyckImage;
   %game.weapon[3] = WpnLaserhawkImage;
   %game.weapon[4] = WpnMinihawkImage;
   %game.weapon[5] = WpnRaptorImage;
   %game.weapon[6] = WpnScorpionImage;
   %game.weaponCount = 6;
}

function FrontlineGame::onMissionLoaded(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onMissionLoaded");

   $Server::MissionType = "Frontline";

   // SimSet for unfinished physical soil tiles
   %game.unfinishedSoilTileSet = new SimSet();
   MissionCleanup.add(%game.unfinishedSoilTileSet);

   // SimSet for meta soil tiles that need updating
   %game.soilTileDirtySet = new SimSet();
   MissionCleanup.add(%game.soilTileDirtySet);

   // SimSet for soil volumes that need to rebuild their geometry
   %game.soilVolumeDirtySet = new SimSet();
   MissionCleanup.add(%game.soilVolumeDirtySet);

   // SimSet for the meta soil worker
   %game.metaSoilWorkerSet = new SimSet();
   MissionCleanup.add(%game.metaSoilWorkerSet);

   Parent::onMissionLoaded(%game);
}

