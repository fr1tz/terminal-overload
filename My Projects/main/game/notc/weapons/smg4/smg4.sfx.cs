// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXPlayList(WpnSMG4FireSoundList)
{
   description = AudioClose3D;
   track[0] = WpnSMG4FireSound;
};

datablock SFXProfile(WpnSMG4FireSound)
{
   filename = "content/o/cat5/p.1/sounds/cat5/charge4fire";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSMG4DryFireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSMG4SwitchinSound)
{
   filename = "content/o/torque3d/3.0/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSMG4ProjectileSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/slide3";
   description = AudioCloseLoop3D;
   preload = true;
};

datablock SFXProfile(WpnSMG4ProjectileExplosionSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/explosion13";
   description = AudioClose3D;
   preload = true;
};




