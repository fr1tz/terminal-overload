// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock AudioProfile(FrmParrotEngineSound)
{
   filename = "content/rotc/p.5.3/sounds/rotc/slide3.wav";
   description = AudioDefaultLooping3D;
	preload = true;
};

datablock AudioProfile(FrmParrotExplosionSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/explosion10.wav";
	description = AudioFar3D;
	preload = true;
};

datablock AudioProfile(FrmParrotSoftImpactSound)
{
   filename = "~/data/vehicles/tank/sound_softimpact.wav";
   description = AudioDefault3D;
	preload = true;
};

datablock AudioProfile(FrmParrotHardImpactSound)
{
   filename = "~/data/vehicles/tank/sound_hardimpact.wav";
   description = AudioDefault3D;
	preload = true;
};
