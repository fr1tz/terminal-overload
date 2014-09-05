// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock BallastShapeData(ItemImpShieldShape)
{
   ignoreDamage = 1;
   shapeFile = "content/xa/notc/core/shapes/standardcat/impshield/p1/shape.dae";
   mass = 0;
   groundConnectionBeamQuad = "ItemImpShieldBeam";
   canStealth = 1; // script field
};

function ItemImpShieldShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemImpShieldShape::onMount()");
   %mountObj.zImpShield = 0.5;
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
   
   %dtTime = 64*4;
   %obj.zUpdateThread = %this.schedule(%dtTime, "updateThread", %obj);
   
   %mount = %obj.getObjectMount();
   if(!isObject(%mount))
      return;
   
   %level = %mount.zImpShield;
   
   if(%mount.zIsSliding)
   {
      %dt = -0.008*4;
   }
   else
   {
      %dt = 0.010*4;
   }
   
   %level = mClamp(%level+%dt, 0, 0.75);
   
   if(%mount.getInventory(ItemEtherboard) > 0)
   {
      if(%level > 0)
      {
         %mount.allowSliding(true);
      }
      else
      {
         %mount.allowSliding(false);
         //if(%mount.zIsSliding)
         //   %mount.getDataBlock().onStopSliding(%mount);
      }
   }
   else
   {
      %mount.allowSliding(false);
      //if(%mount.zIsSliding)
      //   %mount.getDataBlock().onStopSliding(%mount);
   }

   %obj.setLevel(%level);
   %mount.zImpShield = %level;
}


