// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemG1LauncherAmmo)
{
   // Mission editor category
   category = "Ammo";

   // Add the Ammo namespace as a parent.  The ammo namespace provides
   // common ammo related functions and hooks into the inventory system.
   className = "Ammo";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/g1launcher/image/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;

   // Dynamic properties defined by the scripts
   playAmbient = true;
   pickUpName = "Grenade";
   count = 1;
};

datablock ItemData(ItemG1Launcher)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/g1launcher/image/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Grenade launcher";
   description = "Grenade launcher";
};

function ItemG1Launcher::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      %obj.unmountImage(2);
   }
   else
   {
      %obj.mountImage(ItemG1LauncherImage, 2, true);
   }
}

