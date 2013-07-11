// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(WpnRaptorFireSound)
{
   filename = "library/sound/cat5/gunshot1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorDryFireSound)
{
   filename = "library/sound/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorReloadSound)
{
   filename = "art/sound/weapons/wpn_lurker_reload";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorIdleSound)
{
   filename = "art/sound/weapons/wpn_lurker_idle";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorSwitchinSound)
{
   filename = "art/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorGrenadeFireSound)
{
   filename = "art/sound/weapons/wpn_lurker_grenadelaunch";
   description = AudioClose3D;
   preload = true;
};

datablock SFXPlayList(WpnRaptorFireSoundList)
{
   // Use a looped description so the list playback will loop.
   description = AudioClose3D;

   track[0] = WpnRaptorFireSound;
};

datablock SFXProfile(WpnRaptorReleaseMagazineSound)
{
   filename = "library/sound/t3d/snap1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorInsertMagazineSound)
{
   filename = "library/sound/t3d/snap2";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnRaptorChamberSound)
{
   filename = "library/sound/t3d/chamber2";
   description = AudioClose3D;
   preload = true;
};


