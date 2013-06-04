// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Lurker_ScopeScreen_Base)
{
   mapTo = "Lurker_ScopeScreen_Base";
   diffuseMap[0] = "Lurker_D.dds";
   specular[0] = "1 1 1 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   glow[0] = "1";
   emissive[0] = "1";
};

singleton Material(Lurker_Base)
{
   mapTo = "Lurker_Base";
   diffuseMap[0] = "Lurker_D.dds";
   normalMap[0] = "Lurker_N.dds";
   specularMap[0] = "Lurker_S.dds";
   specular[0] = "1 1 1 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   useAnisotropic[0] = "1";
};

singleton Material(Lurker_MuzzleFlash_Base)
{
   mapTo = "Lurker_MuzzleFlash_Base";
   diffuseMap[0] = "Lurker_MuzzleFlash.dds";
   diffuseColor[0] = "0.15 0.15 0.15 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "0";
   doubleSided = "1";
   translucentBlendOp = "Add";
   animFlags[0] = "0x00000005";
   scrollDir[0] = "-0.15 -0.15";
   rotSpeed[0] = "0.25";
   rotPivotOffset[0] = "-0.5 -0.5";
   waveFreq[0] = "5.313";
   waveAmp[0] = "0.016";
   castShadows = "0";
};