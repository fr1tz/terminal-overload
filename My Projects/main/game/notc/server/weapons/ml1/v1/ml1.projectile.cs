// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Called from the repel gun image's "onFire" script function
function WpnML1_spawnProjectile(%datablock, %srcObj, %slot, %muzzlePoint, %muzzleVelocity)
{
	//error("spawnRepelGunProjectile();");

	%p = new Projectile() {
		dataBlock       = %datablock;
		teamId          = %srcObj.teamId;
		initialVelocity = %muzzleVelocity;
		initialPosition = %muzzlePoint;
		sourceObject    = %srcObj;
		sourceSlot      = %slot;
		client          = %srcObj.client;
	};

	return %p;
}

datablock ProjectileData(WpnML1Projectile)
{
   projectileShapeName = "content/fr1tz/oldshapes/raptor/magazine/p1/shape.dae";

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 0;
   radiusDamage        = 0;
   damageRadius        = 0;
   areaImpulse         = 0;
   impactForce         = 0;
   
	energyDrain = 2; // how much energy does firing this projectile drain?

   //explosion = "WpnML1ProjectileExplosion";
   decal     = "WpnML1ProjectileDecal";
   lightDesc = "WpnML1ProjectileLightDesc";

   muzzleVelocity      = 100;
   velInheritFactor    = 1.0;

   armingDelay         = 1000;
   lifetime            = 10000;
   fadeDelay           = 10000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 10.0;
};

function WpnML1Projectile::onExplode(%this, %obj, %pos, %fade)
{
	//Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist);
 
	%p = new StaticShape() {
		dataBlock       = WpnML1Mine;
		teamId          = %obj.teamId;
		client          = %obj.client;
	};

	%pos = VectorAdd(%pos, VectorScale(%normal,0.1));
//	%mat = MatrixCreateFromEuler(%normal);
//	%rot = getSubStr(%mat,6,256);
//	%t = %pos SPC %rot;
	%p.setTransform(%pos);
	%p.zNormal = %normal;
}

function WpnML1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{

}
