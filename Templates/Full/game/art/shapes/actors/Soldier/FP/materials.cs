// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(Mat_FP_Soldier_Arms_Main)
{
   mapTo = "base_FP_Soldier_Arms_Main";
   diffuseMap[0] = "art/shapes/actors/Soldier/FP/FP_SoldierArms_D";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucentBlendOp = "None";
   normalMap[0] = "art/shapes/actors/Soldier/FP/FP_SoldierArms_N.dds";
   specularMap[0] = "art/shapes/actors/Soldier/FP/FP_SoldierArms_S.dds";
};

//-----------------------------------------------------------------------------
// Soldier Skins
// Add names to PlayerData.availableSkins list in art/datablock/player.cs

singleton Material(Mat_DarkBlue_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "DarkBlue_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_DarkBlue_Dif.dds";
};

singleton Material(Mat_DarkGreen_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "DarkGreen_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_DarkGreen_Dif.dds";
};

singleton Material(Mat_LightGreen_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "LightGreen_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_LightGreen_Dif.dds";
};

singleton Material(Mat_Orange_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "Orange_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_Orange_Dif.dds";
};

singleton Material(Mat_Red_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "Red_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_Red_Dif.dds";
};

singleton Material(Mat_Teal_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "Teal_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_Teal_Dif.dds";
};

singleton Material(Mat_Violet_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "Violet_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_Violet_Dif.dds";
};

singleton Material(Mat_Yellow_FP_Soldier_Arms_Main : Mat_FP_Soldier_Arms_Main)
{
   mapTo = "Yellow_FP_Soldier_Arms_Main";
   diffuseMap[0] = "Soldier_FPSarms_Yellow_Dif.dds";
};
