// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(DECAL_RBlast)
{
   baseTex[0] = "art/decals/rBlast";

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = LerpAlpha;
   translucentZWrite = true;
};
