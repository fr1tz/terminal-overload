// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnSMG4ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnSMG4ProjectileDecal)
{
   Material = "xa_notc_core_shapes_mgl1_projectile_p1_decalmat";
   size = "0.2";
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

//-----------------------------------------------------------------------------
// laser trail

datablock MultiNodeLaserBeamData(WpnSMG4ProjectileLaserTrail0)
{
	material = "xa_notc_core_shapes_smg4_trail_p1_lasertrail0mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.2;
	fadeTime = 100;
	windCoefficient = 0.0;

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
	nodeMoveSpeedAdd[2] = 0.5;

	//nodeDistance = 2;
};

datablock MultiNodeLaserBeamData(WpnSMG4ProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_smg4_trail_p1_lasertrail1mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.2;
	fadeTime = 500;
	windCoefficient = 0.0;

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
	nodeMoveSpeedAdd[2] = 0.5;
};

//-----------------------------------------------------------------------------
// explosion

datablock ParticleData(WpnSMG4ProjectileExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= "-0.100122";	// rises slowly
	inheritedVelFactor	= "0";

	lifetimeMS			  = 2000;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/o/rotc/p.5.4/textures/rotc/smoke_particle.png";

	colors[0]	  = "0.393701 0.393701 0.393701 0.393701";
	colors[1]	  = "0.393701 0.393701 0.393701 0.19685";
	colors[2]	  = "0.393701 0.393701 0.393701 0";
	sizes[0]		= "1";
	sizes[1]		= "3";
	sizes[2]		= "0";
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;

	allowLighting = 0;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/smoke_particle.png";
};

datablock ParticleEmitterData(WpnSMG4ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = "10";
	periodVarianceMS = 0;

	ejectionVelocity = 2.0;
	velocityVariance = "0";

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 50;

	particles = "WpnSMG4ProjectileExplosion_Smoke";
   blendStyle = "NORMAL";
   targetLockTimeMS = "480";
};

datablock ParticleData(WpnSMG4ProjectileExplosion_DebrisParticles)
{
	spinSpeed = 200;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;
	dragCoefficient		= "0.997067";
	gravityCoefficient	= "2.49817";
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1500;
	lifetimeVarianceMS	= 0;
	textureName = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.white";
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= "0.3";
	sizes[1]		= "0.3";
	sizes[2]		= "0.3";
	times[0]		= 0.0;
	times[1]		= "0.498039";
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = 0;
   animTexName = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.white";
};

datablock ParticleEmitterData(WpnSMG4ProjectileExplosion_DebrisEmitter)
{
	ejectionPeriodMS = "20";
	periodVarianceMS = 0;
	ejectionVelocity = "15";
	velocityVariance = "5";
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= "20";
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = "5";
	lifetimeVarianceMS = 0;
	overrideAdvances = 0;
	orientParticles  = true;
	particles = "WpnSMG4ProjectileExplosion_DebrisParticles";
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
};

datablock ExplosionData(WpnSMG4ProjectileExplosion)
{
	soundProfile = WpnSMG4ProjectileExplosionSound;

	lifetimeMS = "192";

 	// shape...
	//explosionShape = "share/shapes/rotc/effects/explosion2_white.dts";
	//faceViewer	  = false;
	//playSpeed = 8.0;
	//sizes[0] = "0.2 0.2 0.2";
	//sizes[1] = "0.2 0.2 0.2";
	//times[0] = 0.0;
	//times[1] = 1.0;

	//debris = WpnSMG4ProjectileExplosion_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 180;
	//debrisNum = 3;
	//debrisNumVariance = 0;
	//debrisVelocity = 50.0;
	//debrisVelocityVariance = 10.0;

//	particleEmitter = WpnSMG4ProjectileExplosion_CloudEmitter;
	particleDensity = 25;
	particleRadius = 0.5;

	emitter[0] = WpnSMG4ProjectileExplosion_SmokeEmitter;
	emitter[1] = WpnSMG4ProjectileExplosion_DebrisEmitter;
//	emitter[1] = WpnSMG4ProjectileExplosion_DustEmitter;
//	emitter[2] = WpnSMG4ProjectileExplosion_SparksEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = "4.94118";
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16";
   lightEndBrightness = "0";
   targetLockTimeMS = "480";
};

