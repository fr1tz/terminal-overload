// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::createTeams(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::createTeams");

   %game.numTeams = 3;
   
	if(!isObject(%game.team0))
	{
		%game.team0 = new ScriptObject()
		{
			teamId = 0;
			teamName = "Observers";
			numPlayers = 0;
		};
		MissionCleanup.add(%game.team0);
	}

	if(!isObject(%game.team1))
	{
		%game.team1 = new ScriptObject()
		{
			teamId = 1;
			teamName = "Team1";
			score = 0;
			numPlayers = 0;
			numTerritorySurfaces = 0;
			numCATs = 0;
            repairSpeed = 0.5;
		};
		MissionCleanup.add(%game.team1);
		
		%game.team1.repairObjects = new SimGroup();
		MissionCleanup.add(%game.team1.repairObjects);
	}

	if(!isObject(%game.team2))
	{
		%game.team2 = new ScriptObject()
		{
			teamId = 2;
			teamName = "Team2";
			score = 0;
			numPlayers = 0;
			numTerritorySurfaces = 0;
			numCATs = 0;
            repairSpeed = 0.5;
		};
		MissionCleanup.add(%game.team2);

		%game.team2.repairObjects = new SimGroup();
		MissionCleanup.add(%game.team2.repairObjects);
	}
}

function FrontlineGame::joinTeam(%game, %client, %teamId)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::joinTeam");

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

