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
   
   %obj.zUpdateThread = %this.schedule(32, "updateThread", %obj);
   
   %mount = %obj.getObjectMount();
   if(!isObject(%mount))
      return;
   
   %level = %obj.getLevel();
   %vel = %mount.getVelocity();
   %vel = setWord(%vel, 2, 0); // clear out z component
   %speed = VectorLen(%vel);
   
   if(%level <= 0.02)
   {
      %level += 0.0004;
      %level -= %speed/50000;
   }
   else
   {
      %level += 0.01;
      %level -= %speed/200;
      if(%level < 0.02)
         %level = 0.02;
   }

   //echo(%mount.zBalastLimit);
   //echo("speed:" SPC %speed);
   //echo("level:" SPC %level SPC "(" @ %level * %this.mass @ ")");

   if(%mount.zBalastLimit $= "")
      %mount.zBalastLimit = 0.02;
   
   if(%level > %mount.zBalastLimit)
   {
      // Drop ballast effect
   }
   
   %level = mClamp(%level, 0, %mount.zBalastLimit);
   
   %obj.setLevel(%level);
}

