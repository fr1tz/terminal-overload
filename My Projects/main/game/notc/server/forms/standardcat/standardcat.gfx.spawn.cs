// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(FrmStandardCatSpawnEffect_Particles1 : DefaultParticle)
{
   sizes[0] = "2";
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
   textureName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/corona.png";
   colors[1] = "1 1 1 0";
   colors[2] = "1 1 1 0.330709";
   colors[3] = "1 1 1 0";
   ejectionPeriodMS = "2";
   ejectionVelocity = "0";
   softnessDistance = "1";
   ejectionOffset = "0";
   gravityCoefficient = "2.99634";
   colors[0] = "0.992126 0.992126 0.992126 1";
};

datablock ParticleEmitterData(FrmStandardCatSpawnEffect_ParticleEmitter1 : DefaultEmitter)
{
   particles = "FrmStandardCatSpawnEffect_Particles1";
   ejectionPeriodMS = "1";
   periodVarianceMS = "0";
   softnessDistance = "1";
   ejectionVelocity = "10";
   ejectionOffset = "1.4";
   thetaMin = "0";
   thetaMax = "180";
   orientParticles = "0";
   blendStyle = "ADDITIVE";
   particleDensity = "2";
   particleRadius = "0.1";
   lifetimeMS = "100";
   lightStartRadius = "4.94118";
   lightStartColor = "1 0 0 1";
   lightEndColor = "0.992126 0 0 1";
   lightStartBrightness = "0.784314";
   lightEndBrightness = "1.80392";
   paletteSlot = "-1";
   emitter0 = "FrmStandardCatBleedEffect_Sting_Emitter";
};

datablock ExplosionData(FrmStandardCatSpawnEffect)
{
   lifetimeMS = "192";
   lightStartRadius = "19.6863";
   lightStartColor = "1 1 1 1";
   lightEndColor = "1 1 1 1";
   lightStartBrightness = "9.96078";
   lightEndBrightness = "9.96078";
   emitter[0] = "FrmStandardCatSpawnEffect_ParticleEmitter1";
   targetLockTimeMS = "480";
};

