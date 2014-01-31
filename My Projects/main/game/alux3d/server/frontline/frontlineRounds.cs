// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::startNewRound(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::startNewRound");

	%game.roundRestarting = true;

	// Cleanup
	for( %idx = MissionCleanup.getCount()-1; %idx >= 0; %idx-- )
	{
		%obj = MissionCleanup.getObject(%idx);
  
		if(%obj.getType() & $TypeMasks::ProjectileObjectType
		|| %obj.getType() & $TypeMasks::PlayerObjectType
		|| %obj.getType() & $TypeMasks::VehicleObjectType
		|| %obj.getType() & $TypeMasks::DamagableItemObjectType
		|| %obj.getType() & $TypeMasks::CorpseObjectType)
      {
			%obj.delete();
      }
   
      if(%obj.getClassName() $= "HexagonVolume")
      {
         if(%obj.getDataBlock() == BrickVolume.getId())
            %obj.delete();
      }
	}

	%game.team1.numPlayersOnRoundStart = 0;
	%game.team2.numPlayersOnRoundStart = 0;

   Soil::reset();

   for(%i = 0; %i < ClientGroup.getCount(); %i++)
   {
      %client = ClientGroup.getObject(%i);
		if(%client.team.teamId != 0)
      {
         %playerSpawnPoint = pickPlayerSpawnPoint($Game::DefaultPlayerSpawnGroups);
         %game.spawnPlayer(%client, %playerSpawnPoint);
      }
	}

	%game.roundRestarting = false;
}

function FrontlineGame::checkRoundEnd(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::checkRoundEnd");

	if(%game.roundRestarting)
		return;

   if(%game.team1.numSoilTiles == 0)
   {
      centerPrintAll(%game.team2.teamName @ " have won!", 3);
      //serverPlay2D(BlueVictorySound);
      Game.schedule(5000, "startNewRound");
      %game.roundRestarting = true;
   }
   else if(%game.team2.numSoilTiles == 0)
   {
      centerPrintAll(%game.team1.teamName @ " have won!", 3);
      //serverPlay2D(RedVictorySound);
      Game.schedule(5000, "startNewRound");
      %game.roundRestarting = true;
   }
}
