// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnMG1)
{
   // Mission editor category
   category = "Weapon";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/fr1tz/rotc_hack/shapes/minigun.tp.dts";
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

