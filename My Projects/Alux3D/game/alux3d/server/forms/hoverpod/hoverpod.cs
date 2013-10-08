//------------------------------------------------------------------------------
// Alux Ethernet Prototype
// Copyright notices are in the file named COPYING.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Placement proxy for controllable form

datablock StaticShapeData(FrmHoverpodProxy)
{
   form = FrmHoverpod; // script field

	shadowEnable = false;
	shapeFile = "share/shapes/alux/hoverpod.dts";
   emap = false;
   hudImageNameFriendly = "~/client/ui/hud/pixmaps/hudfill.png";
   hudImageNameEnemy = "~/client/ui/hud/pixmaps/hudfill.png";

	shapeFxTexture[0] = "share/textures/alux/grid1.png";
	shapeFxTexture[1] = "share/textures/alux/circuit1.png";

	shapeFxColor[0] = "1.0 1.0 1.0 1.0";
	shapeFxColor[1] = "1.0 0.0 0.0 1.0";
	shapeFxColor[2] = "1.0 1.0 0.0 1.0";
	shapeFxColor[3] = "0.0 1.0 0.0 1.0";
};

function FrmHoverpodProxy::adjustTransform(%this, %pos, %normal, %eyeVec)
{
   %pos = VectorAdd(%pos, VectorScale(%normal, 0.5));
   %vec = getWord(%eyeVec,0) SPC getWord(%eyeVec,1) SPC 0;
   %yaw = getWord(getAnglesFromVector(%vec), 0);
   %yaw = (%yaw*180.0)/3.14159265358979323846; // rad to deg
   %yaw = mFloor(%yaw);
   if((%yaw % 90) > 45)
      %yaw += 90;
   else
      %yaw += 0;
   %yaw -= (%yaw % 90);
   %yaw = (%yaw*3.14159265358979323846)/180.0; // deg to rad
   %vec = getVectorFromAngles(%yaw, 0);
   %transform = createOrientFromDir(%vec);
   %transform = setWord(%transform, 0, getWord(%pos, 0));
   %transform = setWord(%transform, 1, getWord(%pos, 1));
   %transform = setWord(%transform, 2, getWord(%pos, 2));
   return %transform;
}

//------------------------------------------------------------------------------
// Controllable form

