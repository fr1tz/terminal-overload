// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnRaptorImage)
{
   // Basic Item properties
   shapeFile = "library/shape/alux3d/raptor/image/p1/TP_Raptor.DAE";
   shapeFileFP = "library/shape/alux3d/raptor/image/p3/shape.fp.dae";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = false;
   eyeOffset = "-0.0 0.1 -0.375";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Magazine";
   //minEnergy = 0;

   projectile = WpnRaptorProjectile;

   casing = WpnRaptorProjectileShell;
   shellExitDir        = "1.0 0.3 1.0";
   shellExitOffset     = "0.15 -0.56 -0.1";
   shellExitVariance   = 15.0;
   shellVelocity       = 3.0;

   // Weapon lights up while firing
   lightType = "NoLight";
   lightColor = "0 1 0.952756 1";
   lightRadius = "4";
   lightDuration = "100";
   lightBrightness = 2;

   // Shake camera while firing.
   shakeCamera = false;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "15.0 15.0 15.0";

   useRemainderDT = false;
   maxConcurrentSounds = 1;
   
   // Script fields
   reloadImage = WpnRaptorReloadImage;
   item = WpnRaptor;
   ammo = WpnRaptorAmmo;
   //clip = WpnRaptorClip;
   magazineCapacity = 30;

   stateName[0]                     = "Preactivate";
   stateTransitionGeneric3In[0]     = "Ready";
   stateTransitionGeneric3Out[0]    = "Activate";

   stateName[1]                     = "Activate";
   stateTransitionGeneric0In[1]     = "SprintEnter";
   stateTransitionOnTimeout[1]      = "Ready";
   stateTimeoutValue[1]             = 0.5;
   stateSequence[1]                 = "switch_in";
   stateSound[1]                    = WpnRaptorSwitchinSound;

   stateName[2]                     = "Ready";
   stateTransitionGeneric0In[2]     = "SprintEnter";
   stateTransitionOnMotion[2]       = "ReadyMotion";
   //stateTransitionOnTimeout[2]      = "ReadyFidget";
   stateTimeoutValue[2]             = 10;
   stateWaitForTimeout[2]           = false;
   stateTransitionOnNoAmmo[2]       = "NoAmmo";
   stateTransitionOnTriggerDown[2]  = "Fire";
   stateSequence[2]                 = "ready";
   
   stateName[4]                     = "ReadyMotion";
   stateTransitionGeneric0In[4]     = "SprintEnter";
   stateTransitionOnNoMotion[4]     = "Ready";
   stateTimeoutValue[4]             = 0.15;
   stateWaitForTimeout[4]           = false;
   stateSequenceTransitionIn[4]     = true;
   stateSequenceTransitionOut[4]    = true;
   stateTransitionOnNoAmmo[4]       = "NoAmmo";
   stateTransitionOnTriggerDown[4]  = "Fire";
   stateSequence[4]                 = "ready_moving";

   stateName[3]                     = "ReadyFidget";
   stateTransitionGeneric0In[3]     = "SprintEnter";
   stateTransitionOnMotion[3]       = "ReadyMotion";
   stateTransitionOnTimeout[3]      = "Ready";
   stateTimeoutValue[3]             = 6;
   stateWaitForTimeout[3]           = false;
   stateTransitionOnNoAmmo[3]       = "NoAmmo";
   stateTransitionOnTriggerDown[3]  = "Fire";
   stateSequence[3]                 = "idle_fidget1";
   stateSound[3]                    = WpnRaptorIdleSound;

   stateName[5]                     = "Fire";
   stateTransitionOnTriggerUp[5]    = "Ready";
   stateTransitionOnNoAmmo[5]       = "LockedSound";
   stateTransitionGeneric0In[5]     = "SprintEnter";
   stateTransitionOnTimeout[5]      = "Fire";
   stateTimeoutValue[5]             = 0.096;
   stateFire[5]                     = true;
   stateFireProjectile[5]           = WpnRaptorProjectile;
   stateRecoil[5]                   = "LightRecoil";
   stateAllowImageChange[5]         = false;
   stateSequence[5]                 = "fire";
   stateScaleAnimation[5]           = false;
   stateSequenceNeverTransition[5]  = true;
   stateSequenceRandomFlash[5]      = true;        // use muzzle flash sequence
   //stateScript[5]                   = "onFire";
   stateSound[5]                    = WpnRaptorFireSound;
   //stateEmitter[5]                  = WpnRaptorFireSmokeEmitter;
   //stateEmitterTime[5]              = 0.025;
   stateEjectShell[5]               = true;

   stateName[12]                    = "LockedSound";
   stateTransitionOnTimeout[12]     = "Locked";
   stateTimeoutValue[12]            = 0.032;
   stateSound[12]                   = WpnRaptorReleaseMagazineSound;
   
   stateName[13]                    = "Locked";
   stateTransitionOnMotion[13]      = "LockedMotion";
   stateTimeoutValue[13]            = 10;
   stateWaitForTimeout[13]          = false;
   stateSequence[13]                = "empty";
   stateTransitionOnTriggerUp[13]   = "CheckReload";
   
   stateName[14]                    = "LockedMotion";
   stateTransitionOnNoMotion[14]    = "Locked";
   stateTimeoutValue[14]            = 0.15;
   stateWaitForTimeout[14]          = false;
   stateSequence[14]                = "empty_moving";
   stateSequenceTransitionIn[14]    = true;
   stateSequenceTransitionOut[14]   = true;
   stateTransitionOnTriggerUp[14]   = "CheckReload";
   
   stateName[15]                    = "CheckReload";
   stateTransitionOnTimeout[15]     = "NoAmmo";
   stateTimeoutValue[15]            = 0.032;
   stateScript[15]                  = "onMagazineEmpty";

   stateName[6]                     = "NoAmmo";
   stateTransitionGeneric0In[6]     = "SprintEnter";
   stateTransitionOnMotion[6]       = "NoAmmoMotion";
   stateTransitionOnAmmo[6]         = "Ready";
   stateTimeoutValue[6]             = 10;
   stateWaitForTimeout[6]           = false;
   stateSequence[6]                 = "empty";
   stateTransitionOnTriggerDown[6]  = "DryFire";

   stateName[7]                     = "NoAmmoMotion";
   stateTransitionGeneric0In[7]     = "SprintEnter";
   stateTransitionOnNoMotion[7]     = "NoAmmo";
   stateTimeoutValue[7]             = 0.15;
   stateWaitForTimeout[7]           = false;
   stateSequenceTransitionIn[7]     = true;
   stateSequenceTransitionOut[7]    = true;
   stateTransitionOnTriggerDown[7]  = "DryFire";
   stateTransitionOnAmmo[7]         = "Ready";
   stateSequence[7]                 = "empty_moving";

   stateName[8]                     = "DryFire";
   stateTransitionGeneric0In[8]     = "SprintEnter";
   stateWaitForTimeout[8]           = false;
   stateTimeoutValue[8]             = 0.7;
   stateTransitionOnTimeout[8]      = "NoAmmo";
   stateScript[8]                   = "onDryFire";
   stateSound[8]                    = WpnRaptorDryFireSound;
};

