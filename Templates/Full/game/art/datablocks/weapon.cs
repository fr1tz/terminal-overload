// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This file contains 'generic' datablocks usable by all weapon class items.

// ----------------------------------------------------------------------------
// Audio profiles
// ----------------------------------------------------------------------------

datablock SFXProfile(WeaponUseSound)
{
   filename = "art/sound/weapons/Weapon_switch";
   description = AudioClose3d;
   preload = true;
};

datablock SFXProfile(WeaponPickupSound)
{
   filename = "art/sound/weapons/Weapon_pickup";
   description = AudioClose3d;
   preload = true;
};

datablock SFXProfile(AmmoPickupSound)
{
   filename = "art/sound/weapons/Ammo_pickup";
   description = AudioClose3d;
   preload = true;
};
