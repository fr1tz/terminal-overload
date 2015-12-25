// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function vitcTankVehicleData::create(%block)
{
   %obj = new vitcTankVehicle() {
      dataBlock = %block;
      parentGroup = EWCreatorWindow.objectGroup;
   };
   return %obj;
}

datablock SFXProfile(Wheels1EngineSound)
{
   preload = "1";
   description = "AudioCloseLoop3D";
   fileName = "content/o/torque3d/3.0/sound/cheetah/cheetah_engine.ogg";
};

datablock SFXProfile(Wheels1HardImpactSound)
{
   preload = "1";
   description = "AudioDefault3D";
   fileName = "content/o/torque3d/3.0/sound/cheetah/hardImpact.ogg";
};

datablock SFXProfile(Wheels1SoftImpactSound)
{
   preload = "1";
   description = "AudioDefault3D";
   fileName = "content/o/torque3d/3.0/sound/cheetah/softImpact.ogg";
};

datablock ParticleData(Wheels1TireParticle)
{
   textureName          = "content/o/torque3d/3.0/particles/dustParticle";
   dragCoefficient      = "1.99902";
   gravityCoefficient   = "-0.100122";
   inheritedVelFactor   = "0.0998043";
   constantAcceleration = 0.0;
   lifetimeMS           = 1000;
   lifetimeVarianceMS   = 400;
   colors[0]            = "0.456693 0.354331 0.259843 1";
   colors[1]            = "0.456693 0.456693 0.354331 0";
   sizes[0]             = "0.997986";
   sizes[1]             = "3.99805";
   sizes[2]             = "1.0";
   sizes[3]             = "1.0";
   times[0]             = "0.0";
   times[1]             = "1";
   times[2]             = "1";
   times[3]             = "1";
};

datablock ParticleEmitterData(Wheels1TireEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 10;
   ejectionVelocity = "14.57";
   velocityVariance = 1.0;
   ejectionOffset   = 0.0;
   thetaMin         = 0;
   thetaMax         = 60;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   overrideAdvance = false;
   particles = "Wheels1TireParticle";
   blendStyle = "ADDITIVE";
};

datablock vitcTankVehicleTire(Wheels1Tire)
{
   // Tires act as springs and generate lateral and longitudinal
   // forces to move the vehicle. These distortion/spring forces
   // are what convert wheel angular velocity into forces that
   // act on the rigid body.
   shapeFile = "content/vitc/shapes/wheels1/p1/wheel.dae";
   staticFriction = "7.2";
   kineticFriction = "1";

   // Spring that generates lateral tire forces
   lateralForce = "19000";
   lateralDamping = 6000;
   lateralRelaxation = 1;

   // Spring that generates longitudinal tire forces
   longitudinalForce = 18000;
   longitudinalDamping = 4000;
   longitudinalRelaxation = 1;
   radius = "0.840293";
};

datablock vitcTankVehicleSpring(Wheels1Spring)
{
   // Wheel suspension properties
   length = 0.5;             // Suspension travel
   force = 2800;              // Spring force
   damping = 3600;             // Spring damping
   antiSwayForce = 3;         // Lateral anti-sway force
};

datablock vitcTankVehicleData(Wheels1)
{
   category = "Modules";
   shapeFile = "content/vitc/shapes/wheels1/p1/shape.dae";
   emap = 1;

   mountPose[0] = sitting;
   numMountPoints = 6;

   useEyePoint = true;  // Use the vehicle's camera node rather than the player's

   maxSteeringAngle = 0.585;  // Maximum steering angle, should match animation

   // 3rd person camera settings
   cameraRoll = false;        // Roll the camera with the vehicle
   cameraMaxDist = 7.8;       // Far distance from vehicle
   cameraOffset = 1.0;        // Vertical offset from camera mount point
   cameraLag = "0.3";           // Velocity lag of camera
   cameraDecay = 1.25;        // Decay per sec. rate of velocity lag

   // Rigid Body
   mass = "400";
   massCenter = "0 0.5 0";    // Center of mass for rigid body
   massBox = "0 0 0";         // Size of box used for moment of inertia,
                              // if zero it defaults to object bounding box
   drag = 0.6;                // Drag coefficient
   bodyFriction = 0.6;
   bodyRestitution = 0.4;
   minImpactSpeed = 5;        // Impacts over this invoke the script callback
   softImpactSpeed = 5;       // Play SoftImpact Sound
   hardImpactSpeed = 15;      // Play HardImpact Sound
   integration = 8;           // Physics integration: TickSec/Rate
   collisionTol = "0.1";        // Collision distance tolerance
   contactTol = "0.4";          // Contact velocity tolerance

   // Engine
   engineTorque = 4300;       // Engine power
   engineBrake = "5000";         // Braking when throttle is 0
   brakeTorque = "10000";        // When brakes are applied
   maxWheelSpeed = 50;        // Engine scale by current speed / max speed

   // Energy
   maxEnergy = 100;
   jetForce = 3000;
   minJetEnergy = 30;
   jetEnergyDrain = 2;

   // Sounds
   engineSound = Wheels1EngineSound;
   //squealSound = cheetahSqueal;
   softImpactSound = Wheels1SoftImpactSound;
   hardImpactSound = Wheels1HardImpactSound;

   // Dynamic fields accessed via script
   nameTag = 'Wheels1';
   maxDismountSpeed = 10;
   maxMountSpeed = 5;
   mountPose0 = "sitting";
   tireEmitter = "Wheels1TireEmitter";
   dustEmitter = "Wheels1TireEmitter";
   dustHeight = "1";

   // Mount slots
   turretSlot = 1;
   rightBrakeSlot = 2;
   leftBrakeSlot = 3;
};

