// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
// light images...

datablock ShapeBaseImageData(WpnML1MineLightImage)
{
	// basic item properties
	shapeFile = "content/o/rotc/p.5.4/shapes/rotc/misc/nothing.dts";
	emap = true;

	// mount point & mount offset...
	mountPoint  = 0;
	offset = "0 0 0";

	stateName[0] = "DoNothing";
};

//-----------------------------------------------------------------------------
// shape...

datablock StaticShapeData(WpnML1Mine)
{
	// script damage properties...
	impactDamage        = 10; // only used to determine time for barrier
	impactImpulse       = 0;
	splashDamage        = 40;
	splashDamageRadius  = 6;
	splashImpulse       = 6000;
   splashDamageFalloff = $SplashDamageFalloff::None;
	bypassDamageBuffer  = true;

   shapeFile = "content/xa/rotc_hack/shapes/mine.dts";
};

function WpnML1Mine::onAdd(%this, %obj)
{
	Parent::onAdd(%this, %obj);

   %obj.getHudInfo().setActive(false);

	%obj.mountImage(WpnML1MineLightImage, 0);
	
	%this.checkDetonate(%obj);
	
	%this.schedule(4000, "detonate", %obj, false);
}

function WpnML1Mine::detonate(%this, %obj, %hit)
{
	if(!isObject(%obj))
		return;
		
	if(%obj.detonated)
		return;

	%pos = %obj.getPosition();
	%normal = %obj.zNormal;
	%fade = 1;
	%dist = 0;
	%expType = 0;

	// Disc lock...
	if(isObject(%obj.client.player) && %obj.client.player.isCAT)
	{
		%radius = %this.splashDamageRadius;
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

			%obj.client.player.setDiscTarget(%targetObject);
		}
	}

	ProjectileData::onExplode(%this,%obj,%pos,%normal,%fade,%dist,%expType);
	
	%obj.unmountImage(0);

	createExplosion(RepelGunMineExplosionExplosion, %pos, %normal);

	%obj.startFade(0, 0, true);

	%obj.schedule(1000, "delete");
	
	%obj.detonated = true;
}

function WpnML1Mine::checkDetonate(%this, %obj)
{
	if(!isObject(%obj))
		return;
		
	if(%obj.detonated)
		return;

	%pos = %obj.getWorldBoxCenter();
	%radius = 6;

	%hitEnemy = false;

	InitContainerRadiusSearch(%pos, %radius, $TypeMasks::PlayerObjectType);
	%halfRadius = %radius / 2;
	while ((%targetObject = containerSearchNext()) != 0)
	{
		if(%targetObject.teamId == 0 || %targetObject.teamId == %obj.teamId)
			continue;

      if(%targetObject.hasBarrier())
         continue;

		// Calculate how much exposure the current object has to
		// the effect.  The object types listed are objects
		// that will block an explosion. 
		%coverage = calcExplosionCoverage(%pos, %targetObject,
			$TypeMasks::InteriorObjectType |  $TypeMasks::TerrainObjectType |
			$TypeMasks::ForceFieldObjectType | $TypeMasks::VehicleObjectType |
			$TypeMasks::TurretObjectType);
			
		if (%coverage == 0)
			continue;

		%this.detonate(%obj, true);
		return;
	}	
	
	%this.schedule(50, "checkDetonate", %obj);	
}


