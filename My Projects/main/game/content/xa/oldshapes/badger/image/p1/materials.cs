// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(FP_Badger_Base)
{
   mapTo = "FP_Badger_Base";
   diffuseMap[0] = "./FP_Badger_D.dds";
   normalMap[0] = "./FP_Badger_N.dds";
   specularMap[0] = "./FP_Badger_S.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   useAnisotropic[0] = "1";
};

singleton Material(TP_Badger_Base)
{
   mapTo = "TP_Badger_Base";
   diffuseMap[0] = "./TP_Badger_D.dds";
   normalMap[0] = "./TP_Badger_N.dds";
   specularMap[0] = "./TP_Badger_D.dds";
   specular[0] = "1.0 1.0 1.0 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   pixelSpecular[0] = "1";
};

singleton Material(Badger_MuzzleFlash_Base)
{
   mapTo = "Badger_MuzzleFlash_Base";
   diffuseMap[0] = "./Badger_MuzzleFlash.dds";
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


singleton Material(TP_Badger_FP_Badger_Base)
{
   mapTo = "FP_Badger_Base";
   diffuseMap[0] = "content/xa/oldshapes/badger/image/p1/FP_Badger_D";
   specularPower[0] = "10";
   specularMap[0] = "content/xa/oldshapes/badger/image/p1/FP_Badger_S";
   translucentBlendOp = "None";
   diffuseColor[0] = "0.992157 0.996078 0.996078 1";
   glow[0] = "0";
   emissive[0] = "0";
};

singleton Material(TP_Badger_Base)
{
   mapTo = "TP_Badger_Base";
   diffuseMap[0] = "TP_Badger_D";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
};

singleton Material(TP_Badger_Badger_MuzzleFlash_Base)
{
   mapTo = "Badger_MuzzleFlash_Base";
   diffuseMap[0] = "content/xa/oldshapes/badger/image/p1/Badger_MuzzleFlash";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   translucentBlendOp = "AddAlpha";
   diffuseColor[0] = "0 0.172549 0.172549 1";
   animFlags[0] = "0x00000004";
   waveFreq[0] = "5.313";
   waveAmp[0] = "0.094";
};
