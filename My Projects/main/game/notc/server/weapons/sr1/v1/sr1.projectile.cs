// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSR1ProjectileDecal)
{
   Material = "xa_notc_core_shapes_smg1_projectile_p1_decalmat";
   size = "0.25";
   lifeSpan = "5000";
   randomize = "1";
   texRows = "2";
   texCols = "2";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "3";
   textureCoords[0] = "0 0 0.5 0.5";
   textureCoords[1] = "0.5 0 0.5 0.5";
   textureCoords[2] = "0 0.5 0.5 0.5";
   textureCoords[3] = "0.5 0.5 0.5 0.5";
};

datablock ShotgunProjectileData(WpnSR1Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/smg1/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 2000;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 40;
	impactImpulse      = 6000;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = true;

   explosion           = "WpnSR1ProjectileExplosion";
   decal               = "WpnSR1ProjectileDecal";

   muzzleVelocity      = 10;
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 992;
   fadeDelay           = 1472;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //ParticleEmitter = "WpnSR1ProjectileEmitter";
   //lightDesc = "WpnSR1ProjectileLightDesc";
};

function WpnSR1Projectile::onAdd(%this, %obj)
{
	Parent::onAdd(%this, %obj);
	%vel = %obj.initialVelocity;
	%pos = %obj.initialPosition;
	%pos = VectorAdd(VectorScale(VectorNormalize(%vel),4), %pos);
	%norm = "0 0 1";
	createExplosion(WpnSR1ProjectileFireExplosion, %pos, %norm);
}

function WpnSR1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

