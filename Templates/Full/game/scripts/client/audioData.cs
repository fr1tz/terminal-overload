// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Game specific audio descriptions. Always declare SFXDescription's (the type of sound)
// before SFXProfile's (the sound itself) when creating new ones

singleton SFXDescription(BulletFireDesc : AudioEffect )
{
   isLooping         = false;
   is3D              = true;
   ReferenceDistance = 10.0;
   MaxDistance       = 60.0;
};

singleton SFXDescription(BulletImpactDesc : AudioEffect )
{
   isLooping         = false;
   is3D              = true;
   ReferenceDistance = 10.0;
   MaxDistance       = 30.0;
   volume = 0.4;
   pitch = 1.4;
};
