// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// "Universal" script methods for projectile damage handling.  You can easily
// override these support functions with an equivalent namespace method if your
// weapon needs a unique solution for applying damage.

function ProjectileData::onCollision(%data, %proj, %col, %fade, %pos, %normal)
{
   //echo("ProjectileData::onCollision("@%data.getName()@", "@%proj@", "@%col.getClassName()@", "@%fade@", "@%pos@", "@%normal@")");

   // Apply damage to the object all shape base objects
   if (%data.directDamage > 0)
   {
      if (%col.getType() & ($TypeMasks::ShapeBaseObjectType))
         %col.damage(%proj, %pos, %data.directDamage, %data.damageType);
   }
}

function ProjectileData::onExplode(%data, %proj, %position, %mod)
{
   //echo("ProjectileData::onExplode("@%data.getName()@", "@%proj@", "@%position@", "@%mod@")");

   // Damage objects within the projectiles damage radius
   if (%data.damageRadius > 0)
      radiusDamage(%proj, %position, %data.damageRadius, %data.radiusDamage, %data.damageType, %data.areaImpulse);
}
