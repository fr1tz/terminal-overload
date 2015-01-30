// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(FrmStandardcatDemanifestShape)
{
   ignoreDamage = true;
   shapeFile = "content/xa/notc/core/shapes/standardcat/demanifest/p1/shape.dae";
};

datablock PlayerData(FrmStandardcat)
{
   proxy = FrmStandardcatProxy; // script field
   spore = FrmStandardcatSpore; // script field
   btime = 2000; // script field: how long form is blocked after materialization
   dtime = 5000; // script field: de-materialization time

   allowColorization = 1;

   renderFirstPerson = false;

   computeCRC = false;

   // Third person shape
   shapeFile = "content/xa/notc/core/shapes/standardcat/old.dts";
   cameraMaxDist = 3;
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

   mass = 90;
   drag = 0.0;
   maxdrag = 0;
   density = 10;
   maxDamage = 75;
   maxEnergy[0] = 100; // damage damper
   maxEnergy[1] = 100; // impulse damper
   damageBuffer = 25;
   energyPerDamagePoint = 75;

	repairRate = 0.8;
	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.15;
	rechargeRate = 0.4;

   runForce = 100 * 90;
   runEnergyDrain = 0;
   minRunEnergy = 0;
   maxForwardSpeed = 10;
   maxBackwardSpeed = 10;
   maxSideSpeed = 10;
   
   sprintForce = 100 * 90;
   sprintEnergyDrain = 0;
   minSprintEnergy = 0;
   maxSprintForwardSpeed = 20;
   maxSprintBackwardSpeed = 12;
   maxSprintSideSpeed = 12;
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

	skidSpeed = 25;
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

   boundingBox = "1.0 0.75 2.6";
   crouchBoundingBox = "0.65 0.75 1.3";
   swimBoundingBox = "1 2 2";
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
   numShapeTrails = 5;
   shapeTrailsMaterial = xa_notc_core_shapes_standardcat_trailsmat;
   
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

   // Allowable Inventory Items
   mainWeapon = WpnSMG1;

   maxInv[ItemDamper] = 1;
   maxInv[ItemVAMP] = 1;
   maxInv[ItemImpShield] = 1;
   maxInv[ItemBallast] = 1;
   maxInv[ItemStealth] = 1;
   maxInv[ItemEtherboard] = 1;
   maxInv[ItemLauncher] = 1;
   maxInv[ItemBounce] = 1;
   maxInv[ItemXJump] = 1;

   maxInv[ItemG1Launcher] = 1;
   maxInv[ItemG1LauncherAmmo] = 9999;
   
   maxInv[WpnRazorDiscAmmo] = 9999;
   maxInv[WpnExplosiveDiscAmmo] = 9999;
   maxInv[WpnRepelDiscAmmo] = 9999;

   maxInv[WpnSMG1] = 1;
   maxInv[WpnSMG2] = 1;
   maxInv[WpnMGL1] = 1;
   maxInv[WpnMGL2] = 1;
   maxInv[WpnSG1] = 1;
   maxInv[WpnSG2] = 1;
   maxInv[WpnSG3] = 1;
   maxInv[WpnSR1] = 1;
   maxInv[WpnSR2] = 1;
   maxInv[WpnMG1] = 1;
   maxInv[WpnMG2] = 1;
   maxInv[WpnML1] = 1;
   
   maxInv[WpnMGL1Ammo] = 9999;
   maxInv[WpnSG1Ammo] = 9999;
   maxInv[WpnSG2Ammo] = 9999;
   maxInv[WpnSR1Ammo] = 9999;
   maxInv[WpnMG1Ammo] = 9999;
   maxInv[WpnML1Ammo] = 9999;

   maxInv[Lurker] = 1;
   maxInv[LurkerClip] = 20;

   maxInv[LurkerGrenadeLauncher] = 1;
   maxInv[LurkerGrenadeAmmo] = 20;

   maxInv[Ryder] = 1;
   maxInv[RyderClip] = 10;

   maxInv[ProxMine] = 5;

   maxInv[DeployableTurret] = 5;

   maxInv[WpnBadger] = 1;
   maxInv[WpnBadgerClip] = 8;

   maxInv[WpnRaptor] = 1;
   maxInv[WpnRaptorAmmo] = 120;

   maxInv[WpnBulldog] = 1;
   maxInv[WpnBulldogAmmo] = 4;

   maxInv[WpnSiberion] = 1;
   maxInv[WpnSiberionAmmo] = 120;

   maxInv[WpnPineapple] = 9999;
   
   maxInv[WpnCrackpack] = 1;

   // available skins (see materials.cs in model folder)
   availableSkins =  "base Team1 Team2 DarkBlue	DarkGreen	LightGreen	Orange	Red	Teal	Violet	Yellow";
   useEyePoint = "0";
   maxInvLurkerGrenadeLauncher = "1";
   maxInvRyderClip = "10";
   maxInvWpnRaptorClip = "4";
   maxInvWpnBadger = "1";
   maxInvLurker = "1";
   maxInvProxMine = "5";
   maxInvLurkerGrenadeAmmo = "20";
   maxInvWpnBadgerClip = "8";
   maxInvWpnBulldog = "1";
   maxInvLurkerClip = "20";
   maxInvDeployableTurret = "5";
   maxInvWpnRaptor = "1";
   maxInvRyder = "1";
   maxInvWpnBulldogClip = "4";
   maxInvWpnRaptorAmmo = "120";
   maxInvWpnBulldogAmmo = "4";
   maxInvWpnPineapple = "9999";
   maxInvWpnSiberion = "1";
   maxInvWpnCrackpack = "1";
   maxInvWpnSiberionAmmo = "120";
};

