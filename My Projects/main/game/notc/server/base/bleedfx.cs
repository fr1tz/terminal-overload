// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(BloodExplosionSound)
{
   fileName = "content/rotc/p.5.3/sounds/rotc/explosion1";
   description = AudioDefault3D;
   preload = true;
};

datablock ParticleData(BloodExplosionSprayParticles : DefaultParticle)
{
   sizes[0] = "0.25";
   sizes[1] = "0";
   sizes[2] = "0";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   inheritedVelFactor = "0";
   lifetimeMS = "2000";
   lifetimeVarianceMS = "0";
   dragCoefficient = "0";
   spinSpeed = "0";
   textureName = "content/torque3d/3.0/particles/droplet.png";
   animTexName = "content/torque3d/3.0/particles/droplet.png";
   colors[1] = "0.992126 0.0787402 0.00787402 0";
   colors[2] = "0.996078 0.0784314 0.00784314 0.330709";
   colors[3] = "1 0.0705882 0 0";
   ejectionPeriodMS = "2";
   ejectionVelocity = "0";
   softnessDistance = "1";
   particles = "BloodExplosionParticle";
   ejectionOffset = "0";
   gravityCoefficient = "1";
};

datablock ParticleEmitterData(BloodExplosionSprayEmitter : DefaultEmitter)
{
   particles = "BloodExplosionSprayParticles";
   ejectionPeriodMS = "2";
   periodVarianceMS = "0";
   softnessDistance = "1";
   ejectionVelocity = "5";
   ejectionOffset = "0";
   thetaMin = "0";
   thetaMax = "33";
   orientParticles = "1";
   blendStyle = "NORMAL";
};

datablock ExplosionData(BloodExplosion)
{
   soundProfile = BloodExplosionSound;
   lifetimeMS = "96";
   lightStartRadius = "4.94118";
   lightStartColor = "1 0 0 1";
   lightEndColor = "0.992126 0 0.00787402 1";
   lightStartBrightness = "0.784314";
   lightEndBrightness = "1.96078";
   particleRadius = "0.1";
   particleDensity = "2";
   emitter[0] = "BloodExplosionSprayEmitter";
};

