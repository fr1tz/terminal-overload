// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DebrisData(WpnSG1Shell)
{
   shapeFile = "content/torque3d/3.0/shapes/weapons/shared/RifleShell.DAE";
   lifetime = 6.0;
   minSpinSpeed = 300.0;
   maxSpinSpeed = 400.0;
   elasticity = 0.65;
   friction = 0.05;
   numBounces = 5;
   staticOnMaxBounce = true;
   snapOnMaxBounce = false;
   ignoreWater = true;
   fade = true;
};

