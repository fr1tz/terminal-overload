// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ParticleData(WpnInterceptorDiscExplosion_Particle1)
{
   gravityCoefficient = "1";
   inheritedVelFactor = "0.025";
   lifetimeMS = "500";
   lifetimeVarianceMS = "200";
   useInvAlpha = "1";
   textureName = "content/xa/rotc/p.5.4/textures/rotc/spark02.png";
   animTexName = "content/xa/rotc/p.5.4/textures/rotc/spark02.png";
   colors[0] = "0.980392 0.980392 0.980392 1";
   colors[1] = "1 1 1 0";
   times[1] = "1";
   times[2] = "1";
   allowLighting = "0";
   dragCoeffiecient = "0.4";
   sizes[0] = "2";
   sizes[1] = "2";
};

datablock ParticleEmitterData(WpnInterceptorDiscExplosion_ParticleEmitter1)
{
	ejectionOffset	= 0;

	ejectionPeriodMS = "1";
	periodVarianceMS = 0;

	ejectionVelocity = "15";
	velocityVariance = "5";

	thetaMin			= "0";
	thetaMax			= "180";

	lifetimeMS		 = "100";

	particles = "WpnInterceptorDiscExplosion_Particle1";
   blendStyle = "ADDITIVE";
   orientParticles = "1";
};

datablock ExplosionData(WpnInterceptorDiscExplosion)
{
	soundProfile = WpnInterceptorDiscExplosionSound;

	explosionShape = "content/xa/notc/core/shapes/interceptordisc/explosion/p1/shape.dts";
	faceViewer	  = true;
	playSpeed = 4.0;
	sizes[0] = "4.0 4.0 4.0";
	sizes[1] = "0.0 0.0 0.0";
	times[0] = 0.0;
	times[1] = 1.0;

//	debris = Team1AntiairNearEnemyExplosionDebris;
//	debrisThetaMin = 0;
//	debrisThetaMax = 180;
//	debrisNum = 15;
//	debrisVelocity = 20.0;
//	debrisVelocityVariance = 15.0;

	emitter[0] = WpnInterceptorDiscExplosion_ParticleEmitter1;
//	emitter[0] = Team1AntiairNearEnemyExplosion_Cloud2Emitter;

	// Camera Shaking
	shakeCamera = true;
	camShakeFreq = "10.0 11.0 10.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 20;
	lightEndRadius = 2;
	lightStartColor = "1.0 1.0 1.0 1.0";
	lightEndColor = "1.0 1.0 1.0 0.3";
};

