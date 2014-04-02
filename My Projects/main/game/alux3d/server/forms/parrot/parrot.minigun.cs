// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// fire particle emitter

datablock ParticleData(WpnParrotMinigunFireEmitter_Particles)
{
	dragCoefficient       = 1;
	gravityCoefficient    = 0.0;
	windCoefficient       = 0.0;
	inheritedVelFactor    = 0.5;
	constantAcceleration  = 0.0;
	lifetimeMS            = 50;
	lifetimeVarianceMS    = 0;
	textureName           = "content/xa/rotc/p.5.4/textures/rotc/smoke_particle";
	colors[0]             = "1.0 1.0 1.0 1.0";
	colors[1]             = "1.0 1.0 1.0 1.0";
	colors[2]             = "1.0 1.0 1.0 0.0";
	sizes[0]              = 0.3;
	sizes[1]              = 0.3;
	sizes[2]              = 0.0;
	times[0]              = 0.0;
	times[1]              = 0.5;
	times[2]              = 1.0;

};

datablock ParticleEmitterData(WpnParrotMinigunFireEmitter)
{
	ejectionPeriodMS = 10;
	periodVarianceMS = 0;
	ejectionVelocity = 20.0;
	velocityVariance = 0.2;
	ejectionOffset   = 0;
	thetaMin         = 0;
	thetaMax         = 0;
	phiReferenceVel  = 0;
	phiVariance      = 360;
	overrideAdvances = false;
	orientParticles  = false;
	lifetimeMS       = 0;
	particles        = "WpnParrotMinigunFireEmitter_Particles";
};

//------------------------------------------------------------------------------
// weapon image which does all the work...
// (images do not normally exist in the world, they can only
// be mounted on ShapeBase objects)

datablock ShapeBaseImageData(WpnParrotMinigunImage)
{
	// add the WeaponImage namespace as a parent
	//className = WeaponImage;

	// basic item properties
	shapeFile = "share/shapes/alux/nothing.dts";
	emap = true;

	// mount point & mount offset...
	mountPoint  = 0;
	offset      = "0 0 0";
	rotation    = "0 0 0";
	eyeOffset   = "0.0 -0.25 -0.2";
	eyeRotation = "0 0 0";

	// Adjust firing vector to eye's LOS point?
	correctMuzzleVector = true;

	usesEnergy = true;
	minEnergy = 10;

	projectile = WpnParrotMinigunProjectile;

	// script fields...
	armThread = "holdblaster";  // armThread to use when holding this weapon
	
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
		stateSound[3]                    = WpnParrotMinigunSpinUpSound;
		stateSpinThread[3]               = "SpinUp";

		stateName[9]                     = "Spin";
		stateTransitionOnTriggerUp[9]    = "Cooldown";
		stateTransitionOnTimeout[9]      = "Fire";
		stateTimeoutValue[9]             = 0.1;
		stateAllowImageChange[9]         = false;
		stateArmThread[9]                = "aimblaster";
		stateSound[9]                    = WpnParrotMinigunSpinSound;
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
		stateSound[4]                    = WpnParrotMinigunFireSound;
		stateEmitter[4]                  = WpnParrotMinigunFireEmitter;
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
		stateSound[5]                    = WpnParrotMinigunSpinDownSound;
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

function WpnParrotMinigunImage::getBulletSpread(%this, %obj)
{
   %maxf = 110;
   %f = %obj.getCameraFOV();
   %s = ((%maxf*%maxf)-(%f*%f))/(%maxf*%maxf);
   return 0.07 - 0.07*%s;
}

function WpnParrotMinigunImage::onFire(%this, %obj, %slot)
{
	%projectile = %this.projectile;

	%muzzlePoint = %obj.getMuzzlePoint(%slot);
	%muzzleVector = %obj.getMuzzleVector(%slot);
	%muzzleTransform = createOrientFromDir(VectorNormalize(%muzzleVector));

   %spread = %this.getBulletSpread(%obj);
   %randX = %spread * ((getRandom(1000)-500)/1000);
   %randZ = %spread * ((getRandom(1000)-500)/1000);
	%vec = %randX SPC "1" SPC %randZ;

	%muzzleVector = VectorNormalize(MatrixMulVector(%muzzleTransform, %vec));

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

	%obj.setEnergyLevel(%obj.getEnergyLevel() - %projectile.energyDrain);
 
	%target = %obj.getImageTarget(%slot);
	if(isObject(%target))
		%p.setTarget(%target);
        
	return %p;
}

