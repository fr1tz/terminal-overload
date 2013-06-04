// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Cheetah_Main)
{
   mapTo = "Cheetah_Main";
   diffuseMap[0] = "art/shapes/Cheetah/Cheetah_D";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   normalMap[0] = "art/shapes/Cheetah/Cheetah_N";
   specularMap[0] = "art/shapes/Cheetah/Cheetah_S";
};

singleton Material(Cheetah_TailLights)
{
   mapTo = "Cheetah_TailLights";
   diffuseColor[0] = "0.588235 0 0 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   glow[0] = "1";
   emissive[0] = "1";
};

singleton Material(Cheetah_MuzzleFlash)
{
   mapTo = "Cheetah_MuzzleFlash";
   diffuseMap[0] = "art/shapes/Cheetah/Cheetah_MuzzleFlash_D";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "AddAlpha";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   translucent = "1";
};

singleton Material(Cheetah_Collider)
{
   mapTo = "Collider";
   diffuseColor[0] = "1 0 0 0.75";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
};