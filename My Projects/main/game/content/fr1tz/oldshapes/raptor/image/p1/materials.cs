// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Raptor_ScopeScreen_Base)
{
   mapTo = "Raptor_ScopeScreen_Base";
   diffuseMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_D.dds";
   specular[0] = "1 1 1 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   glow[0] = "1";
   emissive[0] = "1";
   diffuseColor[0] = "1 0.0705882 0 1";
};

singleton Material(Raptor_Base)
{
   mapTo = "Raptor_Base";
   diffuseMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_D.dds";
   normalMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_N.dds";
   specularMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_S.dds";
   specular[0] = "1 1 1 1";
   specularPower[0] = "16";
   translucentBlendOp = "None";
   useAnisotropic[0] = "1";
   diffuseColor[0] = "1 0 0.0235294 1";
   diffuseColor[1] = "0.454902 0.454902 0.454902 1";
   glow[0] = "1";
   emissive[0] = "1";
};

singleton Material(Raptor_MuzzleFlash_Base)
{
   mapTo = "Raptor_MuzzleFlash_Base";
   diffuseMap[0] = "Raptor_MuzzleFlash.dds";
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

singleton Material(TP_Raptor_Raptor_Base)
{
   mapTo = "Raptor_Base";
   diffuseMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_D.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   diffuseColor[0] = "0.996078 0.996078 0.992157 1";
   glow[0] = "0";
   emissive[0] = "0";
};

singleton Material(TP_Raptor_Raptor_ScopeScreen_Base)
{
   mapTo = "Raptor_ScopeScreen_Base";
   diffuseMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_D.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   diffuseColor[0] = "1 0.745098 0 1";
   glow[0] = "1";
   emissive[0] = "1";
};

singleton Material(TP_Raptor_Raptor_MuzzleFlash_Base)
{
   mapTo = "Raptor_MuzzleFlash_Base";
   diffuseMap[0] = "content/fr1tz/oldshapes/raptor/image/p1/Raptor_MuzzleFlash.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "4";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   translucentBlendOp = "Add";
   animFlags[0] = "0x00000004";
   waveFreq[0] = "5.313";
   waveAmp[0] = "0.125";
   diffuseColor[0] = "0.145098 0.145098 0.145098 1";
};
