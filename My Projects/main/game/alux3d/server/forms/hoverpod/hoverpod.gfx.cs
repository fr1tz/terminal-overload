// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmHoverpodSlideContactTrailEmitter_Particle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 350;
	colors[0]	  = "0.7 0.7 0.7 1.0";
	colors[1]	  = "0.7 0.7 0.7 0.5";
	colors[2]	  = "0.7 0.7 0.7 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/rotc/p.5.3/textures/rotc/dustParticle";
	useInvAlpha = true;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmHoverpodSlideContactTrailEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 2;
	velocityVariance = 1;
	ejectionOffset	= 0.75;
	thetaMin			= 90;
	thetaMax			= 90;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0; // forever
	particles = FrmHoverpodSlideContactTrailEmitter_Particle;
};