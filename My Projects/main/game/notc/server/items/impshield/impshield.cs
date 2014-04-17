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
   %vel = %mount.getVelocity();
   %vel = setWord(%vel, 2, 0); // clear out z component
   %speed = VectorLen(%vel);
   
   if(%mount.zImpShieldLimit $= "")
      %mount.zImpShieldLimit = 0.75;
   
   if(%level <= 0.75)
   {
      %level += 0.0001*%dtTime;
      if(%speed > 16)
         %level -= %speed/(50*%dtTime);
      if(%level > %mount.zImpShieldLimit)
         %level = %mount.zImpShieldLimit;
   }
   else
   {
      %level += 0.0003125*%dtTime;
      %level -= %speed/(6.25*%dtTime);
      %level = mClamp(%level, 0.02, 1.0);
   }
   
   //echo(%mount.zImpShieldLimit);
   //echo("speed:" SPC %speed);
   //echo("level:" SPC %level SPC "(" @ %level * %this.mass @ ")");
   
   if(%level > %mount.zImpShieldLimit)
      %this.drop(%obj);

   %level = mClamp(%level, 0, %mount.zImpShieldLimit);

   %obj.setLevel(%level);
   %mount.zImpShield = %level;
}


