// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnExplosiveDiscAmmo)
{
   // Mission editor category
   category = "Ammo";

   // Add the Ammo namespace as a parent.  The ammo namespace provides
   // common ammo related functions and hooks into the inventory system.
   className = "Ammo";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/explosivedisc/ammo/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;

   // Dynamic properties defined by the scripts
   playAmbient = true;
   pickUpName = "Explosive Discs";
   count = 5;
};

