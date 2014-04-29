// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// This file contains Weapon and Ammo Class/"namespace" helper methods as well
// as hooks into the inventory system. These functions are not attached to a
// specific C++ class or datablock, but define a set of methods which are part
// of dynamic namespaces "class". The Items include these namespaces into their
// scope using the  ItemData and ItemImageData "className" variable.
// ----------------------------------------------------------------------------

// All ShapeBase images are mounted into one of 8 slots on a shape.  This weapon
// system assumes all primary weapons are mounted into this specified slot:
$WeaponSlot = 0;

$TargetingMask::Launcher = 1;

//-----------------------------------------------------------------------------
// Weapon Class
//-----------------------------------------------------------------------------

function Weapon::onUse(%data, %obj)
{
   // Default behavior for all weapons is to mount it into the object's weapon
   // slot, which is currently assumed to be slot 0
   if (%obj.getMountedImage($WeaponSlot) != %data.image.getId())
   {
      serverPlay3D(WeaponUseSound, %obj.getTransform());

      %obj.mountImage(%data.image, $WeaponSlot);
      if (%obj.client)
      {
         if (%data.description !$= "")
            messageClient(%obj.client, 'MsgWeaponUsed', '\c0%1 selected.', %data.description);
         else
            messageClient(%obj.client, 'MsgWeaponUsed', '\c0Weapon selected');
      }
   }
}

function Weapon::onPickup(%this, %obj, %shape, %amount)
{
   // The parent Item method performs the actual pickup.
   // For player's we automatically use the weapon if the
   // player does not already have one in hand.
   if (Parent::onPickup(%this, %obj, %shape, %amount))
   {
      serverPlay3D(WeaponPickupSound, %shape.getTransform());
      if (%shape.getClassName() $= "Player" && %shape.getMountedImage($WeaponSlot) == 0)
         %shape.use(%this);
   }
}

function Weapon::onInventory(%this, %obj, %amount)
{
   // Weapon inventory has changed, make sure there are no weapons
   // of this type mounted if there are none left in inventory.
   if (!%amount && (%slot = %obj.getMountSlot(%this.image)) != -1)
      %obj.unmountImage(%slot);
}

//-----------------------------------------------------------------------------
// Weapon Image Class
//-----------------------------------------------------------------------------

function WeaponImage::onMount(%this, %obj, %slot)
{
   %this.updateMagazine(%obj, %slot);
}

function WeaponImage::onUnmount(%this, %obj, %slot)
{

}

// ----------------------------------------------------------------------------
// A "generic" weaponimage onFire handler for most weapons.  Can be overridden
// with an appropriate namespace method for any weapon that requires a custom
// firing solution.

// projectileSpread is a dynamic property declared in the weaponImage datablock
// for those weapons in which bullet skew is desired.  Must be greater than 0,
// otherwise the projectile goes straight ahead as normal.  lower values give
// greater accuracy, higher values increase the spread pattern.
// ----------------------------------------------------------------------------

function WeaponImage::onFire(%this, %obj, %slot)
{
   //echo("\c4WeaponImage::onFire( "@%this.getName()@", "@%obj.client.nameBase@", "@%slot@" )");

   // Make sure we have valid data
   if (!isObject(%this.projectile))
   {
      error("WeaponImage::onFire() - Invalid projectile datablock");
      return;
   }
   
   // Decrement inventory ammo. The image's ammo state is updated
   // automatically by the ammo inventory hooks.
   if ( !%this.infiniteAmmo )
      %obj.decInventory(%this.ammo, 1);

   // Get the player's velocity, we'll then add it to that of the projectile
   %objectVelocity = %obj.getVelocity();
   
   %numProjectiles = %this.projectileNum;
   if (%numProjectiles == 0)
      %numProjectiles = 1;
      
   for (%i = 0; %i < %numProjectiles; %i++)
   {
      if (%this.projectileSpread)
      {
         // We'll need to "skew" this projectile a little bit.  We start by
         // getting the straight ahead aiming point of the gun
         %vec = %obj.getMuzzleVector(%slot);

         // Then we'll create a spread matrix by randomly generating x, y, and z
         // points in a circle
         %matrix = "";
         for(%j = 0; %j < 3; %j++)
            %matrix = %matrix @ (getRandom() - 0.5) * 2 * 3.1415926 * %this.projectileSpread @ " ";
         %mat = MatrixCreateFromEuler(%matrix);

         // Which we'll use to alter the projectile's initial vector with
         %muzzleVector = MatrixMulVector(%mat, %vec);
      }
      else
      {
         // Weapon projectile doesn't have a spread factor so we fire it using
         // the straight ahead aiming point of the gun
         %muzzleVector = %obj.getMuzzleVector(%slot);
      }

      // Add player's velocity
      %muzzleVelocity = VectorAdd(
         VectorScale(%muzzleVector, %this.projectile.muzzleVelocity),
         VectorScale(%objectVelocity, %this.projectile.velInheritFactor));

      // Create the projectile object
      %p = new (%this.projectileType)()
      {
         dataBlock = %this.projectile;
         initialVelocity = %muzzleVelocity;
         initialPosition = %obj.getMuzzlePoint(%slot);
         sourceObject = %obj;
         sourceSlot = %slot;
         client = %obj.client;
         sourceClass = %obj.getClassName();
      };
      MissionCleanup.add(%p);
   }
}

