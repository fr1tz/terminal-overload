// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


datablock PlayerData(FrmTerritoryGenerator2DV)
{
   thirdPersonOnly = true;
   computeCRC = false;

   // Third person shape
   shapeFile = "content/xa/notc/core/shapes/tg2dv/p1/shape.dae";
   cameraMaxDist = 5;
   allowImageStateAnimation = true;

   // First person arms
   imageAnimPrefixFP = "soldier";
   //shapeNameFP[0] = "content/o/torque3d/3.0/shapes/actors/Soldier/FP/FP_SoldierArms.DAE";

   canObserve = 1;
   cmdCategory = "Clients";

   cameraDefaultFov = "80";
   cameraMinFov = "10";
   cameraMaxFov = "180";

   //debrisShapeName = "content/o/torque3d/3.0/shapes/actors/common/debris_player.dts";
   debris = PlayerDebris;

   throwForce = 30;

   minLookAngle = "-1.5";
   maxLookAngle = "1.5";
   maxFreelookAngle = 3.0;

   mass = 9000;
   drag = 0.0;
   maxdrag = 0;
   density = 10;
   maxDamage = 1000;
   maxEnergy[0] = 100; // damage damper
   maxEnergy[1] = 100; // impulse damper
   damageBuffer = 0;

	repairRate = 0.8;
	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.15;
	rechargeRate = 0.4;

   runForce = 100 * 9000;
   runEnergyDrain = 0;
   minRunEnergy = 0;
   maxForwardSpeed = 15;
   maxBackwardSpeed = 15;
   maxSideSpeed = 15;
   
   sprintForce = 100 * 9000;
   sprintEnergyDrain = 0;
   minSprintEnergy = 0;
   maxSprintForwardSpeed = 40;
   maxSprintBackwardSpeed = 40;
   maxSprintSideSpeed = 40;
   sprintStrafeScale = 1.0;
   sprintYawScale = "1.0";
   sprintPitchScale = "1.0";
   sprintCanJump = true;

   crouchForce = "4500";
   maxCrouchForwardSpeed = 3.0;
   maxCrouchBackwardSpeed = 1.0;
   maxCrouchSideSpeed = 1.0;
   
	slideForce = 20 * 90;
	slideEnergyDrain = 0.7;
   slideEnergySlot = 1;
	minSlideEnergy = 1;
	maxSlideForwardSpeed = 30;
	maxSlideBackwardSpeed = 25;
	maxSlideSideSpeed = 12;

   maxUnderwaterForwardSpeed = 8.4;
   maxUnderwaterBackwardSpeed = 7.8;
   maxUnderwaterSideSpeed = 4.0;

   jumpForce = 750;
   jumpEnergyDrain = 0;
   minJumpEnergy = 0;
   jumpDelay = 0;
   
   xJumpEnergySlot = 1;
   xJumpChargeRate = 2.0;
   xJumpSpeedFactorD = 25;
   xJumpPowerBaseConst = 0;
   xJumpPowerMultConst = 60;
   xJumpInstantEnergy = 20;
   
   gravityMod = 2.0;

	skidSpeed = 9999;
	skidFactor = 0.4;
   
   glideForce = 10 * 90;
   airControl = 0.0;

   fallingSpeedThreshold = -6.0;

   landSequenceTime = 0.33;
   transitionToLand = false;
   recoverDelay = 9;
   recoverRunForceScale = 1.2;

   minImpactSpeed = 60;
   minLateralImpactSpeed = 60;
   speedDamageScale = 1;

   boundingBox = "7 7 7";
   pickupRadius = 1;

   // Damage location details
   boxHeadPercentage       = 0.83;
   boxTorsoPercentage      = 0.49;
   boxHeadLeftPercentage         = 0.30;
   boxHeadRightPercentage        = 0.60;
   boxHeadBackPercentage         = 0.30;
   boxHeadFrontPercentage        = 0.60;

   // Foot Prints
   decalData = FrmStandardcatFootprint;
   decalOffset = 0.25;
   footPuffEmitter = "FrmStandardcatFootPuffEmitter";
   footPuffNumParts = 5;
   footPuffRadius = "0.2";

   dustEmitter = "LightPuffEmitter";

   splash = PlayerSplash;
   splashVelocity = 4.0;
   splashAngle = 67.0;
   splashFreqMod = 300.0;
   splashVelEpsilon = 0.60;
   bubbleEmitTime = 0.4;
   splashEmitter[0] = PlayerWakeEmitter;
   splashEmitter[1] = PlayerFoamEmitter;
   splashEmitter[2] = PlayerBubbleEmitter;
   mediumSplashSoundVelocity = 10.0;
   hardSplashSoundVelocity = 20.0;
   exitSplashSoundVelocity = 5.0;
   
   repairParticleEmitter = FrmStandardcatRepairEmitter;
   
   // Shape trails
   numShapeTrails = 0;
   //shapeTrailsMaterial = xa_notc_core_shapes_standardcat_trailsmat;
   
	// Slide visuals
	//slideParticleFootEmitter[0] = FrmStandardcatSlideFootEmitter;
	//slideParticleTrailEmitter[0] = BlueSlideEmitter;
	//slideContactParticleFootEmitter[0] = RedSlideEmitter;
	//slideContactParticleTrailEmitter[0] = FrmStandardcatSlideContactTrailEmitter;
   slideDecal = FrmStandardcatSlideDecal;
 
   // Skid visuals
	skidParticleFootEmitter[0] = FrmStandardcatSkidFootEmitter0;
	skidParticleFootEmitter[1] = FrmStandardcatSkidFootEmitter1;
	skidParticleTrailEmitter[0] = FrmStandardcatSkidTrailEmitter0;
	//skidParticleTrailEmitter[1] = FrmStandardcatSkidTrailEmitter1;
   skidDecal = FrmStandardcatSkidDecal;

   // Controls over slope of runnable/jumpable surfaces
   runSurfaceAngle  = 40;
   jumpSurfaceAngle = 40;
   maxStepHeight = 1.0;  //two meters
   minJumpSpeed = 0;
   maxJumpSpeed = 9999;

   horizMaxSpeed = 200;
   horizResistSpeed = 30;
   horizResistFactor = 0.35;

   upMaxSpeed = 200;
   upResistSpeed = 25;
   upResistFactor = 0.3;

   footstepSplashHeight = 0.35;

   //NOTE:  some sounds commented out until wav's are available

   // Footstep Sounds
   FootSoftSound        = FrmStandardcatLeftFootSoftSound;
   FootHardSound        = FrmStandardcatLeftFootHardSound;
   FootMetalSound       = FrmStandardcatLeftFootMetalSound;
   FootSnowSound        = FrmStandardcatLeftFootSnowSound;
   FootShallowSound     = FrmStandardcatLeftFootShallowSplashSound;
   FootWadingSound      = FrmStandardcatLeftFootWadingSound;
   FootUnderwaterSound  = FrmStandardcatFootUnderwaterSound;
   //FootBubblesSound     = FootLightBubblesSound;
   OtherFootSoftSound        = FrmStandardcatRightFootSoftSound;
   OtherFootHardSound        = FrmStandardcatRightFootHardSound;
   OtherFootMetalSound       = FrmStandardcatRightFootMetalSound;
   OtherFootSnowSound        = FrmStandardcatRightFootSnowSound;
   OtherFootShallowSound     = FrmStandardcatRightFootShallowSplashSound;
   OtherFootWadingSound      = FrmStandardcatRightFootWadingSound;
   OtherFootUnderwaterSound  = FrmStandardcatFootUnderwaterSound;
   //OtherFootBubblesSound     = FootLightBubblesSound;
   
   //movingBubblesSound   = ArmorMoveBubblesSound;
   //waterBreathSound     = WaterBreathMaleSound;

   impactSoftSound      = FrmStandardcatImpactSoftSound;
   impactHardSound      = FrmStandardcatImpactHardSound;
   impactMetalSound     = FrmStandardcatImpactMetalSound;
   impactSnowSound      = FrmStandardcatImpactSnowSound;
   
	slideSound        = FrmStandardcatSlideSound;
	//slideContactSound = FrmStandardcatSlideContactSound;
 
	skidSound         = FrmStandardcatSkidSound;
 
	xJumpSound          = FrmStandardcatXJumpSound;
	xJumpChargeSound    = FrmStandardcatXJumpChargeSound;

   //impactWaterEasy      = ImpactLightWaterEasySound;
   //impactWaterMedium    = ImpactLightWaterMediumSound;
   //impactWaterHard      = ImpactLightWaterHardSound;

   groundImpactMinSpeed    = "45";
   groundImpactShakeFreq   = "4.0 4.0 4.0";
   groundImpactShakeAmp    = "1.0 1.0 1.0";
   groundImpactShakeDuration = 0.8;
   groundImpactShakeFalloff = 10.0;

   //exitingWater         = ExitingWaterLightSound;

   observeParameters = "0.5 4.5 4.5";

   cameraMinDist = "0";
};

