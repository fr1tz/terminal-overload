// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::startGame(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::startGame");

   Parent::startGame(%game);
	%game.createTeams();
	%game.startNewRound();
}

function FrontlineGame::endGame(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::endGame");

   Parent::endGame(%game);
}

function FrontlineGame::onGameDurationEnd(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onGameDurationEnd");

   Parent::onGameDurationEnd(%game);
}

function FrontlineGame::onClientEnterGame(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onClientEnterGame");

	for(%i = 0; %i <= 100; %i++)
   {
      %game.loadDefaultUnit(%client, %i);
   }

   // Resources
   %client.resources = new ScriptObject();
   %game.updateResourcesThread(%client);

   Parent::onClientEnterGame(%game, %client);
}

function FrontlineGame::onClientLeaveGame(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onClientLeaveGame");

   Parent::onClientLeaveGame(%game, %client);

	if(isObject(%client.resources))
		%client.resources.delete();
}

function FrontlineGame::preparePlayer(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::preparePlayer");
   
	// Join team with less players.
	if(%game.team1.numPlayers > %game.team2.numPlayers)
   	%game.joinTeam(%client, 2);
   else
      %game.joinTeam(%client, 1);
}

function FrontlineGame::spawnPlayer(%game, %client, %spawnPoint, %noControl)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::spawnPlayer");
   
   %game.resetResources(%client);

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

function FrontlineGame::onFormDestroyed(%game, %client, %obj)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onFormDestroyed");
   
   %obj.zFormDestroyed = true;
   %obj.removePiecesFromPlay();
}

function FrontlineGame::onDeath(%game, %client, %sourceObject, %sourceClient, %damageType, %damLoc)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::onDeath");
   
   %form = %client.player;
   
   if(isObject(%client))
   {
      %game.onFormDestroyed(%client, %form);
      if(%client == %form.getControllingClient())
         %game.clientLeaveForm(%client, %form);
   }
   
   return;


   // Clear out the name on the corpse
   %client.player.setShapeName("");

   // Schedule corpse removal
   cancelAll(%client.player);
   %client.player.schedule(10000, "startFade", 1000, 0, true);
   %client.player.schedule(11000, "delete");

   // Switch the client over to the death cam and unhook the player object.
   if (isObject(%client.camera) && isObject(%client.player))
   {
      %client.camera.setMode("Corpse", %client.player);
      %client.camera.setDamageFlash(1);
      %client.camera.fovDelta = 0.25;
      %client.camera.viewIrisSizeX = 8;
      %client.camera.viewIrisSizeY = 8;
      %client.camera.viewIrisDtX = -0.025;
      %client.camera.viewIrisDtY = -0.03;
      %client.camera.viewMotionBlurActive = true;
      %client.camera.viewMotionBlurVelMul = 5;
      %client.camera.hearingDeafness = 0.7;
      %client.camera.hearingDeafnessDt = 0.0010;
      %client.camera.hearingTinnitusEnabled = true;
      %client.camera.hearingTinnitusVolume = 1.0;
      %client.camera.hearingTinnitusVolumeDt = -0.005;
      %client.player.mountObject(%client.camera, 4);
      %client.control(%client.camera);
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
      %game.incDeaths( %client, 1, true );
      %game.incScore( %client, -1, false );
   }
   else
   {
      %game.incDeaths( %client, 1, false );
      %game.incScore( %sourceClient, 1, true );
      %game.incKills( %sourceClient, 1, false );

      // If the game may be ended by a client getting a particular score, check that now.
      if ( $Game::EndGameScore > 0 && %sourceClient.kills >= $Game::EndGameScore )
         %game.cycleGame();
   }
}


