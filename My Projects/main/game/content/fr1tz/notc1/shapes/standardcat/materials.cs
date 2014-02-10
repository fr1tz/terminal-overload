
new Material(fr1tz_notc1_shapes_standardcat_footprint)
{
   diffuseMap[0] = "content/fr1tz/notc1/shapes/standardcat/footprint";
   vertColor[0] = true;
   translucent = true;
   castShadows = "0";
   translucentZWrite = "1";
   materialTag0 = "Player";
   mapTo = "footprint";
   glow[0] = "0";
   emissive[0] = "1";
   translucentBlendOp = "AddAlpha";
   showFootprints = "0";
};

singleton Material(fr1tz_notc1_shapes_standardcat_mat2)
{
   mapTo = "armor_red0024";
   glow[0] = "0";
   glow[1] = "1";
   emissive[0] = "0";
   emissive[1] = "1";
   translucentBlendOp = "None";
   animFlags[1] = "0x00000000";
   scrollDir[1] = "0 0";
   scrollSpeed[1] = "0";
   diffuseColor[0] = "0.00392157 0.00392157 0.00392157 1";
   diffuseColor[1] = "0.988235 0.65098 0.0156863 1";
   specularStrength[1] = "0";
   diffuseMap[0] = "content/fr1tz/notc1/textures/white.128.alpha25.png";
   materialTag0 = "Miscellaneous";
   normalMap[0] = "content/fr1tz/notc1/textures/grid128.12.h2.n2.png";
   pixelSpecular[0] = "1";
   diffuseColor[2] = "0.00392157 0.00392157 0.00392157 0";
   glow[2] = "1";
   emissive[2] = "1";
   diffuseColor[3] = "0.00392157 0.00392157 0.00392157 0";
   doubleSided = "1";
   translucent = "0";
   translucentZWrite = "1";
   alphaRef = "0";
   showFootprints = "0";
   cubemap = "fr1tz_notc1_cubemaps_chrome1";
   diffuseMap[1] = "content/fr1tz/notc1/textures/grid.128.8.png";
};

singleton Material(fr1tz_notc1_shapes_standardcat_mat1)
{
   mapTo = "base";
   diffuseMap[0] = "content/fr1tz/notc1/shapes/standardcat/base.png";
   glow[0] = "0";
   emissive[0] = "0";
   diffuseColor[1] = "0.996078 0.996078 0.992157 1";
   diffuseMap[1] = "content/fr1tz/notc1/textures/grid.128.8.png";
   materialTag0 = "Miscellaneous";
   glow[1] = "0";
   emissive[1] = "0";
   translucentBlendOp = "None";
   translucentZWrite = "1";
   showFootprints = "0";
};
