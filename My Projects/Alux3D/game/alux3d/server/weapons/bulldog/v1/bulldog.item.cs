// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnBulldogAmmo)
{
   // Mission editor category
   category = "Ammo";

   // Add the Ammo namespace as a parent.  The ammo namespace provides
   // common ammo related functions and hooks into the inventory system.
   className = "Ammo";

   // Basic Item properties
   shapeFile = "content/fr1tz/oldshapes/bulldog/magazine/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;

   // Dynamic properties defined by the scripts
   pickUpName = "Bulldog Shells";
   count = 2;
};

datablock ItemData(WpnBulldogClip)
{
   // Mission editor category
   category = "AmmoClip";

   // Add the Ammo namespace as a parent.  The ammo namespace provides
   // common ammo related functions and hooks into the inventory system.
   className = "AmmoClip";

   // Basic Item properties
   shapeFile = "content/fr1tz/oldshapes/bulldog/magazine/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;

   // Dynamic properties defined by the scripts
   pickUpName = "Bulldog Magazine";
};

datablock ItemData(WpnBulldog)
{
   // Mission editor category
   category = "Weapon";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/fr1tz/oldshapes/bulldog/image/p1/TP_Bulldog.DAE";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   PreviewImage = 'lurker.png';
   pickUpName = "Bulldog SMG";
   description = "Bulldog";
   image = WpnBulldogImage;
   reticle = "crossHair";
};

