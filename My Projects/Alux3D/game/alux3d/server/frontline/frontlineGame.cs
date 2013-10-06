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
}

function FrontlineGame::startGame(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::startGame");

   Parent::startGame(%game);
   
	createTeams(%game);

	%game.startNewRound();
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

   Parent::onClientEnterGame(%game, %client);
}

function FrontlineGame::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onClientLeaveGame");

   Parent::onClientLeaveGame(%game, %client);

}

function FrontlineGame::preparePlayer(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::preparePlayer");
   
	// Join team with less players.
	if(%game.team1.numPlayers > %game.team2.numPlayers)
   	%game.joinTeam(%client, 2);
   else
      %game.joinTeam(%client, 1);
}

function FrontlineGame::joinTeam(%game, %client, %teamId)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::joinTeam");

	if (%teamid > 2 || %teamid < 0)
		return false;

	if( %client.team != 0 && %teamId == %client.team.teamId)
		return false;

   %client.removeForms();

	// remove from old team...
	if(%client.team == %game.team0)
		%game.team0.numPlayers--;
	else if(%client.team == %game.team1)
		%game.team1.numPlayers--;
	else if(%client.team == %game.team2)
		%game.team2.numPlayers--;

	// add client to new team...
	if(%teamId == 0)
	{
		%client.team = %game.team0;
		%game.team0.numPlayers++;

		%client.setNewbieHelp("You are in observer mode. Click on 'Switch Team' at the top" SPC
			"of the arena window to join a team. Press @bind01 if the arena window is not visible.");

      %client.setLoadingBarText("Use the 'Switch Team' menu to join" SPC
         %game.team1.name SPC "or" SPC %game.team2.name @ "!");
	}
	else
   {
      if(%teamId == 1)
   	{
   		%client.team = %game.team1;
   		%game.team1.numPlayers++;
   	}
   	else if(%teamId == 2)
   	{
   		%client.team = %game.team2;
   		%game.team2.numPlayers++;
   	}

      %client.setLoadingBarText("Press @bind01 to play" SPC  $Server::MissionType);
   }

	// full and simple control cleanup...
	//%client.clearFullControl();
	//%client.clearSimpleControl();

	// notify all clients of team change...
	MessageAll('MsgClientJoinTeam', '\c2%1 joined the %2.',
		%client.playerName,
		%client.team.teamName,
		%client.team.teamId,
		%client,
		%client.sendGuid,
		%client.score,
		%client.isAiControlled(),
		%client.isAdmin,
		%client.isSuperAdmin);

   //%client.createPointer();
	//%client.spawnPlayer();
	//%client.updateHudColors();
   //%client.displayInventory();

   %playerSpawnPoint = pickPlayerSpawnPoint($Game::DefaultPlayerSpawnGroups);
   %game.spawnPlayer(%client, %playerSpawnPoint);

   return;

	%count = ClientGroup.getCount();
	for(%cl= 0; %cl < %count; %cl++)
   {
		%client = ClientGroup.getObject(%cl);
      if(%client.menuVisible && %client.menu $= "teams")
         %client.showTeamsMenu();
   }

   //---------------------------------------------------------------------------
	// HACK HACK HACK: find way to update object colorizations
   // only for the client that switched teams.
	for( %idx = MissionCleanup.getCount()-1; %idx >= 0; %idx-- )
	{
		%obj = MissionCleanup.getObject(%idx);
      %obj.setTeamId(%obj.getTeamId());
	}
	%group = nameToID("EthPath");
	if(%group != -1)
	{
		%count = %group.getCount();
		if (%count != 0)
		{
				for (%i = 0; %i < %count; %i++)
				{
					%zone = %group.getObject(%i);
					%zone.setTeamId(%zone.getTeamId());
				}
		}
	}
   //---------------------------------------------------------------------------
}

function FrontlineGame::spawnPlayer(%game, %client, %spawnPoint, %noControl)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::spawnPlayer");
   
   %client.resetInventory();

	// Remove existing etherform
	if(%client.player > 0 && %client.player.getClassName() $= "Etherform")
		%client.player.delete();

	// observers have no players...
	if(%client.team == %game.team0)
	{
		%client.camera.setFlyMode();
		%client.setControlObject(%client.camera);
		return;
	}

	%data = %game.getEtherformDataBlock(%client);
	%obj = new Etherform() {
		dataBlock = %data;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%obj);
   
	// Setup
	%obj.setTransform(%spawnPoint.getTransform());
	%obj.setCurrTagged(0);
	%obj.setCurrTaggedPos("0 0 0");

	// update the client's observer camera to start with the player...
	%client.camera.setMode("Observer");
	%client.camera.setTransform(%obj.getEyeTransform());

	// give the client control of the player...
	%client.player = %obj;
	%client.control(%obj);
	//%client.updateHudColors();
}

function FrontlineGame::startNewRound(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::startNewRound");

}

function FrontlineGame::getEtherformDataBlock(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> FrontlineGame::getEtherformDataBlock");

   return FrmLight;
}