// callback function: called by engine
function FrmStandardcat::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   
   %obj.zDiscTargetSet = new SimSet();

   %obj.allowJumping(false);
   %obj.allowJetJumping(false);
   %obj.allowCrouching(false);
   %obj.allowProne(false);
   %obj.allowSwimming(false);
   %obj.allowSliding(false);
   %obj.allowChargedXJump(false);
   %obj.allowInstantXJump(false);
   %obj.setEnergyLevel(%this.maxEnergy);
	%obj.isCAT = true;
 
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
function FrmStandardcat::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   
   if(isObject(%obj.zDiscTargetSet))
   {
      %obj.zDiscTargetSet.callOnChildren("schedule", 0, "delete");
      %obj.zDiscTargetSet.clear();
      %obj.zDiscTargetSet.delete();
   }
   
   if(isObject(%obj.zLight))
      %obj.zLight.delete();
}

// callback function: called by engine
function FrmStandardcat::onCollision(%this,%obj,%col,%vec,%vecLen)
{
	Parent::onCollision(%this,%obj,%col,%vec,%vecLen);
 
   if(%obj.getDamageState() !$= "Enabled")
      return;
      
   if(isObject(%obj.getObjectMount()))
      return;

   if(%obj.zDontEnterVehicles)
      return;
      
   if(!%col.isMethod("getDataBlock"))
      return;
 
   %data = %col.getDataBlock();
   
   if(%data.numSeats $= "" || %data.numSeats == 0)
      return;
      
	%searchMask = $TypeMasks::TerrainObjectType | $TypeMasks::InteriorObjectType;
	%start = %obj.getPosition();
	%end = VectorAdd(%start, "0 0 -0.1");
	%scanTarg = ContainerRayCast(%start, %end, %searchMask, %obj);
	if(%scanTarg)
      return;

   %node = -1;
   for(%i = 0; %i < %data.numSeats; %i++)
   {
      if(!isObject(%col.getMountedObjectNode(%i)))
      {
         %node = %i;
         break;
      }
   }

   if(%node == -1)
      return;
      
   %data.mountPassenger(%col, %obj, %node);
}

function FrmStandardcat::onTrigger(%this, %obj, %triggerNum, %val)
{
	// This method is invoked when the player receives a trigger
	// move event.  The player automatically triggers slot 0 and
	// slot 1 off of triggers # 0 & 1.  Trigger # 2 is also used
	// as the jump key.
 
   Parent::onTrigger(%this, %obj, %triggerNum, %val);
   
   if(%triggerNum == 3)
   {
      %obj.setImageTrigger(2, %val);
   }
   
   // Distort player view
   %max = "0 -0.25 0.25";
   %mode = "1 1 1";
   %dt = "0.0 0.1 0.1";
   %rnd = "0.05 0.05 0.05";
   //commandToClient(%obj.client, 'EnableChromaticLens', %max, %mode, %dt, %rnd);
 
   if(!%val || %triggerNum != 2)
      return;

	%vehicle = %obj.getObjectMount();
   if(!isObject(%vehicle))
      return;

   // Disable mounting vehicle seats for a short time
   %obj.zDontEnterVehicles = true;
   %obj.schedule(1000, "setFieldValue", "zDontEnterVehicles", false);
    
   %vehicle.unmountObject(%obj);
   %obj.clearControlObject();

   //%pos = VectorAdd(%obj.getPosition(), "0 0 0");
   //%obj.setPosition(%pos);
   %obj.setVelocity("0 0 0");
   
   %vec = %obj.getEyeVector();
   %vec = VectorScale(%vec, 500);
   %vec = setWord(%vec, 2, 250);
   %obj.impulse(%pos, %vec);
}

