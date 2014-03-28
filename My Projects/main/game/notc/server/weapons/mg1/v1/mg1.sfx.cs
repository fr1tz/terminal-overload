// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(WpnMG1FireSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/spin2fire";
   description = AudioDefaultLoop3D;
   preload = true;
};

datablock SFXProfile(WpnMG1SpinUpSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/spin2up";
   description = AudioDefault3D;
   preload = true;
};

datablock SFXProfile(WpnMG1SpinSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/spin2";
   description = AudioDefaultLoop3D;
   preload = true;
};

datablock SFXProfile(WpnMG1SpinDownSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/spin2down";
   description = AudioDefault3D;
   preload = true;
};

datablock SFXProfile(WpnMG1DryFireSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/weaponEmpty";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1SwitchinSound)
{
   filename = "content/xa/torque3d/3.0/sound/weapons/wpn_lurker_switchin";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileExplosionSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/debris1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound1)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound2)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-2";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound3)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-3";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound4)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-4";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound5)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-5";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound6)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/ricochet1-6";
   description = AudioClose3D;
   preload = true;
};

datablock SFXPlayList(WpnMG1ProjectileMissEnemySoundList)
{
   description = AudioClose3D;
   numSlotsToPlay = 1;
   random = "StrictRandom";
   track[0] = WpnMG1ProjectileMissEnemySound1;
   track[1] = WpnMG1ProjectileMissEnemySound2;
   track[2] = WpnMG1ProjectileMissEnemySound3;
   track[3] = WpnMG1ProjectileMissEnemySound4;
   track[4] = WpnMG1ProjectileMissEnemySound5;
   track[5] = WpnMG1ProjectileMissEnemySound6;
};

