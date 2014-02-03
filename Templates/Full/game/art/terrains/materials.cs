// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// Sample grass
// ----------------------------------------------------------------------------

singleton Material(TerrainFX_grass1)  
{  
   mapTo = "grass1";  
   footstepSoundId = 0;  
   terrainMaterials = "1";  
   ShowDust = "1";  
   showFootprints = "1"; 
   materialTag0 = "Terrain"; 
   effectColor[0] = "0.42 0.42 0 1";
   effectColor[1] = "0.42 0.42 0 1";
   impactSoundId = "0";
};  

new TerrainMaterial()
{
   internalName = "grass1";
   diffuseMap = "art/terrains/Example/grass1";
   detailMap = "art/terrains/Example/grass1_d";
   detailSize = "10";
   isManaged = "1";
   detailBrightness = "1";
   Enabled = "1";
   diffuseSize = "200";
};

singleton Material(TerrainFX_grass1dry)  
{  
   mapTo = "grass1-dry";  
   footstepSoundId = 0;  
   terrainMaterials = "1";  
   ShowDust = "1";  
   showFootprints = "1";
   materialTag0 = "Terrain";  
   effectColor[0] = "0.63 0.55 0 1";
};  

new TerrainMaterial()
{
   internalName = "grass1-dry";
   diffuseMap = "art/terrains/Example/grass1-dry";
   detailMap = "art/terrains/Example/grass1-dry_d";
   detailSize = "10";
   detailDistance = "100";
   isManaged = "1";
   detailBrightness = "1";
   Enabled = "1";
   diffuseSize = "250";
   detailStrength = "2";
};

singleton Material(TerrainFX_dirt_grass)  
{  
   mapTo = "dirt_grass";  
   footstepSoundId = 0;  
   terrainMaterials = "1";  
   ShowDust = "1";  
   showFootprints = "1";
   materialTag0 = "Terrain";  
   effectColor[0] = "0.63 0.55 0 1";
   effectColor[1] = "0.63 0.55 0 0";
};  

new TerrainMaterial()
{
   internalName = "dirt_grass";
   diffuseMap = "art/terrains/Example/dirt_grass";
   detailMap = "art/terrains/Example/dirt_grass_d";
   detailSize = "5";
   detailDistance = "100";
   isManaged = "1";
   detailBrightness = "1";
   Enabled = "1";
   diffuseSize = "200";
};

// ----------------------------------------------------------------------------
// Sample rock
// ----------------------------------------------------------------------------

singleton Material(TerrainFX_rocktest)  
{  
   mapTo = "rocktest";  
   footstepSoundId = "1";  
   terrainMaterials = "1";  
   ShowDust = "1";  
   showFootprints = "1"; 
   materialTag0 = "Terrain"; 
   impactSoundId = "1";
   effectColor[0] = "0.25 0.25 0.25 1";
   effectColor[1] = "0.25 0.25 0.25 0";
};  

new TerrainMaterial()
{
   internalName = "rocktest";
   diffuseMap = "art/terrains/Example/rocktest";
   detailMap = "art/terrains/Example/rocktest_d";
   detailSize = "10";
   detailDistance = "100";
   isManaged = "1";
   detailBrightness = "1";
   Enabled = "1";
   diffuseSize = "400";
};

// ----------------------------------------------------------------------------
// Sample sand
// ----------------------------------------------------------------------------

singleton Material(TerrainFX_sand)  
{  
   mapTo = "sand";  
   footstepSoundId = "3";  
   terrainMaterials = "1";  
   ShowDust = "1";  
   showFootprints = "1"; 
   materialTag0 = "Terrain";  
   specularPower[0] = "1";
   effectColor[0] = "0.84 0.71 0.5 1";
   effectColor[1] = "0.84 0.71 0.5 0.349";
};  

new TerrainMaterial()
{
   internalName = "sand";
   diffuseMap = "art/terrains/Example/sand";
   detailMap = "art/terrains/Example/sand_d";
   detailSize = "10";
   detailDistance = "100";
   isManaged = "1";
   detailBrightness = "1";
   Enabled = "1";
   diffuseSize = "200";
};
