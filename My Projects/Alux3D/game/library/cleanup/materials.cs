// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(DECAL_WpnRaptorProjectile)
{

   vertColor[0] = true;
   translucent = true;
   translucentBlendOp = "LerpAlpha";
   translucentZWrite = true;
   mapTo = "rBlast";
   diffuseColor[0] = "1 0.811765 0 1";
   diffuseMap[0] = "library/texture/alux3d/rBlastInv.png";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   materialTag0 = "Miscellaneous";
};
