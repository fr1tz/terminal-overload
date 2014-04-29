// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(ItemLauncherPseudoProjectile)
{
   // ShotgunProjectileData fields
	numBullets = 1;
	range = 100;
	muzzleSpreadRadius = 0.0;
	referenceSpreadRadius = 0.0;
	referenceSpreadDistance = 50;
   energyDrain = 0;
   muzzleVelocity      = 9999;
   velInheritFactor    = 0;
};

datablock ShapeBaseImageData(ItemLauncherImage)
{
   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/blaster.tp.dts";
   shapeFileFP = "content/xa/rotc_hack/shapes/blaster.fp.dts";
   emap = true;

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
	mountPoint = 4;
	offset = "-0.15 -0.10 -0.05";
	rotation = "1 0 0 -12";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;

   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Energy";
   minEnergy = 0;

   projectile = ItemLauncherPseudoProjectile;
   
	// Targeting
	targetingMask = $TargetingMask::Launcher;
	targetingMaxDist = 250;
   followTarget = false;

   useRemainderDT = false;
   maxConcurrentSounds = 1;

   // Script fields
   item = ItemLauncher;
   //ammo = ItemLauncherAmmo;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                    = "Preactivate";
		stateTransitionOnAmmo[0]        = "Ready";
		stateTransitionOnNoAmmo[0]      = "Ready";

		// waiting for the trigger...
		stateName[1]                    = "Ready";
		//stateTransitionOnNoAmmo[1]      = "NoAmmo";
		stateTransitionOnTriggerDown[1] = "SelectAction";
		stateTransitionOnTarget[1]      = "Target";
		stateTarget[1]                  = true;

		// target...
		stateName[2]                      = "Target";
		//stateTransitionOnNoAmmo[2]        = "NoAmmo";
		stateTransitionOnTargetLocked[2] = "Locked";
		stateTransitionOnNoTarget[2]      = "Ready";
		//stateTransitionOnTriggerDown[2]   = "SelectAction";
		stateTarget[2]                    = true;
		stateSound[2]                     = ItemLauncherTargetSound;
      stateScript[2]                    = "onTarget";

		// target locked...
		stateName[3]                      = "Locked";
		//stateTransitionOnNoAmmo[3]        = "NoAmmo";
		//stateTransitionOnTriggerDown[3]   = "SelectAction";
		stateTransitionOnNoTarget[3]      = "Ready";
		stateTarget[3]                    = true;
		stateSound[3]                     = ItemLauncherTargetLockedSound;
      stateScript[3]                    = "onTargetLocked";

		// select action...
		stateName[4]                    = "SelectAction";
		stateTransitionOnTarget[4]      = "TargetAction";
		stateTransitionOnNoTarget[4]    = "NoTargetAction";
		stateFire[4]                    = true;

		// intercept...
    	stateName[5]                    = "TargetAction";
    	stateTransitionOnTimeout[5]     = "Release";
    	stateTimeoutValue[5]            = 0.0;
		stateFireProjectile[5]          = ItemLauncherPseudoProjectile;
    	stateSound[5]                   = DiscThrowSound;

		// attack...
    	stateName[6]                    = "NoTargetAction";
    	stateTransitionOnTimeout[6]     = "Release";
		stateFireProjectile[6]          = ItemLauncherPseudoProjectile;
    	stateTimeoutValue[6]            = 0.25;

		// release...
    	stateName[7]                    = "Release";
		stateTransitionOnTriggerUp[7]   = "Ready";
		stateTarget[7]                  = false;

		// no ammo...
		stateName[8]                    = "NoAmmo";
		stateTransitionOnAmmo[8]        = "Ready";
		stateTransitionOnTriggerDown[8] = "DryFire";
		stateTarget[8]                  = false;

		// dry fire...
		stateName[9]                    = "DryFire";
		stateTransitionOnTriggerUp[9]   = "NoAmmo";
		stateSound[9]                  = WeaponEmptySound;
	//
	// ...end of image states
	//-------------------------------------------------
};

function ItemLauncherImage::onTarget(%this, %obj, %slot)
{
   echo("ItemLauncherImage::onTarget()");
}

function ItemLauncherImage::onTargetLocked(%this, %obj, %slot)
{
   echo("ItemLauncherImage::onTargetLocked()");
   echo(%obj.getImageTarget(%slot));
}

