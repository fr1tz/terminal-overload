// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Dust emitter

datablock ParticleData(FrmHovercycleDustEmitter_Particle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			  = 1000;
	lifetimeVarianceMS	= 350;
	colors[0]	  = "0.7 0.7 0.7 1.0";
	colors[1]	  = "0.7 0.7 0.7 0.5";
	colors[2]	  = "0.7 0.7 0.7 0.0";
	sizes[0]		= 1.0;
	sizes[1]		= 1.0;
	sizes[2]		= 1.0;
	times[0]		= 0.0;
	times[1]		= 0.5;
	times[2]		= 1.0;
	textureName	= "content/rotc/p.5.3/textures/rotc/dustParticle";
	useInvAlpha = true;
	allowLighting = false;
};

datablock ParticleEmitterData(FrmHovercycleDustEmitter)
{
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 2;
	velocityVariance = 1;
	ejectionOffset	= 0.75;
	thetaMin			= 90;
	thetaMax			= 90;
	phiReferenceVel  = 0;
	phiVariance		= 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS		 = 0; // forever
	particles = FrmHovercycleDustEmitter_Particle;
};

//-----------------------------------------------------------------------------
// laser trail

datablock MultiNodeLaserBeamData(FrmHovercycleLaserTrail)
{
	hasLine   = true;
	lineColor = "0.00 0.50 1.00 1.0";
   lineWidth = 1.0;

	hasInner = false;
	innerColor = "0.00 1.00 0.00 1.0";
	innerWidth = "0.4";

	hasOuter = false;
	outerColor = "0.00 1.00 0.00 1.0";
	outerWidth = "0.4";

	bitmap = "share/textures/alux/laser7";
	bitmapWidth = 0.7;

	blendMode = 1;
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
	fadeTime = 1000;

    windCoefficient = 0.0;

	// node x movement...
	nodeMoveMode[0]     = $NodeMoveMode::None;
	nodeMoveSpeed[0]    = 16.0;
	nodeMoveSpeedAdd[0] = -32.0;
	// node y movement...
	nodeMoveMode[1]     = $NodeMoveMode::None;
	nodeMoveSpeed[1]    = 16.0;
	nodeMoveSpeedAdd[1] = -32.0;
	// node z movement...
	nodeMoveMode[2]     = $NodeMoveMode::None;
	nodeMoveSpeed[2]    = 16.0;
	nodeMoveSpeedAdd[2] = -32.0;

	//nodeDistance = 4;
};
