//------------------------------------------------------------------------------
// Alux Ethernet Prototype
// Copyright notices are in the file named COPYING.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Placement proxy for controllable form

datablock StaticShapeData(FrmHovercycleProxy)
{
   form = FrmHovercycle; // script field

	shadowEnable = false;
	shapeFile = "share/shapes/alux/hovercycle.dts";
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

function FrmHovercycleProxy::adjustTransform(%this, %pos, %normal, %eyeVec)
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

datablock HoverVehicleData(FrmHovercycle)
{
   proxy = FrmHovercycleProxy; // script field
   btime = 0; // script field: how long form is blocked after materialization
   dtime = 5000; // script field: de-materialization time

   // script fields: can soldiers mount this vehicle?
   numSeats = 1;
   //mountable = true;
   //numMountPoints = 1;
   //maxMountSpeed = 10;

   allowColorization = true;

	// *** ShapeBase ***

	//isInvincible = true;

	// 3rd person camera
	 cameraMaxDist = 5;

	// Rigid body
	mass = 1*100;
	drag = 0.0;
	density = 1;

	// Rendering
	shapeFile = "share/shapes/alux/hovercycle.dts";
	computeCRC = true;
	//debrisShapeName = "share/shapes/rotc/misc/debris1.white.dts";
	//debris = ShapeDebris;
	renderWhenDestroyed = false;
	emap = true;
 
	shapeFxTexture[0] = "share/textures/alux/light.png";
	shapeFxTexture[1] = "share/textures/alux/grid1.png";
	shapeFxTexture[2] = "share/textures/alux/grid2.png";
	shapeFxTexture[3] = "share/shapes/alux/light.png";
	shapeFxTexture[4] = "share/textures/alux/blocked.png";
	shapeFxColor[0] = "1.0 1.0 1.0 1.0";

	// *** Vehicle ***

	// 3rd person camera
	cameraRoll = true;         // Roll the camera with the vehicle
	cameraOffset = 2.0;        // Vertical offset from camera mount point
	cameraLag = 0.05;           // Velocity lag of camera
	cameraDecay = 0.75;        // Decay per sec. rate of velocity lag

	// Rigid body
	bodyFriction = 0.5;
	bodyRestitution = 0.2;
	// Physics system
	integration = 4;           // # of physics steps per tick
	collisionTol = 0.1;        // Collision distance tolerance
	contactTol = 0.1;          // Contact velocity tolerance

	// Drag
	minDrag = 60; // Linear Drag (eventually slows you down when not thrusting...constant drag)

	// *** HoverVehicle ***

	// Drag
	gyroDrag = 0.4*100;
	dragForce = 4.0*100;
	vertFactor = 0.1; // factor for vertical velocity drag

	normalForce = 30.0*100;
	restorativeForce = 10.0*100;

	mainThrustForce = 200.0*100;
	reverseThrustForce = 20.0*100;
	strafeThrustForce = 20.0*100;
	floatingGravMag = 10; // factor applied to gravity when floating
	floatingThrustFactor = 0.25; // factor applied to thrust force when floating
	turboFactor = 1.0; // factor applied to thrust force when jetting
	steeringForce = 50.0*100;
	rollForce = 15.0*100;
	pitchForce = 0.0*100;

	// braking force  is applied only when not thrusting
	// and the speed is less than brakingActivationSpeed
	brakingForce = 6.0*100;
	brakingActivationSpeed = 1;

	// Stabilizer "spring"
	stabLenMin = 2;
	stabLenMax = 3;
	stabSpringConstant = 20.0*100;
	stabDampingConstant = 20.0*100;

	//damageEmitter[0] = AssaultTankEmitter;
	//damageEmitter[1] = AssaultTankEmitter;
	//damageEmitter[2] = AssaultTankEmitter;
	//damageEmitterOffset[0] = "0.0 -1.5 0.5 ";
	//damageLevelTolerance[0] = 0.3;
	//damageLevelTolerance[1] = 0.7;
	//numDmgEmitterAreas = 2;

	maxDamage = 120;
	destroyedLevel = 120;

	rechargeRate = 0.7;
	maxEnergy = 150;
	minJetEnergy = 15;
	jetEnergyDrain = 1.3;

	// Rigid Body

	softImpactSpeed = 20; // Play SoftImpact Sound
	hardImpactSpeed = 28; // Play HardImpact Sound

	// Ground Impact Damage (uses DamageType::Ground)
	minImpactSpeed = 29;
	speedDamageScale = 0.010;

	// Object Impact Damage (uses DamageType::Impact)
	collDamageThresholdVel = 23;
	collDamageMultiplier = 0.030;

   // Dust emitter
	dustHeight = 1.0;
	triggerDustHeight = 2.5;
	//dustEmitter = FrmHovercycleDustEmitter;
 
   // Dust trail emitter
	triggerTrailHeight = 2.5;
	dustTrailFreqMod = 15.0;
 	dustTrailOffset = "0.0 0.0 0.0";
	//dustTrailEmitter = FrmHovercycleDustEmitter;
 
   damageParticleEmitter = FrmCrate_DamageEmitter;
 
	laserTrail[0] = FrmHovercycleLaserTrail;
	laserTrail[1] = FrmHovercycleLaserTrail;

	//jetSound = ScoutSqueelSound;
	engineSound = FrmHovercycleEngineSound;
	//floatSound = ScoutThrustSound;
	//softImpactSound = GravSoftImpactSound;
	//hardImpactSound = HardImpactSound;
	//wheelImpactSound = WheelImpactSound;

	//
	softSplashSoundVelocity = 10.0;
	mediumSplashSoundVelocity = 20.0;
	hardSplashSoundVelocity = 30.0;
	exitSplashSoundVelocity = 10.0;

	//exitingWater = VehicleExitWaterSoftSound;
	//impactWaterEasy = VehicleImpactWaterSoftSound;
	//impactWaterMedium = VehicleImpactWaterSoftSound;
	//impactWaterHard = VehicleImpactWaterMediumSound;
	//waterWakeSound = VehicleWakeSoftSplashSound;
};

function FrmHovercycle::onAdd(%this, %obj)
{
	//error("FrmHovercycle::onAdd()");

	Parent::onAdd(%this, %obj);
 	%obj.setBodyPose($PlayerBodyPose::Sliding);

	//%obj.startFade(0, 0, true);
	//%obj.shapeFxSetActive(0, true, true);
	//%obj.shapeFxSetActive(1, true, true);
}

// *** Callback function: called by engine
function FrmHovercycle::onTrigger(%this, %obj, %triggerNum, %val)
{
   return FrmCrate::onTrigger(%this, %obj, %triggerNum, %val);
}

// *** Callback function:
// Invoked by ShapeBase code whenever the object's damage level changes
function FrmHovercycle::onDamage(%this, %obj, %delta)
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
function FrmHovercycle::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
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

function FrmHovercycle::canMaterialize(%this, %client, %pos, %normal, %transform)
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

function FrmHovercycle::materialize(%this, %client, %pos, %normal, %transform)
{
	%player = new HoverVehicle() {
		dataBlock = FrmHovercycle;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%player);
   
	//%player.playAudio(0, CatSpawnSound);
   return %player;
}

function FrmHovercycle::materializeFx(%this, %obj)
{
   FrmCrate::materializeFx(%this, %obj);
}

// Called from script
function FrmHovercycle::dematerialize(%this, %obj)
{
   FrmCrate::dematerialize(%this, %obj);
}

// Called from script
function FrmHovercycle::dematerializeFinish(%this, %obj)
{
   FrmCrate::dematerializeFinish(%this, %obj);
}

// Called from script
function FrmHovercycle::updateSSC(%this, %obj)
{

}

// Called from script
function FrmHovercycle::mountPassenger(%this, %obj, %passenger, %seat)
{
   %obj.mountObject(%passenger, 0);
   %passenger.setControlObject(%obj);
   %passenger.setTransform("0 0 0 0 0 1 0");
   %passenger.setActionThread("scoutroot");
   %passenger.setArmThread("scoutroot");
   %passenger.unmountImage(0);
}
