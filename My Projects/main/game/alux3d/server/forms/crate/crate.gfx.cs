// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmCrate_DamageEmitter_Particle)
{
	spinSpeed = 200;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;
	dragCoefficient		= 1;
	gravityCoefficient	= 3.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	textureName = "content/xa/rotc/p.5.4/textures/rotc/corona";
	colors[0]	  = "1.0 1.0 0.0 1.0";
	colors[1]	  = "1.0 1.0 0.0 1.0";
	colors[2]	  = "1.0 1.0 0.0 0.0";
	sizes[0]		= 0.3;
	sizes[1]		= 0.3;
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	renderDot = true;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmCrate_DamageEmitter)
{
	ejectionPeriodMS = 10;
	periodVarianceMS = 0;
	ejectionVelocity = 15.0;
	velocityVariance = 5.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 50;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = 0; // forever
	lifetimeVarianceMS = 0;
	overrideAdvances = false;
	orientParticles  = false;
	particles = "FrmCrate_DamageEmitter_Particle";
};

//-----------------------------------------------------------------------------
// Materialize effect

datablock ParticleData(FrmCrateMaterializeExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 600;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";

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

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_CloudEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "FrmCrateMaterializeExplosion_Cloud";
};

datablock ParticleData(FrmCrateMaterializeExplosion_Dust)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= -0.01;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	useInvAlpha			 = false;
	//spinRandomMin		  = -90.0;
	//spinRandomMax		  = 500.0;
	textureName			 = "share/shapes/alux/light.png";
	colors[0]	  = "1 1 1 1";
	colors[1]	  = "1 1 1 1";
	colors[2]	  = "1 1 1 0";
	sizes[0]		= 3.2;
	sizes[1]		= 4.6;
	sizes[2]		= 5.0;
	times[0]		= 0.0;
	times[1]		= 0.7;
	times[2]		= 1.0;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_DustEmitter)
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
	particles = "FrmCrateMaterializeExplosion_Dust";
};


datablock ParticleData(FrmCrateMaterializeExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.5;	// rises slowly
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 1250;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";

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

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 250;

	particles = "FrmCrateMaterializeExplosion_Smoke";
};

datablock ParticleData(FrmCrateMaterializeExplosion_Sparks)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 1.0;
	inheritedVelFactor	= 0.2;
	constantAcceleration = 0.0;
	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 350;
	textureName			 = "share/shapes/alux/light.png";
	colors[0]	  = "1 1 1 1";
	colors[1]	  = "1 1 1 1";
	colors[2]	  = "1 1 1 0";
	sizes[0]		= 0.5;
	sizes[1]		= 0.5;
	sizes[2]		= 0.75;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_SparksEmitter)
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
	particles = "FrmCrateMaterializeExplosion_Sparks";
};

datablock DebrisData(FrmCrateMaterializeExplosion_SmallDebris)
{
	// shape...
	shapeFile = "share/shapes/rotc/misc/debris1.white.dts";

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

datablock MultiNodeLaserBeamData(FrmCrateMaterializeExplosion_LargeDebris_LaserTrail)
{
	hasLine = true;
	lineColor	= "1.00 1.00 1.00 0.5";

	hasInner = false;
	innerColor = "1.00 1.00 0.00 0.3";
	innerWidth = "0.20";

	hasOuter = true;
	outerColor = "1.00 1.00 1.00 0.2";
	outerWidth = "0.40";

//	bitmap = "share/shapes/rotc/weapons/missilelauncher/explosion.trail";
//	bitmapWidth = 0.25;

	blendMode = 1;
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
	fadeTime = 1000;
};

datablock ParticleData(FrmCrateMaterializeExplosion_LargeDebris_Particles2)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/cross1";
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

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_LargeDebris_Emitter2)
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
	particles = "FrmCrateMaterializeExplosion_LargeDebris_Particles2";
};

datablock ParticleData(FrmCrateMaterializeExplosion_LargeDebris_Particles1)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 100;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/cross1";
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

datablock ParticleEmitterData(FrmCrateMaterializeExplosion_LargeDebris_Emitter1)
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
	particles = "FrmCrateMaterializeExplosion_LargeDebris_Particles1";
};

datablock ExplosionData(FrmCrateMaterializeExplosion_LargeDebris_Explosion)
{
	soundProfile	= MissileLauncherDebrisSound;

	debris = FrmCrateMaterializeExplosion_SmallDebris;
	debrisThetaMin = 0;
	debrisThetaMax = 60;
	debrisNum = 5;
	debrisVelocity = 15.0;
	debrisVelocityVariance = 10.0;
};