// callback function: called by engine when player get's mounted
function FrmStandardcat::onMount(%this, %obj, %vehicle, %node)
{
   %vehicle.getDataBlock().updateSSC(%vehicle);
}

// callback function: called by engine when player get's unmounted
function FrmStandardcat::onUnmount(%this, %obj, %vehicle, %node)
{
   %vehicle.getDataBlock().updateSSC(%vehicle);
   if(!isObject(%obj.getMountedImage(0)))
      %obj.useWeapon(1);
}

// Called by engine
function FrmStandardcat::onStartSliding(%this, %obj)
{
   //echo("FrmStandardcat::onStartSliding()");
   
   %obj.zIsSliding = true;
   if(isObject(%obj.etherboard))
      %obj.etherboard.getDataBlock().activate(%obj);
}

// Called by engine
function FrmStandardcat::onStopSliding(%this, %obj)
{
   //echo("FrmStandardcat::onStopSliding()");

   %obj.zIsSliding = false;
   if(isObject(%obj.etherboard))
      %obj.etherboard.getDataBlock().deactivate(%obj);
}

// Called by engine
function FrmStandardcat::onJump(%this, %obj)
{
   //echo("FrmStandardcat::onJump()");
}

// Called by engine
function FrmStandardcat::onXJumpChargeStart(%this, %obj)
{
   //echo("FrmStandardcat::onXJumpChargeStart()");
}

// Called by engine
function FrmStandardcat::onXJump(%this, %obj, %dir)
{
   //echo("FrmStandardcat::onXJump()");
   if(%obj.hasInventory(ItemXJump))
      ItemXJump.onXJump(%obj, %dir);
}

// Called by engine
function FrmStandardcat::onEnterLiquid(%this, %obj, %coverage, %type)
{
   // CATs hate water ;)
   %obj.kill("water");
}

// Called by script
function FrmStandardcat::playSpawnEffects(%this, %obj)
{
   %obj.playAudio(0, FrmStandardcatSpawnSound);
   createExplosion(FrmStandardCatSpawnEffect, %obj.getWorldBoxCenter(), "0 0 1");
}

// Called by script
function FrmStandardcat::clientAction(%this, %obj, %nr)
{
   //echo("FrmStandardcat::clientAction()");
   
   Parent::clientAction(%this, %obj, %nr);
   
   if(%nr == 22)
   {
      %ballast = %obj.ballast;
      if(isObject(%ballast))
         %ballast.getDataBlock().drop(%ballast);
   }

   if(%nr == 1)
      %obj.use(WpnSMG1);
   else if(%nr == 2)
      %obj.use(WpnMGL1);
   else if(%nr == 3)
      %obj.use(WpnSG1);
   else if(%nr == 4)
      %obj.use(WpnMG1);
   else if(%nr == 19)
      %obj.cycleWeapon("next");
}

// Called by ShapeBase script code.
function FrmStandardcat::getBleed(%this, %obj, %dmg, %src)
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

function FrmStandardcat::canMaterialize(%this, %client, %pos, %normal, %transform)
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

function FrmStandardcat::materialize(%this, %client, %pos, %normal, %transform)
{
//	if( %this.team == $Team1 )
		%data = FrmStandardcat;
//	else
//		%data = BlueFrmStandardcat;
	%player = new Player() {
		dataBlock = %data;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%player);

   %player.setTransform(%pos SPC getWords(%transform, 3));

	%player.playAudio(0, CatSpawnSound);
 
   %player.ammo[0] = %this.maxEnergy;
   %player.ammo[1] = %this.maxEnergy;
 
   return %player;
}

function FrmStandardcat::materializeFx(%this, %obj)
{
   FrmCrate::materializeFx(%this, %obj);
}

// Called from script
function FrmStandardcat::dematerialize(%this, %obj)
{
   FrmCrate::dematerialize(%this, %obj);
}

// Called from script
function FrmStandardcat::dematerializeFinish(%this, %obj)
{
   FrmCrate::dematerializeFinish(%this, %obj);
}

