// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Inventory items.  These objects rely on the item & inventory support
// system defined in item.cs and inventory.cs

//-----------------------------------------------------------------------------
// Health kits can be added to your inventory and used to heal up.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Audio profiles
//-----------------------------------------------------------------------------
datablock SFXProfile(HealthUseSound)
{
   filename = "art/sound/health_mono_01";
   description = AudioClose3d;
   preload = true;
};

//-----------------------------------------------------------------------------
// Health Kits cannot be picked up and are not meant to be added to
// inventory.  Health is applied automatically when an objects collides
// with a patch.
//-----------------------------------------------------------------------------

datablock ItemData(HealthKitSmall)
{
   // Mission editor category, this datablock will show up in the
   // specified category under the "shapes" root category.
   category = "Health";

   className = "HealthPatch";

   // Basic Item properties
   shapeFile = "art/shapes/items/kit/healthkit.dts";
   mass = 2;
   friction = 1;
   elasticity = 0.3;
   emap = true;

   // Dynamic properties defined by the scripts
   pickupName = "a small health kit";
   repairAmount = 50;
};

// This is the "health patch" dropped by a dying player.
datablock ItemData(HealthKitPatch)
{
   // Mission editor category, this datablock will show up in the
   // specified category under the "shapes" root category.
   category = "Health";

   className = "HealthPatch";

   // Basic Item properties
   shapeFile = "art/shapes/items/patch/healthpatch.dts";
   mass = 2;
   friction = 1;
   elasticity = 0.3;
   emap = true;

   // Dynamic properties defined by the scripts
   pickupName = "a health patch";
   repairAmount = 50;
};
