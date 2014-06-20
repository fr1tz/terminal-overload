// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnSG2Image)
{
   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/smg1/image/p1/shape.tp.dae";
   shapeFileFP = "content/xa/notc/core/shapes/sg2/image/p1/shape.fp.dae";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.15 0.1 -0.25";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Hybrid";
   minEnergy = 36;

   projectile = WpnSG2PseudoProjectile;

   casing = WpnSG2ProjectileShell;
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
   item = WpnSG2;
   ammo = WpnSG2Ammo;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Ready";
		stateTransitionOnNoAmmo[0]		   = "NoAmmo";

		// when mounted...
		stateName[1]                     = "Activate";
		stateTransitionOnTimeout[1]      = "Ready";
		stateTimeoutValue[1]             = 0.25;
		stateSequence[1]                 = "idle";
		stateSpinThread[1]               = "SpinUp";

		// ready to fire, just waiting for the trigger...
		stateName[2]                     = "Ready";
		stateTimeoutValue[2]             = 10;
		stateWaitForTimeout[2]           = false;
		stateTransitionOnNoAmmo[2]       = "NoAmmo";
  		stateTransitionOnNotLoaded[2]    = "Disabled";
		stateTransitionOnTriggerDown[2]  = "Fire";
      stateArmThread[2]                = "aimblaster";
		stateSequence[2]                 = "idle";

		stateName[3]                     = "Fire";
		stateTransitionOnTimeout[3]      = "Reload";
		stateTimeoutValue[3]             = 0.320;
		stateFire[3]                     = true;
		stateFireProjectile[3]           = WpnSG2PseudoProjectile;
		stateRecoil[3]                   = "LightRecoil";
		stateAllowImageChange[3]         = false;
		stateEjectShell[3]               = true;
		stateArmThread[3]                = "aimblaster";
		stateSequence[3]                 = "Fire";
		stateSound[3]                    = WpnSG2FireSound;
      stateSoundFlags[3]               = 1;

		stateName[8]                     = "Reload";
		stateTransitionOnTriggerUp[8]    = "Ready";
		stateTimeoutValue[8]             = 0.960;
		stateWaitForTimeout[8]           = true;
		stateAllowImageChange[8]         = false;
		stateSequence[8]                 = "Reload";
		stateSound[8]                    = WpnSG2ReloadSound;

		stateName[4]                     = "KeepAiming";
		stateTransitionOnNoAmmo[4]       = "NoAmmo";
		stateTransitionOnNotLoaded[4]    = "Disabled";
		stateTransitionOnTriggerDown[4]  = "Fire";
		stateTransitionOnTimeout[4]      = "Ready";
		stateWaitForTimeout[4]           = false;
		stateTimeoutValue[4]             = 2.00;

        // no ammo...
		stateName[5]                     = "NoAmmo";
		stateTransitionOnAmmo[5]         = "Ready";
      stateTransitionOnTriggerDown[5]  = "DryFire";
		stateTimeoutValue[5]             = 0.50;

        // dry fire...
		stateName[6]                     = "DryFire";
		stateTransitionOnTriggerUp[6]    = "NoAmmo";
		stateSound[6]                    = WeaponEmptySound;

		// disabled...
		stateName[7]                     = "Disabled";
		stateTransitionOnLoaded[7]       = "Ready";
		stateAllowImageChange[7]         = false;
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnSG2Image::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);
   
   // Set up recoil
   %obj.setImageRecoilEnabled(%slot, true);
   %obj.setImageCurrentRecoil(%slot, 60);
   %obj.setImageMaxRecoil(%slot, 60);
   %obj.setImageRecoilAdd(%slot, 0);
   %obj.setImageRecoilDelta(%slot, -0);
}



