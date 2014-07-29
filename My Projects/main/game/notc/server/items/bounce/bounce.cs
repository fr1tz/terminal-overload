// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(ItemStandardcatBounceShape)
{
   ignoreDamage = true;
   shapeFile = "content/xa/notc/core/shapes/standardcat/bounce/p1/shape.dae";
};

function ItemStandardcatBounceShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemStandardcatBounceShape::onMount()");
}

function ItemStandardcatBounceShape::onUnmount(%this, %obj, %mountObj, %node)
{
   //echo("ItemStandardcatBounceShape::onUnmount()");
   %obj.schedule(0, "delete");
}

function ItemStandardcatBounceShape::fire(%this, %obj)
{
   //echo("ItemStandardcatBounceShape::fire()");
   
   %mount = %obj.getObjectMount();
   if(!isObject(%mount))
      return;

   if(%mount.getEnergyLevel() < 50)
   {
      if(isObject(%mount.client))
         %mount.client.play2D(GenericNoDiscTargetSound);
      return;
   }

//	if($Sim::Time < %mount.zTimeLastBounced + 1)
//		return;

   %time = getSimTime();
   %targets = new SimSet();

   %pos = %mount.getWorldBoxCenter();
   %radius = 10;
   %mask = $TypeMasks::PlayerObjectType; // | $TypeMasks::ProjectileObjectType;

   InitContainerRadiusSearch(%pos, %radius, %mask);
   while( (%targetObject = containerSearchNext()) != 0 )
      %targets.add(%targetObject);

   %hitEnemy = false;

   %halfRadius = %radius / 2;
   for(%idx = %targets.getCount()-1; %idx >= 0; %idx-- )
   {
      %targetObject = %targets.getObject(%idx);

//      if(%targetObject.getType() & $TypeMasks::ProjectileObjectType)
//         if(!%targetObject.isAlive())
//            continue;

      if(%targetObject.getTeamId() == %mount.getTeamId())
         continue;

      if(mAbs(%targetObject.zTimeLastBounced-%time) < 500)
         continue;

      // Calculate how much exposure the current object has to
      // the effect.  The object types listed are objects
      // that will block an explosion.
      %coverage = calcExplosionCoverage(%pos, %targetObject,
         $TypeMasks::InteriorObjectType |  $TypeMasks::TerrainObjectType |
         $TypeMasks::ForceFieldObjectType | $TypeMasks::VehicleObjectType |
         $TypeMasks::TurretObjectType);

      if(%coverage == 0)
         continue;

      %hitEnemy = true;

      %targetObject.zTimeLastBounced = %time;

      if(%targetObject.getClassName() $= "Projectile")
      {
         %speed = -1;
         %targetObject.explode();
      }
      else
      {
         // bouncy bounce...
         %vec = %targetObject.getVelocity();
         %vec = VectorScale(%vec, -1.5);
         %targetObject.setVelocity(%vec);

         if(%targetObject.getClassName() $= "NortDisc")
         {
            %speed = -1;
            %targetObject.setTrackingAbility(0);
         }
         else
         {
            // damage based on speed...
            %speed = VectorLen(%vec);
            %damage = %speed;
            %dmgpos = %targetObject.getWorldBoxCenter();
            %targetObject.damage(%mount, %dmgpos, %damage, $DamageType::BOUNCE);
         }
      }
   }

	%targets.delete();
 
   if(!%hitEnemy)
      %mount.setEnergyLevel(%mount.getEnergyLevel() - 50);
 
   echo("wee");
 
   // Effect
   %obj.stopAudio(0);
   %obj.playAudio(0, ItemBounceFireSound);
   %obj.setAllMeshesHidden(true);
   if(%hitEnemy)
      %obj.setMeshHidden("Hit", false);
   else
      %obj.setMeshHidden("Miss", false);
   %obj.stopThread(0);
   %obj.playThread(0, "fire");
   %obj.setThreadTimeScale(0, 5);
   %obj.setThreadDir(0, true);
   %obj.startFade(200, 0, true);
}


