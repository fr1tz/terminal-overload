// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(xa_notc_mis_dm1_mat0)
{
   footstepSoundId = 0;
   terrainMaterials = "1";
   ShowDust = "true";
   showFootprints = "true";
   effectColor[0] = "0.00784314 0.0313726 0.996078 1";
   effectColor[1] = "0.0313726 0.996078 0.00784314 1";
   glow[0] = "0";
   emissive[0] = "0";
   detailScale[0] = "64 64";
   scrollDir[0] = "0 -0.03";
   scrollSpeed[0] = "1.647";
   castShadows = "0";
   translucentBlendOp = "None";
   parallaxScale[0] = "1";
   useAnisotropic[0] = "1";
   diffuseColor[0] = "0.00392157 0.00392157 0.00392157 1";
   diffuseMap[1] = "content/xa/notc/mis/dm1/textures/grid1.png";
   glow[1] = "1";
   emissive[1] = "1";
   detailScale[2] = "64 64";
   detailScale[1] = "64 64";
   diffuseColor[2] = "0.00392157 0.00392157 0.00392157 1";
   diffuseColor[1] = "0.992157 0.992157 0.992157 1";
};

singleton Material(xa_notc_mis_dm1_termat1fx)
{
   mapTo = "fr1tz_mis_notc_dm1_termat1";
   footstepSoundId = "2";
   terrainMaterials = "1";
   ShowDust = "true";
   showFootprints = "1";
   materialTag0 = "Terrain";
   effectColor[0] = "0.00784314 0.94902 0.996078 1";
   effectColor[1] = "0.996078 0.00784314 0.901961 1";
   glow[0] = "0";
   emissive[0] = "0";
   detailScale[0] = "64 64";
   scrollDir[0] = "0 -0.03";
   scrollSpeed[0] = "1.647";
   castShadows = "0";
   translucentBlendOp = "None";
   parallaxScale[0] = "1";
   useAnisotropic[0] = "1";
   diffuseColor[0] = "0.0235294 1 0 1";
   diffuseMap[1] = "content/xa/notc/mis/dm1/textures/grid1.png";
   glow[1] = "1";
   emissive[1] = "1";
   detailScale[2] = "64 64";
   detailScale[1] = "64 64";
   diffuseColor[2] = "0.00392157 0.00392157 0.00392157 1";
   diffuseColor[1] = "0.992157 0.992157 0.992157 1";
   impactSoundId = "2";
};

new TerrainMaterial()
{
   internalName = "xa_notc_mis_dm1_termat1";
   diffuseMap = "content/xa/notc/mis/dm1/textures/xa_notc_mis_dm1_termat1";
   diffuseSize = "16";
   detailSize = "4";
   detailDistance = "500";
   detailMap = "content/xa/rotc/p.5.3/textures/rotc/zone.grid";
};

