// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnRaptorProjectileExplosionPlasmaParticles)
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

   colors[0]     = "0.996078 0.996078 0.992157 1";
   colors[1]     = "0.996078 0.921569 0.54902 0.548";
   colors[2]     = "1 0.834646 0 0";

   sizes[0]      = "0.5";
   sizes[1]      = "0.5";
   sizes[2]      = "0.1";

   times[0]      = 0.0;
   times[1]      = "0.494118";
   times[2]      = 1.0;
   animTexName = "art/particles/ricochet.png";
   colors[3] = "1 0.835294 0 1";
};

datablock ParticleEmitterData(WpnRaptorProjectileExplosionPlasmaEmitter)
{
   ejectionPeriodMS = "1";
   ejectionVelocity = "8.333";
   velocityVariance = "5";
   thetaMax = "180";
   softnessDistance = "1";
   particles = "WpnRaptorProjectileExplosionPlasmaParticles";
   lifetimeMS = "15";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   useEmitterColors = "0";
   orientParticles = "1";
};

datablock ParticleData(WpnRaptorProjectileExplosionCloudParticle : DefaultParticle)
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

datablock ParticleEmitterData(WpnRaptorProjectileExplosionCloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnRaptorProjectileExplosionCloudParticle";
   ejectionPeriodMS = "10";
   lifetimeMS = "50";
   originalName = "WpnRaptorProjectileExplosionCloudEmitter";
   thetaMax = "180";
   softnessDistance = "1";
};

datablock ExplosionData(WpnRaptorProjectileExplosion)
{
   lifetimeMS = "192";
   lightStartRadius = "4";
   lightStartColor = "0.992126 0.992126 0.992126 1";
   lightEndColor = "0.992126 0.992126 0.992126 1";
   lightStartBrightness = "0.862745";
   lightEndBrightness = "0";
   particleRadius = "0.1";
   particleDensity = "2";
   emitter[0] = "WpnRaptorProjectileExplosionPlasmaEmitter";
   ParticleEmitter = "BulletDirtDustEmitter";
};

datablock DebrisData(WpnRaptorProjectileShell)
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

