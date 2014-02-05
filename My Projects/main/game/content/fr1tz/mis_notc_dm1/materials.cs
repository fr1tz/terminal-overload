// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(fr1tz_mis_notc_dm1_grid1FX)
{
   mapTo = "fr1tz_mis_notc_dm1_grid1";
   footstepSoundId = 0;
   terrainMaterials = "1";
   ShowDust = "true";
   showFootprints = "true";
   materialTag0 = "Terrain";
   effectColor[0] = "0.00784314 0.0313726 0.996078 1";
   effectColor[1] = "0.0313726 0.996078 0.00784314 1";
   diffuseMap[0] = "content/fr1tz/mis_notc_dm1/textures/grid1.png";
   glow[0] = "1";
   emissive[0] = "1";
};

new TerrainMaterial()
{
   internalName = "fr1tz_mis_notc_dm1_grid1";
   diffuseSize = "16";
   detailSize = "4";
   detailDistance = "500";
   detailMap = "content/fr1tz/mis_notc_dm1/textures/grid1";
   diffuseMap = "content/fr1tz/mis_notc_dm1/textures/metal";
};

