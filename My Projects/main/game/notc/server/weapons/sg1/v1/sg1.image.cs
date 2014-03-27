// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnSG1Image)
{
   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/blaster.tp.dts";
   shapeFileFP = "content/xa/rotc_hack/shapes/blaster.fp.dts";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.3 -0.025 -0.15";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Hybrid";
   minEnergy = 16;

   projectile = WpnSG1Projectile;

   casing = WpnSG1ProjectileShell;
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
   item = WpnSG1;
   ammo = WpnSG1Ammo;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Ready";
		stateTransitionOnNoAmmo[0]       = "NoAmmo";

		// when mounted...
		stateName[1]                     = "Activate";
		stateTransitionOnTimeout[1]      = "Ready";
		stateTimeoutValue[1]             = 0.5;
		stateSequence[1]                 = "activate";
		stateSpinThread[1]               = "SpinDown";

		// ready to fire, just waiting for the trigger...
		stateName[2]                     = "Ready";
		stateTransitionOnNoAmmo[2]       = "NoAmmo";
		stateTransitionOnNotLoaded[2]    = "Disabled";
		stateTransitionOnTriggerDown[2]  = "Fire";
		stateArmThread[2]                = "holdblaster";
		stateSpinThread[2]               = "Stop";
		//stateSequence[2]                 = "idle";

		// fire!...
		stateName[3]                     = "Fire";
		stateTransitionOnTimeout[3]      = "AfterFire";
		stateTimeoutValue[3]             = 0.8;
		stateFire[3]                     = true;
		stateFireProjectile[3]           = WpnSG1Projectile;
		stateRecoil[3]                   = MediumRecoil;
		stateAllowImageChange[3]         = false;
		stateEjectShell[3]               = false;
		stateArmThread[3]                = "aimblaster";
		stateSequence[3]                 = "fire";
		stateSound[3]                    = WpnSG1FireSound;
		//stateEmitter[3]                  = RedBlaster4FireEmitter;
		stateEmitterNode[3]              = "fireparticles";
		stateEmitterTime[3]              = 0.1;
		stateSpinThread[3]               = "Stop";

		// after fire...
		stateName[4]                     = "AfterFire";
		stateTransitionOnTriggerUp[4]    = "KeepAiming";

		// keep aiming...
		stateName[5]                     = "KeepAiming";
		stateTransitionOnNoAmmo[5]       = "NoAmmo";
		stateTransitionOnTriggerDown[5]  = "Fire";
		stateTransitionOnTimeout[5]      = "Ready";
		stateTransitionOnNotLoaded[5]    = "Disabled";
		stateWaitForTimeout[5]           = false;
		stateTimeoutValue[5]             = 2.00;

		// no ammo...
		stateName[6]                     = "NoAmmo";
        stateTransitionOnTriggerDown[6]  = "DryFire";
		stateTransitionOnAmmo[6]         = "Ready";
		stateTimeoutValue[6]             = 0.50;
		//stateSequence[6]                 = "idle";

        // dry fire...
		stateName[7]                     = "DryFire";
		stateTransitionOnTriggerUp[7]    = "NoAmmo";
		stateSound[7]                    = WeaponEmptySound;
		//stateSequence[7]                 = "idle";

		// disabled...
		stateName[8]                     = "Disabled";
		stateTransitionOnLoaded[8]       = "Ready";
		stateAllowImageChange[8]         = false;
		//stateSequence[8]                 = "idle";
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnSG1Image::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);

   // Set up recoil
   %obj.setImageRecoilEnabled(%slot, true);
   %obj.setImageCurrentRecoil(%slot, 60);
   %obj.setImageMaxRecoil(%slot, 60);
   %obj.setImageRecoilAdd(%slot, 0);
   %obj.setImageRecoilDelta(%slot, -0);
}



