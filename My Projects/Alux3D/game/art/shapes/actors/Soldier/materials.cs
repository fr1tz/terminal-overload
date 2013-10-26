// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Mat_Soldier_Main)
{
   mapTo = "base_Soldier_Main";

   normalMap[0] = "art/shapes/actors/Soldier/Soldier_N.dds";
   specularMap[0] = "art/shapes/actors/Soldier/Soldier_Spec.dds";

   diffuseColor[0] = "0.454902 0.454902 0.454902 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = 10;

   doubleSided = false;
   translucent = "0";
   showFootprints = "0";
   materialTag0 = "Player";
   detailMap[0] = "content/fr1tz/alux1/textures/placeholder.png";
   detailScale[0] = "16 16";
   glow[0] = "0";
   emissive[0] = "0";
   translucentBlendOp = "LerpAlpha";
   diffuseMap[0] = "content/fr1tz/alux1/textures/placeholder.png";
   scrollDir[0] = "1 1";
   scrollSpeed[0] = "0.118";
   animFlags[0] = "0x00000000";
};

singleton Material(Mat_Soldier_Dazzle)
{
   mapTo = "base_Soldier_Dazzle";

   diffuseMap[0] = "Soldier_Dazzle.dds";

   diffuseColor[0] = "1 1 1 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = 10;

   doubleSided = false;
   translucent = "1";
   translucentBlendOp = "Add";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   showFootprints = "0";
   materialTag0 = "Player";
};

singleton Material(soldier_rigged_BoundsMaterial)
{
   mapTo = "BoundsMaterial";
   diffuseColor[0] = "0.0705882 1 0 0.27";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
};

singleton Material(soldier_rigged_ShapeBounds)
{
   mapTo = "ShapeBounds";
   diffuseColor[0] = "0.164706 1 0 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   materialTag0 = "Player";
};

//-----------------------------------------------------------------------------
// Soldier Skins
// Add names to PlayerData.availableSkins list in art/datablock/player.cs

singleton Material(Mat_Team1_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Team1_Soldier_Main";
   diffuseColor[0] = "0.996078 0.992157 0.992157 1";
   diffuseMap[0] = "art/shapes/actors/Soldier/Soldier_Red_Dif.dds";
   normalMap[0] = "art/shapes/actors/Soldier/Soldier_N.dds";
   specularMap[0] = "art/shapes/actors/Soldier/Soldier_Spec.dds";
   glow[0] = "0";
   emissive[0] = "0";
};

singleton Material(Mat_Team2_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Team2_Soldier_Main";
};

singleton Material(Mat_DarkBlue_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "DarkBlue_Soldier_Main";
   diffuseMap[0] = "Soldier_DarkBlue_Dif.dds";
};

singleton Material(Mat_DarkGreen_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "DarkGreen_Soldier_Main";
   diffuseMap[0] = "Soldier_DarkGreen_Dif.dds";
};

singleton Material(Mat_LightGreen_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "LightGreen_Soldier_Main";
   diffuseMap[0] = "Soldier_LightGreen_Dif.dds";
};

singleton Material(Mat_Orange_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Orange_Soldier_Main";
   diffuseMap[0] = "Soldier_Orange_Dif.dds";
};

singleton Material(Mat_Red_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Red_Soldier_Main";
   diffuseMap[0] = "Soldier_Red_Dif.dds";
};

singleton Material(Mat_Teal_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Teal_Soldier_Main";
   diffuseMap[0] = "Soldier_Teal_Dif.dds";
};

singleton Material(Mat_Violet_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Violet_Soldier_Main";
   diffuseMap[0] = "Soldier_Violet_Dif.dds";
};

singleton Material(Mat_Yellow_Soldier_Main : Mat_Soldier_Main)
{
   mapTo = "Yellow_Soldier_Main";
   diffuseMap[0] = "Soldier_Yellow_Dif.dds";
};