// ----------------------------------------------------------------------------
// A "generic" weaponimage onAltFire handler for most weapons.  Can be
// overridden with an appropriate namespace method for any weapon that requires
// a custom firing solution.
// ----------------------------------------------------------------------------

function WeaponImage::onAltFire(%this, %obj, %slot)
{
   //echo("\c4WeaponImage::onAltFire("@%this.getName()@", "@%obj.client.nameBase@", "@%slot@")");

   // Decrement inventory ammo. The image's ammo state is updated
   // automatically by the ammo inventory hooks.
   %obj.decInventory(%this.ammo, 1);

   // Get the player's velocity, we'll then add it to that of the projectile
   %objectVelocity = %obj.getVelocity();
   
   %numProjectiles = %this.altProjectileNum;
   if (%numProjectiles == 0)
      %numProjectiles = 1;
      
   for (%i = 0; %i < %numProjectiles; %i++)
   {
      if (%this.altProjectileSpread)
      {
         // We'll need to "skew" this projectile a little bit.  We start by
         // getting the straight ahead aiming point of the gun
         %vec = %obj.getMuzzleVector(%slot);

         // Then we'll create a spread matrix by randomly generating x, y, and z
         // points in a circle
         %matrix = "";
         for(%i = 0; %i < 3; %i++)
            %matrix = %matrix @ (getRandom() - 0.5) * 2 * 3.1415926 * %this.altProjectileSpread @ " ";
         %mat = MatrixCreateFromEuler(%matrix);

         // Which we'll use to alter the projectile's initial vector with
         %muzzleVector = MatrixMulVector(%mat, %vec);
      }
      else
      {
         // Weapon projectile doesn't have a spread factor so we fire it using
         // the straight ahead aiming point of the gun.
         %muzzleVector = %obj.getMuzzleVector(%slot);
      }

      // Add player's velocity
      %muzzleVelocity = VectorAdd(
         VectorScale(%muzzleVector, %this.altProjectile.muzzleVelocity),
         VectorScale(%objectVelocity, %this.altProjectile.velInheritFactor));

      // Create the projectile object
      %p = new (%this.projectileType)()
      {
         dataBlock = %this.altProjectile;
         initialVelocity = %muzzleVelocity;
         initialPosition = %obj.getMuzzlePoint(%slot);
         sourceObject = %obj;
         sourceSlot = %slot;
         client = %obj.client;
      };
      MissionCleanup.add(%p);
   }
}

// ----------------------------------------------------------------------------
// A "generic" weaponimage onWetFire handler for most weapons.  Can be
// overridden with an appropriate namespace method for any weapon that requires
// a custom firing solution.
// ----------------------------------------------------------------------------

function WeaponImage::onWetFire(%this, %obj, %slot)
{
   //echo("\c4WeaponImage::onWetFire("@%this.getName()@", "@%obj.client.nameBase@", "@%slot@")");

   // Decrement inventory ammo. The image's ammo state is updated
   // automatically by the ammo inventory hooks.
   %obj.decInventory(%this.ammo, 1);

   // Get the player's velocity, we'll then add it to that of the projectile
   %objectVelocity = %obj.getVelocity();
   
   %numProjectiles = %this.projectileNum;
   if (%numProjectiles == 0)
      %numProjectiles = 1;
      
   for (%i = 0; %i < %numProjectiles; %i++)
   {
      if (%this.wetProjectileSpread)
      {
         // We'll need to "skew" this projectile a little bit.  We start by
         // getting the straight ahead aiming point of the gun
         %vec = %obj.getMuzzleVector(%slot);

         // Then we'll create a spread matrix by randomly generating x, y, and z
         // points in a circle
         %matrix = "";
         for(%j = 0; %j < 3; %j++)
         %matrix = %matrix @ (getRandom() - 0.5) * 2 * 3.1415926 * %this.wetProjectileSpread @ " ";
         %mat = MatrixCreateFromEuler(%matrix);

         // Which we'll use to alter the projectile's initial vector with
         %muzzleVector = MatrixMulVector(%mat, %vec);
      }
      else
      {
         // Weapon projectile doesn't have a spread factor so we fire it using
         // the straight ahead aiming point of the gun.
         %muzzleVector = %obj.getMuzzleVector(%slot);
      }
      
      // Add player's velocity
      %muzzleVelocity = VectorAdd(
         VectorScale(%muzzleVector, %this.wetProjectile.muzzleVelocity),
         VectorScale(%objectVelocity, %this.wetProjectile.velInheritFactor));

      // Create the projectile object
      %p = new (%this.projectileType)()
      {
         dataBlock = %this.wetProjectile;
         initialVelocity = %muzzleVelocity;
         initialPosition = %obj.getMuzzlePoint(%slot);
         sourceObject = %obj;
         sourceSlot = %slot;
         client = %obj.client;
      };
      MissionCleanup.add(%p);
   }
}

