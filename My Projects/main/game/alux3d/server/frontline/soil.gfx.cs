// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleEmitterNodeData(SoilBuildEmitterNode)
{
   timeMultiple = 1;
};

datablock ParticleData(SoilBuildEmitterTeam2Particle : DefaultParticle)
{
   sizes[0] = "0.997986";
   sizes[1] = "1";
   sizes[2] = "1";
   sizes[3] = "1";
   times[1] = "0.5";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/torque3d/3.0//particles/smoke.png";
   animTexName = "content/xa/torque3d/3.0//particles/smoke.png";
   colors[0] = "0 0 1 1";
   colors[1] = "0 0 1 0.637795";
   colors[2] = "0 0 1 0";
   gravityCoefficient = "-0.1";
};

datablock ParticleEmitterData(SoilBuildEmitterTeam2 : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "SoilBuildEmitterTeam2Particle";
   blendStyle = "NORMAL";
   ejectionOffset = "0";
   thetaMin = "90";
   thetaMax = "90";
   ejectionVelocity = "0.5";
   velocityVariance = "0.5";
   ejectionPeriodMS = "200";
};

datablock ParticleData(SoilBuildEmitterTeam1Particle : DefaultParticle)
{
   sizes[0] = "0.997986";
   sizes[1] = "1";
   sizes[2] = "1";
   sizes[3] = "1";
   times[1] = "0.5";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/torque3d/3.0//particles/smoke.png";
   animTexName = "content/xa/torque3d/3.0//particles/smoke.png";
   colors[0] = "0.996078 0.00784314 0.0313726 1";
   colors[1] = "0.996078 0.00784314 0.0313726 0.637795";
   colors[2] = "0.996078 0.00784314 0.0313726 0";
   gravityCoefficient = "-0.1";
};

datablock ParticleEmitterData(SoilBuildEmitterTeam1 : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "SoilBuildEmitterTeam1Particle";
   blendStyle = "NORMAL";
   ejectionOffset = "0";
   thetaMin = "90";
   thetaMax = "90";
   ejectionVelocity = "0.5";
   velocityVariance = "0.5";
   ejectionPeriodMS = "200";
};

datablock ParticleData(SoilBuildEmitterTeam0Particle : DefaultParticle)
{
   sizes[0] = "0.5";
   sizes[1] = "0.5";
   sizes[2] = "0.5";
   sizes[3] = "0";
   times[1] = "1";
   times[2] = "1";
   dragCoefficient = "0";
   inheritedVelFactor = "0";
   spinSpeed = "0";
   textureName = "content/xa/alux1/textures/core/particle1.png";
   animTexName = "content/xa/alux1/textures/core/particle1.png";
   colors[0] = "0.996078 0.996078 0.992157 1";
   colors[1] = "0.996078 0.972549 0.00784314 1";
   colors[2] = "0.992157 0.996078 0.992157 0";
   gravityCoefficient = "0";
   colors[3] = "0.996078 0.00784314 0.807843 1";
   lifetimeMS = "1200";
   lifetimeVarianceMS = "0";
};

datablock ParticleEmitterData(SoilBuildEmitterTeam0 : DefaultEmitter)
{
   softnessDistance = "1";
   particles = "SoilBuildEmitterTeam0Particle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "0";
   thetaMin = "90";
   thetaMax = "90";
   ejectionVelocity = "0.5";
   velocityVariance = "0";
   ejectionPeriodMS = "25";
   alignDirection = "0 0 1";
};

datablock ParticleData(SoilPopupExplosionDustParticle)
{
   textureName          = "content/xa/torque3d/3.0/particles/impact";
   dragCoefficient      = "1";
   gravityCoefficient   = "0.25";
   windCoefficient      = 0;
   inheritedVelFactor   = 0.0;
   constantAcceleration = "-0.83";
   lifetimeMS           = 800;
   lifetimeVarianceMS   = 300;
   spinRandomMin = -180.0;
   spinRandomMax =  180.0;
   useInvAlpha   = true;

   colors[0]     = "0.496063 0.393701 0.299213 1";
   colors[1]     = "0.692913 0.614173 0.535433 0.552";
   colors[2]     = "0.897638 0.84252 0.795276 0";

   sizes[0]      = "0.997986";
   sizes[1]      = "2";
   sizes[2]      = "2.5";

   times[0]      = 0.0;
   times[1]      = "0.498039";
   times[2]      = 1.0;
   animTexName = "content/xa/torque3d/3.0/particles/impact";
};

datablock ParticleEmitterData(SoilPopupExplosionDustEmitter)
{
   ejectionPeriodMS = "200";
   periodVarianceMS = "0";
   ejectionVelocity = "0";
   velocityVariance = "0";
   thetaMin         = 0.0;
   thetaMax         = 180.0;
   lifetimeMS       = "100";
   particles = "SoilPopupExplosionDustParticle";
   blendStyle = "NORMAL";
   ambientFactor = "0";
};

datablock ExplosionData(SoilPopupExplosion)
{
   lifetimeMS = "96";
   lightStartRadius = "0";
   lightStartColor = "0 1 0.874016 1";
   lightEndColor = "0 1 0.874016 1";
   lightStartBrightness = "0.784314";
   lightEndBrightness = "0";
   particleRadius = "0.6";
   particleDensity = "100";
   ParticleEmitter = "SoilPopupExplosionDustEmitter";
   soundProfile = "SoilPopupExplosionSound";
   lightEndRadius = "0";
};