datablock PlayerData(FrmHoverpod)
{
   proxy = FrmHoverpodProxy; // script field
   btime = 0; // script field: how long form is blocked after materialization
   dtime = 5000; // script field: de-materialization time
   
   // script fields: can soldiers mount this vehicle?
   numSeats = 1;
   //mountable = true;
   //numMountPoints = 1;
   //maxMountSpeed = 10;

   allowColorization = true;

	//className = StandardCat;
	
	//firstPersonOnly = true;
	
	targetLockTimeMS = 200;
	
	//hudImageNameFriendly = "~/client/ui/hud/pixmaps/teammate.cat.png";
	//hudImageNameEnemy = "~/client/ui/hud/pixmaps/enemy.cat.png";

	useEyePoint = true;
	renderFirstPerson = true;
	emap = true;

    eyeOffset = "0 -0.2 -0.02";
    cameraDefaultFov = 110.0;
	cameraMinFov	  = 30.0;
	cameraMaxFov	  = 130.0;
	cameraMinDist = 1;
	cameraMaxDist = 5;

	shapeFile = "share/shapes/alux/hoverpod.dts";
 
	//cloakTexture = "share/shapes/rotc/effects/explosion_white.png";
	shapeFxTexture[0] = "share/textures/alux/light.png";
	shapeFxTexture[1] = "share/textures/alux/grid1.png";
	shapeFxTexture[2] = "share/textures/alux/grid2.png";
	shapeFxTexture[3] = "share/shapes/alux/light.png";
	shapeFxTexture[4] = "share/textures/alux/blocked.png";
	shapeFxColor[0] = "1.0 1.0 1.0 1.0";

	computeCRC = true;

	renderWhenDestroyed = false;
	//debrisShapeName = "share/shapes/rotc/players/standardcat/debris.red.dts";
	//debris = StandardCatDebris;

	aiAvoidThis = true;

	minLookAngle = -1.5;
	maxLookAngle = 1.5;
	minLookAngleMarching = -1.5;
	maxLookAngleMarching = 1.5;
	minLookAngleCrouched = -1.5;
	maxLookAngleCrouched = 1.5;
	minLookAngleProne = -0.8;
	maxLookAngleProne = 0.8;

	maxFreelookAngle = 3.0;

	mass = 180;
	drag = 0.0;
	density = 10;
	gravityMod = 5.0;

	maxDamage = 75;
	damageBuffer = 0;
	maxEnergy = 100;

	repairRate = 0.8;
	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.15;
	energyRechargeRate = 0.4;

	skidSpeed = 20;
	skidFactor = 0.4;

	flyForce = 10 * 90;

	runForce = 300 * 90; // formerly 48 * 90
	runEnergyDrain = 0;
	minRunEnergy = 0;
	
	slideForce = 75 * 90;
	slideEnergyDrain = 0;
	minSlideEnergy = 0;

//	maxForwardSpeed = 100;
//	maxBackwardSpeed = 100;
//	maxSideSpeed = 100;
	maxForwardSpeedSliding = 20;
	maxBackwardSpeedSliding = 20;
	maxSideSpeedSliding = 20;
//	maxForwardSpeedMarching = 8;
//	maxBackwardSpeedMarching = 8;
//	maxSideSpeedMarching = 5;
//	maxForwardSpeedCrouched = 15; NOT USED
//	maxBackwardSpeedCrouched = 12; NOT USED
//	maxSideSpeedCrouched = 10; NOT USED
//	maxForwardSpeedProne = 3; NOT USED
//	maxBackwardSpeedProne = 3; NOT USED
//	maxSideSpeedProne = 2; NOT USED

	maxUnderwaterForwardSpeed = 8.4;
	maxUnderwaterBackwardSpeed = 7.8;
	maxUnderwaterSideSpeed = 7.8;
	// [todo: insert values for other body poses here?]

	jumpForce = 8 * 90;  // 12 * 90
	jumpEnergyDrain = 0;
    reJumpForce = 10 * 90; // script field
    reJumpEnergyDrain = 20; // script field
	minJumpEnergy = 20;
	jumpDelay = 0;
	
	recoverDelay = 9;
	recoverRunForceScale = 1.2;

	minImpactSpeed = 20; //
	speedDamageScale = 5.0; // dynamic field: impact damage multiplier

	boundingBox = "2.0 2.0 1.0";
	pickupRadius = 0.75;

	// Controls over slope of runnable/jumpable surfaces
	maxStepHeight = 1.0;
	maxStepHeightMarching = 1.0;
	maxStepHeightCrouched = 1.0;
	maxStepHeightProne = 0.2;
	runSurfaceAngle  = 40;
	runSurfaceAngleMarching  = 40;
	runSurfaceAngleCrouched  = 40;
	runSurfaceAngleProne  = 50;

	jumpSurfaceAngle = 30;

	minJumpSpeed = 20;
	maxJumpSpeed = 30;

	horizMaxSpeed = 200;
	horizResistSpeed = 30;
	horizResistFactor = 0.35;

	upMaxSpeed = 65;
	upResistSpeed = 25;
	upResistFactor = 0.3;

	footstepSplashHeight = 0.35;

	// Damage location details
	//boxNormalHeadPercentage		 = 0.83;
	//boxNormalTorsoPercentage		= 0.49;
	//boxHeadLeftPercentage			= 0;
	//boxHeadRightPercentage		  = 1;
	//boxHeadBackPercentage			= 0;
	//boxHeadFrontPercentage		  = 1;

	// footprints
	//decalData	= RedStandardCatFootprint;
	//decalOffset = 0.25;

	// foot puffs
	//footPuffEmitter = StandardCatLightPuffEmitter;
	//footPuffNumParts = 10;
	//footPuffRadius = 0.25;
	
	// ground connection beam
	//groundConnectionBeam = StandardCatGroundConnectionBeam;

	// slide emitters
	//slideContactParticleFootEmitter = RedSlideEmitter;
	slideContactParticleTrailEmitter[0] = FrmHoverpodSlideContactTrailEmitter;
	//slideParticleFootEmitter = RedCatSlideFootEmitter;
	//slideParticleTrailEmitter[0] = BlueSlideEmitter;
	//skidParticleFootEmitter = CatSkidFootEmitter;
	//skidParticleTrailEmitter[0] = CatSkidTrailEmitter0;
	//skidParticleTrailEmitter[1] = CatSkidTrailEmitter1;
	
	// damage info eyecandy...
	//damageBufferParticleEmitter = RedCatDamageBufferEmitter;
	//repairParticleEmitter = RedCatRepairEmitter;
	//bufferRepairParticleEmitter = RedCatBufferRepairEmitter;
	//damageParticleEmitter = RedCatDamageEmitter;
	//bufferDamageParticleEmitter = RedCatBufferDamageEmitter;	
	//damageDebris = RedCatDamageDebris;
	//bufferDamageDebris = CatBufferDamageDebris;

	// not implemented in engine...
	// dustEmitter = StandardCatLiftoffDustEmitter;

	//splash = StandardCatSplash;
	//splashVelocity = 4.0;
	//splashAngle = 67.0;
	//splashFreqMod = 300.0;
	//splashVelEpsilon = 0.60;
	//bubbleEmitTime = 0.4;
	//splashEmitter[0] = StandardCatFoamDropletsEmitter;
	//splashEmitter[1] = StandardCatFoamEmitter;
	//splashEmitter[2] = StandardCatBubbleEmitter;
	//mediumSplashSoundVelocity = 10.0;
	//hardSplashSoundVelocity = 20.0;
	//exitSplashSoundVelocity = 5.0;

	//NOTE:  some sounds commented out until wav's are available

	// Footstep Sounds
	//LeftFootSoftSound		= StandardCatLeftFootSoftSound;
	//LeftFootHardSound		= StandardCatLeftFootHardSound;
	//LeftFootMetalSound	  = StandardCatLeftFootMetalSound;
	//LeftFootSnowSound		= StandardCatLeftFootSnowSound;
	//LeftFootShallowSound	= StandardCatLeftFootShallowSplashSound;
	//LeftFootWadingSound	 = StandardCatLeftFootWadingSound;
	//RightFootSoftSound	  = StandardCatRightFootSoftSound;
	//RightFootHardSound	  = StandardCatRightFootHardSound;
	//RightFootMetalSound	 = StandardCatRightFootMetalSound;
	//RightFootSnowSound	  = StandardCatRightFootSnowSound;
	//RightFootShallowSound  = StandardCatRightFootShallowSplashSound;
	//RightFootWadingSound	= StandardCatRightFootWadingSound;
	//FootUnderwaterSound	 = StandardCatFootUnderwaterSound;
	//FootBubblesSound	  = FootBubblesSound;
	//movingBubblesSound	= ArmorMoveBubblesSound;
	//waterBreathSound	  = WaterBreathMaleSound;

	//impactSoftSound		= StandardCatImpactSoftSound;
	//impactHardSound		= StandardCatImpactHardSound;
	//impactMetalSound	  = StandardCatImpactMetalSound;
	//impactSnowSound		= StandardCatImpactSnowSound;

	//impactWaterEasy		= ImpactLightWaterEasySound;
	//impactWaterMedium	 = ImpactLightWaterMediumSound;
	//impactWaterHard		= ImpactLightWaterHardSound;

	//groundImpactMinSpeed	 = 10.0;
	//groundImpactShakeFreq	= "4.0 4.0 4.0";
	//groundImpactShakeAmp	 = "1.0 1.0 1.0";
	//groundImpactShakeDuration = 0.8;
	//groundImpactShakeFalloff = 10.0;

	//exitingWater			= ExitingWaterLightSound;
	slideSound = FrmHoverpodSlideSound;
	slideContactSound = FrmHoverpodSlideContactSound;
	//skidSound = PlayerSkidSound;

	observeParameters = "0.5 4.5 4.5";
};

