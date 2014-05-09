// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnRepelDiscLightDesc)
{
   color = "1 1 1 1";
   range = "10";
   brightness = "4";
};

datablock DecalData(WpnRepelDiscDecal)
{
   Material = "xa_notc_core_shapes_repeldisc_projectile_p1_decalmat";
   size = "2";
   lifeSpan = "0";
   randomize = "0";
   texRows = "1";
   texCols = "1";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "0";
   textureCoords[0] = "0 0 1 1";
   textureCoords[1] = "0 0 1 1";
   textureCoords[2] = "0 0 1 1";
   textureCoords[3] = "0 0 1 1";
   textureCoords[4] = "0 0 1 1";
   textureCoords[5] = "0 0 1 1";
   textureCoords[6] = "0 0 1 1";
   textureCoords[7] = "0 0 1 1";
   textureCoords[8] = "0 0 1 1";
   textureCoords[9] = "0 0 1 1";
   textureCoords[10] = "0 0 1 1";
   fadeTime = "3000";
   paletteSlot = "0";
};

datablock ParticleData(WpnRepelDiscEmitterParticle : DefaultParticle)
{
   dragCoefficient = "0.99218";
   inheritedVelFactor = "0";
   lifetimeMS = "2000";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   useInvAlpha = "0";
   textureName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   animTexName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   colors[0] = "1 1 1 0.5";
   colors[1] = "1 1 1 0";
   colors[3] = "0.732283 1 0 0";
   sizes[0] = "3";
   sizes[1] = "0";
   sizes[2] = "0.997986";
   times[1] = "1";
   times[2] = "1";
};

datablock ParticleEmitterData(WpnRepelDiscEmitter : DefaultEmitter)
{
   particles = "WpnRepelDiscEmitterParticle";
   ejectionPeriodMS = "4";
   ejectionOffset = "0";
   periodVarianceMS = "0";
   paletteSlot = 0;
   ejectionVelocity = "1";
   orientParticles = "1";
   thetaMax = "0";
};

