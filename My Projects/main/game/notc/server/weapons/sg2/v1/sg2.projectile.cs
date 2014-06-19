// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnSG2ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnSG2ProjectileDecal)
{
   Material = "DECAL_RocketEXP";
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
 
   energyDrain = 36;

   explosion           = "WpnSG2ProjectileExplosion";
   decal               = "WpnSG2ProjectileDecal";
   laserTrail[0]       = 0; //"WpnSG2ProjectileLaserTrail";
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
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;
   
   %src = %obj.sourceObject;
   if(isObject(%src))
      %src.getDataBlock().addDiscTarget(%src, %col);
}

