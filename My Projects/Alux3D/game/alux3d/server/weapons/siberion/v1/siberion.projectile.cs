// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightDescription(WpnSiberionProjectileLightDesc : BulletProjectileLightDesc)
{
   color = "0 1 0.952941 1";
   range = "10";
   brightness = "1";
};

datablock DecalData(WpnSiberionProjectileDecal)
{
   Material = "DECAL_WpnSiberionProjectile";
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

datablock ShotgunProjectileData(WpnSiberionPseudoProjectile)
{
   //projectileShapeName = "content/fr1tz/oldshapes/siberion/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;

   muzzleVelocity      = 9999;
   velInheritFactor    = 0;
};

function WpnSiberionPseudoProjectile::onAdd(%this,%obj)
{
   // Create actual projectile.
   %data = WpnSiberionProjectile;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
	%muzzlePoint = %obj.initialPosition;
	%muzzleVector = %obj.initialVelocity;
   %muzzleVector = VectorNormalize(%muzzleVector);
   %muzzleVector = VectorScale(%muzzleVector, %data.muzzleVelocity);
   %p = new Projectile()
   {
      dataBlock = %data;
      initialPosition = %muzzlePoint;
      initialVelocity = %muzzleVector;
      sourceObject = %player;
      sourceSlot = %slot;
      client = %player.client;
   };
   MissionCleanup.add(%p);
      
   // Delete pseudo projectile
   //%obj.delete();
}

datablock ProjectileData(WpnSiberionProjectile)
{
   projectileShapeName = "content/fr1tz/oldshapes/siberion/projectile/p1/shape.dae";

   directDamage        = 30;
   radiusDamage        = 0;
   damageRadius        = 0.5;
   areaImpulse         = 0.5;
   impactForce         = 600;

   explosion           = BulletDirtExplosion;
   decal               = BulletHoleDecal;

   muzzleVelocity      = 300;
   velInheritFactor    = 0;

   armingDelay         = 0;
   lifetime            = 2000;
   fadeDelay           = 2000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = true;
   gravityMod          = 3;
};

function WpnSiberionProjectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   if(!(%col.getType() & $TypeMasks::GameBaseObjectType))
      return;

   %range = 250;
   %effectiveRange = 50;

   %dist = VectorLen(VectorSub(%pos, %obj.initialPosition));
   %distFactor = 1;
   if(%dist > %effectiveRange)
      %distFactor = 1 - (%dist-%effectiveRange) / (%range-%effectiveRange);
      
   //error(%dist SPC %distFactor);
   %damage = %this.directDamage * %distFactor;

   %col.damage(%obj,%pos,%this.directDamage,"BulletProjectile");
}

