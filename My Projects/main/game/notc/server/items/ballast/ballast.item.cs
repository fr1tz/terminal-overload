// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemBallast)
{
   // Mission editor category
   category = "Item";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/xa/oldshapes/raptor/magazine/p1/shape.dae";
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
   %obj.ballast = new BallastShape() {
      dataBlock = ItemBallastShape;
   };
   %obj.mountObject(%obj.ballast, 3);
   MissionCleanup.add(%obj.ballast);
   
   //$ballast = %obj.ballast;
   //$player = %obj;
}
