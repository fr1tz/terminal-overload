// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
// Controllable form

datablock FlyingVehicleData(FrmSoldierpod)
{
   dtime = 5000; // script field: de-materialization time

   allowColorization = true;

   // @name dynamic fields, needed for certain in-script checks -mag
   // @{
   isAircraft = true;
   class = "soldierpod";
   // @}

//   category = "Vehicles"; don't appear in mission editor
   shapeFile = "content/fr1tz/alux1/shapes/soldier/fdv/p1/shape.dae";
   emap = true;

	//hudImageNameFriendly = "~/client/ui/hud/pixmaps/teammate.cat.png";
	//hudImageNameEnemy = "~/client/ui/hud/pixmaps/enemy.cat.png";
   
   renderWhenDestroyed = false;
   //explosion = ScoutDroneExplosion;
   //defunctEffect = ScoutDroneDefunctEffect;
   //debris = BomberDebris;
   //debrisShapeName = "~/data/vehicles/bomber/vehicle.dts";

	//cloakTexture = "share/shapes/rotc/effects/explosion_white.png";
	shapeFxTexture[0] = "share/textures/alux/light.png";
	shapeFxTexture[1] = "share/textures/alux/grid1.png";
	shapeFxTexture[2] = "share/textures/alux/grid2.png";
	shapeFxTexture[3] = "share/shapes/alux/light.png";
	shapeFxTexture[4] = "share/textures/alux/blocked.png";
	shapeFxColor[0] = "1.0 1.0 1.0 1.0";

   drag    = 0.15;
   density = 1.0;

   // 3rd person camera settings...
   cameraRoll = true;         // Roll the camera with the vehicle
   cameraMaxDist = 5;         // Far distance from vehicle
   cameraOffset = 0.0;        // Vertical offset from camera mount point
   cameraLag = 0.05;           // Velocity lag of camera
   cameraDecay = 0.75;        // Decay per sec. rate of velocity lag
   
	maxDamage = 50;
	damageBuffer = 0;
	maxEnergy = 100; // Afterburner and any energy weapon pool

   energyRechargeRate = 0.4;

   // drag...
   minDrag = 120;           // Linear Drag (eventually slows you down when not thrusting...constant drag)
   rotationalDrag = 10;         // Angular Drag (dampens the drift after you stop moving the mouse...also tumble drag)

   // autostabilizer...
   maxAutoSpeed = 0;            // Autostabilizer kicks in when less than this speed. (meters/second)
   autoAngularForce = 200;  // Angular stabilizer force (this force levels you out when autostabilizer kicks in)
   autoLinearForce = 500;   // Linear stabilzer force (this slows you down when autostabilizer kicks in)
   autoInputDamping = 1.00; // Dampen control input so you don't` whack out at very slow speeds

   // maneuvering...
   maxSteeringAngle = 3;          // Max radiens you can rotate the wheel. Smaller number is more maneuverable.
   horizontalSurfaceForce = 16;   // Horizontal center "wing" (provides "bite" into the wind for climbing/diving and turning)
   verticalSurfaceForce = 2;      // Vertical center "wing" (controls side slip. lower numbers make MORE slide.)
   maneuveringForce = 6000;  // Horizontal jets (W,S,D,A key thrust)
   steeringForce = 500/4;      // Steering jets (force applied when you move the mouse)
   steeringRollForce = 750/4; // Steering jets (how much you heel over when you turn)
   rollForce = 0;                 // Auto-roll (self-correction to right you after you roll/invert)
   hoverHeight = 3;               // Height off the ground at rest
   createHoverHeight = 3;         // Height off the ground when created

   // turbo jet...
   jetForce = 0;              // Afterburner thrust (this is in addition to normal thrust)
   minJetEnergy = 0;             // Afterburner can't be used if below this threshhold.
   jetEnergyDrain = 0.0;         // Energy use of the afterburners (low number is less drain...can be fractional)                                                                                                                                                                                                                                                                                          // Auto stabilize speed
   vertThrustMultiple = 2.0;

   // Rigid body
   mass = 20;
   massCenter = "0 0 0";   // Center of mass for rigid body
   massBox = "0 0 0";      // Size of box used for moment of inertia, \
                           // if zero it defaults to object bounding box
   bodyFriction = 0.0;     // Don't mess with this.
   bodyRestitution = 0.1;  // When you hit the ground, how much you rebound. (between 0 and 1)
   minRollSpeed = 0;       // Don't mess with this.
   softImpactSpeed = 14;   // Sound hooks. This is the soft hit.
   hardImpactSpeed = 25;   // Sound hooks. This is the hard hit.
   
   // physics system...
   integration = 4;           // # of physics steps per tick
   collisionTol = 0.25;        // Collision distance tolerance
   contactTol = 0.25;          // Contact velocity tolerance

   // impact damage...
   minImpactSpeed = 1;      // If hit ground at speed above this then it's an impact. Meters/second
   speedDamageScale = 100.0;   // Dynamic field: impact damage multiplier

   // contrail...
   minTrailSpeed = 0;      // The speed your contrail shows up at
   trailEmitter = FrmSoldierpod_ContrailEmitter;
   
   // laser trail...
   laserTrail = FrmSoldierpod_LaserTrail;
   
   // various emitters...
   //forwardJetEmitter = ScoutDroneJetEmitter;
   //downJetEmitter = ScoutDroneJetEmitter;

   //
//   jetSound = Team1ScoutScoutDroneThrustSound;
   engineSound = FrmSoldierpodEngineSound;
//   softImpactSound = SoftImpactSound;
//   hardImpactSound = HardImpactSound;
   //wheelImpactSound = WheelImpactSound;

   //
   softSplashSoundVelocity = 10.0;
   mediumSplashSoundVelocity = 15.0;
   hardSplashSoundVelocity = 20.0;
   exitSplashSoundVelocity = 10.0;

//   exitingWater      = VehicleExitWaterMediumSound;
//   impactWaterEasy   = VehicleImpactWaterSoftSound;
//   impactWaterMedium = VehicleImpactWaterMediumSound;
//   impactWaterHard   = VehicleImpactWaterMediumSound;
//   waterWakeSound    = VehicleWakeMediumSplashSound;

//   dustEmitter = VehicleLiftoffDustEmitter;
   triggerDustHeight = 4.0;
   dustHeight = 1.0;

//   damageEmitter[0] = LightDamageSmoke;
//   damageEmitter[1] = HeavyDamageSmoke;
//   damageEmitter[2] = DamageBubbles;
   damageEmitterOffset[0] = "0.0 -3.0 0.0 ";
   damageLevelTolerance[0] = 0.3;
   damageLevelTolerance[1] = 0.7;
   numDmgEmitterAreas = 1;

//   splashEmitter[0] = VehicleFoamDropletsEmitter;
//   splashEmitter[1] = VehicleFoamEmitter;

	// damage info eyecandy...
	//damageBufferParticleEmitter = RedCatDamageBufferEmitter;
	//repairParticleEmitter = RedCatRepairEmitter;
	//bufferRepairParticleEmitter = RedCatBufferRepairEmitter;
	damageParticleEmitter = FrmCrate_DamageEmitter;

   //
   // dynamic fields for in-script vehicle-implementation...
   //

   mountable = false;
   mountPose[0] = "ScoutDrone";
};

