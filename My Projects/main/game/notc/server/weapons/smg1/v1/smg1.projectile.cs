// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSMG1Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/smg1/projectile/p2/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 1000;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   missEnemyEffect = GenericMissEnemyEffect1;
 
   energyDrain = 5; // how much energy does firing this projectile drain?

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 20;
	impactImpulse      = 600;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;

   explosion           = "WpnSMG1ProjectileExplosion";
   decal               = "WpnSMG1ProjectileDecal";
   //particleEmitter     = "WpnSMG1ProjectileParticleEmitter";
   laserTrail[0]       = WpnSMG1ProjectileLaserTrail0;
   laserTrail[1]       = WpnSMG1ProjectileLaserTrail1;

   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //lightDesc = "WpnSMG1ProjectileLightDesc";
};

function WpnSMG1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

