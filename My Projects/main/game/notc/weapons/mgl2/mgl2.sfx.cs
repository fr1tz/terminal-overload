// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXPlayList(WpnMGL2FireSoundList)
{
   description = AudioClose3D;
   track[0] = WpnMGL2FireSound;
};

datablock SFXProfile(WpnMGL2FireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/fire8";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMGL2DryFireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMGL2SwitchinSound)
{
   filename = "content/o/torque3d/3.0/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMGL2ProjectileSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/slide3";
   description = AudioCloseLoop3D;
   preload = true;
};

datablock SFXProfile(WpnMGL2ProjectileExplosionSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/explosion13";
   description = AudioClose3D;
   preload = true;
};




