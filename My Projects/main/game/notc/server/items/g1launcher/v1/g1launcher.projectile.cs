// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(ItemG1LauncherProjectile)
{
   collisionMask = $CollisionMask::Normal;

   projectileShapeName = "content/xa/notc/core/shapes/mgl1/projectile/p1/shape.dae";

   //sound = ItemG1LauncherProjectileSound;

   //lightDesc = BulletProjectileLightDesc;

	// script damage properties...
   impactDamage        = 0;
   impactImpulse       = 0;
   splashDamage        = 40;
   splashDamageRadius  = 15;
   splashImpulse       = 0;
   splashDamageFalloff = $SplashDamageFalloff::None;
   bypassDamageBuffer  = true;

   explosion           = ItemG1LauncherProjectileExplosion;
   bounceEffect[0]     = ItemG1LauncherProjectileBounceEffect;
   particleEmitter     = ItemG1LauncherProjectile_ParticleEmitter;

   muzzleVelocity      = 200;
   velInheritFactor    = 0.0;

   armingDelay         = 1000;
   lifetime            = 10000;
   fadeDelay           = 10000;
   bounceElasticity    = 0.7;
   bounceFriction      = 0.5;
   isBallistic         = true;
   gravityMod          = 8;
   //lightDesc = "WpnMGL1ProjectileLightDesc";
};

function ItemG1LauncherProjectile::onExplode(%data, %proj, %pos, %mod)
{
   return;

	%radius = %this.splashDamageRadius;
	%sourceObject = %obj.getSourceObject();

	InitContainerRadiusSearch(%pos, %radius, $TypeMasks::ShapeBaseObjectType);
	%halfRadius = %radius / 2;
	while( (%targetObject = containerSearchNext()) != 0 )
	{
        // the observer cameras are ShapeBases; ignore them...
        if(%targetObject.getType() & $TypeMasks::CameraObjectType)
    	   continue;

		// ignore shapes with a barrier...
		if(%targetObject.hasBarrier())
			continue;

		%coverage = calcExplosionCoverage(%pos, %targetObject,
			$TypeMasks::InteriorObjectType |  $TypeMasks::TerrainObjectType |
			$TypeMasks::ForceFieldObjectType | $TypeMasks::VehicleObjectType |
			$TypeMasks::TurretObjectType);

		if (%coverage == 0)
			continue;

        %sourceObject.setDiscTarget(%targetObject);
	}

    Parent::onExplode(%this,%obj,%pos,%normal,%fade,%dist,%expType);
}

