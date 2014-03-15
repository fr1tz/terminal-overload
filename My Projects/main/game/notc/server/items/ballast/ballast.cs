// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock BallastShapeData(ItemBallastShape)
{
   shapeFile = "content/xa/notc/core/shapes/standardcat/ballast/p1/shape.dae";
   mass = 9000;
};

function ItemBallastShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemBallastShape::onMount()");
   %this.updateThread(%obj);
}

function ItemBallastShape::onUnmount(%this, %obj, %mountObj, %node)
{
   //echo("ItemBallastShape::onUnmount()");
   %obj.schedule(0, "delete");
}

function ItemBallastShape::drop(%this, %obj)
{
   //echo("ItemBallastShape::drop()");
   
   %level = %obj.getLevel();
   
   if(%level < 0.005)
      return;
   
   if(%level > 0.02)
      %level = 0.02;
   else
      %level = %level-0.01;
      
   %level = mClamp(%level, 0.0, 1.0);
   %obj.setLevel(%level);
      
   createExplosion(ItemBallastDropExplosion, %obj.getPosition(), "0 0 1");
}

function ItemBallastShape::updateThread(%this, %obj)
{
   //echo("ItemBallastShape::updateThread()");
   
   if(%obj.zUpdateThread !$= "")
   {
      cancel(%obj.zUpdateThread);
      %obj.zUpdateThread = "";
   }
   
   if(!isObject(%obj))
      return;
   
   %dtTime = 256;
   %obj.zUpdateThread = %this.schedule(%dtTime, "updateThread", %obj);
   
   %mount = %obj.getObjectMount();
   if(!isObject(%mount))
      return;
   
   %level = %obj.getLevel();
   %vel = %mount.getVelocity();
   %vel = setWord(%vel, 2, 0); // clear out z component
   %speed = VectorLen(%vel);
   
   if(%mount.zBalastLimit $= "")
      %mount.zBalastLimit = 0.02;
   
   if(%level <= 0.02)
   {
      %level += 0.0000125*%dtTime;
      if(%speed > 16)
         %level -= %speed/(25*%dtTime);
      if(%level > %mount.zBalastLimit)
         %level = %mount.zBalastLimit;
   }
   else
   {
      %level += 0.0003125*%dtTime;
      %level -= %speed/(6.25*%dtTime);
      %level = mClamp(%level, 0.02, 1.0);
   }
   
   //echo(%mount.zBalastLimit);
   //echo("speed:" SPC %speed);
   //echo("level:" SPC %level SPC "(" @ %level * %this.mass @ ")");
   
   if(%level > %mount.zBalastLimit)
      %this.drop(%obj);

   %level = mClamp(%level, 0, %mount.zBalastLimit);
   
   %obj.setLevel(%level);
}

