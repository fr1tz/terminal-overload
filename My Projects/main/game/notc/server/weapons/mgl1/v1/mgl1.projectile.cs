// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnMGL1ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnMGL1ProjectileDecal)
{
   Material = "xa_notc_core_shapes_mgl1_projectile_p1_decalmat";
   size = "2";
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

datablock ShotgunProjectileData(WpnMGL1PseudoProjectile)
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

function WpnMGL1PseudoProjectile::onAdd(%this, %obj)
{
   // Create actual projectile.
   %data = WpnMGL1Projectile;
   %ammo = WpnMGL1Ammo;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   if(%player.getInventory(%ammo) == 0)
      return;
      
   %player.decInventory(%ammo, 1);

   %muzzleVector = %player.getMuzzleVector(0);
	%muzzlePoint = %player.getMuzzlePoint(0);
 
   // Velocity inherited from player
   %iVel = VectorScale(%player.getVelocity(), %data.velInheritFactor);

   %muzzleTransform = createOrientFromDir(%muzzleVector);

	%pos[0] = "0 0 0";
	%vec[0] = "0 1 0.005";
	%pos[1] = "0 0 0.1";
	%vec[1] = "0 1 0.025";

	for(%i = 0; %i < 2; %i++)
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

datablock ProjectileData(WpnMGL1Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mgl1/projectile/p1/shape.dae";
   
   sound = WpnMGL1ProjectileSound;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 0;
	impactImpulse      = 2500;
	splashDamage       = 30;
	splashDamageRadius = 2;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   explodesNearEnemies = true;
   explodesNearEnemiesRadius = 2;
   explodesNearEnemiesMask = $TypeMasks::PlayerObjectType;
 
   energyDrain = 8;

   explosion           = "WpnMGL1ProjectileExplosion";
   decal               = "WpnMGL1ProjectileDecal";
   laserTrail[0]       = "WpnMGL1ProjectileLaserTrail0";
   laserTrail[1]       = "WpnMGL1ProjectileLaserTrail1";
   laserTrail[2]       = "WpnMGL1ProjectileLaserTrail2";
   //particleEmitter     = "WpnMGL1ProjectileParticleEmitter";

   muzzleVelocity      = 300;
   velInheritFactor    = 0.75;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 5;
   //lightDesc = "WpnMGL1ProjectileLightDesc";
};

function WpnMGL1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;
   
   %src = %obj.sourceObject;
   if(isObject(%src))
      %src.getDataBlock().addDiscTarget(%src, %col);
}

