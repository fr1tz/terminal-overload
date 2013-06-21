// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnBulldogImage)
{
   // Basic Item properties
   shapeFile = "art/shapes/weapons/Lurker/TP_Lurker.DAE";
   shapeFileFP = "art/shapes/weapons/Lurker/FP_Lurker.DAE";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   useEyeNode = true;
   animateOnServer = true;

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";
   className = "WeaponImage";

   ammoSource = "Magazine";
   //minEnergy = 0;

   projectile = WpnBulldogProjectile;

   casing = WpnBulldogProjectileShell;
   shellExitDir        = "1.0 0.3 1.0";
   shellExitOffset     = "0.15 -0.56 -0.1";
   shellExitVariance   = 15.0;
   shellVelocity       = 3.0;

   // Weapon lights up while firing
   lightType = "WeaponFireLight";
   lightColor = "0.992126 0.968504 0.708661 1";
   lightRadius = "4";
   lightDuration = "100";
   lightBrightness = 2;

   // Shake camera while firing.
   shakeCamera = false;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "15.0 15.0 15.0";

   useRemainderDT = false;
   
   // Script fields
   reloadImage = WpnBulldogReloadImage;
   item = WpnBulldog;
   ammo = WpnBulldogAmmo;
   clip = WpnBulldogClip;

   // Initial start up state
   stateName[0]                     = "Preactivate";
   stateTransitionGeneric3In[0]     = "Ready";
   stateTransitionGeneric3Out[0]    = "Activate";

   // Activating the gun.  Called when the weapon is first
   // mounted and there is ammo.
   stateName[1]                     = "Activate";
   stateTransitionGeneric0In[1]     = "SprintEnter";
   stateTransitionOnTimeout[1]      = "Ready";
   stateTimeoutValue[1]             = 0.5;
   stateSequence[1]                 = "switch_in";
   stateSound[1]                    = WpnBulldogSwitchinSound;

   // Ready to fire, just waiting for the trigger
   stateName[2]                     = "Ready";
   stateTransitionGeneric0In[2]     = "SprintEnter";
   stateTransitionOnMotion[2]       = "ReadyMotion";
   //stateTransitionOnTimeout[2]      = "ReadyFidget";
   stateTimeoutValue[2]             = 10;
   stateWaitForTimeout[2]           = false;
   stateScaleAnimation[2]           = false;
   stateScaleAnimationFP[2]         = false;
   stateTransitionOnNoAmmo[2]       = "NoAmmo";
   stateTransitionOnTriggerDown[2]  = "Fire";
   stateSequence[2]                 = "idle";

   // Same as Ready state but plays a fidget sequence
   stateName[3]                     = "ReadyFidget";
   stateTransitionGeneric0In[3]     = "SprintEnter";
   stateTransitionOnMotion[3]       = "ReadyMotion";
   stateTransitionOnTimeout[3]      = "Ready";
   stateTimeoutValue[3]             = 6;
   stateWaitForTimeout[3]           = false;
   stateTransitionOnNoAmmo[3]       = "NoAmmo";
   stateTransitionOnTriggerDown[3]  = "Fire";
   stateSequence[3]                 = "idle_fidget1";
   stateSound[3]                    = WpnBulldogIdleSound;

   // Ready to fire with player moving
   stateName[4]                     = "ReadyMotion";
   stateTransitionGeneric0In[4]     = "SprintEnter";
   stateTransitionOnNoMotion[4]     = "Ready";
   stateWaitForTimeout[4]           = false;
   stateScaleAnimation[4]           = false;
   stateScaleAnimationFP[4]         = false;
   stateSequenceTransitionIn[4]     = true;
   stateSequenceTransitionOut[4]    = true;
   stateTransitionOnNoAmmo[4]       = "NoAmmo";
   stateTransitionOnTriggerDown[4]  = "Fire";
   stateSequence[4]                 = "run";

   // Fire the weapon.
   stateName[5]                     = "Fire";
   stateTransitionOnTimeout[5]      = "Pump";
   stateTimeoutValue[5]             = 0.8;
   stateFire[5]                     = true;
   stateFireProjectile[5]           = WpnBulldogProjectile;
   stateRecoil[5]                   = "LightRecoil";
   stateAllowImageChange[5]         = false;
   stateSequence[5]                 = "fire_alt";
   stateScaleAnimation[5]           = false;
   stateScaleAnimationFP[5]         = false;
   stateSequenceNeverTransition[5]  = true;
   stateSequenceRandomFlash[5]      = true;        // use muzzle flash sequence
   //stateScript[5]                   = "onFire";
   stateSound[5]                    = WpnBulldogFireSoundList;
   stateEmitter[5]                  = GunFireSmokeEmitter;
   stateEmitterTime[5]              = 0.025;

   // reload
	stateName[12]                     = "Pump";
	stateTransitionOnTimeout[12]      = "Ready";
	stateTimeoutValue[12]             = 0.8;
	stateAllowImageChange[12]         = false;
	stateEjectShell[12]               = true;
	stateSound[12]                    = WpnBulldogPumpSound;

   // No ammo in the weapon, just idle until something
   // shows up. Play the dry fire sound if the trigger is
   // pulled.
   stateName[6]                     = "NoAmmo";
   stateTransitionGeneric0In[6]     = "SprintEnter";
   stateTransitionOnMotion[6]       = "NoAmmoMotion";
   stateTransitionOnAmmo[6]         = "Ready";
   stateTimeoutValue[6]             = 0.1;   // Slight pause to allow script to run when trigger is still held down from Fire state
   stateScript[6]                   = "onMagazineEmpty";
   stateSequence[6]                 = "idle";
   stateScaleAnimation[6]           = false;
   stateScaleAnimationFP[6]         = false;
   stateTransitionOnTriggerDown[6]  = "DryFire";

   stateName[7]                     = "NoAmmoMotion";
   stateTransitionGeneric0In[7]     = "SprintEnter";
   stateTransitionOnNoMotion[7]     = "NoAmmo";
   stateWaitForTimeout[7]           = false;
   stateScaleAnimation[7]           = false;
   stateScaleAnimationFP[7]         = false;
   stateSequenceTransitionIn[7]     = true;
   stateSequenceTransitionOut[7]    = true;
   stateTransitionOnTriggerDown[7]  = "DryFire";
   stateTransitionOnAmmo[7]         = "Ready";
   stateSequence[7]                 = "run";

   // No ammo dry fire
   stateName[8]                     = "DryFire";
   stateTransitionGeneric0In[8]     = "SprintEnter";
   stateTransitionOnAmmo[8]         = "ReloadClip";
   stateWaitForTimeout[8]           = "0";
   stateTimeoutValue[8]             = 0.7;
   stateTransitionOnTimeout[8]      = "NoAmmo";
   stateScript[8]                   = "onDryFire";
   stateSound[8]                    = WpnBulldogDryFireSound;

   // Start Sprinting
   stateName[9]                    = "SprintEnter";
   stateTransitionGeneric0Out[9]   = "SprintExit";
   stateTransitionOnTimeout[9]     = "Sprinting";
   stateWaitForTimeout[9]          = false;
   stateTimeoutValue[9]            = 0.5;
   stateWaitForTimeout[9]          = false;
   stateScaleAnimation[9]          = false;
   stateScaleAnimationFP[9]        = false;
   stateSequenceTransitionIn[9]    = true;
   stateSequenceTransitionOut[9]   = true;
   stateAllowImageChange[9]        = false;
   stateSequence[9]                = "sprint";

   // Sprinting
   stateName[10]                    = "Sprinting";
   stateTransitionGeneric0Out[10]   = "SprintExit";
   stateWaitForTimeout[10]          = false;
   stateScaleAnimation[10]          = false;
   stateScaleAnimationFP[10]        = false;
   stateSequenceTransitionIn[10]    = true;
   stateSequenceTransitionOut[10]   = true;
   stateAllowImageChange[10]        = false;
   stateSequence[10]                = "sprint";

   // Stop Sprinting
   stateName[11]                    = "SprintExit";
   stateTransitionGeneric0In[11]    = "SprintEnter";
   stateTransitionOnTimeout[11]     = "Ready";
   stateWaitForTimeout[11]          = false;
   stateTimeoutValue[11]            = 0.5;
   stateSequenceTransitionIn[11]    = true;
   stateSequenceTransitionOut[11]   = true;
   stateAllowImageChange[11]        = false;
   stateSequence[11]                = "sprint";
};

function WpnBulldogImage::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);

   // Set up inaccuracy
   %obj.setImageInaccuracy(%slot, "radiusmin", 0.30);
   %obj.setImageInaccuracy(%slot, "radiusmax", 20.0);
   %obj.setImageInaccuracy(%slot, "a1", 1.0);
   %obj.setImageInaccuracy(%slot, "a2", 1.0);
   %obj.setImageInaccuracy(%slot, "b1", 0.96);
   %obj.setImageInaccuracy(%slot, "b2", 0.0);
   %obj.setImageInaccuracy(%slot, "c", 10.0);
   %obj.setImageInaccuracy(%slot, "d", 0.20);
   %obj.setImageInaccuracy(%slot, "f1", 1.00);
   %obj.setImageInaccuracy(%slot, "f2", 0.00);
   %obj.setImageInaccuracy(%slot, "enabled", true);

   // Set up recoil
   %obj.setImageRecoilEnabled(%slot, true);
   %obj.setImageCurrentRecoil(%slot, 75);
   %obj.setImageMaxRecoil(%slot, 75);
   %obj.setImageRecoilAdd(%slot, 0);
   %obj.setImageRecoilDelta(%slot, -0);
}



