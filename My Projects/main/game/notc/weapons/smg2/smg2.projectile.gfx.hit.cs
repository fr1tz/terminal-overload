// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnSMG2ProjectileImpactExplosion_DebrisParticles)
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
	sizes[0]		= 0.25;
	sizes[1]		= 0.25;
	sizes[2]		= 0.25;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = false;
};

datablock ParticleEmitterData(WpnSMG2ProjectileImpactExplosion_DebrisEmitter)
{
	ejectionPeriodMS = 50;
	periodVarianceMS = 0;
	ejectionVelocity = 10.0;
	velocityVariance = 5.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = 5;
	lifetimeVarianceMS = 0;
	overrideAdvances = false;
	orientParticles  = true;
	particles = "WpnSMG2ProjectileImpactExplosion_DebrisParticles";
};


datablock ExplosionData(WpnSMG2ProjectileHit)
{
	soundProfile = WpnSMG2ProjectileImpactSound;

	lifetimeMS = "192";

	// shape...
	//explosionShape = "content/xa/notc/core/shapes/mgl1/impactdmg/p1/shape.dae";
	faceViewer	  = false;
	playSpeed = 4.0;
	sizes[0] = "1.0 1.0 1.0";
	sizes[1] = "0.0 0.0 0.0";
	times[0] = 0.0;
	times[1] = 1.0;

	//emitter[0] = WpnSMG2ProjectileImpact_DebrisEmitter;
	//emitter[1] = WpnSMG2ProjectileImpact_SmokeEmitter;
   emitter[2] = WpnSMG2ProjectileExplosion_CloudEmitter;

	//debris = WpnSMG2ProjectileImpact_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 60;
	//debrisNum = 1;
	//debrisNumVariance = 1;
	//debrisVelocity = 10.0;
	//debrisVelocityVariance = 5.0;

	// Dynamic light
	lightStartRadius = 4;
	lightEndRadius = 0;
	lightStartColor = "0.992126 0.992126 0.992126 1";
	lightEndColor = "0.992126 0.992126 0.992126 1";
   lightCastShadows = 0;

	shakeCamera = false;
   lightStartBrightness = "0.941176";
   lightEndBrightness = "0.941176";
};


