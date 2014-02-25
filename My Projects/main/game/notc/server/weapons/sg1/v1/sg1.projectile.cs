// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSG1Projectile)
{
   //projectileShapeName = "content/xa/notc1/shapes/smg1/projectile/p1/shape.dae";

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
   
	energyDrain = 3; // how much energy does firing this projectile drain?

   explosion           = "WpnSG1ProjectileExplosion";
   decal               = "WpnSG1ProjectileDecal";
   particleEmitter     = "WpnSG1ProjectileEmitter";

   muzzleVelocity      = "2000";
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 992;
   fadeDelay           = 1472;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;

   //lightDesc = "WpnSG1ProjectileLightDesc";
};

function WpnSG1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