function FrmStandardcat::special(%this, %obj, %nr)
{
   return; // mounting & unmounting hoverpods is now done by jumping

   if(%nr != 0)
      return;

	%hoverpod = %obj.getObjectMount();
   if(isObject(%hoverpod))
   {
      if(VectorLen(%hoverpod.getVelocity()) > %hoverpod.getDataBlock().maxMountSpeed)
         return;
      %hoverpod.unmountObject(%obj);
      return;
   }
      
	// if the player is already mounted, re-mount him in the next free seat...
	//if(%player.isMounted())
	//{
	//	%vehicle = %player.getObjectMount();
	//	%player.mountVehicle(%vehicle);
	//	return;
	//}
 
	%selectRange = 4;
	%searchMask = $TypeMasks::PlayerObjectType;
	%pos = %obj.getEyePoint();
	%eye = %obj.getEyeVector();
	%eye = vectorNormalize(%eye);
	%vec = vectorScale(%eye, %selectRange);

	%end = vectorAdd(%vec, %pos);

	%scanTarg = ContainerRayCast(%pos, %end, %searchMask, %obj);

	if(%scanTarg)
	{
		%targetObject = firstWord(%scanTarg);
      //error(%targetObject.getMountedObject(0));
      //error(%targetObject.getDataBlock());
      if(%targetObject.getDataBlock() == FrmHoverpod.getId()
      && !isObject(%targetObject.getMountedObject(0)))
      {
   		//%player.mountVehicle(%targetObject);
         %targetObject.mountObject(%obj, 0);
      }
	}
	else
	{
		//echo("No object found");
	}
}

// Called from script
function FrmStandardcat::onLightEnter(%this, %obj)
{
	%vehicle = %obj.getObjectMount();
   if(isObject(%vehicle))
      %vehicle.getDataBlock().updateSSC(%vehicle);

   %this.onTrigger(%obj, 5, false);
}

// Called from script
function FrmStandardcat::onLightLeft(%this, %obj)
{
	%vehicle = %obj.getObjectMount();
   if(isObject(%vehicle))
      %vehicle.getDataBlock().updateSSC(%vehicle);

   %this.onTrigger(%obj, 5, true);
}

// Called by engine
function FrmStandardcat::onDisabled(%this, %obj, %state)
{
   Parent::onDisabled(%this, %obj, %state);
   
   // Delete all HudInfo objects linked to this object
   while(%obj.zHudInfoSet.getCount() > 0)
      %obj.zHudInfoSet.getObject(0).delete();

   %obj.deactivateStealth();
   %obj.unmountImage(0); // Unmount weapon
   
   // Clear inventory
   %obj.setInventory(ItemDamper, 0);
   %obj.setInventory(ItemVAMP, 0);
   %obj.setInventory(ItemStealth, 0);
   %obj.setInventory(ItemEtherboard, 0);
   %obj.setInventory(ItemImpShield, 0);
   %obj.setInventory(ItemLauncher, 0);
   %obj.setInventory(ItemBounce, 0);
   %obj.setInventory(ItemG1Launcher, 0);
   
   // Unmount any object mounted to us.
   %n = %obj.getMountedObjectCount();
   for(%i = %n-1; %i >= 0; %i--)
      %obj.unmountObject(%obj.getMountedObject(%i));

   %obj.changeSkin("xa_notc_core_shapes_standardcat_erasemat" SPC
      "xa_notc_core_shapes_standardcat_erasemat");
}

// Called from script
function FrmStandardcat::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
{
   Parent::damage(%this, %obj, %sourceObject, %position, %damage, %damageType);
   if(%obj.getDamageState() $= "Disabled")
   {
      %vehicle = %obj.getObjectMount();
      if(isObject(%vehicle))
         %vehicle.unmountObject(%obj);
   }
}

// Called from script
function FrmStandardcat::addDiscTarget(%this, %obj, %target)
{
   if(%target.getDataBlock().ignoreDamage)
      return;

	if(!(%target.getType() & $TypeMasks::ShapeBaseObjectType))
		return;
  
   if(%target == %obj)
      return;
      
   if(%target.getTeamId() == %obj.getTeamId())
      return;

	%count = %obj.zDiscTargetSet.getCount();
	for(%idx= 0; %idx < %count; %idx++)
	{
      %hudInfo = %obj.zDiscTargetSet.getObject(%idx);
      if(%hudInfo.getObject() == %target)
      {
         cancel(%hudInfo.zTimeoutThread);
         %hudInfo.zTimeoutThread = %hudInfo.schedule(3000, "delete");
         return;
      }
   }
   
   %hudInfo = new HudInfo();
   %hudInfo.setObject(%target);
   %hudInfo.setDataSetType(0, $HudInfoDatasetType::DiscTarget);
   %hudInfo.setDataSetBoolField(0, true);
   
   // Ghost HudInfo object to this CAT's client.
   %hudInfo.scopeToClient(%obj.client);
   //%hudInfo.setGhostingListMode("GhostOnly");
   //%hudInfo.addClientToGhostingList(%obj.client);

   %hudInfo.zTimeoutThread = %hudInfo.schedule(3000, "delete");
   %obj.zDiscTargetSet.add(%hudInfo);
   %target.zHudInfoSet.add(%hudInfo);
}

