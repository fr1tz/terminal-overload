// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(WpnMG1Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mg1/projectile/p1/shape.dae";

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 20;
	impactImpulse      = 250;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
 
   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 10;
   missEnemyEffect = WpnMG1ProjectileMissEnemyEffect;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   explosion           = "WpnMG1ProjectileExplosion";
   decal               = "WpnMG1ProjectileDecal";
   particleEmitter     = "WpnMG1ProjectileParticleEmitter";
   laserTrail[0]       = "WpnMG1ProjectileLaserTrail";

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

