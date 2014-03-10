// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemEtherboard)
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
   pickUpName = "Etherboard";
   description = "Etherboard";
};

function ItemEtherboard::onInventory(%this, %obj, %amount)
{
   //echo("ItemEtherboard::onInventory()");
   
   if(%amount == 0)
   {
      if(isObject(%obj.etherboard))
         %obj.etherboard.delete();
      %obj.allowSliding(false);
   }
   else
   {
      %obj.etherboard = new StaticShape() {
         dataBlock = ItemStandardcatEtherboardShape;
      };
      copyPalette(%obj, %obj.etherboard);
      %obj.mountObject(%obj.etherboard, 8);
      %obj.etherboard.startFade(0, 0, true);
      MissionCleanup.add(%obj.etherboard);
      %obj.allowSliding(true);
   }
}
