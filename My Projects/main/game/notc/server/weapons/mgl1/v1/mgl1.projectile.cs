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
   Material = "fr1tz_notc1_shapes_smg1_projectile_p1_decalmat";
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

datablock ShotgunProjectileData(WpnMGL1PseudoProjectile)
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

function WpnMGL1PseudoProjectile::onAdd(%this, %obj)
{
   // Create actual projectile.
   %data = WpnMGL1Projectile;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   %muzzleVector = %player.getMuzzleVector(0);
	%muzzlePoint = %player.getMuzzlePoint(0);

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
		MissionCleanup.add(%p);
	}

	// no need to ghost pseudo projectile to clients...
	//%obj.delete();
}

datablock ProjectileData(WpnMGL1Projectile)
{
   projectileShapeName = "content/fr1tz/notc1/shapes/mgl1/projectile/p1/shape.dae";

   //lightDesc = BulletProjectileLightDesc;

   directDamage        = 0;
   radiusDamage        = 30;
   damageRadius        = 2;
   areaImpulse         = 0;
   impactForce         = 2500;

   explosion           = "WpnMGL1ProjectileExplosion";
   decal               = "WpnMGL1ProjectileDecal";

   muzzleVelocity      = 150;
   velInheritFactor    = 0.75;

   armingDelay         = 0;
   lifetime            = 5000;
   fadeDelay           = 5000;
   bounceElasticity    = 0;
   bounceFriction      = 0;
   isBallistic         = false;
   gravityMod          = 5.0;
   //lightDesc = "WpnMGL1ProjectileLightDesc";
};

function WpnMGL1Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   if(!(%col.getType() & $TypeMasks::GameBaseObjectType))
      return;

   %effectiveRange = 25;
   %dist = VectorLen(VectorSub(%pos, %obj.initialPosition));
   %distFactor = 1;
   if(%dist > %effectiveRange)
      %distFactor = 1 - (%dist-%effectiveRange) / (%this.range-%effectiveRange);
      
   error(%dist SPC %distFactor);
   %damage = %this.directDamage * %distFactor;

   %col.damage(%obj,%pos,%this.directDamage,"BulletProjectile");
}

