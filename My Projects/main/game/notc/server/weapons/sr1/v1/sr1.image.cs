// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnSR1Image)
{
   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/sniper.tp.dts";
   shapeFileFP = "content/xa/rotc_hack/shapes/sniper.fp.dts";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.5 -0.2 -0.2";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Energy";
   minEnergy = 30;
   minCharge = 0.4;

   projectile = WpnSR1Projectile;

   casing = WpnSR1ProjectileShell;
   shellExitDir        = "1.0 0.3 1.0";
   shellExitOffset     = "0.15 -0.56 -0.1";
   shellExitVariance   = 15.0;
   shellVelocity       = 3.0;

   // Weapon lights up while firing
   lightType = "WeaponFireLight";
   lightColor = "0.992126 0.874016 0 1";
   lightRadius = "10";
   lightDuration = "100";
   lightBrightness = 2;

   // Shake camera while firing.
   shakeCamera = "0";
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "15.0 15.0 15.0";

   useRemainderDT = false;
   maxConcurrentSounds = 1;
   
   // Script fields
   reloadImage = WpnSR1ReloadImage;
   item = WpnSR1;
   ammo = WpnSR1Ammo;
   //clip = WpnSR1Clip;
   magazineCapacity = 30;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Activate";
		stateTransitionOnNoAmmo[0]       = "NoAmmo";
		stateTimeoutValue[0]             = 0.25;
		stateSequence[0]                 = "lowered";

		// when mounted...
		stateName[1]                     = "Activate";
		stateTransitionOnTimeout[1]      = "Ready";
		stateTimeoutValue[1]             = 0.25;
		stateSequence[1]                 = "lowered";

		// ready, just waiting for the trigger...
		stateName[2]                     = "Ready";
		stateTransitionOnNoAmmo[2]       = "NoAmmo";
		stateTransitionOnNotLoaded[2]    = "Disabled";
		stateTransitionOnTriggerDown[2]  = "RaiseCharge";
		stateArmThread[2]                = "holdrifle";
		stateSequence[2]                 = "lowered";
		stateScript[2]                   = "onReady";
		stateSpin[2]                     = "FullSpin";

		// raise & charge...
		stateName[3]                     = "RaiseCharge";
		stateTransitionOnTriggerUp[3]    = "CheckFire";
		//stateTransitionOnNoAmmo[3]       = "NoAmmo";
		stateTarget[3]                   = true;
		stateCharge[3]                   = true;
		stateAllowImageChange[3]         = true;
		stateArmThread[3]                = "aimrifle";
		stateSound[3]                    = WpnSR1ChargeSound;
		stateSequence[3]                 = "raisecharge";
		stateScript[3]                   = "onCharge";

		// check fire...
		stateName[4]                     = "CheckFire";
		stateTransitionOnCharged[4]      = "Fire";
		stateTransitionOnNotCharged[4]   = "Ready";
		//stateFire[4]                     = true;
		//stateTarget[4]                   = true;
		stateAllowImageChange[4]         = false;

		// fire!...
		stateName[5]                     = "Fire";
		stateTransitionOnTimeout[5]      = "AfterFire";
		stateTimeoutValue[5]             = 0;
		stateFire[5]                     = true;
		stateFireProjectile[5]           = WpnSR1Projectile;
		stateRecoil[5]                   = NoRecoil;
		stateAllowImageChange[5]         = false;
		//stateEjectShell[5]               = true;
		stateArmThread[5]                = "aimrifle";
		stateSequence[5]                 = "fire";
      stateSound[5]                    = WpnSR1FireSound;
		stateScript[5]                   = "onFire";

		// after fire...
		stateName[8]                     = "AfterFire";
		stateTransitionOnTriggerUp[8]    = "KeepAiming";

		// keep aiming...
		stateName[9]                     = "KeepAiming";
		stateTransitionOnNoAmmo[9]       = "NoAmmo";
		stateTransitionOnTriggerDown[9]  = "Charge";
		stateTransitionOnTimeout[9]      = "Ready";
		stateTransitionOnNotLoaded[9]    = "Disabled";
		stateWaitForTimeout[9]           = false;
		stateTimeoutValue[9]             = 2.00;

		// charge...
		stateName[13]                     = "Charge";
		stateTransitionOnTriggerUp[13]    = "CheckFire";
		//stateTransitionOnNoAmmo[13]       = "NoAmmo";
		stateTarget[13]                   = true;
		stateCharge[13]                   = true;
		stateAllowImageChange[13]         = true;
		stateArmThread[13]                = "aimrifle";
		stateSound[13]                    = WpnSR1ChargeSound;
		stateSequence[13]                 = "charge";
		stateScript[13]                   = "onCharge";

		// no ammo...
		stateName[10]                    = "NoAmmo";
        stateTransitionOnTriggerDown[10] = "DryFire";
		stateTransitionOnAmmo[10]        = "Ready";
		stateSequence[10]                = "lowered";
		stateTimeoutValue[10]            = 0.50;
		stateScript[10]                  = "onNoAmmo";

        // dry fire...
		stateName[11]                    = "DryFire";
		stateTransitionOnTriggerUp[11]   = "NoAmmo";
		stateTransitionOnAmmo[11]        = "Ready";
		stateSound[11]                   = WeaponEmptySound;
		stateSequence[11]                = "idle";

		// disabled...
		stateName[12]                    = "Disabled";
		stateTransitionOnLoaded[12]      = "Ready";
		stateAllowImageChange[12]        = false;
		stateSequence[12]                = "idle";
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnSR1Image::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);
}

function WpnSR1Image::onUnmount(%this, %obj, %slot)
{
   Parent::onUnmount(%this, %obj, %slot);
   %obj.allowSprinting(true);
}

function WpnSR1Image::onReady(%this, %obj, %slot)
{
	//error("onReady");
    %obj.allowSprinting(true);
}

function WpnSR1Image::onCharge(%this, %obj, %slot)
{
	//error("onCharge");
   //%obj.sniperTarget = "";
   %obj.allowSprinting(false);
}

function WpnSR1Image::onFire(%this, %obj, %slot)
{
	//error("onFire");
   %obj.allowSprinting(true);
}

function WpnSR1Image::onNoAmmo(%this, %obj, %slot)
{
	//error("onNoAmmo");
   %obj.allowSprinting(true);
}



