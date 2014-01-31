// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// projectile datablock...

datablock ProjectileData(WpnParrotMinigunProjectile)
{
	stat = "ParrotMinigun";

	// script damage properties...
	impactDamage       = 20;
	impactImpulse      = 500;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;

	energyDrain = 2; // how much energy does firing this projectile drain?

	explodesNearEnemies	      = false;
	explodesNearEnemiesRadius = 10;
	explodesNearEnemiesMask   = $TypeMasks::PlayerObjectType;

	//sound = MinigunProjectileFlybySound;

	//projectileShapeName = "share/shapes/rotc/weapons/blaster/projectile.red.dts";

	explosion               = WpnBadgerProjectileImpact;
	hitEnemyExplosion       = WpnBadgerProjectileImpact;
	hitTeammateExplosion    = WpnBadgerProjectileImpact;
	//nearEnemyExplosion	= DefaultProjectileNearEnemyExplosion;
	//hitDeflectorExplosion = SeekerDiscBounceEffect;

	//fxLight					= WpnParrotMinigunProjectileFxLight;

	missEnemyEffect = WpnParrotMinigunProjectileMissedEnemyEffect;

	laserTail    = WpnBadgerProjectileLaserTail;
	laserTailLen = 8.0;

	laserTrail[0] = WpnParrotMinigunProjectileLaserTrail;

	//particleEmitter	  = WpnParrotMinigunProjectileParticleEmitter;

	muzzleVelocity   = 400 * $Server::Game.slowpokemod;
	velInheritFactor = 1.0 * $Server::Game.slowpokemod;

	isBallistic = false;
	gravityMod  = 4.0 * $Server::Game.slowpokemod;

	armingDelay	= 1000*0;
	lifetime	= 3000;
	fadeDelay	= 5000;

	decals[0] = BulletHoleDecalOne;

	hasLight    = false;
	lightRadius = 10.0;
	lightColor  = "1.0 0.0 0.0";
};

function WpnParrotMinigunProjectile::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
    Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist);

	if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
		return;
}