// callback function: called by engine
function FrmTerritoryGenerator2DV::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);

   %obj.allowJumping(false);
   %obj.allowJetJumping(false);
   %obj.allowCrouching(false);
   %obj.allowProne(false);
   %obj.allowSwimming(false);
   %obj.allowSliding(false);
   %obj.allowChargedXJump(false);
   %obj.allowInstantXJump(false);
   %obj.setEnergyLevel(%this.maxEnergy);
 
   // Setup light
   %obj.zLight = new PointLight() {
      attenuationRatio = "0 1 1";
      radius = "10";
      isEnabled = "1";
      color = "1 1 1 1";
      brightness = "2";
      castShadows = "0";
   };
   MissionCleanup.add(%obj.zLight);
   %obj.mountObject(%obj.zLight, 3);
   
   // Player view spawn effect
   if(isObject(%obj.client))
   {
      %max = "-0.5 0 0.5";
      %mode = "0 0 0";
      %dt = "0.02 0 0.02";
      %rnd = "0.0 0.0 0.0";
      commandToClient(%obj.client, 'EnableChromaticLens', %max, %mode, %dt, %rnd);
      %obj.setDamageFlash(1);
   }
   
   %obj.schedule(0, "playSpawnEffects");
}

// callback function: called by engine
function FrmTerritoryGenerator2DV::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   
   if(isObject(%obj.zLight))
      %obj.zLight.delete();
}

