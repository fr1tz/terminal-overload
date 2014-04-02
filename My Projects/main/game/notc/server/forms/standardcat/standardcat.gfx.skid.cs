// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmStandardcatSkidFootEmitter0_Particle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 2.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 100;
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.5";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/xa/rotc/p.5.4/textures/rotc/dustParticle";
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatSkidFootEmitter0)
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
	particles = FrmStandardcatSkidFootEmitter0_Particle;
};

datablock ParticleData(FrmStandardcatSkidFootEmitter1_Particle)
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
	textureName	= "content/xa/notc/core/textures/spark02";
	useInvAlpha = false;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmStandardcatSkidFootEmitter1)
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
	particles = FrmStandardcatSkidFootEmitter1_Particle;
};

//------------------------------------------------------------------------------

datablock ParticleData(FrmStandardcatSkidTrailEmitter0_Particle)
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
	textureName = "content/xa/rotc/p.5.4/shapes/rotc/misc/debris1.white";
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

datablock ParticleEmitterData(FrmStandardcatSkidTrailEmitter0)
{
	ejectionPeriodMS = "10";
	periodVarianceMS = 0;
	ejectionVelocity = "10";
	velocityVariance = 5.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = "0";
	lifetimeVarianceMS = 0;
	overrideAdvances = 0;
	orientParticles  = true;
	particles = "FrmStandardcatSkidTrailEmitter0_Particle";
   blendStyle = "ADDITIVE";
};

