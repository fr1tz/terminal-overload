// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSG1ProjectileDecal)
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

datablock ShotgunProjectileData(WpnSG1Projectile)
{
   projectileShapeName = "content/fr1tz/notc1/shapes/smg1/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 9;
	range = 500;
	muzzleSpreadRadius = 0.5;
	referenceSpreadRadius = 1.0;
	referenceSpreadDistance = 25;

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 10;
   radiusDamage        = 0;
   damageRadius        = 0;
   areaImpulse         = 0;
   impactForce         = 500;

   explosion           = "WpnSG1ProjectileExplosion";
   decal               = "WpnSG1ProjectileDecal";

   muzzleVelocity      = 5;
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 992;
   fadeDelay           = 1472;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //ParticleEmitter = "WpnSG1ProjectileEmitter";
   //lightDesc = "WpnSG1ProjectileLightDesc";
};

function WpnSG1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