function FrmHoverpod::onAdd(%this, %obj)
{
	//error("FrmHoverpod::onAdd()");

	Parent::onAdd(%this, %obj);
 	%obj.setBodyPose($PlayerBodyPose::Sliding);

	//%obj.startFade(0, 0, true);
	//%obj.shapeFxSetActive(0, true, true);
	//%obj.shapeFxSetActive(1, true, true);
}

// *** Callback function: called by engine
function FrmHoverpod::onTrigger(%this, %obj, %triggerNum, %val)
{
   return FrmCrate::onTrigger(%this, %obj, %triggerNum, %val);
}

// *** Callback function:
// Invoked by ShapeBase code whenever the object's damage level changes
function FrmHoverpod::onDamage(%this, %obj, %delta)
{
	%totalDamage = %obj.getDamageLevel();
	if(%totalDamage >= %this.maxDamage)
	{
      %obj.client.leaveForm(%obj);
      %obj.client.onFormDestroyed(%obj);
      createExplosion(FrmCrateExplosion, %obj.getPosition(), "0 0 1");
      %obj.schedule(0, "delete");
	}
}

// Called from script
function FrmHoverpod::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
{
   if(%obj.getDamageState() $= "Destroyed")
      return;
   Parent::damage(%this, %obj, %sourceObject, %position, %damage, %damageType);
   return;

	%rider = %obj.getMountedObject(0);
	if(!isObject(%rider))
		return;

	if(%damageType $= "LeftMissionArea")
		%rider.damage(%sourceObject, %pos, %damage, %damageType);
}

