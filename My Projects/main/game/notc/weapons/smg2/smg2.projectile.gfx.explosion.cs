// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnSMG2ProjectileExplosion_Smoke)
{
	dragCoeffiecient	  = 1;
	gravityCoefficient	= "0";
	inheritedVelFactor	= 0.0;

	lifetimeMS			  = "200";
	lifetimeVarianceMS	= "0";

	useInvAlpha =  false;

	textureName = "content/xa/notc/core/textures/circle.512.500.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1 1 1 1";
	sizes[0]		= "0.997986";
	sizes[1]		= 0.0;
	times[0]		= 0.0;
	times[1]		= 1.0;

	allowLighting = 0;
   renderDot = 0;
   animTexName = "content/xa/notc/core/textures/circle.512.500.png";
   times[2] = "1";
};

datablock ParticleEmitterData(WpnSMG2ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = "1";
	periodVarianceMS = 0;
	ejectionVelocity = "0";
	velocityVariance = 0;
	ejectionOffset	= 0.0;
	thetaMin			= 80;
	thetaMax			= 80;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = 0;
	orientParticles  = false;
	lifetimeMS		 = "1";
	particles = "WpnSMG2ProjectileExplosion_Smoke";
   paletteSlot = 0;
   blendStyle = "PREMULTALPHA";
   targetLockTimeMS = "480";
};


datablock ParticleData(WpnSMG2ProjectileExplosion_CloudParticle : DefaultParticle)
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

datablock ParticleEmitterData(WpnSMG2ProjectileExplosion_CloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnSMG2ProjectileExplosion_CloudParticle";
   ejectionPeriodMS = "1";
   lifetimeMS = "1";
   originalName = "WpnSR1ProjectileExplosionCloudEmitter";
   thetaMax = "153";
   softnessDistance = "1";
   paletteSlot = 0;
};

datablock ExplosionData(WpnSMG2ProjectileExplosion)
{
	lifetimeMS = "192";

	// shape...
	//explosionShape = "content/o/rotc/p.5.4/shapes/rotc/effects/explosion5.green.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0 0 0";
	sizes[1] = "0.20 0.20 0.20";
	times[0] = 0.0;
	times[1] = 1.0;

	emitter[0] = WpnSMG2ProjectileExplosion_SmokeEmitter;
	//emitter[1] = WpnSMG2ProjectileExplosion_SmokeEmitter;
   emitter[2] = WpnSMG2ProjectileExplosion_CloudEmitter;

	//debris = WpnSMG2ProjectileExplosion_Debris;
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

