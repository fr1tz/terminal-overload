// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Undercity Materials
//--------------------------------------------

singleton Material(ucityHealthKit)
{
   mapTo = "healthkit";
   diffuseMap[0] = "healthkit_d";
   normalMap[0] = "healthkit_n";
   translucent=false;
   pixelSpecular[0] = true;
   specular[0] = "0.5 0.5 0.5 0.5";
   specularPower[0] = 32.0;
   //detailMap[0] = "detail";
};
