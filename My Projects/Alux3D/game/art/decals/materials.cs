// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(DECAL_scorch)
{
   baseTex[0] = "./scorch_decal.png";

   translucent = true;
   translucentBlendOp = None;
   translucentZWrite = true;
   alphaTest = true;
   alphaRef = 84;
};

singleton Material(DECAL_RocketEXP)
{
   baseTex[0] = "art/decals/rBlast";

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = LerpAlpha;
   translucentZWrite = true;
};

singleton Material(DECAL_bulletHole)
{
   baseTex[0] = "art/decals/Bullet Holes/BulletHole_Walls.dds";

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = LerpAlpha;
   translucentZWrite = true;
};

singleton Material(DECAL_defaultblobshadow)
{
   baseTex[0] = "art/decals/defaultblobshadow";

   translucent = true;
   translucentBlendOp = LerpAlpha;
   translucentZWrite = true;
   alphaTest = false;
   //alphaRef = 64;
   //emissive[0] = "1";
};
