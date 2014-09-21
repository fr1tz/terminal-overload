
singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_mat1)
{
   mapTo = "xa_notc_core_shapes_mgl1_projectile_p1_mat1";
   diffuseColor[0] = "0.996078 0.996078 0.992157 1";
   diffuseColorPaletteSlot[0] = "0";
   doubleSided = "1";
   translucentBlendOp = "LerpAlpha";
   glow[0] = "0";
   emissive[0] = "1";
   castShadows = "0";
   translucent = "1";
   diffuseMap[0] = "content/xa/notc/core/textures/grid.128.8.png";
   wireframe[0] = "1";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_mat2)
{
   mapTo = "xa_notc_core_shapes_mgl1_projectile_p1_mat2";
   diffuseColor[0] = "0.996078 0.992157 0.996078 1";
   diffuseMap[0] = "content/xa/notc/core/shapes/mgl1/projectile/p1/trail.png";
   doubleSided = "0";
   translucentBlendOp = "AddAlpha";
   glow[0] = "1";
   emissive[0] = "1";
   translucent = "1";
   diffuseColorPaletteSlot[0] = "0";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_mat3)
{
   mapTo = "xa_notc_core_shapes_mgl1_projectile_p1_mat3";
   diffuseColor[0] = "0.996078 0.996078 0.992157 1";
   diffuseColorPaletteSlot[0] = "0";
   doubleSided = "1";
   translucentBlendOp = "LerpAlpha";
   glow[0] = "0";
   emissive[0] = "1";
   translucent = "1";
   wireframe[0] = "1";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_lasertrail0mat0)
{
   diffuseColor[0] = "0.996078 0.996078 0.996078 1";
   doubleSided = "0";
   translucentBlendOp = "LerpAlpha";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
   glow[0] = "0";
   glowOnly[0] = "0";
   emissive[0] = "1";
   vertColor[0] = "1";
   materialTag0 = "Miscellaneous";
   mapTo = "trail.png";
   diffuseColorPaletteSlot[0] = "0";
   wireframe[0] = "0";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_lasertrail1mat0)
{
   diffuseColor[0] = "0.992157 0.992157 0.992157 1";
   doubleSided = "1";
   translucentBlendOp = "AddAlpha";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
   glow[0] = "0";
   glowOnly[0] = "0";
   emissive[0] = "1";
   vertColor[0] = "1";
   materialTag0 = "Miscellaneous";
   mapTo = "trail.png";
   diffuseColorPaletteSlot[0] = "0";
   wireframe[0] = "1";
   diffuseColor[1] = "1 1 1 0";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_lasertrail2mat0)
{
   diffuseColor[0] = "0.627451 0.627451 0.627451 1";
   doubleSided = "0";
   translucentBlendOp = "LerpAlpha";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
   glow[0] = "1";
   glowOnly[0] = "1";
   emissive[0] = "1";
   vertColor[0] = "1";
   diffuseMap[0] = "content/xa/rotc/p.5.4/textures/rotc/ring1.png";
   materialTag0 = "Miscellaneous";
   mapTo = "trail.png";
   diffuseColorPaletteSlot[0] = "-1";
   wireframe[0] = "1";
};

singleton Material(xa_notc_core_shapes_mgl1_projectile_p1_decalmat)
{
   baseTex[0] = "content/xa/torque3d/3.0/decals/rBlast";

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = LerpAlpha;
   translucentZWrite = true;
};

