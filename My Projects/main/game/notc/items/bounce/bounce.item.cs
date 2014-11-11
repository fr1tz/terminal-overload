// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemBounce)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/standardcat/bounce/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "B.O.U.N.C.E.";
   description = "B.O.U.N.C.E.";
};

function ItemBounce::onInventory(%this, %obj, %amount)
{
   //echo("ItemBounce::onInventory()");
   
   if(%amount == 0)
   {
      if(isObject(%obj.zBounce))
         %obj.zBounce.delete();
   }
   else
   {
      %obj.zBounce = new StaticShape() {
         dataBlock = ItemStandardcatBounceShape;
      };
      copyPalette(%obj, %obj.zBounce);
      MissionCleanup.add(%obj.zBounce);
      %obj.mountObject(%obj.zBounce, 8);
      %obj.zBounce.setAllMeshesHidden(true);
   }
}
