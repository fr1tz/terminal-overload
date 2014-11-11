// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemVAMP)
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
   pickUpName = "V-AMP";
   description = "V-AMP";
};

function ItemVAMP::onInventory(%this, %obj, %amount)
{
   //echo("ItemEtherboard::onInventory()");
   
   if(%amount == 0)
   {
      %obj.zVAMP = 0;
   }
   else
   {
      %obj.zVAMP = 0.5;
   }
}
