// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// fire particle emitter

datablock ParticleData(WpnMG1FireEmitter_Particles)
{
	dragCoefficient       = 1;
	gravityCoefficient    = 0.0;
	windCoefficient       = 0.0;
	inheritedVelFactor    = 0.5;
	constantAcceleration  = 0.0;
	lifetimeMS            = 50;
	lifetimeVarianceMS    = 0;
	textureName           = "content/rotc/p.5.4/textures/rotc/smoke_particle";
	colors[0]             = "1.0 1.0 1.0 1.0";
	colors[1]             = "1.0 1.0 1.0 1.0";
	colors[2]             = "1.0 1.0 1.0 0.0";
	sizes[0]              = 0.3;
	sizes[1]              = 0.3;
	sizes[2]              = 0.0;
	times[0]              = 0.0;
	times[1]              = 0.5;
	times[2]              = 1.0;

};

datablock ParticleEmitterData(WpnMG1FireEmitter)
{
	ejectionPeriodMS = 10;
	periodVarianceMS = 0;
	ejectionVelocity = 20.0;
	velocityVariance = 0.2;
	ejectionOffset   = 0;
	thetaMin         = 0;
	thetaMax         = 0;
	phiReferenceVel  = 0;
	phiVariance      = 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS       = 0;
	particles        = "WpnMG1FireEmitter_Particles";
};

