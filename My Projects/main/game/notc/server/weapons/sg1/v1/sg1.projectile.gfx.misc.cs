// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSG1ProjectileDecal)
{
   Material = "xa_notc1_shapes_sg1_projectile_p1_decalmat";
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
};

datablock ParticleData(WpnSG1ProjectileEmitterParticle : DefaultParticle)
{
   sizes[0] = "0.1";
   sizes[1] = "0.4";
   sizes[2] = "0.997986";
   sizes[3] = "0.997986";
   times[1] = "1";
   times[2] = "1";
   dragCoefficient = "0.997067";
   inheritedVelFactor = "0";
   textureName = "content/xa/notc1/textures/grid.128.4.glow.png";
   animTexName = "content/xa/notc1/textures/grid.128.4.glow.png";
   colors[0] = "0.996078 0.92549 0.00784314 1";
   colors[1] = "0.996078 0.835294 0.0156863 0";
   lifetimeMS = "500";
   lifetimeVarianceMS = "250";
   useInvAlpha = "0";
};

datablock ParticleEmitterData(WpnSG1ProjectileEmitter : DefaultEmitter)
{
   particles = "WpnSG1ProjectileEmitterParticle";
   ejectionPeriodMS = "2";
   ejectionOffset = "0";
   periodVarianceMS = "1";
};


