// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// projectile particle emitter

datablock ParticleData(WpnRFL1ProjectileParticleEmitter_Particles)
{
	dragCoefficient      = "0.99218";
	gravityCoefficient   = 0.0;
	windCoefficient      = 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			   = "400";
	lifetimeVarianceMS	= 0;
	spinRandomMin        = 0;
	spinRandomMax        = 0;
	textureName			   = "content/o/rotc/p.5.4/textures/rotc/corona";
	colors[0]            = "0.996078 0.996078 0.996078 1";
	colors[1]            = "1 1 1 0";
	sizes[0]             = "2";
	sizes[1]             = "0";
	times[0]             = 0.0;
	times[1]             = 1.0;
	useInvAlpha          = false;
	renderDot            = 0;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/corona";
   times[2] = "1";
};

datablock ParticleEmitterData(WpnRFL1ProjectileParticleEmitter)
{
	ejectionPeriodMS = "5";
	periodVarianceMS = 0;
	ejectionVelocity = 0;
	velocityVariance = 2.5;
	ejectionOffset   = 0.0;
	thetaMin         = 0;
	thetaMax         = 0;
	phiReferenceVel  = 0;
	phiVariance      = 0;
	overrideAdvances = 0;
	orientParticles  = false;
	//lifetimeMS		 = 1000;
	particles = "WpnRFL1ProjectileParticleEmitter_Particles";
   paletteSlot = 0;
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
};

//-----------------------------------------------------------------------------
// laser trail

datablock MultiNodeLaserBeamData(WpnRFL1ProjectileLaserTrail0)
{
	material[0] = "xa_notc_core_shapes_rfl1_trail_p1_lasertrail0mat0";
   width[0] = 0.2;
 
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;

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
};

datablock MultiNodeLaserBeamData(WpnRFL1ProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_mgl1_projectile_p1_lasertrail1mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.001;
	fadeTime = 300;
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


datablock MultiNodeLaserBeamData(WpnRFL1ProjectileLaserTrail2)
{
	material = "xa_notc_core_shapes_mgl1_projectile_p1_lasertrail2mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.05;
	fadeTime = 1000;
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
	nodeMoveMode[2]     = $NodeMoveMode::ConstantSpeed;
	nodeMoveSpeed[2]    = 0.5;
	nodeMoveSpeedAdd[2] = 0.5;

	nodeDistance = 2;
};

//-----------------------------------------------------------------------------
// bounce

datablock ParticleData(WpnRFL1ProjectileBounceExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.4;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 200;

	useInvAlpha =  true;

	textureName = "content/o/rotc/p.5.4/textures/rotc/smoke_particle";

	colors[0]	  = "1.0 1.0 1.0 0.5";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 1.0;

	allowLighting = false;
};

datablock ParticleEmitterData(WpnRFL1ProjectileBounceExplosion_SmokeEmitter)
{
	ejectionOffset	= 0;

	ejectionPeriodMS = 40;
	periodVarianceMS = 0;

	ejectionVelocity = 2.0;
	velocityVariance = 0.1;

	thetaMin			= 0.0;
	thetaMax			= 60.0;

	lifetimeMS		 = 100;

	particles = "WpnRFL1ProjectileBounceExplosion_Smoke";
};

datablock ExplosionData(WpnRFL1ProjectileBounceExplosion)
{
	soundProfile = AssaultRifleProjectileBounceSound;

	lifetimeMS = 50;

	emitter[0] = WpnRFL1ProjectileBounceExplosion_SmokeEmitter;

	// Dynamic light
	lightStartRadius = 10;
	lightEndRadius = 0;
	lightStartColor = "1 1 1";
	lightEndColor = "1 1 1";
};


//-----------------------------------------------------------------------------
// explosion

datablock ParticleData(WpnRFL1ProjectileExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= "0";

	lifetimeMS			  = "250";
	lifetimeVarianceMS	= 0;

	useInvAlpha = false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/o/rotc/p.5.4/textures/rotc/laser1.white.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1 1 1 0.496063";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= "0.5";
	sizes[1]		= "0";
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= "1";
	times[2]		= 1.0;

	allowLighting = 0;
 
   animTexName = "content/o/rotc/p.5.4/textures/rotc/laser1.white.png";
   spinSpeed = "0";
};

datablock ParticleEmitterData(WpnRFL1ProjectileExplosion_CloudEmitter)
{
	ejectionPeriodMS = "5";
	periodVarianceMS = 0;

	ejectionVelocity = "20";
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "WpnRFL1ProjectileExplosion_Cloud";
   blendStyle = "ADDITIVE";
   paletteSlot = 0;
   glow = "1";
};


datablock ParticleData(WpnRFL1ProjectileExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.1;	// rises slowly
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 2000;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/o/rotc/p.5.4/textures/rotc/smoke_particle.png";

	colors[0]	  = "0.4 0.4 0.4 0.4";
	colors[1]	  = "0.4 0.4 0.4 0.2";
	colors[2]	  = "0.4 0.4 0.4 0.0";
	sizes[0]		= 0.0;
	sizes[1]		= 6.0;
	sizes[2]		= 0.6;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;

	allowLighting = false;
};

datablock ParticleEmitterData(WpnRFL1ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 2.0;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 50;

	particles = "WpnRFL1ProjectileExplosion_Smoke";
};

datablock ParticleData(WpnRFL1ProjectileExplosion_DebrisParticles)
{
	spinSpeed = 200;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;
	dragCoefficient		= 1;
	gravityCoefficient	= 2.5;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1500;
	lifetimeVarianceMS	= 0;
	textureName = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.white";
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 0.55;
	sizes[1]		= 0.55;
	sizes[2]		= 0.55;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = false;
};

datablock ParticleEmitterData(WpnRFL1ProjectileExplosion_DebrisEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 30.0;
	velocityVariance = 20.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = 8;
	lifetimeVarianceMS = 0;
	overrideAdvances = false;
	orientParticles  = true;
	particles = "WpnRFL1ProjectileExplosion_DebrisParticles";
};

datablock ExplosionData(WpnRFL1ProjectileExplosion)
{
	soundProfile = WpnRFL1ProjectileExplosionSound;

	lifetimeMS = "192";

 	// shape...
	//explosionShape = "share/shapes/rotc/effects/explosion2_white.dts";
	//faceViewer	  = false;
	//playSpeed = 8.0;
	//sizes[0] = "0.2 0.2 0.2";
	//sizes[1] = "0.2 0.2 0.2";
	//times[0] = 0.0;
	//times[1] = 1.0;

	//debris = WpnRFL1ProjectileExplosion_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 180;
	//debrisNum = 3;
	//debrisNumVariance = 0;
	//debrisVelocity = 50.0;
	//debrisVelocityVariance = 10.0;

//	particleEmitter = WpnRFL1ProjectileExplosion_CloudEmitter;
	particleDensity = 25;
	particleRadius = 0.5;

	emitter[0] = WpnRFL1ProjectileExplosion_SmokeEmitter;
	emitter[1] = WpnRFL1ProjectileExplosion_DebrisEmitter;
   emitter[2] = WpnRFL1ProjectileExplosion_CloudEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = "9.96078";
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16";
   lightEndBrightness = "0";
   targetLockTimeMS = "480";

};

