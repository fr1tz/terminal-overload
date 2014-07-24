// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ExplosionData(WpnRepelDiscHit)
{
	soundProfile = WpnRepelDiscHitSound;

	// Shape
	explosionShape = "content/xa/notc/core/shapes/repeldisc/explosion/p1/shape.dts";
	faceViewer = false;
	playSpeed = 4.0;
	sizes[0] = "0.1 0.1 0.1";
	sizes[1] = "0.5 0.5 0.5";
	times[0] = 0.0;
	times[1] = 1.0;

	// Dynamic light
	lightStartRadius = 0;
	lightEndRadius = 0;
	lightStartColor = "0.984252 0.992126 0.992126 1";
	lightEndColor = "0.984252 0.984252 0.984252 1";
   lightStartBrightness = "16.0784";
   lightEndBrightness = "16.1569";
};
