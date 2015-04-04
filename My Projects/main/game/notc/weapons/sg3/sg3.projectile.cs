// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSG3Projectile)
{
   //projectileShapeName = "content/xa/notc/core/shapes/smg1/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	range = 1000;
   bulletDistMode = 1;
	numBullets = 10;
	muzzleSpreadRadius = 0.5;
	referenceSpreadRadius = 1.0;
	referenceSpreadDistance = 15;
 
   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   missEnemyEffect = GenericMissEnemyEffect1;

   energyDrain = 2; // how much energy does firing this projectile drain?

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 15;
	impactImpulse      = 600;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;

   //tracer = WpnSG3ProjectileTracer;

   explosion                  = "WpnSMG2ProjectileExplosion";
   impactExplosion[0]         = "WpnSMG2ProjectileHit";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   impactExplosion[1]         = "WpnSMG2ProjectileImpact";
   impactExplosionTypeMask[1] = $TypeMasks::StaticObjectType;
   decal                      = "WpnSMG2ProjectileDecal";
   //particleEmitter          = "WpnSG3ProjectileParticleEmitter";
   laserTrail[0]              = WpnSG3ProjectileLaserTrail0;
   laserTrailFlags[0]         = 8;
   //laserTrail[1]              = WpnSG3ProjectileLaserTrail1;
   laserTrailFlags[1]         = 0;
   //laserTrail[2]            = WpnSG3ProjectileLaserTrail2;
   laserTrailFlags[2]         = 0;

   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 1;
   //lightDesc = "WpnSG3ProjectileLightDesc";
};

function WpnSG3Projectile::onAdd(%this, %obj)
{
   //Parent::onAdd(%this, %obj);
   
   return;

   %data = WpnSG3Projectile;
   %ammo = WpnSG3Ammo;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   if(%player.getInventory(%ammo) == 0)
   {
      %obj.delete();
      return;
   }

   %player.decInventory(%ammo, 1);
}

function WpnSG3Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;

   %src = %obj.sourceObject;
   if(!isObject(%src))
      return;

   %currTime = getSimTime();

   // NOTE: This was a problem with ROTC, may not be
   //       a problem with Terminal Overload:
   // FIXME: strange linux version bug:
   //        after the game has been running a long time
   //        (%currTime == %obj.hitTime)
   //        often evaluates to false even if the
   //        values appear to be equal.
   //        (%currTime - %obj.hitTime) evaluates to 1
   //        in those cases.
   if(%currTime - %obj.hitTime <= 1)
   {
      %col.numSG3BulletHits += 1;
      if(%col.numSG3BulletHits == 4)
         %src.getDataBlock().addDiscTarget(%src, %col);
   }
   else
   {
      %obj.hitTime = %currTime;
      %col.numSG3BulletHits = 1;
   }
}

