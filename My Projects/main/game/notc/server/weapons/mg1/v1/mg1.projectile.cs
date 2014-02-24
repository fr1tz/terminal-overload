// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(WpnMG1Projectile)
{
   projectileShapeName = "content/fr1tz/notc1/shapes/mg1/projectile/p1/shape.dae";

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 20;
   radiusDamage        = 0;
   damageRadius        = 0;
   areaImpulse         = 0;
   impactForce         = 250;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   explosion           = "WpnMG1ProjectileExplosion";
   decal               = "WpnMG1ProjectileDecal";
   particleEmitter     = "WpnMG1ProjectileParticleEmitter";

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

