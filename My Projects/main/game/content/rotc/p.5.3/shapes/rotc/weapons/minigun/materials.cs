
singleton Material(DefaultMaterial6)
{
   mapTo = "flash.front";
   diffuseMap[0] = "content/rotc/p.5.3/shapes/rotc/weapons/minigun/flash.front";
   glow[1] = "1";
   emissive[1] = "1";
   translucent = "1";
   translucentBlendOp = "AddAlpha";
};

singleton Material(DefaultMaterial5)
{
   mapTo = "image.barrel.blue";
   diffuseMap[0] = "content/rotc/p.5.3/shapes/rotc/weapons/minigun/image.barrel.blue";
   glow[1] = "1";
   emissive[1] = "1";
   castShadows = "0";
   translucent = "1";
   translucentBlendOp = "AddAlpha";
   translucentZWrite = "0";
   alphaRef = "20";
   diffuseMap[1] = "content/rotc/p.5.3/textures/rotc/rainbow1.png";
   materialTag0 = "Miscellaneous";
};

singleton Material(DefaultMaterial4)
{
   mapTo = "image";
   diffuseMap[0] = "content/rotc/p.5.3/shapes/rotc/weapons/minigun/image";
   glow[1] = "1";
   emissive[1] = "1";
   diffuseMap[1] = "content/rotc/p.5.3/textures/rotc/zone.grid.png";
   scrollDir[1] = "0 0.138";
   rotSpeed[1] = "1.529";
   castShadows = "0";
   materialTag0 = "Miscellaneous";
};
