// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(FP_Ryder_Base)
{
   mapTo = "FP_Ryder_Base";
   diffuseMap[0] = "./FP_Ryder_D.dds";
   normalMap[0] = "./FP_Ryder_N.dds";
   specularMap[0] = "./FP_Ryder_S.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   useAnisotropic[0] = "1";
};

singleton Material(TP_Ryder_Base)
{
   mapTo = "TP_Ryder_Base";
   diffuseMap[0] = "./TP_Ryder_D.dds";
   normalMap[0] = "./TP_Ryder_N.dds";
   specularMap[0] = "./TP_Ryder_D.dds";
   specular[0] = "1.0 1.0 1.0 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   pixelSpecular[0] = "1";
};

singleton Material(Ryder_MuzzleFlash_Base)
{
   mapTo = "Ryder_MuzzleFlash_Base";
   diffuseMap[0] = "./Ryder_MuzzleFlash.dds";
   diffuseColor[0] = "0.05 0.05 0.05 1";
   specular[0] = "0 0 0 1";
   specularPower[0] = "10";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
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

