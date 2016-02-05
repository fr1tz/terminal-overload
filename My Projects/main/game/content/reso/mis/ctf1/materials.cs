
new TerrainMaterial()
{
   diffuseMap = "content/o/torque3d/3.0/terrains/Example/sand";
   diffuseSize = "64";
   detailSize = "0.5";
   detailStrength = "0.1";
   detailDistance = "9999";
   macroSize = "4";
   macroStrength = "0.1";
   macroDistance = "9999";
   internalName = "reso_mis_ctf1_termat1";
};

singleton Material(reso_mis_ctf1_termat1)
{
   mapTo = "reso_mis_ctf1_termat1";
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
   glow[1] = "1";
   emissive[1] = "1";
   detailScale[2] = "64 64";
   detailScale[1] = "64 64";
   diffuseColor[2] = "0.00392157 0.00392157 0.00392157 1";
   diffuseColor[1] = "0.992157 0.992157 0.992157 1";
   impactSoundId = "2";
};

