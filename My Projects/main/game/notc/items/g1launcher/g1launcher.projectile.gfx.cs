// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// decal

datablock DecalData(ItemG1LauncherProjectile_Decal)
{
   Material = "xa_notc_core_shapes_g1launcher_decal_p1_mat";
   size = "40";
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
// laser trails

datablock MultiNodeLaserBeamData(ItemG1LauncherProjectile_LaserTrail0)
{
	material = "xa_notc_core_shapes_g1launcher_trail_p1_mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.5;
	fadeTime = 1000;
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
	nodeMoveMode[2]     = $NodeMoveMode::ConstantSpeed;
	nodeMoveSpeed[2]    = 0.5;
	nodeMoveSpeedAdd[2] = 0.5;

	nodeDistance = 2;
};

//-----------------------------------------------------------------------------
// projectile particle emitter

datablock ParticleData(ItemG1LauncherProjectile_ParticleEmitter_Particles)
{
   dragCoefficient      = 0;
   gravityCoefficient   = 0.0;
   windCoefficient      = 0.0;
   inheritedVelFactor   = 0.0;
   constantAcceleration = 0.0;
   lifetimeMS           = "1500";
   lifetimeVarianceMS   = "1000";
   textureName          = "content/o/rotc/p.5.4/textures/rotc/corona.png";
   colors[0]     = "1.0 1.0 1.0 1.0";
   colors[1]     = "1 1 1 0";
   colors[2]     = "1 1 1 0";
   sizes[0]      = "1";
   sizes[1]      = "2";
   sizes[2]      = 0.50;
   times[0]      = 0.0;
   times[1]      = "1";
   times[2]      = 1.0;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/corona.png";
};

datablock ParticleEmitterData(ItemG1LauncherProjectile_ParticleEmitter)
{
   ejectionPeriodMS = 5;
   periodVarianceMS = 0;
   ejectionVelocity = "1";
   velocityVariance = "0";
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = "40";
   phiReferenceVel  = 0;
   phiVariance      = 360;
   overrideAdvances = 0;
   orientParticles  = false;
   lifetimeMS       = 0;
   particles = "ItemG1LauncherProjectile_ParticleEmitter_Particles";
   paletteSlot = 0;
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
};

//-----------------------------------------------------------------------------
// bounce

datablock ExplosionData(ItemG1LauncherProjectileBounceEffect)
{
    soundProfile = ItemG1LauncherProjectileBounceSound;
    
	// Shape
	explosionShape = "content/xa/notc/core/shapes/sr2/explosion/p1/shape.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0.0 0.0 0.0";
	sizes[1] = "0.4 0.4 0.4";
	times[0] = 0.0;
	times[1] = 1.0;
};

//-----------------------------------------------------------------------------
// explosion

datablock ParticleData(ItemG1LauncherProjectileExplosion_Cloud)
{
	dragCoeffiecient	  = 0.4;
	gravityCoefficient	= 0;
	inheritedVelFactor	= "0";

	lifetimeMS			  = "500";
	lifetimeVarianceMS	= 0;

	useInvAlpha =  false;
	spinRandomMin = "-400";
	spinRandomMax =  "400";

	textureName = "content/o/rotc/p.5.4/textures/rotc/cross1.png";

	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.0";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 12.0;
	sizes[1]		= "0";
	sizes[2]		= 0.0;
	times[0]		= 0.0;
	times[1]		= "1";
	times[2]		= 1.0;
   animTexName = "content/o/rotc/p.5.4/textures/rotc/cross1.png";
   constantAcceleration = "0";
};

datablock ParticleEmitterData(ItemG1LauncherProjectileExplosion_CloudEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;

	ejectionVelocity = "0";
	velocityVariance = "0";

	thetaMin			= 0.0;
	thetaMax			= 90.0;

	lifetimeMS		 = 100;

	particles = "ItemG1LauncherProjectileExplosion_Cloud";
 
   paletteSlot = 0;
   blendStyle = "ADDITIVE";
   targetLockTimeMS = "480";
};

datablock ExplosionData(ItemG1LauncherProjectileExplosion)
{
	soundProfile = ItemG1LauncherProjectileExplosionSound;

	faceViewer	  = true;
	explosionScale = "0.8 0.8 0.8";

	lifetimeMS = 200;

	particleEmitter = ItemG1LauncherProjectileExplosion_CloudEmitter;
	particleDensity = 600;
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

