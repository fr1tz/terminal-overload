// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemLauncher)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/assaultrifle.tp.dts";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Launcher";
   description = "Launcher";
};

function ItemLauncher::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      %obj.unmountImage(1);
   }
   else
   {
      %obj.mountImage(ItemLauncherImage, 1, true);
   }
}

