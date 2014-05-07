// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnRazorDiscDecal)
{
   Material = "xa_notc_core_shapes_sg1_projectile_p1_decalmat";
   size = "1";
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

datablock ParticleData(WpnRazorDiscEmitter : DefaultParticle)
{
   sizes[0] = "1.29708";
   sizes[1] = "0";
   sizes[2] = "0.997986";
   sizes[3] = "0.997986";
   times[1] = "1";
   times[2] = "1";
   dragCoefficient = "0.99218";
   inheritedVelFactor = "0";
   textureName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   animTexName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   colors[0] = "1 1 1 1";
   colors[1] = "1 1 1 0";
   lifetimeMS = "0";
   lifetimeVarianceMS = "0";
   useInvAlpha = "0";
   colors[3] = "0.732283 1 0 0";
   spinSpeed = "0";
   spinRandomMin = "-360";
   spinRandomMax = "360";
   ejectionPeriodMS = "4";
   ejectionOffset = "0";
   thetaMax = "0";
   orientParticles = "1";
   particles = "WpnRazorDiscEmitterParticle";
   paletteSlot = "0";
};

datablock ParticleEmitterData(WpnRazorDiscEmitter : DefaultEmitter)
{
   particles = "WpnRazorDiscEmitterParticle";
   ejectionPeriodMS = "4";
   ejectionOffset = "0";
   periodVarianceMS = "0";
   paletteSlot = 0;
   ejectionVelocity = "1";
   orientParticles = "1";
};



datablock ParticleData(WpnRazorDiscEmitterParticle : DefaultParticle)
{
   dragCoefficient = "0.99218";
   inheritedVelFactor = "0";
   lifetimeMS = "500";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   useInvAlpha = "0";
   textureName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   animTexName = "content/xa/notc/core/shapes/razordisc/projectile/p1/trail.png";
   colors[0] = "1 1 1 1";
   colors[1] = "1 1 1 0";
   colors[3] = "0.732283 1 0 0";
   sizes[0] = "3";
   sizes[1] = "0";
   sizes[2] = "0.997986";
   times[1] = "1";
   times[2] = "1";
};
