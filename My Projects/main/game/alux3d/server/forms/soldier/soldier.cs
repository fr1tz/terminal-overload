// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(FrmSoldierProxy : FrmCrateProxy)
{
   form = FrmSoldier; // script field
	shapeFile = "share/shapes/alux/soldier.dts";
};

function FrmSoldierProxy::adjustTransform(%this, %pos, %normal, %eyeVec)
{
   %pos = VectorAdd(%pos, VectorScale(%normal, 0.25));
   %vec = getWord(%eyeVec,0) SPC getWord(%eyeVec,1) SPC 0;
   %transform = createOrientFromDir(%vec);
   %transform = setWord(%transform, 0, getWord(%pos, 0));
   %transform = setWord(%transform, 1, getWord(%pos, 1));
   %transform = setWord(%transform, 2, getWord(%pos, 2));
   return %transform;
}

//------------------------------------------------------------------------------

datablock PlayerData(FrmSoldier)
{
   proxy = FrmSoldierProxy; // script field
   spore = FrmSoldierSpore; // script field
   btime = 2000; // script field: how long form is blocked after materialization
   dtime = 5000; // script field: de-materialization time

   allowColorization = true;

   renderFirstPerson = false;

   computeCRC = false;

   // Third person shape
   shapeFile = "content/torque3d/3.0/shapes/actors/Soldier/soldier_rigged.DAE";
   cameraMaxDist = 3;
   allowImageStateAnimation = true;

   // First person arms
   imageAnimPrefixFP = "soldier";
   //shapeNameFP[0] = "content/torque3d/3.0/shapes/actors/Soldier/FP/FP_SoldierArms.DAE";

   canObserve = 1;
   cmdCategory = "Clients";

   cameraDefaultFov = "80";
   cameraMinFov = "80";
   cameraMaxFov = "180";

   debrisShapeName = "content/torque3d/3.0/shapes/actors/common/debris_player.dts";
   debris = PlayerDebris;

   throwForce = 30;

   minLookAngle = "-1.5";
   maxLookAngle = "1.5";
   maxFreelookAngle = 3.0;

   mass = 90;
   drag = 0.0;
   maxdrag = 0.0;
   density = 1.1;
   maxDamage = 100;
   maxEnergy =  60;
   repairRate = 0.33;
   energyPerDamagePoint = 75;

   rechargeRate = 0.256;

   runForce = 50 * 90;
   runEnergyDrain = 0;
   minRunEnergy = 0;
   maxForwardSpeed = 5;
   maxBackwardSpeed = 3;
   maxSideSpeed = 3;

   sprintForce = 50 * 90;
   sprintEnergyDrain = 0;
   minSprintEnergy = 0;
   maxSprintForwardSpeed = 8;
   maxSprintBackwardSpeed = 6;
   maxSprintSideSpeed = 6;
   sprintStrafeScale = 1.0;
   sprintYawScale = "1.0";
   sprintPitchScale = "1.0";
   sprintCanJump = true;

   crouchForce = 50 * 90;
   maxCrouchForwardSpeed = 3.0;
   maxCrouchBackwardSpeed = 1.0;
   maxCrouchSideSpeed = 1.0;

   maxUnderwaterForwardSpeed = 8.4;
   maxUnderwaterBackwardSpeed = 7.8;
   maxUnderwaterSideSpeed = 4.0;

   jumpForce =  8 * 90;
   jumpEnergyDrain = 0;
   minJumpEnergy = 0;
   jumpDelay = "15";
   airControl = 0.0;

   fallingSpeedThreshold = -6.0;

   landSequenceTime = 0.33;
   transitionToLand = false;
   recoverDelay = 0;
   recoverRunForceScale = 0;

   minImpactSpeed = 10;
   minLateralImpactSpeed = 20;
   speedDamageScale = 0.4;

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
   decalOffset = 0.25;

   footPuffEmitter = "LightPuffEmitter";
   footPuffNumParts = 10;
   footPuffRadius = "0.25";

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

   // Controls over slope of runnable/jumpable surfaces
   runSurfaceAngle  = "25";
   jumpSurfaceAngle = 80;
   maxStepHeight = 0.35;  //two meters
   minJumpSpeed = 20;
   maxJumpSpeed = 30;

   horizMaxSpeed = 68;
   horizResistSpeed = 33;
   horizResistFactor = 0.35;

   upMaxSpeed = 80;
   upResistSpeed = 25;
   upResistFactor = 0.3;

   footstepSplashHeight = 0.35;

   //NOTE:  some sounds commented out until wav's are available

   // Footstep Sounds
   FootSoftSound        = FootLightSoftSound;
   FootHardSound        = FootLightHardSound;
   FootMetalSound       = FootLightMetalSound;
   FootSnowSound        = FootLightSnowSound;
   FootShallowSound     = FootLightShallowSplashSound;
   FootWadingSound      = FootLightWadingSound;
   FootUnderwaterSound  = FootLightUnderwaterSound;

   //FootBubblesSound     = FootLightBubblesSound;
   //movingBubblesSound   = ArmorMoveBubblesSound;
   //waterBreathSound     = WaterBreathMaleSound;

   //impactSoftSound      = ImpactLightSoftSound;
   //impactHardSound      = ImpactLightHardSound;
   //impactMetalSound     = ImpactLightMetalSound;
   //impactSnowSound      = ImpactLightSnowSound;

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
   DecalData = "PlayerFootprint";

   // Allowable Inventory Items
   mainWeapon = WpnRaptor;

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
};

