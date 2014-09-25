// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnMG2ProjectileProximityExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 250;
	lifetimeVarianceMS	= 0;

	useInvAlpha = false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.5";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 3.0;
	sizes[1]		= 1.5;
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;

	allowLighting = false;
};

datablock ParticleEmitterData(WpnMG2ProjectileProximityExplosion_CloudEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;

	ejectionVelocity = 0.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "WpnMG2ProjectileProximityExplosion_Cloud";
 
   paletteSlot = 0;
};

datablock ParticleData(WpnMG2ProjectileProximityExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.1;	// rises slowly
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 2000;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";

	colors[0]	  = "0.4 0.4 0.4 0.4";
	colors[1]	  = "0.4 0.4 0.4 0.2";
	colors[2]	  = "0.4 0.4 0.4 0.0";
	sizes[0]		= 0.0;
	sizes[1]		= 2.0;
	sizes[2]		= 0.6;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;

	allowLighting = false;
};

datablock ParticleEmitterData(WpnMG2ProjectileProximityExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 20;
	periodVarianceMS = 0;

	ejectionVelocity = 2.0;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 50;

	particles = "WpnMG2ProjectileProximityExplosion_Smoke";
};

datablock ParticleData(WpnMG2ProjectileProximityExplosion_Shrapnel)
{
	dragCoefficient		= 1;
	gravityCoefficient	= 0.0;
	windCoefficient	= 0.0;
	inheritedVelFactor	= 0.2;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/corona.png";
	colors[0]	  = "1 1 1 1.0";
	colors[1]	  = "1 1 1 0.5";
	colors[2]	  = "1 1 1 0.0";
	sizes[0]		= 0.5;
	sizes[1]		= 0.5;
	sizes[2]		= 0.5;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	allowLighting = false;
	renderDot = false;
};

datablock ParticleEmitterData(WpnMG2ProjectileProximityExplosion_ShrapnelEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;
	ejectionVelocity = 5;
	velocityVariance = 0;
	ejectionOffset	= 1.0;
	thetaMin			= 0;
	thetaMax			= 180;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 50;
	particles = "WpnMG2ProjectileProximityExplosion_Shrapnel";
   paletteSlot = 0;
};

datablock ExplosionData(WpnMG2ProjectileProximityExplosion)
{
	soundProfile = WpnMG2ProjectileProximityExplosionSound;

	lifetimeMS = "192";

 	// shape...
	explosionShape = "content/xa/notc/core/shapes/mgl1/splashdmg/p1/shape.dae";
	faceViewer	  = false;
	playSpeed = 4.0;
	sizes[0] = "1.0 1.0 1.0";
	sizes[1] = "0.0 0.0 0.0";
	times[0] = 0.0;
	times[1] = 1.0;

	//debris = WpnMG2ProjectileProximityExplosion_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 180;
	//debrisNum = 3;
	//debrisNumVariance = 0;
	//debrisVelocity = 50.0;
	//debrisVelocityVariance = 10.0;

	particleEmitter = WpnMG2ProjectileProximityExplosion_CloudEmitter;
	particleDensity = 10;
	particleRadius = 0.5;

	emitter[0] = WpnMG2ProjectileProximityExplosion_SmokeEmitter;
//	emitter[1] = WpnMG2ProjectileProximityExplosion_ShrapnelEmitter;
//	emitter[1] = WpnMG2ProjectileProximityExplosion_DustEmitter;
//	emitter[2] = WpnMG2ProjectileProximityExplosion_SparksEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = "10";
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16.0784";
   lightEndBrightness = "16.1569";
};
