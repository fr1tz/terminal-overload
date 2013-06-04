// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(ProxMine_Base)
{
   mapTo = "ProxMine_Base";
   diffuseMap[0] = "ProxMine_D.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   normalMap[0] = "ProxMine_N.dds";
   pixelSpecular[0] = "1";
   specularMap[0] = "ProxMine_S.dds";
   useAnisotropic[0] = "1";
};

singleton Material(ProxMine_Glow_Base)
{
   mapTo = "ProxMine_Glow_Base";
   diffuseMap[0] = "ProxMine_Glow.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
   glow[0] = "1";
   emissive[0] = "1";
   translucentBlendOp = "Add";
};
