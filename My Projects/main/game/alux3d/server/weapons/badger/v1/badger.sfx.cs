// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(WpnBadgerFireSound)
{
   filename = "content/rotc/p.5.3/sounds/rotc/fire2";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnBadgerDryFireSound)
{
   filename = "content/rotc/p.5.3/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnBadgerReloadSound)
{
   filename = "content/torque3d/3.0/sound/weapons/wpn_ryder_reload";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnBadgerSwitchinSound)
{
   filename = "content/torque3d/3.0/sound/weapons/wpn_ryder_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXPlayList(WpnBadgerFireSoundList)
{
   // Use a looped description so the list playback will loop.
   description = AudioClose3D;

   track[ 0 ] = WpnBadgerFireSound;
};