// Called from script
function FrmStandardcat::launchOffensiveDisc(%this, %obj)
{
   %muzzlePoint = %obj.getMuzzlePoint(%slot);
   %muzzleVec = %obj.getMuzzleVector(%slot);
   
   if(%obj.hasInventory(WpnRepelDiscAmmo))
      WpnRepelDisc.launch(%obj, %muzzlePoint, %muzzleVec, %obj.zDiscTargetSet);
   else if(%obj.hasInventory(WpnRazorDiscAmmo))
      WpnRazorDisc.launch(%obj, %muzzlePoint, %muzzleVec, %obj.zDiscTargetSet);
   else if(%obj.hasInventory(WpnExplosiveDiscAmmo))
      WpnExplosiveDisc.launch(%obj, %muzzlePoint, %muzzleVec, %obj.zDiscTargetSet);
}

// Called from script
function FrmStandardcat::selectDiscSlot(%this, %obj, %slot)
{
   echo("FrmStandardcat::selectDiscSlot():" SPC %slot);
}

// Called from script
function FrmStandardcat::fireBounce(%this, %obj)
{
   //echo("FrmStandardcat::fireBounce()");
   if(isObject(%obj.zBounce))
      %obj.zBounce.getDataBlock().fire(%obj.zBounce);
}

// Called from script
function FrmStandardcat::activateStealth(%this, %obj, %time)
{
   //echo("FrmStandardcat::activateStealth()");

   %obj.setCollisionMask($CollisionMask::Stealth);
   %obj.zStealthActive = true;
   
   // Change skin
   // %obj.changeSkin("xa_notc_core_shapes_standardcat_stealthmat1" SPC
   //    "xa_notc_core_shapes_standardcat_stealthmat2");
   
   // Start flickering
   %n = %obj.getMountedObjectCount();
   for(%i = 0; %i < %n; %i++)
   {
      %m = %obj.getMountedObject(%i);
      if(isObject(%m) && %m.isMethod("getDataBlock") && %m.getDataBlock().canStealth)
         %m.setFlickerTime(32);
   }
   %obj.setFlickerTime(32);
   
   %obj.zStealthThread = %obj.schedule(%time, "deactivateStealth");
}

// Called from script
function FrmStandardcat::deactivateStealth(%this, %obj)
{
   //echo("FrmStandardcat::deactivateStealth()");

   cancel(%obj.zStealthThread);
   %obj.zStealthThread = "";

   %obj.setCollisionMask($CollisionMask::Normal);
   %obj.zStealthActive = false;
   
   // Change skin
   // %obj.changeSkin("base" SPC "armor_red0024");
   
   // Stop flickering
   %n = %obj.getMountedObjectCount();
   for(%i = 0; %i < %n; %i++)
   {
      %m = %obj.getMountedObject(%i);
      if(isObject(%m) && %m.isMethod("getDataBlock") && %m.getDataBlock().canStealth)
         %m.setFlickerTime(0);
   }
   %obj.setFlickerTime(0);
}

// Called from script
function FrmStandardcat::isStealthActive(%this, %obj)
{
   return %obj.zStealthActive;
}

// Called from script
function FrmStandardcat::updateImpulseDamperProperties(%this, %obj)
{
   if(%obj.zHasFlag)
      %obj.setRechargeRate(1000, 1);
   else
      %obj.setRechargeRate(%obj.zImpulseDamperRechargeRate, 1);
}

// Called from script
function FrmStandardcat::onFlagTaken(%this, %obj)
{
   %obj.zHasFlag = true;
   %this.updateImpulseDamperProperties(%obj);
}

// Called from script
function FrmStandardcat::onFlagDropped(%this, %obj)
{
   %obj.zHasFlag = false;
   %this.updateImpulseDamperProperties(%obj);
}
