// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemBallast)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/standardcat/ballast/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Ballast";
   description = "Ballast";
};

function ItemBallast::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      if(isObject(%obj.ballast))
         %obj.ballast.delete();
   }
   else
   {
      %obj.ballast = new BallastShape() {
         dataBlock = ItemBallastShape;
      };
      copyPalette(%obj, %obj.ballast);
      %obj.mountObject(%obj.ballast, 3);
      MissionCleanup.add(%obj.ballast);
   }
}
