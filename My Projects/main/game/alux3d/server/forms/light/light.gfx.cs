// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleEmitterNodeData(FrmLightParticleEmitterNode)
{
   timeMultiple = 1;
};

datablock ParticleData(FrmLightTeam1Particle : DefaultParticle)
{
   sizes[0] = "1";
   sizes[1] = "0.5";
   sizes[2] = "0";
   sizes[3] = "1";
   times[1] = "0.498039";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/alux1/textures/ring.png";
   animTexName = "content/xa/alux1/textures/ring.png";
   colors[0] = "1 0 0 0.5";
   colors[1] = "1 0 0 0.25";
   colors[2] = "1 0 0 0";
   gravityCoefficient = "0";
   colors[3] = "0.732283 1 0 0";
   lifetimeMS = "1000";
   lifetimeVarianceMS = "0";
};

datablock ParticleEmitterData(FrmLightTeam1ParticleEmitter : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "FrmLightTeam1Particle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "0";
   thetaMin = "0";
   thetaMax = "180";
   ejectionVelocity = "0";
   velocityVariance = "0";
   ejectionPeriodMS = "20";
};

datablock ParticleData(FrmLightTeam2Particle : DefaultParticle)
{
   sizes[0] = "1";
   sizes[1] = "0.5";
   sizes[2] = "0";
   sizes[3] = "1";
   times[1] = "0.498039";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/alux1/textures/ring.png";
   animTexName = "content/xa/alux1/textures/ring.png";
   colors[0] = "0 0 1 0.5";
   colors[1] = "0 0 1 0.25";
   colors[2] = "0 0 1 0";
   gravityCoefficient = "0";
   colors[3] = "0.732283 1 0 0";
   lifetimeMS = "1000";
   lifetimeVarianceMS = "0";
};

datablock ParticleEmitterData(FrmLightTeam2ParticleEmitter : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "FrmLightTeam2Particle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "0";
   thetaMin = "0";
   thetaMax = "180";
   ejectionVelocity = "0";
   velocityVariance = "0";
   ejectionPeriodMS = "20";
};
