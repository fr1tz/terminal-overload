// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnMGL2ProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnMGL2ProjectileDecal)
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

datablock ShotgunProjectileData(WpnMGL2PseudoProjectile)
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

function WpnMGL2PseudoProjectile::onAdd(%this, %obj)
{
   // Create actual projectile.
   %data = WpnMGL2Projectile;
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

datablock ProjectileData(WpnMGL2Projectile)
{
   projectileShapeName = "content/xa/notc/core/shapes/mgl1/projectile/p2/shape.dae";
   
   sound = WpnMGL2ProjectileSound;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
	impactDamage       = 0;
	impactImpulse      = 5000;
	splashDamage       = 60;
	splashDamageRadius = 2;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
 
   explodesNearEnemies = true;
   explodesNearEnemiesRadius = 2;
   explodesNearEnemiesMask = $TypeMasks::PlayerObjectType;
 
   energyDrain = 16;

   explosion                  = "WpnMGL2ProjectileExplosion";
   nearEnemyExplosion         = "WpnMGL2ProjectileSplashDmgExplosion";
   impactExplosion[0]         = "WpnMGL2ProjectileImpactDmgExplosion";
   impactExplosionTypeMask[0] = $TypeMasks::ShapeBaseObjectType;
   decal                      = "WpnMGL2ProjectileDecal";
   laserTrail[0]              = "WpnMGL2ProjectileLaserTrail0";
   //laserTrail[1]            = "WpnMGL2ProjectileLaserTrail1";
   laserTrail[2]              = "WpnMGL2ProjectileLaserTrail2";
   //particleEmitter          = "WpnMGL2ProjectileParticleEmitter";

   muzzleVelocity      = 300;
   velInheritFactor    = 0.75;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 5;
   //lightDesc = "WpnMGL2ProjectileLightDesc";
};

function WpnMGL2Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;
   
   %src = %obj.sourceObject;
   if(isObject(%src))
      %src.getDataBlock().addDiscTarget(%src, %col);
}

