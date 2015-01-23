// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXPlayList(WpnSG2FireSoundList)
{
   description = AudioClose3D;
   track[0] = WpnSG2FireSound;
};

datablock SFXProfile(WpnSG2FireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/fire5";
   description = AudioDefault3D;
   preload = true;
};

datablock SFXProfile(WpnSG2ReloadSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/pumpgun1";
   description = AudioDefault3D;
   preload = true;
};

datablock SFXProfile(WpnSG2DryFireSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSG2SwitchinSound)
{
   filename = "content/o/torque3d/3.0/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnSG2ProjectileSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/slide3";
   description = AudioCloseLoop3D;
   preload = true;
};

datablock SFXProfile(WpnSG2ProjectileExplosionSound)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/explosion5";
   description = AudioClose3D;
   preload = true;
};




