// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnInterceptorDiscLightDesc)
{
   color = "1 1 1 1";
   range = "10";
   brightness = "4";
};

datablock MultiNodeLaserBeamData(WpnInterceptorDiscLaserTrail0)
{
	material = "xa_notc_core_shapes_interceptordisc_projectile_p1_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.1;
	fadeTime = 1500;
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

datablock DecalData(WpnInterceptorDiscDecal)
{
   Material = "xa_notc_core_shapes_interceptordisc_projectile_p1_decalmat";
   size = "3";
   lifeSpan = "3000";
   randomize = "1";
   texRows = "4";
   texCols = "2";
   textureCoordCount = "7";
   textureCoords[0] = "0 0 0.25 0.5";
   textureCoords[1] = "0.25 0 0.25 0.5";
   textureCoords[2] = "0.5 0 0.25 0.5";
   textureCoords[3] = "0.75 0 0.25 0.5";
   textureCoords[4] = "0 0.5 0.25 0.5";
   textureCoords[5] = "0.25 0.5 0.25 0.5";
   textureCoords[6] = "0.5 0.5 0.25 0.5";
   textureCoords[7] = "0.75 0.5 0.25 0.5";
   textureCoords[8] = "0 0.5 0.25 0.25";
   textureCoords[9] = "0.25 0.5 0.25 0.25";
   textureCoords[10] = "0.5 0.5 0.25 0.25";
   textureCoords[11] = "0.75 0.5 0.25 0.25";
   textureCoords[12] = "0 0.75 0.25 0.25";
   textureCoords[13] = "0.25 0.75 0.25 0.25";
   textureCoords[14] = "0.5 0.75 0.25 0.25";
   textureCoords[15] = "0.75 0.75 0.25 0.25";
   fadeTime = "3000";
};

datablock ParticleData(WpnInterceptorDiscEmitterParticle : DefaultParticle)
{
   dragCoefficient = "0.99218";
   inheritedVelFactor = "0";
   lifetimeMS = "500";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   useInvAlpha = "0";
   textureName = "content/xa/rotc/p.5.4/textures/rotc/zone.grid.png";
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/zone.grid.png";
   colors[0] = "1 1 1 0.5";
   colors[1] = "1 1 1 0";
   colors[3] = "0.732283 1 0 0";
   sizes[0] = "1";
   sizes[1] = "1";
   sizes[2] = "0.997986";
   times[1] = "1";
   times[2] = "1";
   sizes[3] = "1";
};

datablock ParticleEmitterData(WpnInterceptorDiscEmitter : DefaultEmitter)
{
   particles = "WpnInterceptorDiscEmitterParticle";
   ejectionPeriodMS = "4";
   ejectionOffset = "0";
   periodVarianceMS = "0";
   paletteSlot = 0;
   ejectionVelocity = "1";
   orientParticles = "0";
   thetaMax = "0";
};

