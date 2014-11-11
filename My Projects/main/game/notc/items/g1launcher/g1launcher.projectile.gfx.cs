// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// projectile particle emitter

datablock ParticleData(ItemG1LauncherProjectile_ParticleEmitter_Particles)
{
   dragCoefficient      = 0;
   gravityCoefficient   = 0.0;
   windCoefficient      = 0.0;
   inheritedVelFactor   = 0.0;
   constantAcceleration = 0.0;
   lifetimeMS           = 400;
   lifetimeVarianceMS   = 100;
   textureName          = "content/xa/rotc/p.5.4/textures/rotc/ring1";
   colors[0]     = "1.0 1.0 1.0 1.0";
   colors[1]     = "1.0 1.0 1.0 0.5";
   colors[2]     = "1.0 1.0 1.0 0.0";
   sizes[0]      = 0.90;
   sizes[1]      = 0.70;
   sizes[2]      = 0.50;
   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(ItemG1LauncherProjectile_ParticleEmitter)
{
   ejectionPeriodMS = 5;
   periodVarianceMS = 0;
   ejectionVelocity = 3;
   velocityVariance = 2;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 180;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   overrideAdvances = false;
   orientParticles  = false;
   lifetimeMS       = 0;
   particles = "ItemG1LauncherProjectile_ParticleEmitter_Particles";
   paletteSlot = 0;
};

//-----------------------------------------------------------------------------
// bounce

datablock ExplosionData(ItemG1LauncherProjectileBounceEffect)
{
    soundProfile = ItemG1LauncherProjectileBounceSound;
};

//-----------------------------------------------------------------------------
// explosion

datablock ParticleData(ItemG1LauncherProjectileExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= 0.025;

	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 0;

	useInvAlpha =  false;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 12.0;
	sizes[1]		= 9.0;
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 0.25;
	times[2]		= 1.0;
};

datablock ParticleEmitterData(ItemG1LauncherProjectileExplosion_CloudEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = 6.25;
	velocityVariance = 0.25;

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "ItemG1LauncherProjectileExplosion_Cloud";
 
   paletteSlot = 0;
};

datablock ExplosionData(ItemG1LauncherProjectileExplosion)
{
	soundProfile = ItemG1LauncherProjectileExplosionSound;

	faceViewer	  = true;
	explosionScale = "0.8 0.8 0.8";

	lifetimeMS = 200;

	particleEmitter = ItemG1LauncherProjectileExplosion_CloudEmitter;
	particleDensity = 300;
	particleRadius = 15;

	//emitter[0] = ItemG1LauncherProjectileExplosion_DustEmitter;
	//emitter[1] = ItemG1LauncherProjectileExplosion_SmokeEmitter;
	//emitter[2] = ItemG1LauncherProjectileExplosion_SparksEmitter;

	// Camera shake
	shakeCamera = false;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 15;
	lightEndRadius = 0;
	lightStartColor = "1.0 1.0 1.0";
	lightEndColor = "0.0 0.0 0.0";
};

