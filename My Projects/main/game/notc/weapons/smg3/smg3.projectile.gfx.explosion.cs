// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnSMG3ProjectileExplosion_Smoke)
{
	dragCoeffiecient	  = 1;
	gravityCoefficient	= "0";
	inheritedVelFactor	= 0.0;

	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 200;

	useInvAlpha =  false;

	textureName = "content/o/rotc/p.5.4/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= "0.997986";
	sizes[1]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 1.0;

	allowLighting = 0;
   renderDot = 0;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/corona.png";
   times[2] = "1";
};

datablock ParticleEmitterData(WpnSMG3ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = "10";
	velocityVariance = "3";
	ejectionOffset	= 0.0;
	thetaMin			= "0";
	thetaMax			= "180";
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = 0;
	orientParticles  = false;
	lifetimeMS		 = 50;
	particles = "WpnSMG3ProjectileExplosion_Smoke";
   paletteSlot = 0;
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
};

datablock ExplosionData(WpnSMG3ProjectileExplosion)
{
	//soundProfile = WpnSMG3ProjectileImpactSound;

	lifetimeMS = "288";

	// shape...
	//explosionShape = "content/o/rotc/p.5.4/shapes/rotc/effects/explosion5.green.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0 0 0";
	sizes[1] = "0.19 0.19 0.19";
	times[0] = 0.0;
	times[1] = 1.0;

	emitter[0] = "WpnSMG3ProjectileExplosion_SmokeEmitter";

	//debris = WpnSMG3ProjectileExplosion_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 60;
	//debrisNum = 1;
	//debrisNumVariance = 1;
	//debrisVelocity = 10.0;
	//debrisVelocityVariance = 5.0;

	// Dynamic light
	lightStartRadius = 4;
	lightEndRadius = 0;
	lightStartColor = "1 1 1 1.0";
	lightEndColor = "1 1 1 1.0";

	shakeCamera = false;
   lightStartBrightness = "0.941176";
   lightEndBrightness = "0.941176";
   targetLockTimeMS = "480";
};
