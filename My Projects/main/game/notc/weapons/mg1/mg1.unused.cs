// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(WpnMG1ProjectileMissEnemySound1)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-1";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound2)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-2";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound3)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-3";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound4)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-4";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound5)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-5";
   description = AudioClose3D;
   preload = true;
};

datablock SFXProfile(WpnMG1ProjectileMissEnemySound6)
{
   filename = "content/o/rotc/p.5.4/sounds/rotc/ricochet1-6";
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

