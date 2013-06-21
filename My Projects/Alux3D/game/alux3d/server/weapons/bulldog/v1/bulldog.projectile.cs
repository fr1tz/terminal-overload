// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnBulldogProjectile)
{
   projectileShapeName = "library/shape/alux3d/bulldog/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 10;
	range = "250";
	muzzleSpreadRadius = 0.1;
	referenceSpreadRadius = 1.0;
	referenceSpreadDistance = 30;

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 15;
   radiusDamage        = 0;
   damageRadius        = 0.5;
   areaImpulse         = 0.5;
   impactForce         = 600;

   explosion           = "WpnBulldogProjectileExplosion";
   decal               = "bulletHoleDecal";

   muzzleVelocity      = "600"; // 900
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = "3968";
   fadeDelay           = 1472;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   ParticleEmitter = "WpnBulldogProjectileEmitter";
};

function WpnBulldogProjectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   // Apply impact force from the projectile.

   // Apply damage to the object all shape base objects
   if ( %col.getType() & $TypeMasks::GameBaseObjectType )
      %col.damage(%obj,%pos,%this.directDamage,"BulletProjectile");
}

