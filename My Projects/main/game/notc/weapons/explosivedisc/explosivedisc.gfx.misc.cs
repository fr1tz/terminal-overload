// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnExplosiveDiscLightDesc)
{
   color = "1 1 1 1";
   range = "10";
   brightness = "4";
};

datablock DecalData(WpnExplosiveDiscDecal)
{
   Material = "xa_notc_core_shapes_explosivedisc_projectile_p1_decalmat";
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

datablock ParticleData(WpnExplosiveDiscEmitterParticle : DefaultParticle)
{
	dragCoefficient		= 1.0;
	gravityCoefficient	= 0.0;
	inheritedVelFactor	= 0.0;
	constantAcceleration = 0.0;
	lifetimeMS			   = 1000;
	lifetimeVarianceMS	= 250;
	colors[0]	  = "1.0 1.0 1.0 1.0";
	colors[1]	  = "1.0 1.0 1.0 0.5";
	colors[2]	  = "1.0 1.0 1.0 0.0";
	sizes[0]		= 0.9;
	sizes[1]		= 0.9;
	sizes[2]		= 0.5;
	times[0]		= 0.0;
	times[1]		= 0.2;
	times[2]		= 1.0;
   textureName = "content/o/rotc/p.5.4/textures/rotc/dustParticle.png";
   animTexName = "content/o/rotc/p.5.4/textures/rotc/dustParticle.png";
};

datablock ParticleEmitterData(WpnExplosiveDiscEmitter : DefaultEmitter)
{
   particles = "WpnExplosiveDiscEmitterParticle";
	ejectionPeriodMS = 5;
	periodVarianceMS = 0;
	ejectionVelocity = 5;
	velocityVariance = 0;
	ejectionOffset   = 0;
	thetaMin         = 20;
	thetaMax         = 30;
	phiReferenceVel  = 0;
	phiVariance      = 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS       = 0;
   paletteSlot      = 0;
};