function FrmSoldierpod::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   %obj.setFlyMode();
   %obj.playThread(0, "ambient");
}

function FrmSoldierpod::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   
   // delete engine light...
//   %obj.light.delete();
}

// *** Callback function: called by engine
function FrmSoldierpod::onImpact(%this, %obj, %col, %vec, %vecLen)
{
   if(%obj.hasMaterialized)
      return;

   %client = %obj.client;
   %pos = %obj.getPosition();
   %normal = "0 0 1";
   %transform = %obj.getTransform();

   %start = %pos;
   %end = VectorAdd(%pos, "0 0 -10");

   %c = containerRayCast(%start, %end, $TypeMasks::StaticObjectType, %obj);

   %x = getWord(%c,1); 
   %y = getWord(%c,2);
   %z = getWord(%c,3);

   %pos = %x SPC %y SPC %z;

   %transform = setWord(%transform, 0, getWord(%pos, 0));
   %transform = setWord(%transform, 1, getWord(%pos, 1));
   %transform = setWord(%transform, 2, getWord(%pos, 2));

   %error = FrmSoldier.canMaterialize(%client, %pos, %normal, %transform);
   error(%error);
   if(%error !$= "")
   {
      %this.explode(%obj);
      return;
   }

   %player = FrmSoldier.materialize(%client, %pos, %normal, %transform);
   %player.setTransform(%transform);
   //%client.proxy.removeClientFromGhostingList(%client);
   //%client.proxy.setTransform("0 0 0");
   %player.setLoadoutCode(%obj.loadoutCode);

   createExplosion(FrmSoldierSpawnExplosion, %player.getPosition(), "0 0 1");

   if(true || %obj == %client.player)
   {
      %client.control(%player);
      %client.player = %player;
      %client.inventoryMode = "";
      %client.displayInventory();
   }

   %obj.schedule(0, "delete");

   %obj.hasMaterialized = true;
}

