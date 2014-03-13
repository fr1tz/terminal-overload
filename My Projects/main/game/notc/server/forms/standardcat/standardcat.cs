// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

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
   //shapeNameFP[0] = "content/xa/torque3d/3.0/shapes/actors/Soldier/FP/FP_SoldierArms.DAE";

   canObserve = 1;
   cmdCategory = "Clients";

   cameraDefaultFov = "80";
   cameraMinFov = "80";
   cameraMaxFov = "180";

   debrisShapeName = "content/xa/torque3d/3.0/shapes/actors/common/debris_player.dts";
   debris = PlayerDebris;

   throwForce = 30;

   minLookAngle = "-1.5";
   maxLookAngle = "1.5";
   maxFreelookAngle = 3.0;

   mass = 90;
   drag = 0.0;
   maxdrag = 0;
   density = 10;
   maxDamage = 150;
   maxEnergy =  100;
   damageBuffer = 50;
   energyPerDamagePoint = 75;

	repairRate = 0.8;
	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.15;
	rechargeRate = 0.4;

   runForce = 9000*2;
   runEnergyDrain = 0;
   minRunEnergy = 0;
   maxForwardSpeed = 8;
   maxBackwardSpeed = 8;
   maxSideSpeed = 5;
   
	slideForce = 20 * 90 *2;
	slideEnergyDrain = 0;
	minSlideEnergy = 0;
	maxSlideForwardSpeed = 30;
	maxSlideBackwardSpeed = 25;
	maxSlideSideSpeed = 12;

   sprintForce = 9000*2;
   sprintEnergyDrain = 0;
   minSprintEnergy = 0;
   maxSprintForwardSpeed = 15;
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

   maxUnderwaterForwardSpeed = 8.4;
   maxUnderwaterBackwardSpeed = 7.8;
   maxUnderwaterSideSpeed = 4.0;

   jumpForce = 24 * 90;
   jumpEnergyDrain = 0;
   minJumpEnergy = 0;
   jumpDelay = 0;

	skidSpeed = 20;
	skidFactor = 0.4;
   
   glideForce = 10 * 90 * 2;
   airControl = 0.0;

   fallingSpeedThreshold = -6.0;

   landSequenceTime = 0.33;
   transitionToLand = false;
   recoverDelay = 9;
   recoverRunForceScale = 1.2;

   minImpactSpeed = 30;
   minLateralImpactSpeed = 30;
   speedDamageScale = 1;

   boundingBox = "0.65 0.75 1.85";
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
   jumpSurfaceAngle = 30;
   maxStepHeight = 1.0;  //two meters
   minJumpSpeed = 20;
   maxJumpSpeed = 30;

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

   maxInv[ItemBallast] = 1;
   maxInv[ItemEtherboard] = 1;

   maxInv[WpnSMG1] = 1;
   maxInv[WpnMGL1] = 1;
   maxInv[WpnSG1] = 1;
   maxInv[WpnSR1] = 1;
   maxInv[WpnMG1] = 1;
   maxInv[WpnML1] = 1;

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

   %obj.allowJetJumping(false);
   %obj.allowCrouching(false);
   %obj.allowProne(false);
   %obj.allowSwimming(false);
   %obj.allowSliding(false);
   %obj.playAudio(0, SoldierSpawnGaspSound);
   %obj.setEnergyLevel(%this.maxEnergy);
	%obj.isCAT = true;
	%obj.getTeamObject().numCATs++;
}

// callback function: called by engine
function FrmStandardcat::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
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
   
   // Distort player view
   %max = "0 -0.25 0.25";
   %mode = "1 1 1";
   %dt = "0.0 0.1 0.1";
   %rnd = "0.05 0.05 0.05";
   //commandToClient(%obj.client, 'EnableChromaticLens', %max, %mode, %dt, %rnd);
   
   
   if(%triggerNum == 5)
   {
      if(%val)
         %obj.zBalastLimit = 0.02;
      else
         %obj.zBalastLimit = 1.0;
   }
 
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
   
   if(isObject(%obj.etherboard))
      %obj.etherboard.getDataBlock().activate(%obj);
}

// Called by engine
function FrmStandardcat::onStopSliding(%this, %obj)
{
   //echo("FrmStandardcat::onStopSliding()");
   
   if(isObject(%obj.etherboard))
      %obj.etherboard.getDataBlock().deactivate(%obj);
}

// Called by engine
function FrmStandardcat::onJump(%this, %obj)
{
   //echo("FrmStandardcat::onJump()");
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
      %obj.use(WpnBadger);
   else if(%nr == 2)
      %obj.use(WpnRaptor);
   else if(%nr == 3)
      %obj.use(WpnBulldog);
   else if(%nr == 4)
      %obj.use(WpnSiberion);
   else if(%nr == 5)
      %obj.use(WpnCrackpack);
   else if(%nr == 21)
      %obj.reloadWeapon();
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

