// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnSMG2Image)
{
   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/sg1/image/p2/shape.tp.dae";
   shapeFileFP = "content/xa/notc/core/shapes/sg1/image/p1/shape.fp.dae";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.1 -0.1 -0.2";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Energy";
   minEnergy = 0;

   projectile = WpnSMG2Projectile;

   casing = WpnSMG2ProjectileShell;
   shellExitDir        = "1.0 0.3 1.0";
   shellExitOffset     = "0.15 -0.56 -0.1";
   shellExitVariance   = 15.0;
   shellVelocity       = 3.0;

   // Weapon lights up while firing
   lightType = "WeaponFireLight";
   lightColor = "1 1 1 1";
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
   reloadImage = WpnSMG2ReloadImage;
   item = WpnSMG2;
   ammo = WpnSMG2Ammo;
   //clip = WpnSMG2Clip;
   magazineCapacity = 30;
   
	//-------------------------------------------------
	// image states...
	//
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Ready";
		stateTransitionOnNoAmmo[0]		   = "NoAmmo";

      stateName[1]                     = "Activate";
      stateArmThread[1]                = "holdblaster";
      stateTransitionOnTimeout[1]      = "Ready";
      stateTimeoutValue[1]             = 0.5;
      stateSequence[1]                 = "idle";

      stateName[2]                     = "Ready";
      stateArmThread[2]                = "holdblaster";
      //stateTransitionOnTimeout[2]      = "ReadyFidget";
      stateTimeoutValue[2]             = 10;
      stateWaitForTimeout[2]           = false;
      stateTransitionOnNoAmmo[2]       = "NoAmmo";
      stateTransitionOnTriggerDown[2]  = "Fire";
      stateSequence[2]                 = "idle";

      stateName[5]                     = "Fire";
		stateArmThread[5]                = "aimarmcannon";
      stateTransitionOnTriggerUp[5]    = "KeepAiming";
      stateTransitionOnNoAmmo[5]       = "NoAmmo";
      stateTransitionOnTimeout[5]      = "Fire";
      stateTimeoutValue[5]             = 0.064;
      stateFire[5]                     = true;
      stateFireProjectile[5]           = WpnSMG2Projectile;
      stateRecoil[5]                   = "LightRecoil";
      stateAllowImageChange[5]         = false;
      stateSequence[5]                 = "fire";
      stateScaleAnimation[5]           = true;
      stateSequenceNeverTransition[5]  = true;
      stateSequenceRandomFlash[5]      = false;        // use muzzle flash sequence
      stateSound[5]                    = WpnSMG2FireSound;
      stateSoundFlags[5]               = 0;
      //stateScript[5]                 = "onFire";
      //stateEmitter[5]                = WpnSMG2FireSmokeEmitter;
      //stateEmitterTime[5]            = 0.025;
      stateEjectShell[5]               = false;
   
		stateName[7]                     = "KeepAiming";
		stateTransitionOnNoAmmo[7]       = "NoAmmo";
		stateTransitionOnNotLoaded[7]    = "Disabled";
		stateTransitionOnTriggerDown[7]  = "Fire";
		stateTransitionOnTimeout[7]      = "Ready";
		stateWaitForTimeout[7]           = false;
		stateTimeoutValue[7]             = 1.00;

      stateName[6]                     = "NoAmmo";
      stateTransitionOnAmmo[6]         = "Ready";
      stateTimeoutValue[6]             = 10;
      stateWaitForTimeout[6]           = false;
      stateSequence[6]                 = "empty";
      stateTransitionOnTriggerDown[6]  = "DryFire";

      stateName[8]                     = "DryFire";
      stateWaitForTimeout[8]           = false;
      stateTimeoutValue[8]             = 0.7;
      stateTransitionOnTimeout[8]      = "NoAmmo";
      stateScript[8]                   = "onDryFire";
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnSMG2Image::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);

   // Set up inaccuracy.
   %obj.setImageInaccuracy(%slot, "radiusmin", 5.0);
   %obj.setImageInaccuracy(%slot, "radiusmax", 5.0);
   %obj.setImageInaccuracy(%slot, "a1", 0.0);
   %obj.setImageInaccuracy(%slot, "a2", 0.0);
   %obj.setImageInaccuracy(%slot, "b1", 0.90);
   %obj.setImageInaccuracy(%slot, "b2", 0.0);
   %obj.setImageInaccuracy(%slot, "c", 20.0);
   %obj.setImageInaccuracy(%slot, "d", 0.0);
   %obj.setImageInaccuracy(%slot, "f1", 1.00);
   %obj.setImageInaccuracy(%slot, "f2", 2.50);
   %obj.setImageInaccuracy(%slot, "enabled", true);

   // Set up recoil.
   %obj.setImageRecoilEnabled(%slot, true);
   %obj.setImageCurrentRecoil(%slot, 7);
   %obj.setImageMaxRecoil(%slot, 7);
   %obj.setImageRecoilAdd(%slot, 0);
   %obj.setImageRecoilDelta(%slot, -0);
}



