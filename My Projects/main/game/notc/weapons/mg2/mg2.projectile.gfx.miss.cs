// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnMG2ProjectileMissEnemyEffect_CloudParticles)
{
	dragCoeffiecient	  = 1.0;
	gravityCoefficient	= -0.0;
	inheritedVelFactor	= 0.0;

	lifetimeMS			  = 500;
	lifetimeVarianceMS	= 200;

	useInvAlpha =  false;

   textureName = "content/o/rotc/p.5.4/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 0.25";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 1.0;

	allowLighting = false;
   renderDot = true;
};

datablock ParticleEmitterData(WpnMG2ProjectileMissEnemyEffect_CloudEmitter)
{
	ejectionOffset	= 0;

	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 0.0;
	velocityVariance = 0.0;

	thetaMin			= 90.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 50;

	particles = "WpnMG2ProjectileMissEnemyEffect_CloudParticles";
};

datablock ExplosionData(WpnMG2ProjectileMissEnemyEffect)
{
	soundProfile = WpnMG2ProjectileMissEnemySoundList;

	// shape...
	//explosionShape = "share/shapes/rotc/effects/explosion5.green.dts";
	faceViewer	  = true;
	playSpeed = 4.0;
	sizes[0] = "0.01 0.01 0.01";
	sizes[1] = "0.07 0.07 0.07";
	times[0] = 0.0;
	times[1] = 1.0;

	particleEmitter = WpnMG2ProjectileMissEnemyEffect_CloudEmitter;
	particleDensity = 10;
	particleRadius = 0.25;

	//emitter[0] = RedMinigunProjectileImpact_SmokeEmitter;

	// dynamic light...
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "0.0 0.0 0.0";
	lightEndColor = "0.0 0.0 0.0";
};

