// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleEmitterNodeData(PacketLineEntryEmitterNode)
{
   timeMultiple = 1;
};

datablock ParticleData(PacketLineEntryEmitterParticle : DefaultParticle)
{
   sizes[0] = "0.5";
   sizes[1] = "4";
   sizes[2] = "0.5";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/notc/core/textures/grid128.12.h1.png";
   animTexName = "content/xa/notc/core/textures/grid128.12.h1.png";
   colors[0] = "0.996078 0.996078 0.992157 1";
   colors[1] = "0.996078 0.996078 0.992157 1";
   colors[2] = "0.992157 0.996078 0.992157 0";
   gravityCoefficient = "0";
   colors[3] = "0.996078 0.00784314 0.807843 1";
   lifetimeMS = "400";
   lifetimeVarianceMS = "0";
   constantAcceleration = "-10";
};

datablock ParticleEmitterData(PacketLineEntryEmitter : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "PacketLineEntryEmitterParticle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "1.458";
   thetaMin = "0";
   thetaMax = "180";
   ejectionVelocity = "5";
   velocityVariance = "0";
   ejectionPeriodMS = "25";
   alignDirection = "0 0 1";
};


