// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock BallastShapeData(ItemImpShieldShape)
{
   ignoreDamage = true;
   shapeFile = "content/xa/notc/core/shapes/standardcat/impshield/p1/shape.dae";
   mass = 0;
};

function ItemImpShieldShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemImpShieldShape::onMount()");
   %this.updateThread(%obj);
}

function ItemImpShieldShape::onUnmount(%this, %obj, %mountObj, %node)
{
   //echo("ItemImpShieldShape::onUnmount()");
   %obj.schedule(0, "delete");
}

function ItemImpShieldShape::drop(%this, %obj)
{
   //echo("ItemImpShieldShape::drop()");
   
   %level = %obj.getLevel();
   
   if(%level < 0.005)
      return;
   
   if(%level > 0.02)
      %level = 0.02;
   else
      %level = %level-0.01;
      
   %level = mClamp(%level, 0.0, 1.0);
   %obj.setLevel(%level);
      
   createExplosion(ItemImpShieldDropExplosion, %obj.getPosition(), "0 0 1");
}

function ItemImpShieldShape::updateThread(%this, %obj)
{
   //echo("ItemImpShieldShape::updateThread()");
   
   if(%obj.zUpdateThread !$= "")
   {
      cancel(%obj.zUpdateThread);
      %obj.zUpdateThread = "";
   }
   
   if(!isObject(%obj))
      return;
   
   %dtTime = 64;
   %obj.zUpdateThread = %this.schedule(%dtTime, "updateThread", %obj);
   
   %mount = %obj.getObjectMount();
   if(!isObject(%mount))
      return;
   
   %level = %obj.getLevel();
   
   %contact = false;
	if(!%mount.zIsSliding)
   {
      %start = %mount.getWorldBoxCenter();
      %end	= VectorAdd(%start, "0 0 -3");
      %mask = $TypeMasks::StaticObjectType;
      %contact = containerRayCast(%start, %end, %mask, %mount);
   }

   if(%contact)
   {
      %dt = 0.010;
   }
   else
   {
      %dt = -0.008;
   }
   
   %level = mClamp(%level+%dt, 0, 0.75);

   %obj.setLevel(%level);
   %mount.zImpShield = %level;
}


