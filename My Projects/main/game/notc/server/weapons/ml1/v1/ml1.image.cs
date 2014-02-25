// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnML1Image)
{
   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/repelgun.tp.dts";
   shapeFileFP = "content/xa/rotc_hack/shapes/repelgun.fp.dts";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.25 -0.4 -0.2";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Energy";
   minEnergy = 10;

   projectile = WpnML1Projectile;

   casing = WpnML1ProjectileShell;
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
   item = WpnML1;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Ready";
		stateTransitionOnNoAmmo[0]		 = "NoAmmo";

		// when mounted...
		stateName[1]                     = "Activate";
		stateTransitionOnTimeout[1]      = "Ready";
		stateTimeoutValue[1]             = 0.5;
		stateSpinThread[1]               = "Stop";
		stateSequence[1]                 = "Activate";

		// ready to fire, just waiting for the trigger...
		stateName[2]                     = "Ready";
		stateTransitionOnNoAmmo[2]       = "NoAmmo";
  		stateTransitionOnNotLoaded[2]    = "Disabled";
		stateTransitionOnTriggerDown[2]  = "Fire1";
        stateArmThread[2]                = "holdrifle";
		stateSpinThread[2]               = "Stop";

		stateName[3]                     = "Fire1";
		stateTransitionOnTimeout[3]      = "Fire2";
		stateTransitionOnTriggerUp[3]    = "Cooldown";
		stateTransitionOnNoAmmo[3]       = "Cooldown";
		stateTimeoutValue[3]             = 0.17;
		stateSpinThread[3]               = "FullSpeed";
		stateFire[3]                     = true;
		//stateFireProjectile[3]           = RedWpnML1Projectile;
		stateAllowImageChange[3]         = false;
		stateArmThread[3]                = "aimrifle";
		stateSequence[3]                 = "Fire";
		stateSound[3]                    = WpnML1FireSound;
		stateScript[3]                   = "onFire";

		stateName[4]                     = "Fire2";
		stateTransitionOnTimeout[4]      = "Fire3";
		stateTransitionOnTriggerUp[4]    = "Cooldown";
		stateTransitionOnNoAmmo[4]       = "Cooldown";
		stateTimeoutValue[4]             = 0.17;
		//stateFireProjectile[4]           = RedWpnML1Projectile;
		stateAllowImageChange[4]         = false;
		stateSequence[4]                 = "Fire";
		stateSound[4]                    = WpnML1FireSound;
		stateScript[4]                   = "onFire";

		stateName[5]                     = "Fire3";
		stateTransitionOnTimeout[5]      = "Fire4";
		stateTransitionOnTriggerUp[5]    = "Cooldown";
		stateTransitionOnNoAmmo[5]       = "Cooldown";
		stateTimeoutValue[5]             = 0.17;
		stateSpinThread[5]               = "FullSpeed";
		//stateFireProjectile[5]           = RedWpnML1Projectile;
		stateAllowImageChange[5]         = false;
		stateSequence[5]                 = "Fire";
		stateSound[5]                    = WpnML1FireSound;
		stateScript[5]                   = "onFire";

		stateName[6]                     = "Fire4";
		stateTransitionOnTimeout[6]      = "Cooldown";
		stateTransitionOnNoAmmo[6]       = "Cooldown";
		stateTimeoutValue[6]             = 0.17;
		stateSpinThread[6]               = "FullSpeed";
		//stateFireProjectile[6]           = RedWpnML1Projectile;
		stateAllowImageChange[6]         = false;
		stateSequence[6]                 = "Fire";
		stateSound[6]                    = WpnML1FireSound;
		stateScript[6]                   = "onFire";

		stateName[7]                     = "Cooldown";
		stateTransitionOnTimeout[7]      = "KeepAiming";
		stateTimeoutValue[7]             = 1.0;
		stateSpinThread[7]               = "SpinDown";
		stateArmThread[7]                = "aimrifle";

		stateName[8]                     = "KeepAiming";
		stateTransitionOnNoAmmo[8]       = "NoAmmo";
		stateTransitionOnNotLoaded[8]    = "Disabled";
		stateTransitionOnTriggerDown[8]  = "Fire1";
		stateTransitionOnTimeout[8]      = "Ready";
		stateWaitForTimeout[8]           = false;
		stateTimeoutValue[8]             = 2.00;
		stateSpinThread[8]               = "Stop";

        // no ammo...
		stateName[9]                     = "NoAmmo";
		stateTransitionOnAmmo[9]         = "Ready";
        stateTransitionOnTriggerDown[9]  = "DryFire";
		stateTimeoutValue[9]             = 0.50;
		stateSequence[9]                 = "NoAmmo";

        // dry fire...
		stateName[10]                    = "DryFire";
		stateTransitionOnTriggerUp[10]   = "NoAmmo";
		stateSound[10]                   = WeaponEmptySound;

		// disabled...
		stateName[11]                    = "Disabled";
		stateTransitionOnLoaded[11]      = "Ready";
		stateAllowImageChange[11]        = false;
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnML1Image::onFire(%this, %obj, %slot)
{
	%projectile = WpnML1Projectile;

	// determine muzzle-point...
	%muzzlePoint = %obj.getMuzzlePoint(%slot);

	// determine initial projectile velocity...
	%muzzleVector = %obj.getMuzzleVector(%slot);

	%objectVelocity = %obj.getVelocity();
	%muzzleVelocity = VectorAdd(
		VectorScale(%muzzleVector, %projectile.muzzleVelocity),
		VectorScale(%objectVelocity, %projectile.velInheritFactor));

	%p = WpnML1_spawnProjectile(%projectile, %obj, %slot, %muzzlePoint, %muzzleVelocity);
	MissionCleanup.add(%p);

	//%obj.setEnergyLevel(%obj.getEnergyLevel() - %projectile.energyDrain);
	%obj.decGrenadeAmmo(0.25);

	return %p;
}

