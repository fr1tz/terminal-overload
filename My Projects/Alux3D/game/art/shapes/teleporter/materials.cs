// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Teleporter)
{
   mapTo = "teleporter";
   diffuseMap[0] = "Teleporter";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
};

singleton Material(teleporter_collision)
{
   mapTo = "collision";
   diffuseColor[0] = "0.588235 0.588235 0.588235 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
};

singleton Material(Teleporter_Main)
{
   mapTo = "Teleporter_Main";
   diffuseMap[0] = "art/shapes/Teleporter/Teleporter_d.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "23";
   translucentBlendOp = "None";
   normalMap[0] = "art/shapes/Teleporter/Teleporter_n.dds";
   specularMap[0] = "art/shapes/Teleporter/Teleporter_s.dds";
};

singleton Material(Teleporter_Glow_Main)
{
   mapTo = "Teleporter_Glow_Main";
   diffuseMap[0] = "art/shapes/Teleporter/Teleporter_glow.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";
   translucent = "1";
   glow[0] = "1";
   doubleSided = "1";
   castShadows = "0";
   translucentBlendOp = "Add";
   scrollDir[0] = "0 0";
   scrollSpeed[0] = "0";
   waveFreq[0] = "0.781";
   waveAmp[0] = "0.203";
   animFlags[0] = "0x00000001";
   emissive[0] = "1";
};

singleton Material(Teleporter_Animated_GlowU_Main)
{
   mapTo = "Teleporter_Animated_GlowU_Main";
   diffuseMap[0] = "art/shapes/Teleporter/Teleporter_glow.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";
   translucent = "1";
   emissive[0] = "1";
   translucentBlendOp = "Add";
   animFlags[0] = "0x00000001";
   scrollDir[0] = "-1 0";
   scrollSpeed[0] = "0.706";
};

singleton Material(Teleporter_Animated_GlowV_Main)
{
   mapTo = "Teleporter_Animated_GlowV_Main";
   diffuseMap[0] = "art/shapes/Teleporter/Teleporter_glow.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";
   translucent = "1";
   emissive[0] = "0";
   animFlags[0] = "0x00000001";
   scrollDir[0] = "0 1";
   scrollSpeed[0] = "0.353";
   translucentBlendOp = "Add";
   castShadows = "0";
};

singleton Material(Teleporter_GlowWave_Main)
{
   mapTo = "Teleporter_GlowWave_Main";
   diffuseMap[0] = "art/shapes/Teleporter/Teleporter_glow.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";
   translucent = "1";
   glow[0] = "1";
   doubleSided = "1";
   animFlags[0] = "0x00000005";
   scrollDir[0] = "0 0.31";
   waveFreq[0] = "0.313";
   waveAmp[0] = "0.094";
   castShadows = "0";
   translucentBlendOp = "Add";
   emissive[0] = "1";
};
