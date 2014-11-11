// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(ItemStandardcatEtherboardShape)
{
   ignoreDamage = true;
   shapeFile = "content/xa/notc/core/shapes/standardcat/etherboard/p1/shape.dae";
   canStealth = true; // script field
};

function ItemStandardcatEtherboardShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemStandardcatEtherboardShape::onMount()");
}

function ItemStandardcatEtherboardShape::onUnmount(%this, %obj, %mountObj, %node)
{
   //echo("ItemStandardcatEtherboardShape::onUnmount()");
   %obj.schedule(0, "delete");
}

function ItemStandardcatEtherboardShape::activate(%this, %obj)
{
   //echo("ItemStandardcatEtherboardShape::activate()");
   
   %obj.etherboard.playThread(0, "activate");
   %obj.etherboard.setThreadTimeScale(0, 4);
   %obj.etherboard.setThreadDir(0, true);
   %obj.etherboard.startFade(500, 0, false);
}

function ItemStandardcatEtherboardShape::deactivate(%this, %obj)
{
   //echo("ItemStandardcatEtherboardShape::deactivate()");

   %obj.etherboard.playThread(0, "activate");
   %obj.etherboard.setThreadTimeScale(0, 4);
   %obj.etherboard.setThreadPosition(0, 1);
   %obj.etherboard.setThreadDir(0, false);
   %obj.etherboard.startFade(100, 0, true);
}

