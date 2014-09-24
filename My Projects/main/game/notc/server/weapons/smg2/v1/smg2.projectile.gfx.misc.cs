// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnSMG2ProjectileParticleEmitter_Particles)
{
	dragCoefficient      = "0.997067";
	gravityCoefficient   = 0.0;
	windCoefficient      = 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			   = 30;
	lifetimeVarianceMS	= 0;
	spinRandomMin        = 0;
	spinRandomMax        = 0;
	textureName			   = "content/xa/rotc/p.5.4/textures/rotc/corona";
	colors[0]            = "0.94902 0.996078 0.00784314 0.021";
	colors[1]            = "1 0.627451 0 0";
	sizes[0]             = "4.99908";
	sizes[1]             = "4.99908";
	times[0]             = 0.0;
	times[1]             = 1.0;
	useInvAlpha          = false;
	renderDot            = 0;
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/corona";
   times[2] = "1";
};

datablock ParticleEmitterData(WpnSMG2ProjectileParticleEmitter)
{
	ejectionPeriodMS = 1;
	periodVarianceMS = 0;
	ejectionVelocity = 0;
	velocityVariance = 2.5;
	ejectionOffset   = 0.0;
	thetaMin         = 0;
	thetaMax         = 0;
	phiReferenceVel  = 0;
	phiVariance      = 0;
	overrideAdvances = false;
	orientParticles  = false;
	//lifetimeMS		 = 1000;
	particles = "WpnSMG2ProjectileParticleEmitter_Particles";
};

datablock LightDescription(WpnSMG2ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnSMG2ProjectileDecal)
{
   Material = "xa_notc_core_shapes_smg2_decal_p1_mat0";
   size = "1";
   lifeSpan = "2000";
   randomize = "1";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "0";
   textureCoords[0] = "0 0 1 1";
   paletteSlot = 0;
   textureCoords[1] = "0.25 0 0.25 0.5";
   textureCoords[2] = "0.5 0 0.25 0.5";
   textureCoords[3] = "0.75 0 0.25 0.5";
   textureCoords[4] = "0 0.5 0.25 0.5";
   textureCoords[5] = "0.25 0.5 0.25 0.5";
   textureCoords[6] = "0.5 0.5 0.25 0.5";
   textureCoords[7] = "0.75 0.5 0.25 0.5";
};

datablock MultiNodeLaserBeamData(WpnSMG2ProjectileLaserTrail0)
{
	material = "xa_notc_core_shapes_smg2_beam_p1_mat0";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.30;
	fadeTime = 200;
	windCoefficient = 0.0;
	//nodeDistance = 3;

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
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(WpnSMG2ProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_smg2_beam_p1_mat1";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.1;
	fadeTime = 75;
	windCoefficient = 0.0;
	//nodeDistance = 3;

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
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(WpnSMG2ProjectileLaserTrail2)
{
	material = "xa_notc_core_shapes_smg2_beam_p1_mat2";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.6;
	fadeTime = 150;
	windCoefficient = 0.0;
	//nodeDistance = 3;

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
   nodeMoveSpeedAdd[2] = 1.0;
};