datablock DebrisData(FrmCrateMaterializeExplosion_LargeDebris)
{
	// shape...
	shapeFile = "share/shapes/rotc/misc/debris2.white.dts";

	explosion = FrmCrateMaterializeExplosion_LargeDebris_Explosion;

	//laserTrail = FrmCrateMaterializeExplosion_LargeDebris_LaserTrail;
	emitters[0] = FrmCrateMaterializeExplosion_LargeDebris_Emitter2;
	//emitters[1] = FrmCrateMaterializeExplosion_LargeDebris_Emitter1;

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

datablock ExplosionData(FrmCrateMaterializeExplosion)
{
	soundProfile = FrmCrateMaterializeSound;

	faceViewer	  = true;
	explosionScale = "0.8 0.8 0.8";

	lifetimeMS = 200;

//	debris = FrmCrateMaterializeExplosion_LargeDebris;
//	debrisThetaMin = 0;
//	debrisThetaMax = 60;
//	debrisNum = 5;
//	debrisVelocity = 30.0;
//	debrisVelocityVariance = 10.0;

	particleEmitter = FrmCrateMaterializeExplosion_CloudEmitter;
	particleDensity = 50;
	particleRadius = 3;

//	emitter[0] = FrmCrateMaterializeExplosion_SparksEmitter;
//	emitter[1] = FrmCrateMaterializeExplosion_DustEmitter;
//	emitter[2] = FrmCrateMaterializeExplosion_SmokeEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "1.0 1.0 0.0";
	lightEndColor = "0.0 0.0 0.0";
};

//-----------------------------------------------------------------------------
// Dematerialize effect

datablock ParticleData(FrmCrateDematerializeExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 600;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";

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

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_CloudEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "FrmCrateDematerializeExplosion_Cloud";
};

datablock ParticleData(FrmCrateDematerializeExplosion_Dust)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= -0.01;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	useInvAlpha			 = false;
	//spinRandomMin		  = -90.0;
	//spinRandomMax		  = 500.0;
	textureName			 = "share/shapes/alux/light.png";
	colors[0]	  = "1 1 1 1";
	colors[1]	  = "1 1 1 1";
	colors[2]	  = "1 1 1 0";
	sizes[0]		= 3.2;
	sizes[1]		= 4.6;
	sizes[2]		= 5.0;
	times[0]		= 0.0;
	times[1]		= 0.7;
	times[2]		= 1.0;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_DustEmitter)
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
	particles = "FrmCrateDematerializeExplosion_Dust";
};


datablock ParticleData(FrmCrateDematerializeExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.5;	// rises slowly
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 1250;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";

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

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 250;

	particles = "FrmCrateDematerializeExplosion_Smoke";
};

datablock ParticleData(FrmCrateDematerializeExplosion_Sparks)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 1.0;
	inheritedVelFactor	= 0.2;
	constantAcceleration = 0.0;
	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 350;
	textureName			 = "share/shapes/alux/light.png";
	colors[0]	  = "1 1 1 1";
	colors[1]	  = "1 1 1 1";
	colors[2]	  = "1 1 1 0";
	sizes[0]		= 0.5;
	sizes[1]		= 0.5;
	sizes[2]		= 0.75;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_SparksEmitter)
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
	particles = "FrmCrateDematerializeExplosion_Sparks";
};

datablock DebrisData(FrmCrateDematerializeExplosion_SmallDebris)
{
	// shape...
	shapeFile = "share/shapes/rotc/misc/debris1.white.dts";

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

datablock MultiNodeLaserBeamData(FrmCrateDematerializeExplosion_LargeDebris_LaserTrail)
{
	hasLine = true;
	lineColor	= "1.00 1.00 1.00 0.5";

	hasInner = false;
	innerColor = "1.00 1.00 0.00 0.3";
	innerWidth = "0.20";

	hasOuter = true;
	outerColor = "1.00 1.00 1.00 0.2";
	outerWidth = "0.40";

//	bitmap = "share/shapes/rotc/weapons/missilelauncher/explosion.trail";
//	bitmapWidth = 0.25;

	blendMode = 1;
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
	fadeTime = 1000;
};

datablock ParticleData(FrmCrateDematerializeExplosion_LargeDebris_Particles2)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/cross1";
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

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_LargeDebris_Emitter2)
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
	particles = "FrmCrateDematerializeExplosion_LargeDebris_Particles2";
};

datablock ParticleData(FrmCrateDematerializeExplosion_LargeDebris_Particles1)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient		= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 100;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/cross1";
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

datablock ParticleEmitterData(FrmCrateDematerializeExplosion_LargeDebris_Emitter1)
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
	particles = "FrmCrateDematerializeExplosion_LargeDebris_Particles1";
};

datablock ExplosionData(FrmCrateDematerializeExplosion_LargeDebris_Explosion)
{
	soundProfile	= MissileLauncherDebrisSound;

	debris = FrmCrateDematerializeExplosion_SmallDebris;
	debrisThetaMin = 0;
	debrisThetaMax = 60;
	debrisNum = 5;
	debrisVelocity = 15.0;
	debrisVelocityVariance = 10.0;
};

datablock DebrisData(FrmCrateDematerializeExplosion_LargeDebris)
{
	// shape...
	shapeFile = "share/shapes/rotc/misc/debris2.white.dts";

	explosion = FrmCrateDematerializeExplosion_LargeDebris_Explosion;

	//laserTrail = FrmCrateDematerializeExplosion_LargeDebris_LaserTrail;
	emitters[0] = FrmCrateDematerializeExplosion_LargeDebris_Emitter2;
	//emitters[1] = FrmCrateDematerializeExplosion_LargeDebris_Emitter1;

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

datablock ExplosionData(FrmCrateDematerializeExplosion)
{
	soundProfile = FrmCrateDematerializeSound;

	faceViewer	  = true;
	explosionScale = "0.8 0.8 0.8";

	lifetimeMS = 200;

//	debris = FrmCrateDematerializeExplosion_LargeDebris;
//	debrisThetaMin = 0;
//	debrisThetaMax = 60;
//	debrisNum = 5;
//	debrisVelocity = 30.0;
//	debrisVelocityVariance = 10.0;

	particleEmitter = FrmCrateDematerializeExplosion_CloudEmitter;
	particleDensity = 50;
	particleRadius = 3;

//	emitter[0] = FrmCrateDematerializeExplosion_SparksEmitter;
//	emitter[1] = FrmCrateDematerializeExplosion_DustEmitter;
//	emitter[2] = FrmCrateDematerializeExplosion_SmokeEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "1.0 1.0 0.0";
	lightEndColor = "0.0 0.0 0.0";
};