//-----------------------------------------------------------------------------
// Magazine Management
//-----------------------------------------------------------------------------

function WeaponImage::updateMagazine(%this, %obj, %slot)
{
   //echo("WeaponImage::updateMagazine: " SPC %this SPC %obj SPC %slot);
   
   if(%this.ammo !$= "")
   {
      %rounds = %obj.getInventory(%this.ammo);
      %obj.setImageMagazineRounds(%slot, %rounds);
   }
}

//-----------------------------------------------------------------------------
// Ammmo Class
//-----------------------------------------------------------------------------

function Ammo::onPickup(%this, %obj, %shape, %amount)
{
   // The parent Item method performs the actual pickup.
   if (Parent::onPickup(%this, %obj, %shape, %amount))
      serverPlay3D(AmmoPickupSound, %shape.getTransform());
}

function Ammo::onInventory(%this, %obj, %amount)
{
   //echo("Ammo::onInventory: " SPC %this SPC %obj SPC %amount);
   
   if(%this.giveWeapon !$= "")
      %obj.incInventory(%this.giveWeapon, 1);

   // The ammo inventory state has changed, we need to update any
   // mounted images using this ammo to reflect the new state.
   for(%i = 0; %i < 8; %i++)
   {
      if ((%image = %obj.getMountedImage(%i)) > 0)
         %image.updateMagazine(%obj, %i);
   }
}

// ----------------------------------------------------------------------------
// Weapon cycling
// ----------------------------------------------------------------------------

function ShapeBase::clearWeaponCycle(%this)
{
   %this.totalCycledWeapons = 0;
}

function ShapeBase::addToWeaponCycle(%this, %weapon)
{
   %this.cycleWeapon[%this.totalCycledWeapons++ - 1] = %weapon;
}

function ShapeBase::cycleWeapon(%this, %direction)
{
   // Can't cycle what we don't have
   if (%this.totalCycledWeapons == 0)
      return;
      
   // Find out the index of the current weapon, if any (not all
   // available weapons may be part of the cycle)
   %currentIndex = -1;
   if (%this.getMountedImage($WeaponSlot) != 0)
   {
      %curWeapon = %this.getMountedImage($WeaponSlot).item.getName();
      for (%i=0; %i<%this.totalCycledWeapons; %i++)
      {
         if (%this.cycleWeapon[%i] $= %curWeapon)
         {
            %currentIndex = %i;
            break;
         }
      }
   }

   // Get the next weapon index
   %nextIndex = 0;
   %dir = 1;
   if (%currentIndex != -1)
   {
      if (%direction $= "prev")
      {
         %dir = -1;
         %nextIndex = %currentIndex - 1;
         if (%nextIndex < 0)
         {
            // Wrap around to the end
            %nextIndex = %this.totalCycledWeapons - 1;
         }
      }
      else
      {
         %nextIndex = %currentIndex + 1;
         if (%nextIndex >= %this.totalCycledWeapons)
         {
            // Wrap back to the beginning
            %nextIndex = 0;
         }
      }
   }
   
   // We now need to check if the next index is a valid weapon.  If not,
   // then continue to cycle to the next weapon, in the appropriate direction,
   // until one is found.  If nothing is found, then do nothing.
   %found = false;
   for (%i=0; %i<%this.totalCycledWeapons; %i++)
   {
      %weapon = %this.cycleWeapon[%nextIndex];
      if (%weapon !$= "" && %this.hasInventory(%weapon)) // && %this.hasAmmo(%weapon))
      {
         // We've found out weapon
         %found = true;
         break;
      }
      
      %nextIndex = %nextIndex + %dir;
      if (%nextIndex < 0)
      {
         %nextIndex = %this.totalCycledWeapons - 1;
      }
      else if (%nextIndex >= %this.totalCycledWeapons)
      {
         %nextIndex = 0;
      }
   }
   
   if (%found)
   {
      %this.use(%this.cycleWeapon[%nextIndex]);
   }
}
