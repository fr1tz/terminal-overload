// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSG2ProjectileDecal)
{
   Material = "DECAL_RocketEXP";
   size = "1";
   lifeSpan = "5000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "3";
   textureCoords[0] = "0 0 0.5 0.5";
   textureCoords[1] = "0.5 0 0.5 0.5";
   textureCoords[2] = "0 0.5 0.5 0.5";
   textureCoords[3] = "0.5 0.5 0.5 0.5";
};

//-----------------------------------------------------------------------------
// laser trail

datablock MultiNodeLaserBeamData(WpnSG2ProjectileLaserTrail0)
{
	material = "xa_notc_core_shapes_sg2_projectile_p1_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.1;
	fadeTime = 150;
	windCoefficient = 0.0;

	// node x movement...
	nodeMoveMode[0]     = $NodeMoveMode::None;
	nodeMoveSpeed[0]    = -0.002;
	nodeMoveSpeedAdd[0] =  0.004;
	// node y movement...
	nodeMoveMode[1]     = $NodeMoveMode::None;
	nodeMoveSpeed[1]    = -0.002;
	nodeMoveSpeedAdd[1] =  0.004;
	// node z movement...
	nodeMoveMode[2]     = $NodeMoveMode::None;
	nodeMoveSpeed[2]    = 0.5;
	nodeMoveSpeedAdd[2] = 0.5;
};

//-----------------------------------------------------------------------------
// explosion

datablock ParticleData(WpnSG2ProjectileExplosion_Dust)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= -0.01;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 2000;
	lifetimeVarianceMS	= 100;
	useInvAlpha			 = true;
	spinRandomMin		  = -90.0;
	spinRandomMax		  = 500.0;
	textureName			 = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";
	colors[0]	  = "0.9 0.9 0.9 0.5";
	colors[1]	  = "0.9 0.9 0.9 0.5";
	colors[2]	  = "0.9 0.9 0.9 0.0";
	sizes[0]		= 0.9;
	sizes[1]		= 1.5;
	sizes[2]		= 1.6;
	times[0]		= 0.0;
	times[1]		= 0.7;
	times[2]		= 1.0;
	allowLighting = true;
};

datablock ParticleEmitterData(WpnSG2ProjectileExplosion_DustEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 2.0;
	velocityVariance = 0.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 180;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	lifetimeMS		 = 50;
	particles = "WpnSG2ProjectileExplosion_Dust";
};


datablock ParticleData(WpnSG2ProjectileExplosion_Smoke)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= -0.1;	// rises slowly
	inheritedVelFactor	= "0";

	lifetimeMS			  = "2000";
	lifetimeVarianceMS	= 0;

	useInvAlpha =  true;
	spinRandomMin = -200.0;
	spinRandomMax =  200.0;

	textureName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";

	colors[0]	  = "0.4 0.4 0.4 0.519";
	colors[1]	  = "0.4 0.4 0.4 0.2";
	colors[2]	  = "0.4 0.4 0.4 0.0";
	sizes[0]		= "5";
	sizes[1]		= "5";
	sizes[2]		= "5";
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";
   allowLighting = "0";
   constantAcceleration = "-0.42";
   dragCoefficient = "0";
   ejectionPeriodMS = "1";
   ejectionVelocity = "30";
   velocityVariance = "10";
   thetaMax = "180";
   particles = "WpnSG2ProjectileExplosion_Smoke";
   blendStyle = "NORMAL";
   targetLockTimeMS = "480";
};

datablock ParticleEmitterData(WpnSG2ProjectileExplosion_SmokeEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;

	ejectionVelocity = "10";
	velocityVariance = "0";

	thetaMin			= 0.0;
	thetaMax			= 180.0;

	lifetimeMS		 = 50;

	particles = "WpnSG2ProjectileExplosion_Smoke";
   blendStyle = "NORMAL";
   targetLockTimeMS = "480";
};

datablock ParticleData(WpnSG2ProjectileExplosion_DebrisParticles)
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
	sizes[0]		= 0.55;
	sizes[1]		= 0.55;
	sizes[2]		= 0.55;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	useInvAlpha =  false;
	allowLighting = false;
};

datablock ParticleEmitterData(WpnSG2ProjectileExplosion_DebrisEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;
	ejectionVelocity = 30.0;
	velocityVariance = 20.0;
	ejectionOffset	= 0.0;
	thetaMin			= 0;
	thetaMax			= 60;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	lifetimeMS		 = 8;
	lifetimeVarianceMS = 0;
	overrideAdvances = false;
	orientParticles  = true;
	particles = "WpnSG2ProjectileExplosion_DebrisParticles";
};

datablock ExplosionData(WpnSG2ProjectileExplosion)
{
	soundProfile = WpnSG2ProjectileExplosionSound;

	lifetimeMS = "192";

 	// shape...
	//explosionShape = "share/shapes/rotc/effects/explosion2_white.dts";
	//faceViewer	  = false;
	//playSpeed = 8.0;
	//sizes[0] = "0.2 0.2 0.2";
	//sizes[1] = "0.2 0.2 0.2";
	//times[0] = 0.0;
	//times[1] = 1.0;

	//debris = WpnSG2ProjectileExplosion_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 180;
	//debrisNum = 3;
	//debrisNumVariance = 0;
	//debrisVelocity = 50.0;
	//debrisVelocityVariance = 10.0;

//	particleEmitter = WpnSG2ProjectileExplosion_CloudEmitter;
	particleDensity = 25;
	particleRadius = 0.5;

	emitter[0] = WpnSG2ProjectileExplosion_SmokeEmitter;
	emitter[1] = WpnSG2ProjectileExplosion_DebrisEmitter;
//	emitter[1] = WpnSG2ProjectileExplosion_DustEmitter;
//	emitter[2] = WpnSG2ProjectileExplosion_SparksEmitter;

	// Camera shake
	shakeCamera = true;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16";
   lightEndBrightness = "16.1569";
   debrisNum = "7";
   debrisVelocity = "40";
   targetLockTimeMS = "480";
};

//-----------------------------------------------------------------------------
// impact

datablock ExplosionData(WpnSG2ProjectileImpact : WpnSG2ProjectileExplosion)
{
	soundProfile = WpnSG2ProjectileExplosionSound;
	debrisThetaMax = 60;
	emitter[2] = DefaultMediumWhiteDebrisEmitter;
};


datablock ParticleData(WpnSG2ProjectileExplosion_Smoke)
{
   dragCoefficient = "0";
   gravityCoefficient = "-0.1";
   inheritedVelFactor = "0";
   lifetimeMS = "2000";
   spinRandomMin = "-200";
   spinRandomMax = "200";
   useInvAlpha = "1";
   textureName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle.png";
   colors[0] = "0.4 0.4 0.4 0.519";
   colors[1] = "0.4 0.4 0.4 0.2";
   colors[2] = "0.4 0.4 0.4 0";
   sizes[0] = "8";
   sizes[1] = "10";
   sizes[2] = "12";
   times[1] = "0.5";
   times[2] = "1";
   allowLighting = "0";
   dragCoeffiecient = "0.4";
   constantAcceleration = "-0.42";
};