function FrmTerritoryGenerator2DV::onTrigger(%this, %obj, %triggerNum, %val)
{
	// This method is invoked when the player receives a trigger
	// move event.  The player automatically triggers slot 0 and
	// slot 1 off of triggers # 0 & 1.  Trigger # 2 is also used
	// as the jump key.

   Parent::onTrigger(%this, %obj, %triggerNum, %val);
   
   if(%triggerNum == 0 && %val)
      %this.transform(%obj);
}

// Called by script
function FrmTerritoryGenerator2DV::playSpawnEffects(%this, %obj)
{
   %obj.playAudio(0, FrmStandardcatSpawnSound);
   createExplosion(FrmStandardCatSpawnEffect, %obj.getWorldBoxCenter(), "0 0 1");
}

// Called by script
function FrmTerritoryGenerator2DV::clientAction(%this, %obj, %nr)
{
   //echo("FrmTerritoryGenerator2DV::clientAction()");
   
   Parent::clientAction(%this, %obj, %nr);
}

// Called by ShapeBase script code.
function FrmTerritoryGenerator2DV::getBleed(%this, %obj, %dmg, %src)
{
   if(%dmg > 90)
      return FrmStandardCatBleedEffect100;
   else if(%dmg > 80)
      return FrmStandardCatBleedEffect90;
   else if(%dmg > 70)
      return FrmStandardCatBleedEffect80;
   else if(%dmg > 60)
      return FrmStandardCatBleedEffect70;
   else if(%dmg > 50)
      return FrmStandardCatBleedEffect60;
   else if(%dmg > 40)
      return FrmStandardCatBleedEffect50;
   else if(%dmg > 30)
      return FrmStandardCatBleedEffect40;
   else if(%dmg > 20)
      return FrmStandardCatBleedEffect30;
   else if(%dmg > 10)
      return FrmStandardCatBleedEffect20;
   else if(%dmg > 0)
      return FrmStandardCatBleedEffect10;
   else
      return FrmStandardCatBleedEffect0;
}

