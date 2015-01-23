// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnSMG1ProjectileExplosion_Smoke)
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

datablock ParticleEmitterData(WpnSMG1ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 3;
	velocityVariance = 0;
	ejectionOffset	= 0.0;
	thetaMin			= 80;
	thetaMax			= 80;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 50;
	particles = "WpnSMG1ProjectileExplosion_Smoke";
   paletteSlot = 0;
};

datablock ParticleData(WpnSMG1ProjectileExplosion_DebrisParticles)
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

datablock ParticleEmitterData(WpnSMG1ProjectileExplosion_DebrisEmitter)
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
	particles = "WpnSMG1ProjectileExplosion_DebrisParticles";
};

datablock ParticleData(WpnSMG1ProjectileExplosion_CloudParticle : DefaultParticle)
{
   sizes[0] = "0";
   sizes[1] = "5";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   textureName = "content/o/rotc/p.5.4/textures/rotc/unnamed1.png";
   animTexName = "content/o/rotc/p.5.4/textures/rotc/unnamed1.png";
   lifetimeMS = "100";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   spinRandomMin = "-573";
   spinRandomMax = "541";
   colors[0] = "0.996078 0.996078 0.996078 0.556";
   colors[2] = "1 1 1 1";
   colors[3] = "1 1 1 1";
   inheritedVelFactor = "0";
   constantAcceleration = "0";
   useInvAlpha = "0";
   colors[1] = "0.996078 0.992157 0.996078 0";
};

datablock ParticleEmitterData(WpnSMG1ProjectileExplosion_CloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnSMG1ProjectileExplosion_CloudParticle";
   ejectionPeriodMS = "1";
   lifetimeMS = "1";
   originalName = "WpnSR1ProjectileExplosionCloudEmitter";
   thetaMax = "153";
   softnessDistance = "1";
   paletteSlot = 0;
};

datablock ExplosionData(WpnSMG1ProjectileExplosion)
{
	soundProfile = WpnSMG1ProjectileExplosionSound;

	lifetimeMS = "192";

	// shape...
	//explosionShape = "content/o/rotc/p.5.4/shapes/rotc/effects/explosion5.green.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0 0 0";
	sizes[1] = "0.20 0.20 0.20";
	times[0] = 0.0;
	times[1] = 1.0;

	emitter[0] = WpnSMG1ProjectileExplosion_DebrisEmitter;
	//emitter[1] = WpnSMG1ProjectileExplosion_SmokeEmitter;
   emitter[2] = WpnSMG1ProjectileExplosion_CloudEmitter;

	//debris = WpnSMG1ProjectileExplosion_Debris;
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

