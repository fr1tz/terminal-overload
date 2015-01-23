// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(FrmStandardCatBleedEffect_Decal)
{
   size = "2";
   material = xa_notc_core_shapes_standardcat_blood_p1_decalmat;
   textureCoordCount = "0";
   lifeSpan = "250";
   fadeTime = "2500";
   paletteSlot = 0;
};

datablock DebrisData(FrmStandardCatBleedEffect_Debris)
{
	// shape...
	shapeFile = "content/xa/notc/core/shapes/standardcat/blood/p1/shape.dae";
 
   // decal...
   decal = FrmStandardCatBleedEffect_Decal;

	// bounce...
	staticOnMaxBounce = "0";
	numBounces = "0";

	// physics...
	gravModifier = 4.0;
	elasticity = 0.6;
	friction = 0.1;

	// spin...
	minSpinSpeed = 60;
	maxSpinSpeed = 600;

	// lifetime...
	lifetime = 4.0;
	lifetimeVariance = 1.0;
   explodeOnMaxBounce = "1";
};

datablock ParticleData(FrmStandardCatBleedEffect_Particles : DefaultParticle)
{
   sizes[0] = "1";
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
   textureName = "content/o/rotc/p.5.4/textures/rotc/spark02.png";
   animTexName = "content/o/rotc/p.5.4/textures/rotc/spark02.png";
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

//------------------------------------------------------------------------------

datablock ExplosionData(FrmStandardCatBleedEffect0)
{
	// shape...
	explosionShape = "content/xa/rotc_hack/shapes/explosion_white.dts";
	faceViewer	  = true;
	playSpeed = 4.0;
	sizes[0] = "0.0 0.0 0.0";
	sizes[1] = "0.1 0.1 0.1";
	times[0] = 0.0;
	times[1] = 1.0;

	// dynamic light...
	lightStartRadius = 4;
	lightEndRadius = 0;
	lightStartColor = "1.0 1.0 1.0";
	lightEndColor = "0.0 0.0 0.0";
};

//------------------------------------------------------------------------------

datablock ParticleEmitterData(FrmStandardCatBleedEffect10Emitter : DefaultEmitter)
{
   particles = "FrmStandardCatBleedEffect_Particles";
   ejectionPeriodMS = "1";
   periodVarianceMS = "0";
   softnessDistance = "1";
   ejectionVelocity = "15";
   ejectionOffset = "0";
   thetaMin = "0";
   thetaMax = "180";
   orientParticles = "1";
   blendStyle = "ADDITIVE";
   soundProfile = "FrmStandardcatBleedEffectSound";
   particleDensity = "2";
   particleRadius = "0.1";
   emitter[0] = "FrmStandardCatBleedEffect_Sting_Emitter";
   lifetimeMS = "96";
   lightStartRadius = "4.94118";
   lightStartColor = "1 0 0 1";
   lightEndColor = "0.992126 0 0 1";
   lightStartBrightness = "0.784314";
   lightEndBrightness = "1.80392";
   paletteSlot = -1;
   emitter0 = "FrmStandardCatBleedEffect_Sting_Emitter";
};

datablock ExplosionData(FrmStandardCatBleedEffect10)
{
   soundProfile = FrmStandardcatBleedEffectSound;
   lifetimeMS = "64";
   lightStartRadius = "4.94118";
   lightStartColor = "1 0 0 1";
   lightEndColor = "0.992126 0 0 1";
   lightStartBrightness = "0.784314";
   lightEndBrightness = "1.80392";
   particleRadius = "0.1";
   particleDensity = "2";
   emitter[0] = "FrmStandardCatBleedEffect10Emitter";
   Debris = "FrmStandardCatBleedEffect_Debris";
   debrisThetaMax = "60";
   debrisNum = "2";
   debrisVelocity = 10;
};

//------------------------------------------------------------------------------

datablock ExplosionData(FrmStandardCatBleedEffect20 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "96";
   debrisNum = "6";
};

datablock ExplosionData(FrmStandardCatBleedEffect30 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "128";
   debrisNum = "6";
};

datablock ExplosionData(FrmStandardCatBleedEffect40 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "160";
   debrisNum = "8";
};

datablock ExplosionData(FrmStandardCatBleedEffect50 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "192";
   debrisNum = "10";
};

datablock ExplosionData(FrmStandardCatBleedEffect60 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "224";
   debrisNum = "12";
};

datablock ExplosionData(FrmStandardCatBleedEffect70 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "256";
   debrisNum = "14";
};

datablock ExplosionData(FrmStandardCatBleedEffect80 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "288";
   debrisNum = "16";
};

datablock ExplosionData(FrmStandardCatBleedEffect90 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "320";
   debrisNum = "18";
};

datablock ExplosionData(FrmStandardCatBleedEffect100 : FrmStandardCatBleedEffect10)
{
   lifetimeMS = "352";
   debrisNum = "20";
};