// *** callback function: called by engine
function FrmSoldier::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   
   %obj.playAudio(0, SoldierSpawnGaspSound);
   
   %obj.setEnergyLevel(%this.maxEnergy);
   
	%obj.isCAT = true;
	%obj.getTeamObject().numCATs++;
}

// callback function: called by engine
function FrmSoldier::onCollision(%this,%obj,%col,%vec,%vecLen)
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

function FrmSoldier::onTrigger(%this, %obj, %triggerNum, %val)
{
	// This method is invoked when the player receives a trigger
	// move event.  The player automatically triggers slot 0 and
	// slot 1 off of triggers # 0 & 1.  Trigger # 2 is also used
	// as the jump key.
 
   Parent::onTrigger(%this, %obj, %triggerNum, %val);
   
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
function FrmSoldier::onMount(%this, %obj, %vehicle, %node)
{
   %vehicle.getDataBlock().updateSSC(%vehicle);
}

// callback function: called by engine when player get's unmounted
function FrmSoldier::onUnmount(%this, %obj, %vehicle, %node)
{
   %vehicle.getDataBlock().updateSSC(%vehicle);
   if(!isObject(%obj.getMountedImage(0)))
      %obj.useWeapon(1);
}

// Called by script
function FrmSoldier::clientAction(%this, %obj, %nr)
{
   Parent::clientAction(%this, %obj, %nr);

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

function FrmSoldier::canMaterialize(%this, %client, %pos, %normal, %transform)
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

function FrmSoldier::materialize(%this, %client, %pos, %normal, %transform)
{
//	if( %this.team == $Team1 )
		%data = FrmSoldier;
//	else
//		%data = BlueFrmSoldier;
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

function FrmSoldier::materializeFx(%this, %obj)
{
   FrmCrate::materializeFx(%this, %obj);
}

// Called from script
function FrmSoldier::dematerialize(%this, %obj)
{
   FrmCrate::dematerialize(%this, %obj);
}

// Called from script
function FrmSoldier::dematerializeFinish(%this, %obj)
{
   FrmCrate::dematerializeFinish(%this, %obj);
}

function FrmSoldier::special(%this, %obj, %nr)
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
function FrmSoldier::onLightEnter(%this, %obj)
{
	%vehicle = %obj.getObjectMount();
   if(isObject(%vehicle))
      %vehicle.getDataBlock().updateSSC(%vehicle);

   %this.onTrigger(%obj, 5, false);
}

// Called from script
function FrmSoldier::onLightLeft(%this, %obj)
{
	%vehicle = %obj.getObjectMount();
   if(isObject(%vehicle))
      %vehicle.getDataBlock().updateSSC(%vehicle);

   %this.onTrigger(%obj, 5, true);
}

// Called from script
function FrmSoldier::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
{
   Parent::damage(%this, %obj, %sourceObject, %position, %damage, %damageType);
   if(%obj.getDamageState() $= "Disabled")
   {
      %vehicle = %obj.getObjectMount();
      if(isObject(%vehicle))
         %vehicle.unmountObject(%obj);
   }
}

