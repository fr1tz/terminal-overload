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
         color = "1 1 1";
			numPlayers = 0;
		};
		MissionCleanup.add(%game.team0);
	}

	if(!isObject(%game.team1))
	{
		%game.team1 = new ScriptObject()
		{
			teamId = 1;
         color = theLevelInfo.teamColors1;
			score = 0;
			numPlayers = 0;
			numTerritoryZones = 0;
			numCATs = 0;
         repairSpeed = 0.05;
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
         color = theLevelInfo.teamColors2;
			score = 0;
			numPlayers = 0;
			numTerritoryZones = 0;
			numCATs = 0;
         repairSpeed = 0.05;
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
		%client.playerName,
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
   Game.roundRestarting = true;
   
   // Update team colors here so mappers don't have to restart the
   // server when experimenting with team colors.
   Game.team0.color = theLevelInfo.teamColors0;
   Game.team1.color = theLevelInfo.teamColors1;
   Game.team2.color = theLevelInfo.teamColors2;

   // Cleanup
   for( %idx = MissionCleanup.getCount()-1; %idx >= 0; %idx-- )
   {
      %obj = MissionCleanup.getObject(%idx);
      if(!%obj.isMethod("getType"))
         continue;
         
      if(%obj.getType() & $TypeMasks::CameraObjectType)
         continue;
         
      if(%obj.getType() & $TypeMasks::ProjectileObjectType
      || %obj.getType() & $TypeMasks::ShapeBaseObjectType)
         %obj.delete();
   }

   Game.team1.numPlayersOnRoundStart = 0;
   Game.team2.numPlayersOnRoundStart = 0;

   TerritoryZones_reset();

   for( %clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++ )
   {
      %client = ClientGroup.getObject(%clientIndex);
      
      ETH::resetLoadout(%client);

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
      
   if(Game.team0.numTerritoryZones > 0)
      return;

   if(Game.team1.numTerritoryZones == 0 && Game.team1.numCATs == 0)
   {
      centerPrintAll("Team 2 has won this round!",3);
      serverPlay2D(BlueVictorySound);
      schedule(5000, MissionGroup, "ETH::startNewRound");
      Game.roundRestarting = true;
   }
   else if(Game.team2.numTerritoryZones == 0 && Game.team2.numCATs == 0)
   {
      centerPrintAll("Team 1 has won this round!",3);
      serverPlay2D(RedVictorySound);
      schedule(5000, MissionGroup, "ETH::startNewRound");
      Game.roundRestarting = true;
   }
}

function ETH::resetLoadout(%client)
{
   %active[0] = true;
   %active[1] = true;
   %active[2] = true;
   %active[3] = true;
   %active[4] = false;
   %active[5] = false;
   %active[6] = false;

   %icon[0] = "content/xa/notc/core/icons/p1/smg1.32x32.png";
   %icon[1] = "content/xa/notc/core/icons/p1/mgl1.32x32.png";
   %icon[2] = "content/xa/notc/core/icons/p1/sr1.32x32.png";
   %icon[3] = "content/xa/notc/core/icons/p1/mg1.32x32.png";

   for(%i = 0; %i < 6; %i++)
   {
      %client.zLoadoutProgress[%i] = 1.0;
      %client.zLoadoutProgressDt[%i] = 0.0;
      %client.LoadoutHud_UpdateSlot(%i, %active[%i], %icon[%i], 1.0);
   }
}

function ETH::loadoutEtherform(%player)
{
   // Setup ShapeBase HudInfo object icon
   %player.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %player.zShapeBaseHudInfo.setDatasetIntField(2, 128);
   
   copyPalette(%player, %player.zBallastShape1);
   copyPalette(%player, %player.zBallastShape2);
}

function ETH::loadoutPlayer(%player)
{
   //echo("ETH::loadoutPlayer()");

   %client = %player.client;
   if(!isObject(%client))
      return;

   // Setup ShapeBase HudInfo object icon
   %player.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %player.zShapeBaseHudInfo.setDatasetIntField(2, %client.zActiveLoadout+1);

   %player.setInventory(ItemDamper, 1);
   %player.setInventory(ItemVAMP, 1);
   %player.setInventory(ItemEtherboard, 1);
   %player.setInventory(ItemImpShield, 1);
   %player.setInventory(ItemLauncher, 1);
   %player.setInventory(ItemBounce, 1);
   %player.setInventory(ItemXJump, 1);

   %player.setInventory(ItemG1Launcher, 1);
   
   %player.setInventory(WpnRepelDiscAmmo, 9999);
   %player.setInventory(WpnExplosiveDiscAmmo, 9999);
   
   %player.clearWeaponCycle();
   switch(%client.zActiveLoadout)
   {
      case 0:
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnSMG2, 1);
         %player.setInventory(WpnSG3, 1);
         %player.addToWeaponCycle(WpnSMG2);
         %player.addToWeaponCycle(WpnSG3);
         %player.mountImage(WpnSMG2Image, 0);
      case 1:
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnMGL2, 1);
         %player.addToWeaponCycle(WpnMGL2);
         %player.mountImage(WpnMGL2Image, 0);
      case 2:
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnSR2, 1);
         %player.addToWeaponCycle(WpnSR2);
         %player.mountImage(WpnSR2Image, 0);
      case 3:
         %player.setInventory(WpnMG2, 1);
         %player.addToWeaponCycle(WpnMG2);
         %player.mountImage(WpnMG2Image, 0);
   }
}

