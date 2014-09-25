// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(WpnMG1Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mg1/projectile/p2/shape.dae";

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
   nearEnemyExplosion = "WpnMG1ProjectileProximityExplosion";
   //missEnemyEffect = WpnMG1ProjectileMissEnemyEffect;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   explosion           = "WpnMG1ProjectileExplosion";
   decal               = "WpnMG1ProjectileDecal";
   //particleEmitter     = "WpnMG1ProjectileParticleEmitter";
   //laserTrail[0]       = "WpnMG1ProjectileLaserTrail";

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
   //echo("WpnMG1Projectile::onCollision()");
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   %obj.zNoSplashDamage = true;
}

function WpnMG1Projectile::onExplode(%this, %obj, %pos, %mod)
{
   //echo("WpnMG1Projectile::onExplode()");
   if(!%obj.zNoSplashDamage)
      Parent::onExplode(%this, %obj, %pos, %mod);
}