function Wheels1::onAdd(%this, %obj)
{
   VehicleData::onAdd(%this, %obj);  // NOTE: we're skipping vitcTankVehicleData

   %obj.setShapeName("Wheels" @ %obj.getId());
   
   for(%i = 0; %i <= 5; %i++)
   {
      %obj.setWheelTire(%i, Wheels1Tire);
      %obj.setWheelSpring(%i, Wheels1Spring);
      %obj.setWheelPowered(%i, true);
      //%obj.setWheelSteering(%i, false);
   }
   
   %obj.setWheelSteeringLever(0, 0);
   %obj.setWheelSteeringLever(1, 0);
   %obj.setWheelSteeringLever(2, 0);
   %obj.setWheelSteeringLever(3, 1);
   %obj.setWheelSteeringLever(4, 1);
   %obj.setWheelSteeringLever(5, 1);

   %obj.ssc = new SimpleServerSideController();
   %obj.useServerSideController(%obj.ssc);
   %obj.engineThrottleWidget = createWidget(%obj, "Wheels1EngineThrottleWidget");
   %obj.leftSteeringLeverWidget = createWidget(%obj, "Wheels1LeftSteeringLeverWidget");
   %obj.rightSteeringLeverWidget = createWidget(%obj, "Wheels1RightSteeringLeverWidget");
}

function Wheels1::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   
   %obj.ssc.delete();
   %obj.engineThrottleWidget.delete();
   %obj.leftSteeringLeverWidget.delete();
   %obj.rightSteeringLeverWidget.delete();
}

function Wheels1EngineThrottleWidget::getDescription(%this)
{
   return "Engine Throttle";
}

function Wheels1EngineThrottleWidget::getType(%this)
{
   return 3;	
}

function Wheels1EngineThrottleWidget::getGridSizeN(%this)
{
   return "2 6";	
}

function Wheels1EngineThrottleWidget::update(%this, %args)
{
   %val = getWord(%args, 0);
   %this.moduleObj.ssc.y = %val;
   echo("Wheels1EngineThrottleWidget:" SPC %this.moduleObj.ssc.y);
}

//-----------------------------------------------------------------------------

function Wheels1LeftSteeringLeverWidget::getDescription(%this)
{
   return "Left Thread";
}

function Wheels1LeftSteeringLeverWidget::getType(%this)
{
   return 3;	
}

function Wheels1LeftSteeringLeverWidget::getGridSizeN(%this)
{
   return "2 6";	
}

function Wheels1LeftSteeringLeverWidget::update(%this, %args)
{
   %val = getWord(%args, 0);
   %this.moduleObj.ssc.x = %val;
   echo("Wheels1LeftSteeringLeverWidget:" SPC %this.moduleObj.ssc.x);
}

//-----------------------------------------------------------------------------

function Wheels1RightSteeringLeverWidget::getDescription(%this)
{
   return "Right Thread";
}

function Wheels1RightSteeringLeverWidget::getType(%this)
{
   return 3;	
}

function Wheels1RightSteeringLeverWidget::getGridSizeN(%this)
{
   return "2 6";	
}

function Wheels1RightSteeringLeverWidget::update(%this, %args)
{
   %val = getWord(%args, 0);
   %this.moduleObj.ssc.z = %val;
   echo("Wheels1RightSteeringLeverWidget:" SPC %this.moduleObj.ssc.z);
}

