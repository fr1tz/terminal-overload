// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ExplosionData(WpnExplosiveDiscBounceEffect)
{
	soundProfile = WpnExplosiveDiscBounceEffectSound;

	lifetimeMS = 300;

	// shape...
	//explosionShape = "content/o/rotc/p.5.4/shapes/rotc/effects/explosion5.green.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0.01 0.01 0.01";
	sizes[1] = "0.20 0.20 0.20";
	times[0] = 0.0;
	times[1] = 1.0;

	//debris = WpnExplosiveDiscBounceEffect_Debris;
	//debrisThetaMin = 0;
	//debrisThetaMax = 60;
	//debrisNum = 1;
	//debrisNumVariance = 1;
	//debrisVelocity = 10.0;
	//debrisVelocityVariance = 5.0;

	// Dynamic light
	//lightStartRadius = 4;
	//lightEndRadius = 0;
	//lightStartColor = "1 1 1 1.0";
	//lightEndColor = "1 1 1 1.0";

	shakeCamera = false;
};

