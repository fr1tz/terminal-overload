// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmStandardcatSkidFootEmitter_Particle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 2.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 300;
	lifetimeVarianceMS	= 100;
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 0.0 0.5";
	colors[2]	  = "1.0 1.0 0.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/rotc/p.5.3/textures/rotc/dustParticle";
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatSkidFootEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 1;
	velocityVariance = 0;
	ejectionOffset	= 0.75;
	thetaMin			= 20;
	thetaMax			= 50;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0; // forever
	particles = FrmStandardcatSkidFootEmitter_Particle;
};

//------------------------------------------------------------------------------

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
	textureName	= "content/rotc/p.5.3/textures/rotc/spark00";
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
	textureName	= "content/rotc/p.5.3/textures/rotc/smoke_particle";
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

