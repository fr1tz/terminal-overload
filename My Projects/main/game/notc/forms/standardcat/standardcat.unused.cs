// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmStandardcatSkidTrailEmitter0_Particle)
{
	dragCoefficient		= 0.0;
	gravityCoefficient	= 3.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 350;
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.5";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 0.5;
	sizes[1]		= 0.5;
	sizes[2]		= 0.5;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/o/rotc/p.5.4/textures/rotc/spark00";
	useInvAlpha = false;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatSkidTrailEmitter0)
{
	ejectionPeriodMS = 2;
	periodVarianceMS = 0;
	ejectionVelocity = 10;
	velocityVariance = 5;
	ejectionOffset	= 0.0;
	thetaMin			= 20;
	thetaMax			= 50;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = true;
	lifetimeMS		 = 0; // forever
	particles = FrmStandardcatSkidTrailEmitter0_Particle;
};

datablock ParticleData(FrmStandardcatSkidTrailEmitter1_Particle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 350;
	colors[0]	  = "0.5 0.5 0.5 1.0";
	colors[1]	  = "0.5 0.5 0.5 0.5";
	colors[2]	  = "0.5 0.5 0.5 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/o/rotc/p.5.4/textures/rotc/smoke_particle";
	useInvAlpha = true;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatSkidTrailEmitter1)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 0;
	velocityVariance = 0;
	ejectionOffset	= 0.25;
	thetaMin			= 90;
	thetaMax			= 90;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0; // forever
	particles = FrmStandardcatSkidTrailEmitter1_Particle;
};

//------------------------------------------------------------------------------
// damage particle emitter

datablock ParticleData(FrmStandardcatDamageEmitter_Particle)
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
	textureName = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.red";
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 0.25;
	sizes[1]		= 0.25;
	sizes[2]		= 0.25;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatDamageEmitter)
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
	orientParticles  = true;
	particles = "FrmStandardcatDamageEmitter_Particle";
};

//------------------------------------------------------------------------------
// buffer damage particle emitter

datablock ParticleData(FrmStandardcatBufferDamageEmitter_Particle)
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
	textureName = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.white";
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 0.25;
	sizes[1]		= 0.25;
	sizes[2]		= 0.25;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatBufferDamageEmitter)
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
	orientParticles  = true;
	particles = "FrmStandardcatBufferDamageEmitter_Particle";
};

//------------------------------------------------------------------------------
// damage debris...

datablock DebrisData(FrmStandardcatDamageDebris)
{
    // 2d billboard...
    render2D = true;
    texture = "content/o/rotc/p.5.4/textures/rotc/halo1.red.png";
    textureWidth = 0.5;

	// shape...
	shapeFile = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.red.dts";

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
	lifetime = 4.0;
	lifetimeVariance = 1.0;
};

//------------------------------------------------------------------------------
// buffer damage debris...

datablock DebrisData(FrmStandardcatBufferDamageDebris)
{
    // 2d billboard...
    render2D = true;
    texture = "content/o/rotc/p.5.4/textures/rotc/halo1.white.png";
    textureWidth = 0.5;

	// shape...
	shapeFile = "content/o/rotc/p.5.4/shapes/rotc/misc/debris1.white.dts";

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

//------------------------------------------------------------------------------
// buffer repair particle emitter...

datablock ParticleData(FrmStandardcatBufferRepairEmitter_Particle)
{
	dragCoefficient		= 0.0;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 220;
	lifetimeVarianceMS	= 0;
	colors[0]	  = "1.0 1.0 1.0 0.0";
	colors[1]	  = "1.0 1.0 1.0 1.0";
	colors[2]	  = "1.0 1.0 1.0 1.0";
	sizes[0]		= 3.0;
	sizes[1]		= 2.0;
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	spinRandomMin = 0.0;
	spinRandomMax = 0.0;
	textureName	= "content/o/rotc/p.5.4/textures/rotc/cross1";
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatBufferRepairEmitter)
{
	ejectionPeriodMS = 10;
	periodVarianceMS = 0;
	ejectionVelocity = -20.0;
	velocityVariance = 0;
	ejectionOffset	= 4.0;
	thetaMin			= 30;
	thetaMax			= 70;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvance  = false;
	orientParticles  = false;
	lifetimeMS		 = 0; // forever
	particles = FrmStandardcatBufferRepairEmitter_Particle;
};

