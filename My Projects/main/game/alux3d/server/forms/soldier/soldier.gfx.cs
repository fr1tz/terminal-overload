// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//----------------------------------------------------------------------------
// Foot prints
//----------------------------------------------------------------------------

datablock DecalData(FrmSoldierFootprint)
{
	sizeX = "0.18";
	sizeY = "0.27";
	textureName = "content/rotc/p.5.3/textures/inf/footprint";
	SelfIlluminated = false;
};

//----------------------------------------------------------------------------
// Foot puffs
//----------------------------------------------------------------------------

datablock ParticleData(FrmSoldierFootPuff)
{
	dragCoefficient		= 2.0;
	gravityCoefficient	= -0.01;
	inheritedVelFactor	= 0.6;
	constantAcceleration = 0.0;
	lifetimeMS			  = 800;
	lifetimeVarianceMS	= 100;
	useInvAlpha			 = true;
	spinRandomMin		  = -35.0;
	spinRandomMax		  = 35.0;
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 2.0;
	times[0]		= 0.0;
	times[1]		= 1.0;
	textureName	= "content/rotc/p.5.3/textures/rotc/dustParticle";
};

datablock ParticleEmitterData(FrmSoldierFootPuffEmitter)
{
	ejectionPeriodMS = 35;
	periodVarianceMS = 10;
	ejectionVelocity = 0.2;
	velocityVariance = 0.1;
	ejectionOffset	= 0.0;
	thetaMin			= 20;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	useEmitterColors = true;
	particles = FrmSoldierFootPuff;
};

//----------------------------------------------------------------------------
// Spawn explosion
//----------------------------------------------------------------------------

datablock ParticleData(FrmSoldierSpawnExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 600;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/rotc/p.5.3/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 6.0;
	sizes[1]		= 6.0;
	sizes[2]		= 2.0;
	times[0]		= 0.0;
	times[1]		= 0.2;
	times[2]		= 1.0;

	allowLighting = true;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_CloudEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "FrmSoldierSpawnExplosion_Cloud";
};

datablock ParticleData(FrmSoldierSpawnExplosion_Dust)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= -0.01;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 100;
	useInvAlpha			 = true;
	spinRandomMin		  = -90.0;
	spinRandomMax		  = 500.0;
	textureName			 = "content/rotc/p.5.3/textures/rotc/smoke_particle.png";
	colors[0]	  = "0.9 0.9 0.9 0.5";
	colors[1]	  = "0.9 0.9 0.9 0.5";
	colors[2]	  = "0.9 0.9 0.9 0.0";
	sizes[0]		= 3.2;
	sizes[1]		= 4.6;
	sizes[2]		= 5.0;
	times[0]		= 0.0;
	times[1]		= 0.7;
	times[2]		= 1.0;
	allowLighting = true;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_DustEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 15.0;
	velocityVariance = 0.0;
	ejectionOffset	= 0.0;
	thetaMin			= 90;
	thetaMax			= 90;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	lifetimeMS		 = 250;
	particles = "FrmSoldierSpawnExplosion_Dust";
};


datablock ParticleData(FrmSoldierSpawnExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.5;	// rises slowly
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 1250;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/rotc/p.5.3/textures/rotc/smoke_particle.png";

	colors[0]	  = "0.9 0.9 0.9 0.4";
	colors[1]	  = "0.9 0.9 0.9 0.2";
	colors[2]	  = "0.9 0.9 0.9 0.0";
	sizes[0]		= 2.0;
	sizes[1]		= 6.0;
	sizes[2]		= 2.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;

	allowLighting = true;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 250;

	particles = "FrmSoldierSpawnExplosion_Smoke";
};

datablock ParticleData(FrmSoldierSpawnExplosion_Sparks)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.2;
	constantAcceleration = 0.0;
	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 350;
	textureName			 = "content/rotc/p.5.3/textures/rotc/particle1.png";
	colors[0]	  = "0.56 0.36 0.26 1.0";
	colors[1]	  = "0.56 0.36 0.26 1.0";
	colors[2]	  = "1.0 0.36 0.26 0.0";
	sizes[0]		= 0.5;
	sizes[1]		= 0.5;
	sizes[2]		= 0.75;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_SparksEmitter)
{
	ejectionPeriodMS = 2;
	periodVarianceMS = 0;
	ejectionVelocity = 12;
	velocityVariance = 6.75;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = true;
	lifetimeMS		 = 100;
	particles = "FrmSoldierSpawnExplosion_Sparks";
};

datablock DebrisData(FrmSoldierSpawnExplosion_SmallDebris)
{
	// shape...
	shapeFile = "content/rotc/p.5.3/shapes/rotc/misc/debris1.white.dts";

	// bounce...
	staticOnMaxBounce = true;
	numBounces = 5;

	// physics...
	gravModifier = 2.0;
	elasticity = 0.6;
	friction = 0.1;

	// spin...
	minSpinSpeed = 60;
	maxSpinSpeed = 600;

	// lifetime...
	lifetime = 2.0;
	lifetimeVariance = 1.0;
};

