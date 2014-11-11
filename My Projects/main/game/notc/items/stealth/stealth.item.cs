// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemStealth)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/standardcat/etherboard/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Stealth Module";
   description = "Stealth Module";
};

function ItemStealth::onInventory(%this, %obj, %amount)
{
   //echo("ItemStealth::onInventory()");
   
   if(%amount == 0)
   {
      %obj.zHasStealth = false;
   }
   else
   {
      %obj.zHasStealth = true;
   }
}
