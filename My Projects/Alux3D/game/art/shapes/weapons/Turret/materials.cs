// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Turret_Base)
{
   mapTo = "Turret_Base";
   diffuseMap[0] = "art/shapes/weapons/Turret/Turret_D.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   normalMap[0] = "art/shapes/weapons/Turret/Turret_N.dds";
   pixelSpecular[0] = "1";
   specularMap[0] = "art/shapes/weapons/Turret/Turret_D.dds";
   useAnisotropic[0] = "1";
   materialTag0 = "Weapon";
};

singleton Material(Turret_Lazer_Base)
{
   mapTo = "Turret_Lazer_Base";
   diffuseMap[0] = "art/shapes/weapons/Turret/Turret_Lazer_D.dds";
   diffuseColor[0] = "1 1 1 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
   doubleSided = "0";
   translucentBlendOp = "Add";
   animFlags[0] = "0x00000000";
   scrollDir[0] = "0 0";
   rotSpeed[0] = "0";
   rotPivotOffset[0] = "0 0";
   waveFreq[0] = "0";
   waveAmp[0] = "0";
   castShadows = "1";
   translucentZWrite = "0";
   materialTag0 = "Weapon";
   materialTag1 = "FX";
};

singleton Material(Turret_Lazer_Base)
{
   mapTo = "Turret_Lazer_Base";
   diffuseMap[0] = "./Turret_Lazer_D.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
   translucentBlendOp = "Add";
};

singleton Material(CollisionMat)
{
   mapTo = "CollisionMat";
   diffuseColor[0] = "1 0 0 0.75";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
};


singleton Material(Turret_MuzzleFlash_Base)
{
   mapTo = "Turret_MuzzleFlash_Base";
   diffuseColor[0] = "1 1 1 1";
   diffuseMap[0] = "art/shapes/weapons/Turret/Turret_MuzzleFlash.dds";
   specular[0] = "0 0 0 1";
   specularPower[0] = "10";
   glow[0] = "1";
   emissive[0] = "1";
   doubleSided = "1";
   animFlags[0] = "0x00000005";
   scrollDir[0] = "-0.15 -0.15";
   rotSpeed[0] = "0.25";
   rotPivotOffset[0] = "-0.5 -0.5";
   waveFreq[0] = "5.313";
   waveAmp[0] = "0.016";
   castShadows = "0";
   translucent = "1";
   translucentBlendOp = "Add";
   translucentZWrite = "0";
   materialTag1 = "FX";
   materialTag0 = "Weapon";
};
