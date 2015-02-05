// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnSMG3)
{
   // Mission editor category
   category = "Weapon";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/smg1/image/p1/shape.tp.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   PreviewImage = 'lurker.png';
   pickUpName = "SMG3";
   description = "SMG3";
   image = WpnSMG3Image;
   reticle = "crossHair";
};