function ETH::switchToEtherform(%client)
{
   %player = %client.player;
   if(!isObject(%player))
      return;
      
   if(%player.getClassName() $= "Etherform")
      return;
      
   // Update loadout
   %damage = %player.getDamageLevel();
   %maxDamage = %player.getDataBlock().maxDamage;
   %percent = 1 - %damage/%maxDamage;
   %slot = %client.zActiveLoadout;
   %client.zLoadoutProgress[%slot] = %percent;
   %client.LoadoutHud_UpdateSlot(%slot, "", "", %percent);
   error(%percent);

   %tagged = %player.isTagged();
   %pos = %player.getWorldBoxCenter();

   %etherform = new Etherform() {
      dataBlock = FrmEtherform;
      client = %client;
      teamId = %client.team.teamId;
   };
	MissionCleanup.add(%etherform);
   Game.loadout(%etherform);

   %mat = %player.getTransform();
   %dmg = %player.getDamageLevel();
   %nrg = %player.getEnergyLevel();
   %buf = %player.getDamageBufferLevel();
   %vel = %player.getVelocity();

   %etherform.setTransform(%mat);
   %etherform.setTransform(%pos);
   %etherform.setDamageLevel(%dmg);
   %etherform.setShieldLevel(%buf);

//   if(%tagged || $Server::Game.tagMode == $Server::Game.alwaystag)
//      %etherform.setTagged();

   %client.control(%etherform);
   
   if(%player.getDamageState() $= "Enabled")
      %player.schedule(0, "delete");

   %etherform.setEnergyLevel(%nrg - 50);
   %etherform.applyImpulse(%pos, VectorScale(%vel,100));
   %etherform.playAudio(0, EtherformSpawnSound);

	%client.player = %etherform;
 
   // Demanifest effect
   if(%player.getDamageState() $= "Enabled")
   {
      %shape = new StaticShape() {
         dataBlock = FrmStandardcatDemanifestShape;
      };
      MissionCleanup.add(%shape);
      copyPalette(%etherform, %shape);
      %shape.playThread(0, "ambient");
      %shape.setThreadTimeScale(0, 3);
      %shape.setThreadDir(0, true);
      %shape.startFade(200, 50, true);
      %shape.schedule(500, "delete");
      
      %etherform.mountObject(%shape, 8);
   }
}

