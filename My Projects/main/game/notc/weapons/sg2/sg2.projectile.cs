// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSG2PseudoProjectile)
{
   //projectileShapeName = "content/xa/oldshapes/siberion/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;
 
   energyDrain = 16;

   muzzleVelocity      = 9999;
   velInheritFactor    = 0;
};

function WpnSG2PseudoProjectile::onAdd(%this, %obj)
{
   // Create actual projectile.
   %data = WpnSG2Projectile;
   %ammo = WpnSG2Ammo;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   if(%player.getInventory(%ammo) == 0)
      return;
      
   %player.decInventory(%ammo, 1);

   %muzzleVector = %player.getMuzzleVector(0);
	%muzzlePoint = %player.getMuzzlePoint(0);
 
   createExplosion(WpnMGL1FireExplosion, %muzzlePoint, %muzzleVector);
 
   // Velocity inherited from player
   %iVel = VectorScale(%player.getVelocity(), %data.velInheritFactor);

   %muzzleTransform = createOrientFromDir(%muzzleVector);

	%pos[0] = "0 0 0";
	%vec[0] = "0 1 0";
	%pos[1] = "0 0 0.1";
	%vec[1] = "0 1 0.025";

	for(%i = 0; %i < 1; %i++)
	{
		%position =	VectorAdd(
			%muzzlePoint,
			MatrixMulVector(%muzzleTransform, %pos[%i])
		);
		%velocity = VectorScale(MatrixMulVector(%muzzleTransform, %vec[%i]), %data.muzzleVelocity);
      %velocity = VectorAdd(%velocity, %iVel);

		// create the projectile object...
		%p = new Projectile() {
			dataBlock       = %data;
			teamId          = %obj.teamId;
			initialVelocity = %velocity;
			initialPosition = %position;
			sourceObject    = %player;
			sourceSlot      = %slot;
			client          = %player.client;
		};
      copyPalette(%player, %p);
		MissionCleanup.add(%p);
	}

	// No need to ghost pseudo projectile to clients.
	%obj.schedule(0, "delete");
}

datablock ProjectileData(WpnSG2Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mgl1/projectile/p1/shape.dae";

   sound = WpnSG2ProjectileSound;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 120;
	impactImpulse      = 5000;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 10;
   missEnemyEffect = WpnMG1ProjectileMissEnemyEffect;
   
   energyDrain = 16;
 
   explosion           = "WpnSG2ProjectileExplosion";
   decal               = "WpnSG2ProjectileDecal";
   laserTrail[0]       = "WpnSG2ProjectileLaserTrail0";
   //particleEmitter     = "WpnSG2ProjectileParticleEmitter";

   muzzleVelocity      = 200;
   velInheritFactor    = 0.5;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 3;
   //lightDesc = "WpnSG2ProjectileLightDesc";
};

function WpnSG2Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   %src = %obj.sourceObject;
   if(isObject(%src))
      %src.getDataBlock().addDiscTarget(%src, %col);

   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;
}

