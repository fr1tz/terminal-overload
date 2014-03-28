// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ExplosionData(GenericMissEnemyEffect1)
{
	soundProfile = GenericMissEnemyEffect1Sound;

	// Shape
	explosionShape = "content/xa/rotc_hack/shapes/explosion2_white.dts";
	faceViewer	  = true;
	playSpeed = 8.0;
	sizes[0] = "0.07 0.07 0.07";
	sizes[1] = "0.01 0.01 0.01";
	times[0] = 0.0;
	times[1] = 1.0;

	// Dynamic light
	lightStartRadius = 5;
	lightEndRadius = 0;
	lightStartColor = "1 1 1";
	lightEndColor = "1 1 1";
};

