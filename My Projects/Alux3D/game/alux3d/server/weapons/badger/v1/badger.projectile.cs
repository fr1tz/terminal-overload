// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnBadgerProjectile)
{
   projectileShapeName = "content/alux3d/release1/shapes/badger/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = "250";
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 20;
   radiusDamage        = 0;
   damageRadius        = 0.5;
   areaImpulse         = 0.5;
   impactForce         = 500;

   explosion           = "WpnBadgerProjectileExplosion";
   decal               = "bulletHoleDecal";

   muzzleVelocity      = "600"; // 900
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 992;
   fadeDelay           = 1472;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
};

function WpnBadgerProjectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   // Apply impact force from the projectile.

   // Apply damage to the object all shape base objects
   if ( %col.getType() & $TypeMasks::GameBaseObjectType )
      %col.damage(%obj,%pos,%this.directDamage,"BulletProjectile");
}

