// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// "Universal" script methods for projectile damage handling.  You can easily
// override these support functions with an equivalent namespace method if your
// weapon needs a unique solution for applying damage.

function ProjectileData::onCollision(%data, %proj, %col, %fade, %pos, %normal)
{
   //echo("ProjectileData::onCollision("@%data.getName()@", "@%proj@", "@%col.getClassName()@", "@%fade@", "@%pos@", "@%normal@")");
   
	if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
		return;

	// apply impulse...
	if(%data.impactImpulse > 0)
	{
      %impulseVec = VectorNormalize(%proj.getVelocity());
		%impulseVec = VectorScale(%impulseVec, %data.impactImpulse);
		%col.impulse(%pos, %impulseVec, %proj);
	}

	// bail out here if projectile doesn't do impact damage...
	if( %data.impactDamage == 0 )
		return;

	// call damage func...
	%col.damage(%proj, %pos, %data.impactDamage, "Impact");

	// if projectile was fired by a player, regain some of his energy...
   %sourceObject = %proj.sourceObject;
   %regainEnergy = false;
   if(isObject(%sourceObject))
      %regainEnergy = %sourceObject.getClassName() $= "Player";
	if(%regainEnergy)
	{
		%newSrcEnergy = %sourceObject.getEnergyLevel() + %data.energyDrain;
		%sourceObject.setEnergyLevel(%newSrcEnergy);
	}
}

function ProjectileData::onExplode(%data, %proj, %pos, %mod)
{
   //echo("ProjectileData::onExplode("@%data.getName()@", "@%proj@", "@%position@", "@%mod@")");

   // can we bail out early?
   if(%data.splashDamageRadius == 0)
      return;

	%radius = %data.splashDamageRadius;
   %typeMask = $TypeMasks::ShapeBaseObjectType;
   %collisionMask = %data.collisionMask;
 
	%damage = %data.splashDamage;
	%damageType = "Splash";
 
   %sourceObject = %proj.sourceObject;
   %regainEnergy = false;
   if(isObject(%sourceObject))
      %regainEnergy = %sourceObject.getClassName() $= "Player";

	%targets = new SimSet();

	InitContainerRadiusSearch2(%pos, %radius, %typeMask, %collisionMask);
	while( (%targetObject = containerSearchNext()) != 0 )
		%targets.add(%targetObject);

	for(%idx = %targets.getCount()-1; %idx >= 0; %idx-- )
	{
		%targetObject = %targets.getObject(%idx);

      if(%targetObject == %proj)
         continue;
         
      if(!%targetObject.isMethod("getDataBlock"))
         continue;
         
      if(%targetObject.getDataBlock().ignoreDamage)
         continue;

        // the observer cameras are ShapeBases; ignore them...
      if(%targetObject.getType() & $TypeMasks::CameraObjectType)
         continue;

		%coverage = calcExplosionCoverage(%pos, %targetObject,
			$TypeMasks::InteriorObjectType |  $TypeMasks::TerrainObjectType |
			$TypeMasks::ForceFieldObjectType | $TypeMasks::VehicleObjectType |
			$TypeMasks::TurretObjectType);

		if (%coverage == 0)
			continue;

      %center = %targetObject.getWorldBoxCenter();
		%col = containerRayCast2(%pos, %center, %typeMask, %collisionMask, %proj);
		%col = getWord(%col, 1) SPC getWord(%col, 2) SPC getWord(%col, 3);
		%dist = VectorLen(VectorSub(%col, %pos));

		%prox = %radius - %dist;
		if(%data.splashDamageFalloff == $SplashDamageFalloff::Exponential)
			%distScale = (%prox*%prox) / (%radius*%radius);
		else if(%data.splashDamageFalloff == $SplashDamageFalloff::None)
			%distScale = 1;
		else
			%distScale = %prox / %radius;

		// apply impulse...
		if(%data.splashImpulse > 0)
		{
			%impulseVec = VectorNormalize(VectorSub(%center, %pos));
			%impulseVec = VectorScale(%impulseVec, %data.splashImpulse);
			%targetObject.impulse(%pos, %impulseVec, %proj);
		}

		// bail out here if projectile doesn't do splash damage...
		if( %data.splashDamage == 0 )
			continue;

		// call damage func...
		%targetObject.damage(%proj, %pos,
			%damage * %coverage * %distScale, %damageType);

		// if projectile was fired by a player, regain some of his energy...
		if(%regainEnergy)
		{
			%newSrcEnergy = %sourceObject.getEnergyLevel()
				+ %data.energyDrain*%distScale;
			%sourceObject.setEnergyLevel(%newSrcEnergy);
		}
	}

	%targets.delete();
}
