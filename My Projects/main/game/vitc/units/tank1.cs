// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(Tank1)
{
   category = "Units";
};

function Tank1::create(%block)
{
   %unit = Wheels1.create();
   %turret = Turret1.create();
   %barrel = Barrel1.create();
   
   %unit.mountObject(%turret, 0);
   %turret.mountObject(%barrel, 0);
   
   return %unit;
}
