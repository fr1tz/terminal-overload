// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnMG2Image)
{
   // Basic Item properties
   shapeFile = "content/xa/rotc_hack/shapes/minigun.tp.dts";
   shapeFileFP = "content/xa/rotc_hack/shapes/minigun.fp.dts";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   animateOnServer = true;
   useEyeNode = "0";
   eyeOffset = "0.275 -0.25 -0.2";

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;
   correctMuzzleVectorTP = false;
   
   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";

   ammoSource = "Energy";
   minEnergy = 0;

   projectile = WpnMG2Projectile;

   casing = WpnMG2ProjectileShell;
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
   item = WpnMG2;

	//-------------------------------------------------
	// image states...
	//
		// preactivation...
		stateName[0]                     = "Preactivate";
		stateTransitionOnAmmo[0]         = "Activate";
		stateTransitionOnNoAmmo[0]       = "NoAmmo";

		// when mounted...
		stateName[1]                     = "Activate";
		stateTransitionOnTimeout[1]      = "Ready";
		stateTimeoutValue[1]             = 0.5;
		stateSequence[1]                 = "idle";
		stateSpinThread[1]               = "SpinDown";

		// ready to fire, just waiting for the trigger...
		stateName[2]                     = "Ready";
		stateTransitionOnNoAmmo[2]       = "NoAmmo";
		stateTransitionOnNotLoaded[2]    = "Disabled";
		stateTransitionOnTriggerDown[2]  = "Fire";
		stateArmThread[2]                = "holdblaster";
		stateSpinThread[2]               = "Stop";
		stateSequence[2]                 = "idle";

		// charge...
		stateName[3]                     = "Charge";
		stateTransitionOnTriggerUp[3]    = "Cooldown";
		stateTransitionOnTimeout[3]      = "Spin";
		stateTimeoutValue[3]             = 0.5;
		stateAllowImageChange[3]         = false;
		stateArmThread[3]                = "aimblaster";
		stateSound[3]                    = WpnMG2SpinUpSound;
		stateSpinThread[3]               = "SpinUp";

		stateName[9]                     = "Spin";
		stateTransitionOnTriggerUp[9]    = "Cooldown";
		stateTransitionOnTimeout[9]      = "Fire";
		stateTimeoutValue[9]             = 0.1;
		stateAllowImageChange[9]         = false;
		stateArmThread[9]                = "aimblaster";
		stateSound[9]                    = WpnMG2SpinSound;
		stateSpinThread[9]               = "FullSpeed";

		// fire!...
		stateName[4]                     = "Fire";
		stateTransitionOnTimeout[4]      = "Fire";
		stateTransitionOnTriggerUp[4]    = "Cooldown";
		stateTransitionOnNoAmmo[4]       = "Cooldown";
		stateTimeoutValue[4]             = 0.075;
		stateFire[4]                     = true;
		stateAllowImageChange[4]         = false;
		stateEjectShell[4]               = true;
		stateArmThread[4]                = "aimblaster";
		stateSequence[4]                 = "fire";
		stateSequenceRandomFlash[4]      = true;
		stateSound[4]                    = WpnMG2FireSound;
		stateEmitter[4]                  = WpnMG2FireEmitter;
		stateEmitterNode[4]              = "fireparticles";
		stateEmitterTime[4]              = 0.1;
		stateSpinThread[4]               = "FullSpeed";
		stateScript[4]                   = "onFire";

		// cooldown...
		stateName[5]                     = "Cooldown";
		stateTransitionOnTimeout[5]      = "Ready";
		stateTimeoutValue[5]             = 0.5;
		stateAllowImageChange[5]         = false;
		stateEjectShell[5]               = true;
		stateArmThread[5]                = "aimblaster";
		stateSound[5]                    = WpnMG2SpinDownSound;
		stateSpinThread[5]               = "SpinDown";

		// no ammo...
		stateName[6]                     = "NoAmmo";
        	stateTransitionOnTriggerDown[6]  = "DryFire";
		stateTransitionOnAmmo[6]         = "Ready";
		stateTimeoutValue[6]             = 0.50;
		stateSequence[6]                 = "idle";

        	// dry fire...
		stateName[7]                     = "DryFire";
		stateTransitionOnTriggerUp[7]    = "NoAmmo";
		stateSound[7]                    = WeaponEmptySound;

		// disabled...
		stateName[8]                     = "Disabled";
		stateTransitionOnLoaded[8]       = "Ready";
		stateAllowImageChange[8]         = false;
		stateSequence[8]                 = "idle";
	//
	// ...end of image states
	//-------------------------------------------------
};

function WpnMG2Image::getBulletSpread(%this, %obj)
{
   %spread = (%obj.getCameraFov()*%obj.getCameraFov()*100) / (80000*100);
   //echo(%spread);
   return %spread;
   //return 0.015;
}

function WpnMG2Image::onFire(%this, %obj, %slot)
{
	%projectile = %this.projectile;
   %ammo = %this.ammo;
   
	// determine muzzle-point...
	%muzzlePoint = %obj.getMuzzlePoint(%slot);

	// determine initial projectile velocity...
	%muzzleVector = %obj.getMuzzleVector(%slot);

	//
	%p = VectorAdd(%muzzlePoint, %muzzleVector);
	%r = 0.5 * %this.getBulletSpread(%obj);
	for(%i = 0; %i < 3; %i++)
	{
		%rand = getRandom(10)-5;
		if(%rand == 0)
			%newpos[%i] = getWord(%p, %i);
		else
			%newpos[%i] = getWord(%p, %i) + %r / %rand;
	}
	%muzzleVector = VectorSub(%newpos[0] SPC %newpos[1] SPC %newpos[2], %muzzlePoint);
	%muzzleVector = VectorNormalize(%muzzleVector );

	%objectVelocity = %obj.getVelocity();
	%muzzleVelocity = VectorAdd(
		VectorScale(%muzzleVector, %projectile.muzzleVelocity),
		VectorScale(%objectVelocity, %projectile.velInheritFactor));

	// create the projectile object...
	%p = new Projectile() {
		dataBlock       = %projectile;
		teamId          = %obj.teamId;
		initialVelocity = %muzzleVelocity;
		initialPosition = %muzzlePoint;
		sourceObject    = %obj;
		sourceSlot      = %slot;
		client	    = %obj.client;
	};
	MissionCleanup.add(%p);
   copyPalette(%obj, %p);

	%obj.setEnergyLevel(%obj.getEnergyLevel() - %projectile.energyDrain);
   %obj.decInventory(%ammo, 1);

	return %p;
}



