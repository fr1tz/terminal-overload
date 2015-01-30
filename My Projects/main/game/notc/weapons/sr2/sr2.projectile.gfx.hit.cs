// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ExplosionData(WpnSR2ProjectileHit)
{
	explosionShape = "content/xa/notc/core/shapes/mgl1/impactdmg/p1/shape.dae";
	faceViewer	  = false;
	playSpeed = 4.0;
	sizes[0] = "3.0 3.0 3.0";
	sizes[1] = "0.0 0.0 0.0";
	times[0] = 0.0;
	times[1] = 1.0;
 
	// Camera shake
	shakeCamera = true;
	camShakeFreq = "10.0 6.0 9.0";
	camShakeAmp = "20.0 20.0 20.0";
	camShakeDuration = 0.5;
	camShakeRadius = 20.0;

	// Dynamic light
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16.0784";
   lightEndBrightness = "16.1569";
};

