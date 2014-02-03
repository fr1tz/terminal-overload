// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(DefaultParticle)
{
   textureName = "core/art/defaultParticle";
   dragCoefficient = 0.498534;
   gravityCoefficient = 0;
   inheritedVelFactor = 0.499022;
   constantAcceleration = 0.0;
   lifetimeMS = 1313;
   lifetimeVarianceMS = 500;
   useInvAlpha = true;
   spinRandomMin = -360;
   spinRandomMax = 360;
   spinSpeed = 1;

   colors[0] = "0.992126 0.00787402 0.0314961 1";
   colors[1] = "1 0.834646 0 0.645669";
   colors[2] = "1 0.299213 0 0.330709";
   colors[3] = "0.732283 1 0 0";
   
   sizes[0] = 0;
   sizes[1] = 0.497467;
   sizes[2] = 0.73857;
   sizes[3] = 0.997986;
   
   times[0] = 0.0;
   times[1] = 0.247059;
   times[2] = 0.494118;
   times[3] = 1;
   
   animTexName = "core/art/defaultParticle";
};

datablock ParticleEmitterData(DefaultEmitter)
{
   ejectionPeriodMS = "50";
   ejectionVelocity = "1";
   velocityVariance = "0";
   ejectionOffset = "0.2";
   thetaMax = "40";
   particles = "DefaultParticle";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   softnessDistance = "1";
};
