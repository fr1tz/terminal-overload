// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(WpnMG2ProjectileMissEnemySound1)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG2ProjectileMissEnemySound2)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-2";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG2ProjectileMissEnemySound3)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-3";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG2ProjectileMissEnemySound4)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-4";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG2ProjectileMissEnemySound5)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-5";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG2ProjectileMissEnemySound6)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-6";
   description = AudioClose3D;
   preload = true;
};

datablock SFXPlayList(WpnMG2ProjectileMissEnemySoundList)
{
   description = AudioClose3D;
   numSlotsToPlay = 1;
   random = "StrictRandom";
   track[0] = WpnMG2ProjectileMissEnemySound1;
   track[1] = WpnMG2ProjectileMissEnemySound2;
   track[2] = WpnMG2ProjectileMissEnemySound3;
   track[3] = WpnMG2ProjectileMissEnemySound4;
   track[4] = WpnMG2ProjectileMissEnemySound5;
   track[5] = WpnMG2ProjectileMissEnemySound6;
};

