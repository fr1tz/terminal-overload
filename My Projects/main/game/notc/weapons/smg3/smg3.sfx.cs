// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXDescription(WpnSMG3FireSoundDescription : AudioEffect)
{
   volume            = 1.0;
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 125.0;
   MinDistance       = 125.0;
   MaxDistance       = 150.0;
};

datablock SFXProfile(WpnSMG3FireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/charge5";
   description = WpnSMG3FireSoundDescription;
   preload = true;
};

datablock SFXProfile(WpnSMG3DryFireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSMG3SwitchinSound)
{
   filename = "content/o/torque3d/3.0/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSMG3ProjectileImpactSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/debris1";
   description = AudioDefault3D;
   preload = true;
};




