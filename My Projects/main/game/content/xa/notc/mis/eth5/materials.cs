new TerrainMaterial()
{
   detailDistance = "6000";
   internalName = "eth5";
   detailMap = "content/xa/notc/mis/eth5/textures/xa_notc_mis_eth5_grid";
   diffuseSize = "4";
   detailSize = "4";
   detailStrength = "1";
   macroStrength = "0.1";
   diffuseMap = "content/xa/notc/mis/eth5/textures/xa_notc_mis_eth5_grid";
};

singleton Material(xa_notc_mis_eth5_gridfx)
{
   mapTo = "xa_notc_mis_eth5_grid";
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

singleton Material(xa_notc_mis_eth5_territoryzone_terrainmat)
{
   diffuseColor[0] = "1 1 1 1";
   diffuseColorPaletteSlot[0] = "0";
   doubleSided = "0";
   translucentBlendOp = "LerpAlpha";
   parallaxScale[0] = "0";
   castShadows = "0";
   translucent = "0";
   showFootprints = "0";
   glow[0] = "0";
   emissive[0] = "0";
   materialTag0 = "Miscellaneous";
   animFlags[0] = "0x00000000";
   mapTo = "zone.grid.png";
   wireframe[0] = "0";
   diffuseColorPaletteSlot[1] = "0";
   glow[1] = "0";
   emissive[1] = "0";
   wireframe[1] = "0";
   diffuseColor[1] = "1 1 1 0.25";
   diffuseMap[0] = "content/xa/notc/mis/eth5/textures/territory";
   translucentZWrite = "1";
   effectColor[0] = "InvisibleBlack";
};

singleton Material(xa_notc_mis_eth5_territoryzone_bordermat)
{
   diffuseColor[0] = "0.992157 0.992157 0.992157 1";
   diffuseColorPaletteSlot[0] = "1";
   doubleSided = "0";
   translucentBlendOp = "AddAlpha";
   parallaxScale[0] = "0.25";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
   glow[0] = "1";
   emissive[0] = "1";
   materialTag0 = "Miscellaneous";
   wireframe[0] = "0";
   diffuseColorPaletteSlot[1] = "1";
   glow[1] = "1";
   wireframe[1] = "0";
};

singleton Material(xa_notc_mis_eth5_territoryzone_othermat)
{
   diffuseColor[0] = "1 1 1 0.5";
   diffuseColorPaletteSlot[0] = "0";
   doubleSided = "0";
   translucentBlendOp = "LerpAlpha";
   parallaxScale[0] = "0";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
   glow[0] = "0";
   emissive[0] = "0";
   materialTag0 = "Miscellaneous";
   specular[2] = "1 1 1 1";
   diffuseColor[1] = "White";
   translucentZWrite = "1";
};

