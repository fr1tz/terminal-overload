// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemImpShield)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/standardcat/impshield/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Impulse Shield";
   description = "Impulse Shield";
};

function ItemImpShield::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      if(isObject(%obj.ballast))
         %obj.ballast.delete();
   }
   else
   {
      %obj.ballast = new BallastShape() {
         dataBlock = ItemImpShieldShape;
      };
      copyPalette(%obj, %obj.ballast);
      %obj.mountObject(%obj.ballast, 3);
      MissionCleanup.add(%obj.ballast);
   }
}