function WpnRaptorImage::onMount(%this, %obj, %slot)
{
   Parent::onMount(%this, %obj, %slot);

   // Set up inaccuracy.
   %obj.setImageInaccuracy(%slot, "radiusmin", 2.0);
   %obj.setImageInaccuracy(%slot, "radiusmax", 20.0);
   %obj.setImageInaccuracy(%slot, "a1", 1.0);
   %obj.setImageInaccuracy(%slot, "a2", 1.0);
   %obj.setImageInaccuracy(%slot, "b1", 0.95);
   %obj.setImageInaccuracy(%slot, "b2", 0.0);
   %obj.setImageInaccuracy(%slot, "c", 10.0);
   %obj.setImageInaccuracy(%slot, "d", 0.3);
   %obj.setImageInaccuracy(%slot, "f1", 1.00);
   %obj.setImageInaccuracy(%slot, "f2", 0.80);
   %obj.setImageInaccuracy(%slot, "enabled", true);

   // Set up recoil.
   %obj.setImageRecoilEnabled(%slot, true);
   %obj.setImageCurrentRecoil(%slot, 7);
   %obj.setImageMaxRecoil(%slot, 7);
   %obj.setImageRecoilAdd(%slot, 0);
   %obj.setImageRecoilDelta(%slot, -0);
}



