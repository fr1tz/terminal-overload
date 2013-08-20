// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(DECAL_WpnRaptorProjectile)
{

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = "LerpAlpha";
   translucentZWrite = "0";
   mapTo = "rBlast";
   diffuseColor[0] = "0 1 0.929412 1";
   diffuseMap[0] = "art/decals/rBlast.png";
   glow[0] = "0";
   emissive[0] = "0";
   castShadows = "0";
   materialTag0 = "Miscellaneous";
   animFlags[0] = "0x00000000";
   scrollDir[0] = "1 1";
   scrollSpeed[0] = "0";
   showFootprints = "0";
};
