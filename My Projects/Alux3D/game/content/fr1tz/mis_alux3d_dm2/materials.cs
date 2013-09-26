// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(fr1tz_mis_alux3d_dm2_ter1FX)
{
   mapTo = "fr1tz_mis_alux3d_dm2_ter1";
   footstepSoundId = 0;
   terrainMaterials = "1";
   ShowDust = "0";
   showFootprints = "true";
   materialTag0 = "Terrain";
   effectColor[0] = "0.603922 0.505882 0.4 1";
   effectColor[1] = "0.701961 0.631373 0.552941 0";
};

new TerrainMaterial()
{
   internalName = "fr1tz_mis_alux3d_dm2_ter1";
   diffuseMap = "art/terrains/Example/stone";
   diffuseSize = "400";
   detailMap = "art/terrains/Example/stone_d";
   detailSize = "10";
   detailDistance = "400";
   parallaxScale = "0";
   normalMap = "art/terrains/Example/stone_n";
};

singleton Material(fr1tz_mis_alux3d_dm2_grid1FX)
{
   mapTo = "fr1tz_mis_alux3d_dm2_grid1";
   footstepSoundId = 0;
   terrainMaterials = "1";
   ShowDust = "true";
   showFootprints = "true";
   materialTag0 = "Terrain";
   effectColor[0] = "0.00784314 0.0313726 0.996078 1";
   effectColor[1] = "0.0313726 0.996078 0.00784314 1";
};

new TerrainMaterial()
{
   internalName = "fr1tz_mis_alux3d_dm2_grid1";
   diffuseMap = "library/texture/alux3d/dm2/grid1";
   diffuseSize = "4";
   detailMap = "library/texture/alux3d/dm2/grid1";
   detailSize = "4";
   detailDistance = "500";
   normalMap = "library/texture/alux3d/dm2/grid1_n";
};

