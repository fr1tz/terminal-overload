// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(fr1tz_mis_alux3d_frontline2_snowFX)
{
   mapTo = "fr1tz_mis_alux3d_frontline2_snow";
   footstepSoundId = "3";
   terrainMaterials = "1";
   ShowDust = "0";
   showFootprints = "true";
   materialTag0 = "Terrain";
   effectColor[0] = "0.603922 0.505882 0.4 1";
   effectColor[1] = "0.701961 0.631373 0.552941 0";
   diffuseMap[0] = "library/texture/nat/Snow.jpg";
   normalMap[0] = "library/texture/nat/normal1.png";
   castShadows = "0";
   detailMap[0] = "library/texture/nat/detail1.jpg";
   detailScale[0] = "1 1";
};

new TerrainMaterial()
{
   internalName = "fr1tz_mis_alux3d_frontline2_snow";
   diffuseMap = "library/texture/nat/Snow";
   diffuseSize = "16";
   detailMap = "library/texture/nat/detail1";
   detailSize = "16";
   detailDistance = "200";
   detailStrength = "1";
   parallaxScale = "0";
   normalMap = "library/texture/nat/normal1";
};

