// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSMG2Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/smg1/projectile/p2/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   missEnemyEffect = GenericMissEnemyEffect1;
 
   energyDrain = 0; //5 // how much energy does firing this projectile drain?

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 20;
	impactImpulse      = 600;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   tracer = WpnSMG2ProjectileTracer;

   explosion                  = "WpnSMG2ProjectileExplosion";
   impactExplosion[0]         = "WpnSMG2ProjectileHit";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   impactExplosion[1]         = "WpnSMG2ProjectileImpact";
   impactExplosionTypeMask[1] = $TypeMasks::StaticObjectType;
   decal                      = "WpnSMG2ProjectileDecal";
   //particleEmitter          = "WpnSMG2ProjectileParticleEmitter";
   laserTrail[0]              = WpnSMG2ProjectileLaserTrail0;
   laserTrailFlags[0]         = 2;
   //laserTrail[1]            = WpnSMG2ProjectileLaserTrail1;
   laserTrailFlags[1]         = 0;
   //laserTrail[2]            = WpnSMG2ProjectileLaserTrail2;
   laserTrailFlags[2]         = 0;

   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //lightDesc = "WpnSMG2ProjectileLightDesc";
};

function WpnSMG2Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