datablock MultiNodeLaserBeamData(FrmSoldierSpawnExplosion_LargeDebris_LaserTrail)
{
	hasLine = true;
	lineColor	= "1.00 1.00 1.00 0.5";

	hasInner = false;
	innerColor = "1.00 1.00 0.00 0.3";
	innerWidth = "0.20";

	hasOuter = true;
	outerColor = "1.00 1.00 1.00 0.2";
	outerWidth = "0.40";

//	bitmap = "content/rotc/p.5.3/shapes/rotc/weapons/missilelauncher/explosion.trail";
//	bitmapWidth = 0.25;

	blendMode = 1;
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
	fadeTime = 1000;
};

datablock ParticleData(FrmSoldierSpawnExplosion_LargeDebris_Particles2)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/rotc/p.5.3/textures/rotc/cross1";
	colors[0]	  = "1.0 1.0 1.0 0.6";
	colors[1]	  = "1.0 1.0 1.0 0.4";
	colors[2]	  = "1.0 1.0 1.0 0.2";
	colors[3]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	sizes[3]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.333;
	times[2]		= 0.666;
	times[3]		= 1.0;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_LargeDebris_Emitter2)
{
	ejectionPeriodMS = 30;
	periodVarianceMS = 0;
	ejectionVelocity = 2.0;
	velocityVariance = 0.0;
	ejectionOffset	= 0.0;
	thetaMin			= 45;
	thetaMax			= 45;
	phiReferenceVel  = 75000;
	phiVariance		= 0;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0;
	particles = "FrmSoldierSpawnExplosion_LargeDebris_Particles2";
};

datablock ParticleData(FrmSoldierSpawnExplosion_LargeDebris_Particles1)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 100;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/rotc/p.5.3/textures/rotc/cross1";
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 0.5";
	colors[3]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 2.0;
	sizes[1]		= 2.0;
	sizes[2]		= 2.0;
	sizes[3]		= 2.0;
	times[0]		= 0.0;
	times[1]		= 0.333;
	times[2]		= 0.666;
	times[3]		= 1.0;
};

datablock ParticleEmitterData(FrmSoldierSpawnExplosion_LargeDebris_Emitter1)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 10.0;
	velocityVariance = 0.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 180;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0;
	particles = "FrmSoldierSpawnExplosion_LargeDebris_Particles1";
};

datablock ExplosionData(FrmSoldierSpawnExplosion_LargeDebris_Explosion)
{
	soundProfile	= MissileLauncherDebrisSound;

	debris = FrmSoldierSpawnExplosion_SmallDebris;
	debrisThetaMin = 0;
	debrisThetaMax = 60;
	debrisNum = 5;
	debrisVelocity = 15.0;
	debrisVelocityVariance = 10.0;
};

datablock DebrisData(FrmSoldierSpawnExplosion_LargeDebris)
{
	// shape...
	shapeFile = "content/rotc/p.5.3/shapes/rotc/misc/debris2.white.dts";

	explosion = FrmSoldierSpawnExplosion_LargeDebris_Explosion;

	//laserTrail = FrmSoldierSpawnExplosion_LargeDebris_LaserTrail;
	emitters[0] = FrmSoldierSpawnExplosion_LargeDebris_Emitter2;
	//emitters[1] = FrmSoldierSpawnExplosion_LargeDebris_Emitter1;

	// bounce...
	numBounces = 0;
	explodeOnMaxBounce = true;

	// physics...
	gravModifier = 2.0;
	elasticity = 0.6;
	friction = 0.1;

	// spin...
	minSpinSpeed = 60;
	maxSpinSpeed = 600;

	// lifetime...
	lifetime = 20.0;
	lifetimeVariance = 0.0;
};

datablock ExplosionData(FrmSoldierSpawnExplosion)
{
	soundProfile = FrmSoldierSpawnExplosionSound;

	faceViewer	  = true;
	explosionScale = "0.8 0.8 0.8";

	lifetimeMS = 200;

//	debris = FrmSoldierSpawnExplosion_LargeDebris;
//	debrisThetaMin = 0;
//	debrisThetaMax = 60;
//	debrisNum = 5;
//	debrisVelocity = 30.0;
//	debrisVelocityVariance = 10.0;

//	particleEmitter = FrmSoldierSpawnExplosion_CloudEmitter;
//	particleDensity = 100;
//	particleRadius = 4;

	emitter[0] = FrmSoldierSpawnExplosion_DustEmitter;
	emitter[1] = FrmSoldierSpawnExplosion_SmokeEmitter;
	//emitter[2] = FrmSoldierSpawnExplosion_SparksEmitter;

	// Camera shake
	shakeCamera = true;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 18;
	lightEndRadius = 0;
	lightStartColor = "1.0 1.0 0.0";
	lightEndColor = "0.0 0.0 0.0";
};

