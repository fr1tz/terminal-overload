// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnMGL1ProjectileExplosionSparkParticle : DefaultParticle)
{
   sizes[0] = "0.25";
   sizes[1] = "0.5";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "0.5";
   times[2] = "1";
   spinSpeed = "0";
   textureName = "content/torque3d/3.0/particles/droplet.png";
   animTexName = "content/torque3d/3.0/particles/droplet.png";
   inheritedVelFactor = "0";
   lifetimeMS = "100";
   lifetimeVarianceMS = "25";
   useInvAlpha = "0";
   colors[0] = "0.996078 0.992157 0.992157 1";
   colors[1] = "0.00784314 0.996078 0.92549 0.552";
   colors[2] = "0 1 0.929412 0";
   colors[3] = "1 0 1 1";
};

datablock ParticleEmitterData(WpnMGL1ProjectileExplosionSparkEmitter : DefaultEmitter)
{
   particles = "WpnMGL1ProjectileExplosionSparkParticle";
   ejectionPeriodMS = "1";
   thetaMax = "90";
   phiVariance = "360";
   orientParticles = "1";
   lifetimeMS = "25";
   softnessDistance = "1";
   ejectionVelocity = "10";
   ejectionOffset = "0";
   thetaMin = "90";
};

datablock ParticleData(WpnMGL1ProjectileExplosionPlasmaParticles)
{
   textureName          = "content/torque3d/3.0/particles/ricochet.png";
   dragCoefficient      = "0.99218";
   gravityCoefficient   = "0";
   windCoefficient      = 0;
   inheritedVelFactor   = 0.0;
   constantAcceleration = "0";
   lifetimeMS           = "200";
   lifetimeVarianceMS   = "100";
   spinRandomMin = -180.0;
   spinRandomMax =  180.0;
   useInvAlpha   = "1";

   colors[0]     = "0.992126 0.992126 0.992126 1";
   colors[1]     = "1 0.721569 0 0.543307";
   colors[2]     = "1 0.721569 0 0";

   sizes[0]      = "0.497467";
   sizes[1]      = "0.497467";
   sizes[2]      = "0.0976622";

   times[0]      = 0.0;
   times[1]      = "0.494118";
   times[2]      = 1.0;
   animTexName = "content/torque3d/3.0/particles/ricochet.png";
   colors[3] = "1 0.835294 0 1";
};

datablock ParticleEmitterData(WpnMGL1ProjectileExplosionPlasmaEmitter)
{
   ejectionPeriodMS = "1";
   ejectionVelocity = "15";
   velocityVariance = "5";
   thetaMax = "180";
   softnessDistance = "1";
   particles = "WpnMGL1ProjectileExplosionPlasmaParticles";
   lifetimeMS = "15";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   useEmitterColors = "0";
   orientParticles = "1";
};

datablock ParticleData(WpnMGL1ProjectileExplosionCloudParticle : DefaultParticle)
{
   sizes[0] = "0";
   sizes[1] = "2.08333";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   textureName = "content/fr1tz/alux1/textures/particle1.png";
   animTexName = "content/fr1tz/alux1/textures/particle1.png";
   lifetimeMS = "50";
   lifetimeVarianceMS = "0";
   spinSpeed = "0";
   spinRandomMin = "-573";
   spinRandomMax = "541";
   colors[0] = "0.996078 0.392157 0.92549 1";
   colors[2] = "0.996078 0.00784314 0.878431 1";
   colors[3] = "0.94902 0.00784314 0.996078 1";
   inheritedVelFactor = "0";
   constantAcceleration = "0";
   useInvAlpha = "0";
   colors[1] = "0.996078 0.407843 0.968628 0";
};

datablock ParticleEmitterData(WpnMGL1ProjectileExplosionCloudEmitter : DefaultEmitter)
{
   ejectionVelocity = "0";
   ejectionOffset = "0";
   particles = "WpnMGL1ProjectileExplosionCloudParticle";
   ejectionPeriodMS = "1";
   lifetimeMS = "5";
   originalName = "WpnMGL1ProjectileExplosionCloudEmitter";
   thetaMax = "153";
   softnessDistance = "1";
};

datablock ExplosionData(WpnMGL1ProjectileExplosion)
{
   lifetimeMS = "96";
   lightStartRadius = "0.941176";
   lightStartColor = "0 1 0.874016 1";
   lightEndColor = "0 1 0.874016 1";
   lightStartBrightness = "1.96078";
   lightEndBrightness = "0";
   particleRadius = "0.1";
   particleDensity = "2";
   ParticleEmitter = "BulletDirtDustEmitter";
   soundProfile = "WpnMGL1ProjectileExplosionSound";
   lightEndRadius = "0";
   emitter[0] = "WpnMGL1ProjectileExplosionCloudEmitter";
};

datablock DebrisData(WpnMGL1ProjectileShell)
{
   shapeFile = "content/torque3d/3.0/shapes/weapons/shared/RifleShell.DAE";
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

