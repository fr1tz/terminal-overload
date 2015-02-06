// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSMG3Projectile)
{
   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   //missEnemyEffect = GenericMissEnemyEffect1;
 
   energyDrain = 2; // how much energy does firing this projectile drain?

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 15;
	impactImpulse      = 0;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   //tracer = WpnSMG3ProjectileTracer;

   explosion                  = "WpnSMG3ProjectileExplosion";
   impactExplosion[0]         = "WpnSMG3ProjectileHit";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   impactExplosion[1]         = "WpnSMG3ProjectileImpact";
   impactExplosionTypeMask[1] = $TypeMasks::StaticObjectType;
   decal                      = "WpnSMG3ProjectileDecal";
   //particleEmitter          = "WpnSMG3ProjectileParticleEmitter";
   laserTrail[0]              = WpnSMG3ProjectileLaserTrail0;
   laserTrailFlags[0]         = 8;
   //laserTrail[1]            = WpnSMG3ProjectileLaserTrail1;
   laserTrailFlags[1]         = 0;
   //laserTrail[2]            = WpnSMG3ProjectileLaserTrail2;
   laserTrailFlags[2]         = 0;

   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //lightDesc = "WpnSMG3ProjectileLightDesc";
};

function WpnSMG3Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

