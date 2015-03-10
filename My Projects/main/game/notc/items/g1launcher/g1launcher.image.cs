// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(ItemG1LauncherImage)
{
   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/g1launcher/image/p1/shape.dae";
   shapeFileFP = "content/o/rotc/p.5.4/shapes/rotc/misc/nothing.dts";
   emap = true;

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
	mountPoint = 4;
	offset = "0.20 0 0.05";
	rotation = "1 0 0 -12";
   eyeOffset = "1 0 0";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;

   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Magazine";
   //minEnergy = 0;

   useRemainderDT = false;
   maxConcurrentSounds = 1;

   projectile = ItemG1LauncherProjectile;
   ammo = ItemG1LauncherAmmo;
   //item = ItemG1;

	//-------------------------------------------------
	// Image states
	//
		// Preactivation
		stateName[0]                    = "Preactivate";
		stateTransitionOnAmmo[0]        = "Ready";
		stateTransitionOnNoAmmo[0]      = "NoAmmo";

		// Waiting for the trigger
		stateName[1]                    = "Ready";
		stateTransitionOnNoAmmo[1]      = "NoAmmo";
		stateTransitionOnTriggerDown[1] = "Charge";

		// Charge
      stateName[2]                    = "Charge";
      stateTransitionOnTriggerUp[2]   = "Fire";
      stateCharge[2]                  = true;
      stateSound[2]                   = ItemG1LauncherChargeSound;
      stateAllowImageChange[2]        = false;

      // Fire
      stateName[3]                    = "Fire";
      stateTransitionOnTimeout[3]     = "NoAmmo";
      stateTimeoutValue[3]            = 0.0;
      stateAllowImageChange[3]        = false;
      stateFire[3]                    = true;
      stateSound[3]                   = ItemG1LauncherFireSound;
      stateScript[3]                  = "onFire";

      // No ammo
      stateName[4]                    = "NoAmmo";
      stateTransitionOnAmmo[4]        = "Ready";
      stateTransitionOnTriggerDown[4] = "DryFire";

      // Dry fire
      stateName[5]                    = "DryFire";
      stateTransitionOnTriggerUp[5]   = "NoAmmo";
      stateSound[5]                   = WeaponEmptySound;
	//
	// End of image states
	//-------------------------------------------------
};

function ItemG1LauncherImage::onFire(%this, %obj, %slot)
{
   //echo("ItemG1LauncherImage::onFire()");
   
	%projectile = %this.projectile;

	%muzzlePoint = %obj.getMuzzlePoint(%slot);
	%muzzleVector = %obj.getMuzzleVector(%slot);

	%objectVelocity = %obj.getVelocity();
	%muzzleVelocity = VectorAdd(
		VectorScale(%muzzleVector, %projectile.muzzleVelocity),
		VectorScale(%objectVelocity, %projectile.velInheritFactor));
  
	%throwCoefficient = %obj.getImageCharge(%slot);
	if( %throwCoefficient > 1 )
      %throwCoefficient = 1;
      
   %muzzleVelocity = VectorScale(%muzzleVelocity, %throwCoefficient);

	%p = new Projectile() {
		dataBlock       = %projectile;
		teamId          = %obj.teamId;
		initialVelocity = %muzzleVelocity;
		initialPosition = %muzzlePoint;
		sourceObject    = %obj;
		sourceSlot      = %slot;
		client	       = %obj.client;
	};
	MissionCleanup.add(%p);
   copyPalette(%obj, %p);

   %obj.decInventory(%this.ammo, 1);
   %obj.schedule(5000, "incInventory", %this.ammo, 1);

	return %p;
}


