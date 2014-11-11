// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnMG1Ammo)
{
   // Mission editor category
   category = "Ammo";

   // Add the Ammo namespace as a parent.  The ammo namespace provides
   // common ammo related functions and hooks into the inventory system.
   className = "Ammo";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/mg1/ammo/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;

   // Dynamic properties defined by the scripts
   giveWeapon = WpnMG1;
   playAmbient = true;
   pickUpName = "MG1 Ammo";
   count = 100;
};

datablock ItemData(WpnMG1)
{
   // Mission editor category
   category = "Weapon";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/minigun.tp.dts";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   PreviewImage = 'lurker.png';
   pickUpName = "MG1";
   description = "MG1";
   image = WpnMG1Image;
   reticle = "crossHair";
};

