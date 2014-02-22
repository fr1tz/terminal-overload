// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnMG1ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnMG1ProjectileDecal)
{
   Material = "fr1tz_notc1_shapes_smg1_projectile_p1_decalmat";
   size = "0.25";
   lifeSpan = "5000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "3";
   textureCoords[0] = "0 0 0.5 0.5";
   textureCoords[1] = "0.5 0 0.5 0.5";
   textureCoords[2] = "0 0.5 0.5 0.5";
   textureCoords[3] = "0.5 0.5 0.5 0.5";
};

datablock ProjectileData(WpnMG1Projectile)
{
   projectileShapeName = "content/fr1tz/notc1/shapes/smg1/projectile/p1/shape.dae";

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 20;
   radiusDamage        = 0;
   damageRadius        = 0;
   areaImpulse         = 0;
   impactForce         = 250;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   explosion           = "WpnMG1ProjectileExplosion";
   decal               = "WpnMG1ProjectileDecal";

   muzzleVelocity      = 400;
   velInheritFactor    = 1.0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 5.0;
   //lightDesc = "WpnMG1ProjectileLightDesc";
};

function WpnMG1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