function FrmHoverpod::canMaterialize(%this, %client, %pos, %normal, %transform)
{
	%ownTeamId = %client.player.getTeamId();

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

function FrmHoverpod::materialize(%this, %client, %pos, %normal, %transform)
{
	%player = new Player() {
		dataBlock = FrmHoverpod;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%player);
   
	//%player.playAudio(0, CatSpawnSound);
   return %player;
}

function FrmHoverpod::materializeFx(%this, %obj)
{
   FrmCrate::materializeFx(%this, %obj);
}

// Called from script
function FrmHoverpod::dematerialize(%this, %obj)
{
   FrmCrate::dematerialize(%this, %obj);
}

// Called from script
function FrmHoverpod::dematerializeFinish(%this, %obj)
{
   FrmCrate::dematerializeFinish(%this, %obj);
}

// Called from script
function FrmHoverpod::updateSSC(%this, %obj)
{
   %soldier = %obj.getMountedObject(0);
   if(isObject(%soldier) && isObject(%soldier.getControllingClient()))
   {
      %obj.ssc = new HoverPodController() {
         client = %soldier.client;
      };
      MissionCleanup.add(%obj.ssc);
   	%obj.useServerSideController(%obj.ssc);
   }
   else
   {
      if(isObject(%obj.ssc))
      {
         %obj.ssc.delete();
         %obj.ssc = "";
      }
   }
}

// Called from script
function FrmHoverpod::mountPassenger(%this, %obj, %passenger, %seat)
{
   %pos = %obj.getPosition();
   %transform = %pos SPC "0 0 1 0";
   %obj.setTransform(%transform);
   %obj.mountObject(%passenger, 0);
}

