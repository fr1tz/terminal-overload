// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(WpnMG2Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mg2/projectile/p1/shape.dae";
   hideShapeWhileOverlappingMuzzlePoint = true;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 20;
	impactImpulse      = 250;
	splashDamage       = 5;
	splashDamageRadius = 5;
	splashImpulse      = 0;
 
   explodesNearEnemies = true;
   explodesNearEnemiesRadius = 5;
   explodesNearEnemiesMask = $TypeMasks::PlayerObjectType;
   //missEnemyEffect = WpnMG2ProjectileMissEnemyEffect;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   explosion                  = "WpnMG2ProjectileExplosion";
   nearEnemyExplosion         = "WpnMG2ProjectileProximityExplosion";
   impactExplosion[0]         = "WpnMG2ProjectileHit";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   decal                      = "WpnMG2ProjectileDecal";
   //particleEmitter          = "WpnMG2ProjectileParticleEmitter";
   //laserTrail[0]            = "WpnMG2ProjectileLaserTrail0";
   laserTrailFlags[0]         = 0;

   muzzleVelocity      = 400;
   velInheritFactor    = 1.0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 5.0;
   //lightDesc = "WpnMG2ProjectileLightDesc";
};

function WpnMG2Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   //echo("WpnMG2Projectile::onCollision()");
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   %obj.zNoSplashDamage = true;
}

function WpnMG2Projectile::onExplode(%this, %obj, %pos, %mod)
{
   //echo("WpnMG2Projectile::onExplode()");
   if(!%obj.zNoSplashDamage)
      Parent::onExplode(%this, %obj, %pos, %mod);
}

