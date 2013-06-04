// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This is the default save location for any Decal datablocks created in the
// Decal Editor (this script is executed from onServerCreated())

datablock DecalData(ScorchBigDecal)
{
   Material = "DECAL_scorch";
   size = "5.0";
   lifeSpan = "50000";
};

datablock DecalData(ScorchRXDecal)
{
   Material = "DECAL_RocketEXP";
   size = "5.0";
   lifeSpan = "20000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   clippingAngle = "80";
   screenStartRadius = "200";
   screenEndRadius = "100";
};

datablock DecalData(bulletHoleDecal)
{
   Material = "DECAL_bulletHole";
   size = "0.25";
   lifeSpan = "5000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
};
