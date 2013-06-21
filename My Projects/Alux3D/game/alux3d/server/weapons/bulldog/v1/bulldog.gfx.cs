// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnBulldogProjectileParticles : DefaultParticle)
{
   sizes[0] = "0.0946103";
   sizes[1] = "0.497467";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   inheritedVelFactor = "0";
   lifetimeMS = "1000";
   lifetimeVarianceMS = "0";
   dragCoefficient = "0";
   spinSpeed = "0";
   textureName = "library/texture/alux3d/ring.png";
   animTexName = "library/texture/alux3d/ring.png";
   colors[1] = "0.992126 0.0787402 0.00787402 0";
   colors[2] = "0.996078 0.0784314 0.00784314 0.330709";
   colors[3] = "1 0.0705882 0 0";
   ejectionPeriodMS = "2";
   ejectionVelocity = "0";
   softnessDistance = "1";
   particles = "WpnBulldogProjectileParticle";
   ejectionOffset = "0";
};

datablock ParticleEmitterData(WpnBulldogProjectileEmitter : DefaultEmitter)
{
   particles = "WpnBulldogProjectileParticles";
   ejectionPeriodMS = "2";
   periodVarianceMS = "0";
   softnessDistance = "1";
   ejectionVelocity = "1";
   ejectionOffset = "0";
   thetaMin = "180";
   thetaMax = "90";
};

datablock ParticleData(WpnBulldogProjectileExplosionPlasmaParticles)
{
   textureName          = "art/particles/ricochet.png";
   dragCoefficient      = "0.99218";
   gravityCoefficient   = "0";
   windCoefficient      = 0;
   inheritedVelFactor   = 0.0;
   constantAcceleration = "0";
   lifetimeMS           = "400";
   lifetimeVarianceMS   = "100";
   spinRandomMin = -180.0;
   spinRandomMax =  180.0;
   useInvAlpha   = "1";

   colors[0]     = "0.992126 0.992126 0.992126 1";
   colors[1]     = "1 0.0705882 0 0.543307";
   colors[2]     = "1 0.0705882 0 0";

   sizes[0]      = "0.497467";
   sizes[1]      = "0.497467";
   sizes[2]      = "0.0976622";

   times[0]      = 0.0;
   times[1]      = "0.494118";
   times[2]      = 1.0;
   animTexName = "art/particles/ricochet.png";
   colors[3] = "1 0.835294 0 1";
};

datablock ParticleEmitterData(WpnBulldogProjectileExplosionPlasmaEmitter)
{
   ejectionPeriodMS = "1";
   ejectionVelocity = "8.333";
   velocityVariance = "5";
   thetaMax = "180";
   softnessDistance = "1";
   particles = "WpnBulldogProjectileExplosionPlasmaParticles";
   lifetimeMS = "15";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   useEmitterColors = "0";
   orientParticles = "1";
};

datablock ParticleData(WpnBulldogProjectileExplosionCloudParticle : DefaultParticle)
{
   sizes[0] = "0.997986";
   sizes[1] = "0.5";
   sizes[2] = "2";
   sizes[3] = "0";
   times[1] = "0.5";
   times[2] = "1";
   textureName = "art/particles/dustParticle.png";
   animTexName = "art/particles/dustParticle.png";
   lifetimeMS = "150";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   spinRandomMin = "-573";
   spinRandomMax = "541";
   colors[0] = "0.992126 0.992126 0.992126 1";
   colors[2] = "1 0.952756 0 0";
   colors[3] = "0.94902 0.00784314 0.996078 1";
   inheritedVelFactor = "0";
   constantAcceleration = "-10";
   useInvAlpha = "0";
   colors[1] = "0.996078 0.980392 0.654902 0.637795";
};

datablock ParticleEmitterData(WpnBulldogProjectileExplosionCloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnBulldogProjectileExplosionCloudParticle";
   ejectionPeriodMS = "10";
   lifetimeMS = "50";
   originalName = "WpnBulldogProjectileExplosionCloudEmitter";
   thetaMax = "180";
   softnessDistance = "1";
};

datablock ExplosionData(WpnBulldogProjectileExplosion)
{
   lifetimeMS = "192";
   lightStartRadius = "4";
   lightStartColor = "0.992126 0.992126 0.992126 1";
   lightEndColor = "0.992126 0.992126 0.992126 1";
   lightStartBrightness = "0.862745";
   lightEndBrightness = "0";
   particleRadius = "0.1";
   particleDensity = "2";
   emitter[0] = "WpnBulldogProjectileExplosionPlasmaEmitter";
   ParticleEmitter = "BulletDirtDustEmitter";
};

datablock DebrisData(WpnBulldogProjectileShell)
{
   shapeFile = "art/shapes/weapons/shared/RifleShell.DAE";
   lifetime = 6.0;
   minSpinSpeed = 300.0;
   maxSpinSpeed = 400.0;
   elasticity = 0.65;
   friction = 0.05;
   numBounces = 5;
   staticOnMaxBounce = true;
   snapOnMaxBounce = false;
   ignoreWater = true;
   fade = true;
};


datablock ParticleData(WpnBulldogProjectileParticle : DefaultParticle)
{
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   lifetimeMS = "1000";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   textureName = "library/texture/alux3d/ring.png";
   animTexName = "library/texture/alux3d/ring.png";
   colors[1] = "0.992157 0.0862745 0.0156863 0";
   colors[2] = "0.996078 0.0784314 0.00784314 0.330709";
   colors[3] = "1 0.0705882 0 0";
   sizes[0] = "0.1";
   sizes[1] = "0.5";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
};
