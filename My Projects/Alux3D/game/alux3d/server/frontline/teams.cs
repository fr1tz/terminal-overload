// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createTeams(%game)
{
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

