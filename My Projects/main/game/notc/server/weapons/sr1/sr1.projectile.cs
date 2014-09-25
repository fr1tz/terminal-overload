// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSR1Projectile)
{
   collisionMask = $CollisionMask::Normal;

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 2000;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;
 
   energyDrain = 30;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 40;
	impactImpulse      = 6000;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = true;
 
   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   missEnemyEffect = WpnSR1ProjectileMissedEnemyEffect;

   explosion           = WpnSR1ProjectileExplosion;
   decal               = WpnSR1ProjectileDecal;
   laserTrail[0]       = WpnSR1ProjectileLaserTrail0;
   laserTrailFlags[0]  = 0;
   laserTrail[1]       = WpnSR1ProjectileLaserTrail1;
   laserTrailFlags[1]  = 0;
   laserTrail[2]       = WpnSR1ProjectileLaserTrail2;
   laserTrailFlags[2]  = 0;

   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //lightDesc = "WpnSR1ProjectileLightDesc";
};

function WpnSR1Projectile::onAdd(%this, %obj)
{
	Parent::onAdd(%this, %obj);
	//%vel = %obj.initialVelocity;
	//%pos = %obj.initialPosition;
	//%pos = VectorAdd(VectorScale(VectorNormalize(%vel),4), %pos);
	//%norm = "0 0 1";
	//createExplosion(WpnSR1ProjectileFireExplosion, %pos, %norm);
}

function WpnSR1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   if(%col.getType() & $TypeMasks::ShapeBaseObjectType)
   {
      %col.activateStealth(4000);
      %src = %obj.sourceObject;
      if(isObject(%src))
         %src.getDataBlock().addDiscTarget(%src, %col);
   }

   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
}

