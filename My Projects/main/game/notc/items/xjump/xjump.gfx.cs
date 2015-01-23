// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(ItemXJumpProjectileDecal)
{
   Material = "xa_notc_core_shapes_standardcat_xjump_decal_p1_mat";
   size = "4";
   lifeSpan = "5000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "3";
   textureCoords[0] = "0 0 0.5 0.5";
   textureCoords[1] = "0.5 0 0.5 0.5";
   textureCoords[2] = "0 0.5 0.5 0.5";
   textureCoords[3] = "0.5 0.5 0.5 0.5";
};

datablock ParticleData(ItemXJumpProjectileExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 600;
	lifetimeVarianceMS	= 0;

	useInvAlpha = false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/o/rotc/p.5.4/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 2.0;
	sizes[1]		= 2.0;
	sizes[2]		= 0.5;
	times[0]		= 0.0;
	times[1]		= 0.2;
	times[2]		= 1.0;

	allowLighting = true;
};

datablock ParticleEmitterData(ItemXJumpProjectileExplosion_CloudEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;

	ejectionVelocity = 0.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "ItemXJumpProjectileExplosion_Cloud";
};

datablock ParticleData(ItemXJumpProjectileExplosion_Particle0)
{
	dragCoefficient		= "0";
	gravityCoefficient	= "0";
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = "500";
	lifetimeVarianceMS	= 100;
	useInvAlpha			 = "0";
	spinRandomMin		  = "0";
	spinRandomMax		  = "1";
	textureName			 = "content/o/rotc/p.5.4/textures/rotc/zone.grid.png";
	colors[0]	  = "0.996078 0.996078 0.996078 1";
	colors[1]	  = "0.996078 0.996078 0.996078 1";
	colors[2]	  = "0.897638 0.897638 0.897638 0";
	sizes[0]		= "2";
	sizes[1]		= "0";
	sizes[2]		= "0";
	times[0]		= 0.0;
	times[1]		= "1";
	times[2]		= 1.0;
	allowLighting = 1;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/zone.grid.png";
   spinSpeed = "0";
};

datablock ParticleEmitterData(ItemXJumpProjectileExplosion_Emitter0)
{
	ejectionPeriodMS = "1";
	periodVarianceMS = 0;
	ejectionVelocity = "15";
	velocityVariance = 0.0;
	ejectionOffset	= 0.0;
	thetaMin			= "85";
	thetaMax			= "85";
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = 0;
	lifetimeMS		 = "75";
	particles = "ItemXJumpProjectileExplosion_Particle0";
   orientParticles = "1";
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
   paletteSlot = "0";
};

datablock ExplosionData(ItemXJumpProjectileExplosion)
{
	//soundProfile = ItemXJumpActivateSound;

	lifetimeMS = "192";

	debrisThetaMin = 0;
	debrisThetaMax = 180;
	debrisNum = 3;
	debrisVelocity = 50.0;
	debrisVelocityVariance = 10.0;

	//particleEmitter = ItemXJumpProjectileExplosion_CloudEmitter;
	particleDensity = 50;
	particleRadius = 1;

	emitter[0] = ItemXJumpProjectileExplosion_Emitter0;

	// Camera shake
	shakeCamera = true;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "10.0 0.0 0.0";
	camShakeDuration = 0.5;
	camShakeRadius = 1.0;

	// Dynamic light
	lightStartRadius = "14.9804";
	lightEndRadius = 0;
	lightStartColor = "1 0.795276 0.19685 1";
	lightEndColor = "1 0.795276 0.19685 0.3";
   lightStartBrightness = "0.941176";
   lightEndBrightness = "0.941176";
   targetLockTimeMS = "480";
};

datablock MultiNodeLaserBeamData(ItemXJumpProjectileLaserTrail0)
{
	material = "xa_notc_core_shapes_xjump_lasertrail_p1_mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.3;
	fadeTime = 100;
	windCoefficient = 0.0;
	//nodeDistance = 3;

   // node x movement...
   nodeMoveMode[0]     = $NodeMoveMode::None;
   nodeMoveSpeed[0]    = -0.002;
   nodeMoveSpeedAdd[0] =  0.004;
   // node y movement...
   nodeMoveMode[1]     = $NodeMoveMode::None;
   nodeMoveSpeed[1]    = -0.002;
   nodeMoveSpeedAdd[1] =  0.004;
   // node z movement...
   nodeMoveMode[2]     = $NodeMoveMode::None;
   nodeMoveSpeed[2]    = 0.5;
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(ItemXJumpProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_xjump_lasertrail_p1_mat1";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.6;
	fadeTime = 200;
	windCoefficient = 0.0;
	//nodeDistance = 3;

   // node x movement...
   nodeMoveMode[0]     = $NodeMoveMode::None;
   nodeMoveSpeed[0]    = -0.002;
   nodeMoveSpeedAdd[0] =  0.004;
   // node y movement...
   nodeMoveMode[1]     = $NodeMoveMode::None;
   nodeMoveSpeed[1]    = -0.002;
   nodeMoveSpeedAdd[1] =  0.004;
   // node z movement...
   nodeMoveMode[2]     = $NodeMoveMode::None;
   nodeMoveSpeed[2]    = 0.5;
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(ItemXJumpProjectileLaserTrail2)
{
	material = "xa_notc_core_shapes_xjump_lasertrail_p1_mat2";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 1.5;
	fadeTime = 3000;
	windCoefficient = 0.0;
	nodeDistance = 4;

   // Node x movement
   nodeMoveMode[0]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[0]    = -2.0;
   nodeMoveSpeedAdd[0] =  4.0;
   // Node y movement
   nodeMoveMode[1]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[1]    = -2.0;
   nodeMoveSpeedAdd[1] =  4.0;
   // Node z movement
   nodeMoveMode[2]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[2]    = -2.0;
   nodeMoveSpeedAdd[2] =  4.0;
};


