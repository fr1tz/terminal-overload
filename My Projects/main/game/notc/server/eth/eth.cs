// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ETH::createTeams(%game)
{
   echo("ETH::createTeams()");

	if(!isObject(%game.team0))
	{
		%game.team0 = new ScriptObject()
		{
			teamId = 0;
			name = "Observers";
         color = theLevelInfo.teamColors0;
			numPlayers = 0;
		};
		MissionCleanup.add(%game.team0);
	}

	if(!isObject(%game.team1))
	{
		%game.team1 = new ScriptObject()
		{
			teamId = 1;
			name = "Reds";
         color = theLevelInfo.teamColors1;
			score = 0;
			numPlayers = 0;
			numTerritoryZones = 0;
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
			name = "Blues";
         color = theLevelInfo.teamColors2;
			score = 0;
			numPlayers = 0;
			numTerritoryZones = 0;
			numCATs = 0;
            repairSpeed = 0.5;
		};
		MissionCleanup.add(%game.team2);

		%game.team2.repairObjects = new SimGroup();
		MissionCleanup.add(%game.team2.repairObjects);
	}
}

function ETH::joinTeam(%client, %teamId)
{
   echo("ETH::joinTeam()" SPC %client SPC "-> team" SPC %teamId);

	if (%teamid > 2 || %teamid < 0)
		return false;

	if( %client.team != 0 && %teamId == %client.team.teamId)
		return false;

	// Remove from old team.
	if(%client.team == Game.team0)
		Game.team0.numPlayers--;
	else if(%client.team == Game.team1)
		Game.team1.numPlayers--;
	else if(%client.team == Game.team2)
		Game.team2.numPlayers--;

	// Add client to new team.
	if(%teamId == 0)
	{
		%client.team = Game.team0;
		Game.team0.numPlayers++;
	}
	else
   {
      if(%teamId == 1)
   	{
   		%client.team = Game.team1;
   		Game.team1.numPlayers++;
   	}
   	else if(%teamId == 2)
   	{
   		%client.team = Game.team2;
   		Game.team2.numPlayers++;
   	}
   }
   
	// Notify all clients of team change.
	MessageAll('MsgClientJoinTeam', '\c2%1 joined team %2.',
		%client.name,
		%client.team.teamId,
		%client.team.teamId,
		%client,
		%client.sendGuid,
		%client.score,
		%client.isAiControlled(),
		%client.isAdmin,
		%client.isSuperAdmin);

	return true;
}

function ETH::onDeath(%client)
{
   echo("ETH::onDeath()");

   %client.timeOfDeath = getSimTime();

   // Clear out the name on the corpse
   %client.player.setShapeName("");

   // Schedule corpse removal
   cancelAll(%client.player);
   %client.player.schedule(10000, "startFade", 1000, 0, true);
   %client.player.schedule(11000, "delete");

   // Switch the client over to the death cam and unhook the player object.
   if (isObject(%client.deathCamera) && isObject(%client.player))
   {
      %client.deathCamera.controlMode = "Stationary";
      %client.deathCamera.setDamageFlash(1);
      %client.deathCamera.fovDelta = 0.25;
      %client.deathCamera.viewIrisSizeX = 8;
      %client.deathCamera.viewIrisSizeY = 8;
      %client.deathCamera.viewIrisDtX = -0.025;
      %client.deathCamera.viewIrisDtY = -0.03;
      %client.deathCamera.viewMotionBlurActive = true;
      %client.deathCamera.viewMotionBlurVelMul = 5;
      %client.deathCamera.hearingDeafness = 0.7;
      %client.deathCamera.hearingDeafnessDt = 0.0010;
      %client.deathCamera.hearingTinnitusEnabled = false;
      %client.deathCamera.hearingTinnitusVolume = 1.0;
      %client.deathCamera.hearingTinnitusVolumeDt = -0.005;
      %client.player.mountObject(%client.deathCamera, 4);
      %client.control(%client.deathCamera);
   }
   %client.player = 0;

   // Display damage appropriate kill message
   %sendMsgFunction = "sendMsgClientKilled_" @ %damageType;
   if ( !isFunction( %sendMsgFunction ) )
      %sendMsgFunction = "sendMsgClientKilled_Default";
   call( %sendMsgFunction, 'MsgClientKilled', %client, %sourceClient, %damLoc );

   // Dole out points and check for win
   if (( %damageType $= "Suicide" || %sourceClient == %client ) && isObject(%sourceClient))
   {
      Game.incDeaths( %client, 1, true );
      Game.incScore( %client, -1, false );
   }
   else
   {
      Game.incDeaths( %client, 1, false );
      Game.incScore( %sourceClient, 1, true );
      Game.incKills( %sourceClient, 1, false );

      // If the game may be ended by a client getting a particular score, check that now.
      if ( $Game::EndGameScore > 0 && %sourceClient.kills >= $Game::EndGameScore )
         Game.cycleGame();
   }
}

function ETH::startNewRound()
{
   // Cleanup
   for( %idx = MissionCleanup.getCount()-1; %idx >= 0; %idx-- )
   {
      %obj = MissionCleanup.getObject(%idx);
      if(!%obj.isMethod("getType"))
         continue;
      if(%obj.getType() & $TypeMasks::ProjectileObjectType
      || %obj.getType() & $TypeMasks::PlayerObjectType
      || %obj.getType() & $TypeMasks::CorpseObjectType)
         %obj.delete();
   }

   Game.team1.numPlayersOnRoundStart = 0;
   Game.team2.numPlayersOnRoundStart = 0;

   TerritoryZones_reset();

   for( %clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++ )
   {
      %client = ClientGroup.getObject(%clientIndex);

      // Do not respawn observers.
      if(%client.team == Game.team1 || %client.team == Game.team2 )
         Game.preparePlayer(%client);
   }

   //serverUpdateMusic();
   //serverUpdateGameStatus();

   Game.roundRestarting = false;
}

function ETH::checkRoundEnd()
{
   if(Game.roundRestarting)
      return;

   if(Game.team1.numTerritoryZones == 0 && Game.team1.numCATs == 0)
   {
      centerPrintAll(Game.team2.name @ " have won!",3);
      serverPlay2D(BlueVictorySound);
      schedule(5000, MissionEnvironment, "startNewRound");
      Game.roundRestarting = true;
   }
   else if(Game.team2.numTerritoryZones == 0 && Game.team2.numCATs == 0)
   {
      centerPrintAll(Game.team1.name @ " have won!",3);
      serverPlay2D(RedVictorySound);
      schedule(5000, MissionEnvironment, "startNewRound");
      Game.roundRestarting = true;
   }
}
