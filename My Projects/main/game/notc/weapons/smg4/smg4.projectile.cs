// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSMG4PseudoProjectile)
{
   //projectileShapeName = "content/xa/oldshapes/siberion/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;
 
   energyDrain = 3;

   muzzleVelocity      = 9999;
   velInheritFactor    = 0;
};

function WpnSMG4PseudoProjectile::onAdd(%this, %obj)
{
   // Create actual projectile.
   %data = WpnSMG4Projectile;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   %muzzleVector = %obj.initialVelocity; //%player.getMuzzleVector(0);
	%muzzlePoint = %player.getMuzzlePoint(0);
 
   // Velocity inherited from player
   %iVel = VectorScale(%player.getVelocity(), %data.velInheritFactor);
   
   %velocity = VectorScale(%muzzleVector, %data.muzzleVelocity);
   %velocity = VectorAdd(%velocity, %iVel);

   // create the projectile object...
   %p = new Projectile() {
      dataBlock       = %data;
      teamId          = %obj.teamId;
      initialVelocity = %velocity;
      initialPosition = %muzzlePoint;
      sourceObject    = %player;
      sourceSlot      = %slot;
      client          = %player.client;
   };
   copyPalette(%player, %p);
   MissionCleanup.add(%p);

	// No need to ghost pseudo projectile to clients.
	%obj.schedule(0, "delete");
}

datablock ProjectileData(WpnSMG4Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mg1/projectile/p1/shape.dae";
   
   sound = WpnSMG4ProjectileSound;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 15;
	impactImpulse      = 1000;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;
   missEnemyEffect = GenericMissEnemyEffect1;
 
   energyDrain = 5;

   explosion                  = "WpnSMG1ProjectileExplosion";
   //nearEnemyExplosion         = "WpnSMG4ProjectileSplashDmgExplosion";
   impactExplosion[0]         = "WpnSMG1ProjectileImpactDmgExplosion";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   decal                      = "WpnSMG4ProjectileDecal";
   laserTrail[0]              = 0; //"WpnSMG4ProjectileLaserTrail0";
   //laserTrail[1]            = "WpnSMG4ProjectileLaserTrail0";
   //laserTrail[2]              = "WpnSMG4ProjectileLaserTrail2";
   //particleEmitter          = "WpnSMG4ProjectileParticleEmitter";

   muzzleVelocity      = 500;
   velInheritFactor    = 0.8;

   armingDelay         = 0;
   lifetime            = 2000;
   fadeDelay           = 2000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 5;
   //lightDesc = "WpnSMG4ProjectileLightDesc";
};

function WpnSMG4Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;
   
//   %src = %obj.sourceObject;
//   if(isObject(%src))
//      %src.getDataBlock().addDiscTarget(%src, %col);
}

