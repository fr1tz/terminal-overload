// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnBadgerProjectileExplosionPlasmaParticles)
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
   colors[1]     = "0.32549 0.996078 0.964706 0.543307";
   colors[2]     = "0 0.976471 1 0";

   sizes[0]      = "0.497467";
   sizes[1]      = "0.497467";
   sizes[2]      = "0.0976622";

   times[0]      = 0.0;
   times[1]      = "0.494118";
   times[2]      = 1.0;
   animTexName = "art/particles/ricochet.png";
   colors[3] = "1 0.835294 0 1";
};

datablock ParticleEmitterData(WpnBadgerProjectileExplosionPlasmaEmitter)
{
   ejectionPeriodMS = "1";
   ejectionVelocity = "8.333";
   velocityVariance = "5";
   thetaMax = "180";
   softnessDistance = "1";
   particles = "WpnBadgerProjectileExplosionPlasmaParticles";
   lifetimeMS = "15";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   useEmitterColors = "0";
   orientParticles = "1";
};

datablock ParticleData(WpnBadgerProjectileExplosionCloudParticle : DefaultParticle)
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

datablock ParticleEmitterData(WpnBadgerProjectileExplosionCloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnBadgerProjectileExplosionCloudParticle";
   ejectionPeriodMS = "10";
   lifetimeMS = "50";
   originalName = "WpnBadgerProjectileExplosionCloudEmitter";
   thetaMax = "180";
   softnessDistance = "1";
};

datablock ExplosionData(WpnBadgerProjectileExplosion)
{
   lifetimeMS = "192";
   lightStartRadius = "4";
   lightStartColor = "0 0.92126 1 1";
   lightEndColor = "0 0.976378 1 1";
   lightStartBrightness = "4.94118";
   lightEndBrightness = "0";
   particleRadius = "0.1";
   particleDensity = "2";
   emitter[0] = "WpnBadgerProjectileExplosionPlasmaEmitter";
   ParticleEmitter = "BulletDirtDustEmitter";
};

datablock DebrisData(WpnBadgerProjectileShell)
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