// *** Callback function:
// Invoked by ShapeBase code whenever the object's damage level changes
function FrmSoldierpod::onDamage(%this, %obj, %delta)
{
	%totalDamage = %obj.getDamageLevel();
	if(%totalDamage >= %this.maxDamage)
	{
      %this.explode(%obj);
	}
}

// *** Callback function:
// Invoked by ShapeBase code when object's damageState was set to 'Destroyed'
function FrmSoldierpod::onDestroyed(%this, %obj, %prevState)
{
   // nothing here right now
}

// called by ShapeBase::impulse() script function
function FrmSoldierpod::impulse(%this, %obj, %position, %impulseVec, %src)
{
   return; // ignore impulses
}

// Called from script
function FrmSoldierpod::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
{
   if(%obj.getDamageState() $= "Destroyed")
      return;

   %damage *= 4;

   Parent::damage(%this, %obj, %sourceObject, %position, %damage, %damageType);
   
   return;

   // ScoutDrone died?
   if(%obj.getDamageLevel() >= %this.maxDamage)
   {
      // create wreck...
      %wreck = new RigidShape() {
  		   dataBlock = ScoutDroneWreck;
  	   };
      MissionCleanup.add(%wreck);

      // wreck bounces away from point of impact...
      %wreck.setTransform(%obj.getTransform());
      //%wreck.applyImpulse(%obj.getPosition(), %obj.getVelocity());
      %impulseVec = VectorNormalize(%position);
      %impulseVec = VectorScale(%impulseVec, 4000);
      %wreck.applyImpulse(%obj.getPosition(), %impulseVec);
         
      %wreck.schedule(60*1000, "startFade", 3*1000, 0, true);
      %wreck.schedule(60*1000+3*1000, "delete");

      %client = %obj.client;

      // the wreck is now this client's "player"...
      %wreck.setShapeName(%obj.getShapeName());
      %client.player = %wreck;

      // tell client he died...
      %location = "Body";
      %sourceClient = %sourceObject ? %sourceObject.client : 0;
      %client.onDeath(%sourceObject, %sourceClient, %damageType, %location);

      // delete the (invisible) player mounted on the ScoutDrone...
      %obj.getMountedObject(0).delete();
      
      // put ScoutDrone away and schedule its removal...
      %obj.schedule(500,"setTransform","0 0 -10000");
      %obj.schedule(2000,"delete");
   }
}

// Called from script
function FrmSoldierpod::explode(%this, %obj)
{
   %pos = %obj.getPosition();
   createExplosion(FrmSoldierpodExplosion, %pos, "0 0 1");
   %obj.schedule(0, "delete");
   %obj.client.onDeath(0, 0, 0, 0);
}

// Called from script
function FrmSoldierpod::canMaterialize(%this, %client, %pos, %normal, %transform)
{
   return FrmSoldier::canMaterialize(%this, %client, %pos, %normal, %transform);
}

// Called from script
function FrmSoldierpod::materialize(%this, %client)
{
	%player = new FlyingVehicle() {
		dataBlock = %this;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%player);
	//%player.playAudio(0, CatSpawnSound);

   return %player;
}

// Called from script
function FrmSoldierpod::materializeFx(%this, %obj)
{
   FrmCrate::materializeFx(%this, %obj);
}

// Called from script
function FrmSoldierpod::dematerialize(%this, %obj)
{
   FrmCrate::dematerialize(%this, %obj);
}

// Called from script
function FrmSoldierpod::dematerializeFinish(%this, %obj)
{
   FrmCrate::dematerializeFinish(%this, %obj);
}

// called by ShapeBase script code...
function FrmSoldierpod::getBleed(%this, %obj, %dmg, %src)
{
   return Player::getBleed(%this, %obj, %dmg, %src);
}