function FrmTerritoryGenerator2DV::canMaterialize(%this, %client, %pos, %normal, %transform)
{
	%ownTeamId = %client.team.teamId;
 
 	InitContainerRadiusSearch(%pos, 0.1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.getDataBlock().getId() == MetaSoilTile.getId())
      {
         if(%srchObj.teamId == %ownTeamId)
            return "";
      }
	}
 
   return "No friendly soil found";

	%inOwnZone = false;
	%inOwnTerritory = false;
	%inEnemyZone = false;

	InitContainerRadiusSearch(%pos, 0.0001, $TypeMasks::TacticalSurfaceObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
		// object actually in this zone?
		//%inSrchZone = false;
		//for(%i = 0; %i < %srchObj.getNumObjects(); %i++)
		//{
      //   error(%srchObj.getObject(%i).getDataBlock().getName());
		//	if(%srchObj.getObject(%i) == %this.player)
		//	{
		//		%inSrchZone = true;
		//		break;
		//	}
		//}
		//if(!%inSrchZone)
		//	continue;

		%zoneTeamId = %srchObj.getTeamId();
		%zoneBlocked = %srchObj.zBlocked;

		if(%zoneTeamId != %ownTeamId && %zoneTeamId != 0)
		{
			%inEnemyZone = true;
			break;
		}
		else if(%zoneTeamId == %ownTeamId)
		{
			%inOwnZone = true;
			if(%srchObj.getDataBlock().getName() $= "TerritorySurface"
			|| %srchObj.getDataBlock().isTerritoryZone)
				%inOwnTerritory = true;
		}
	}

   %spawn = true;
	if(%inEnemyZone)
	{
		return "You cannot materialize on an enemy's surface!";
	}
	else if(%inOwnZone && !%inOwnTerritory)
	{
		return "This surface can't be used to materialize!";
	}
	else if(!%inOwnZone)
	{
		return "You can only materialize on your team's surfaces!";
	}
	else if(%zoneBlocked)
	{
		return "This surface is currently blocked!";
	}

   return "";
}

// Called from script
function FrmTerritoryGenerator2DV::transform(%this, %obj)
{
   %pos = %obj.getPosition();

   // Check for nearby objects.
   %radius = 22;
   %typeMask = $TypeMasks::ShapeBaseObjectType | $TypeMasks::StaticShapeObjectType;
	InitContainerRadiusSearch(%pos, %radius, %typeMask);
	while((%targetObject = containerSearchNext()) != 0)
	{
      if(%targetObject == %obj)
         continue;
         
      if(%targetObject.getType() & $TypeMasks::TerrainObjectType)
         continue;

      //echo(%targetObject.getClassName());
      %obj.client.beepMsg("You're too close to another object!");
      return;
	}

   %x1 = getWord(%pos, 0);
   %y1 = getWord(%pos, 1);
   %z1 = getWord(%pos, 2);
   
   %x2 = snapFloat(%x1, 4);
   if(%x2 > %x1)
      %x2 -= 2;
   else
      %x2 += 2;
      
   %y2 = snapFloat(%y1, 4);
   if(%y2 > %y1)
      %y2 -= 2;
   else
      %y2 += 2;
      
   %noTerrain = false;
   %min = 999999999999999;
   %max = -999999999999999;
   for(%x = %x2-6; %x <= %x2+6; %x += 4)
   {
      for(%y = %y2-6; %y <= %y2+6; %y += 4)
      {
         %start = %x SPC %y SPC %z1+4;
         %end = %x SPC %y SPC %z1-12;
         %mask = $TypeMasks::TerrainObjectType;
         %c = ContainerRayCast(%start, %end, %mask, 0);
         if(%c == 0)
         {
            %noTerrain = true;
            break;
         }
         %z = getWord(%c, 3);
         if(%z > %max)
            %max = %z;
         if(%z < %min)
            %min = %z;
      }
      if(%noTerrain)
         break;
   }
   
   if(%noTerrain)
   {
      if(isObject(%obj.client))
         %obj.client.beepMsg("Missing grid!");
      return;
   }
   
   if(%max - %min > 6)
   {
      if(isObject(%obj.client))
         %obj.client.beepMsg("Grid is too uneven!");
      return;
   }
   
   %pos2 = %x2 SPC %y2 SPC %max;
   
   %struct = TerritoryGenerator2.create();
   %struct.setTeamId(%obj.getTeamId());
   %struct.setTransform(%pos2);
   %struct.getDataBlock().updateAssetsThread(%struct);
   %struct.setDamageLevel(%struct.getDataBlock().maxDamage * %obj.getDamagePercent());

   createExplosion(FrmStandardCatSpawnEffect, %pos2, "0 0 1");
   
   %obj.setDamageLevel(%this.maxDamage);
   %obj.setTransform(%pos2);
   %obj.schedule(0, "delete");
   Game.onUnitDestroyed(%obj);
   
   if(isObject(%obj.client))
   {
      if(isObject(%obj.client.zTerritoryGenerator))
         %obj.client.zTerritoryGenerator.destroy();
      %obj.client.zTerritoryGenerator = %struct;
   }
}

