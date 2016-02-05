// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock resoPlayerData(FrmAlphaDisc)
{
   renderFirstPerson = false;

   computeCRC = false;

   // Third person shape
   shapeFile = "content/reso/shapes/alphadisc/p1/shape.dae";
   cameraMaxDist = 3;
   allowImageStateAnimation = true;

   // First person arms
   imageAnimPrefixFP = "soldier";
   //shapeNameFP[0] = "content/o/torque3d/3.0/shapes/actors/Soldier/FP/FP_SoldierArms.DAE";

   canObserve = 1;
   cmdCategory = "Clients";

   cameraDefaultFov = "80";
   cameraMinFov = "1";
   cameraMaxFov = "180";

   //debrisShapeName = "content/o/torque3d/3.0/shapes/actors/common/debris_player.dts";
   debris = PlayerDebris;

   throwForce = 30;

   minLookAngle = "-1.5";
   maxLookAngle = "1.5";
   maxFreelookAngle = 3.0;

   mass = 90;
   drag = 0.0;
   maxdrag = 0;
   density = 10;
   maxDamage = 50;
   maxEnergy[0] = ($Server::RESO::Mutator::AS ? 100 : 9999999999);
   maxEnergy[1] = ($Server::RESO::Mutator::AM ? 100 : 9999999999);
   maxEnergy[2] = 100;
   damageBuffer = 25;
   energyPerDamagePoint = 75;

	repairRate = 0.8;
	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.15;
	rechargeRate[0] = ($Server::RESO::Mutator::AS ? 0.4 : 9999999999);
	rechargeRate[1] = ($Server::RESO::Mutator::AM ? 0.4 : 9999999999);
	rechargeRate[2] = 0.4;

   runForce = 100 * 90;
   runEnergyDrain = 0;
   minRunEnergy = 0;
   maxForwardSpeed = 10;
   maxBackwardSpeed = 10;
   maxSideSpeed = 10;
   
   sprintForce = 100 * 90;
   sprintEnergyDrain = 0;
   minSprintEnergy = 0;
   maxSprintForwardSpeed = 20;
   maxSprintBackwardSpeed = 12;
   maxSprintSideSpeed = 12;
   sprintStrafeScale = 1.0;
   sprintYawScale = "1.0";
   sprintPitchScale = "1.0";
   sprintCanJump = true;

   crouchForce = "4500";
   maxCrouchForwardSpeed = 3.0;
   maxCrouchBackwardSpeed = 1.0;
   maxCrouchSideSpeed = 1.0;
   
	slideForce = 20 * 90;
	slideEnergyDrain = 0.7;
   slideEnergySlot = 1;
	minSlideEnergy = 0;
	maxSlideForwardSpeed = 30;
	maxSlideBackwardSpeed = 25;
	maxSlideSideSpeed = 12;

   maxUnderwaterForwardSpeed = 8.4;
   maxUnderwaterBackwardSpeed = 7.8;
   maxUnderwaterSideSpeed = 4.0;

   jumpForce = 750;
   jumpEnergyDrain = 0;
   minJumpEnergy = 0;
   jumpDelay = 0;
   
   xJumpEnergySlot = 2;
   xJumpChargeRate = 2.0;
   xJumpSpeedFactorD = 25;
   xJumpPowerBaseConst = 0;
   xJumpPowerMultConst = 60;
   xJumpInstantEnergy = 20;
   
   gravityMod = 2.0;

	skidSpeed = 25;
	skidFactor = 0.4;
   
   glideForce = 10 * 90;
   airControl = 0.0;

   fallingSpeedThreshold = -6.0;

   landSequenceTime = 0.33;
   transitionToLand = false;
   recoverDelay = 9;
   recoverRunForceScale = 1.2;

   minImpactSpeed = 0;
   minLateralImpactSpeed = 0;
   speedDamageScale = 1;

   boundingBox = "1.5 1.5 1.0";
   crouchBoundingBox = "1.5 1.5 1.0";
   swimBoundingBox = "1.5 1.5 1.0";
   pickupRadius = 0.75;

   // Damage location details
   boxHeadPercentage       = 0.83;
   boxTorsoPercentage      = 0.49;
   boxHeadLeftPercentage         = 0.30;
   boxHeadRightPercentage        = 0.60;
   boxHeadBackPercentage         = 0.30;
   boxHeadFrontPercentage        = 0.60;

   // Foot Prints
   decalData = FrmAlphaDiscFootprint;
   decalOffset = 0.25;
   footPuffEmitter = "FrmAlphaDiscFootPuffEmitter";
   footPuffNumParts = 5;
   footPuffRadius = "0.2";

   dustEmitter = "LightPuffEmitter";

   splash = PlayerSplash;
   splashVelocity = 4.0;
   splashAngle = 67.0;
   splashFreqMod = 300.0;
   splashVelEpsilon = 0.60;
   bubbleEmitTime = 0.4;
   splashEmitter[0] = PlayerWakeEmitter;
   splashEmitter[1] = PlayerFoamEmitter;
   splashEmitter[2] = PlayerBubbleEmitter;
   mediumSplashSoundVelocity = 10.0;
   hardSplashSoundVelocity = 20.0;
   exitSplashSoundVelocity = 5.0;
   
   repairParticleEmitter = FrmAlphaDiscRepairEmitter;
   damageParticleEmitter = FrmAlphaDiscDamageEmitter;
   damageParticleMultiplier = 2;
   bufferDamageParticleEmitter = FrmAlphaDiscBufferDamageEmitter;
   bufferDamageParticleMultiplier = 2;
   
   // Shape trails
   numShapeTrails = 0;
   shapeTrailsMaterial = "reso_shapes_alphadisc_p1_trailsmat";
   
	// Slide visuals
	//slideParticleFootEmitter[0] = FrmAlphaDiscSlideFootEmitter;
	//slideParticleTrailEmitter[0] = BlueSlideEmitter;
	//slideContactParticleFootEmitter[0] = RedSlideEmitter;
	//slideContactParticleTrailEmitter[0] = FrmAlphaDiscSlideContactTrailEmitter;
   slideDecal = FrmAlphaDiscSlideDecal;
 
   // Skid visuals
	skidParticleFootEmitter[0] = FrmAlphaDiscSkidFootEmitter0;
	skidParticleFootEmitter[1] = FrmAlphaDiscSkidFootEmitter1;
	skidParticleTrailEmitter[0] = FrmAlphaDiscSkidTrailEmitter0;
	//skidParticleTrailEmitter[1] = FrmAlphaDiscSkidTrailEmitter1;
   skidDecal = FrmAlphaDiscSkidDecal;

   // Controls over slope of runnable/jumpable surfaces
   runSurfaceAngle  = 40;
   jumpSurfaceAngle = 40;
   maxStepHeight = 1.0;  //two meters
   minJumpSpeed = 0;
   maxJumpSpeed = 9999;

   horizMaxSpeed = 200;
   horizResistSpeed = 30;
   horizResistFactor = 0.35;

   upMaxSpeed = 200;
   upResistSpeed = 25;
   upResistFactor = 0.3;

   footstepSplashHeight = 0.35;

   //NOTE:  some sounds commented out until wav's are available

   // Footstep Sounds
   FootSoftSound        = FrmAlphaDiscLeftFootSoftSound;
   FootHardSound        = FrmAlphaDiscLeftFootHardSound;
   FootMetalSound       = FrmAlphaDiscLeftFootMetalSound;
   FootSnowSound        = FrmAlphaDiscLeftFootSnowSound;
   FootShallowSound     = FrmAlphaDiscLeftFootShallowSplashSound;
   FootWadingSound      = FrmAlphaDiscLeftFootWadingSound;
   FootUnderwaterSound  = FrmAlphaDiscFootUnderwaterSound;
   //FootBubblesSound     = FootLightBubblesSound;
   OtherFootSoftSound        = FrmAlphaDiscRightFootSoftSound;
   OtherFootHardSound        = FrmAlphaDiscRightFootHardSound;
   OtherFootMetalSound       = FrmAlphaDiscRightFootMetalSound;
   OtherFootSnowSound        = FrmAlphaDiscRightFootSnowSound;
   OtherFootShallowSound     = FrmAlphaDiscRightFootShallowSplashSound;
   OtherFootWadingSound      = FrmAlphaDiscRightFootWadingSound;
   OtherFootUnderwaterSound  = FrmAlphaDiscFootUnderwaterSound;
   //OtherFootBubblesSound     = FootLightBubblesSound;
   
   //movingBubblesSound   = ArmorMoveBubblesSound;
   //waterBreathSound     = WaterBreathMaleSound;

   impactSoftSound      = FrmAlphaDiscImpactSoftSound;
   impactHardSound      = FrmAlphaDiscImpactHardSound;
   impactMetalSound     = FrmAlphaDiscImpactMetalSound;
   impactSnowSound      = FrmAlphaDiscImpactSnowSound;
   
	slideSound        = FrmAlphaDiscSlideSound;
	//slideContactSound = FrmAlphaDiscSlideContactSound;
 
	skidSound         = FrmAlphaDiscSkidSound;
 
	xJumpSound          = FrmAlphaDiscXJumpSound;
	xJumpChargeSound    = FrmAlphaDiscXJumpChargeSound;

   //impactWaterEasy      = ImpactLightWaterEasySound;
   //impactWaterMedium    = ImpactLightWaterMediumSound;
   //impactWaterHard      = ImpactLightWaterHardSound;

   groundImpactMinSpeed    = "60";
   groundImpactShakeFreq   = "4.0 4.0 4.0";
   groundImpactShakeAmp    = "1.0 1.0 1.0";
   groundImpactShakeDuration = 0.8;
   groundImpactShakeFalloff = 10.0;

   //exitingWater         = ExitingWaterLightSound;

   observeParameters = "0.5 4.5 4.5";

   cameraMinDist = "0";


};

// callback function: called by engine
function FrmAlphaDisc::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   
   %obj.zDiscTargetSet = new SimSet();

   %obj.allowJumping(false);
   %obj.allowJetJumping(false);
   %obj.allowCrouching(false);
   %obj.allowProne(false);
   %obj.allowSwimming(false);
   %obj.allowSliding(false);
   %obj.allowChargedXJump(false);
   %obj.allowInstantXJump(false);
   %obj.setEnergyLevel(%this.maxEnergy);
   %obj.setDamageBufferLevel(%this.damageBuffer);
	%obj.isCAT = true;
	
   //%obj.ssc = new SimpleServerSideController();
   //%obj.useServerSideController(%obj.ssc);
  // %obj.ssc.trigger[0] = false;
   //%obj.ssc.trigger[1] = false;
   //%obj.ssc.trigger[2] = false;
   //%obj.ssc.trigger[3] = false;
   //%obj.ssc.trigger[4] = false;
   //%obj.ssc.trigger[5] = false;
 
   // Setup light
   %obj.zLight = new PointLight() {
      attenuationRatio = "0 1 1";
      radius = "10";
      isEnabled = "1";
      color = "1 1 1 1";
      brightness = "2";
      castShadows = "0";
   };
   MissionCleanup.add(%obj.zLight);
   %obj.mountObject(%obj.zLight, 3);
   
   // Player view spawn effect
   if(isObject(%obj.client))
   {
      %max = "-0.5 0 0.5";
      %mode = "0 0 0";
      %dt = "0.02 0 0.02";
      %rnd = "0.0 0.0 0.0";
      commandToClient(%obj.client, 'EnableChromaticLens', %max, %mode, %dt, %rnd);
      %obj.setDamageFlash(1);
   }
   
   %obj.schedule(0, "playSpawnEffects");
}

// callback function: called by engine
function FrmAlphaDisc::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   
   if(isObject(%obj.zDiscTargetSet))
   {
      %obj.zDiscTargetSet.callOnChildren("schedule", 0, "delete");
      %obj.zDiscTargetSet.clear();
      %obj.zDiscTargetSet.delete();
   }
   
   if(isObject(%obj.zLight))
      %obj.zLight.delete();
  
   if(isObject(%obj.ssc))
      %obj.ssc.delete();
}

// callback function: called by engine
function FrmAlphaDisc::onCollision(%this,%obj,%col,%vec,%vecLen)
{
	//Parent::onCollision(%this,%obj,%col,%vec,%vecLen);
    echo("FrmAlphaDisc::onCollision()" SPC %obj SPC %col SPC %vec SPC %vecLen);
    
	if(!(%col.getType() & $TypeMasks::PlayerObjectType))
	   return;
   
    %vel1 = %vec;
    %vel2 = %col.getVelocity();
    
    //echo("dot:" SPC VectorDot(VectorNormalize(%vel1), VectorNormalize(%vel2)));
    
    if(VectorLen(%vel2) < 0.001)
    {
    	%col.schedule(0, "damage", %obj, %col.getPosition(), 100, "Impact");
    	%obj.schedule(0, "setVelocity", %vec);
    }
    else
    {
    	%col.schedule(0, "impulse", %col.getPosition(), VectorScale(%vec, -1000), %obj);
    	//%obj.schedule(0, "impulse", %obj.getPosition(), VectorScale(%vec, -1), %obj);    	
    }
    
    
	return;

	if(false)
	{
	   %speed = VectorLen(%obj.getVelocity());
	   %vec = VectorSub(%collidedObject.getPosition(), %obj.getPosition());
	   %vec = VectorNormalize(%vec);
	   //%collidedObject.applyImpulse(%collidedObject.getPosition(), %vec);
	   
	   %obj.setVelocity(VectorScale(%vec, %speed));
	}
		
	
   if(%obj.getDamageState() !$= "Enabled")
      return;
      
   if(isObject(%obj.getObjectMount()))
      return;

   %colpos = VectorAdd(%pos, %vec);  
   %pos = %obj.getPosition();
   %obj.setVelocity("0 0 0");
   error(%vec SPC %vecLen);
   //%obj.setPosition(%colpos);
   //createExplosion(FrmAlphaDiscSpawnExplosion, %pos, "0 0 1", "255 255 255 255");
}

// callback function: called by engine
function FrmAlphaDisc::onImpact(%this, %obj, %collidedObject, %vec, %vecLen)
{
	echo("FrmAlphaDisc::onImpact()" SPC %obj SPC %collidedObject SPC %vec SPC %vecLen);
	if(!(%collidedObject.getType() & $TypeMasks::PlayerObjectType))
	   %obj.setVelocity(VectorScale(%vec, -1));	
	return;
	
	%pos = VectorAdd(%obj.getPosition(), VectorScale(%vec, %velLen/32));
	//%obj.setPosition(%pos);
	//%obj.setVelocity("0 0 0");
	%obj.schedule(0, "setPosition", %pos);
	%obj.schedule(0, "setVelocity", "0 0 0");
}

function FrmAlphaDisc::damage(%this, %obj, %sourceObject, %position, %damage, %damageType)
{
   echo("FrmAlphaDisc::damage()" SPC %obj SPC %sourceObject SPC %position SPC %damage SPC %damageType);
   if (!isObject(%obj) || %obj.getState() $= "Dead" || !%damage)
      return;
  
   %pos = %obj.getPosition();
   createExplosion(FrmAlphaDiscSpawnExplosion, %pos, "0 0 1", "255 255 255 255");
   Game.onUnitDestroyed(%obj);
   %obj.schedule(0, "delete");
  
   return;
      
   Parent::damage(%this, %obj, %sourceObject, %position, %damage, %damageType);

   %location = "Body";

   // Deal with client callbacks here because we don't have this
   // information in the onDamage or onDisable methods
   %client = %obj.client;
   %sourceClient = %sourceObject ? %sourceObject.client : 0;

   if (isObject(%client))
   {
      // Determine damage direction
      if (%damageType !$= "Suicide")
         %obj.setDamageDirection(%sourceObject, %position);

      if (%obj.getState() $= "Dead")
         Game.onUnitDestroyed(%obj);
   }
}


// Called by script
function FrmAlphaDisc::playSpawnEffects(%this, %obj)
{
   %obj.playAudio(0, FrmAlphaDiscSpawnSound);
   createExplosion(FrmAlphaDiscSpawnEffect, %obj.getWorldBoxCenter(), "0 0 1");
}


// Called by ShapeBase script code.
function FrmAlphaDisc::getBleed(%this, %obj, %dmg, %src)
{
//   echo(%dmg);
//   if(%dmg > 0)
//      return FrmAlphaDiscBleedEffect50;
//   else
//      return FrmAlphaDiscBleedEffect30;

   if(%dmg > 90)
      return FrmAlphaDiscBleedEffect100;
   else if(%dmg > 80)
      return FrmAlphaDiscBleedEffect90;
   else if(%dmg > 70)
      return FrmAlphaDiscBleedEffect80;
   else if(%dmg > 60)
      return FrmAlphaDiscBleedEffect70;
   else if(%dmg > 50)
      return FrmAlphaDiscBleedEffect60;
   else if(%dmg > 40)
      return FrmAlphaDiscBleedEffect50;
   else if(%dmg > 30)
      return FrmAlphaDiscBleedEffect40;
   else if(%dmg > 20)
      return FrmAlphaDiscBleedEffect30;
   else if(%dmg > 10)
      return FrmAlphaDiscBleedEffect20;
   else if(%dmg > 0)
      return FrmAlphaDiscBleedEffect10;
   else
      return FrmAlphaDiscBleedEffect0;
}



// Called by engine
function FrmAlphaDisc::onDisabled(%this, %obj, %state)
{
   Parent::onDisabled(%this, %obj, %state);
   
   // Remove light.
   %obj.zLight.delete();
   %obj.zLight = "";
   
   // Delete all HudInfo objects linked to this object
   while(%obj.zHudInfoSet.getCount() > 0)
      %obj.zHudInfoSet.getObject(0).delete();

   %obj.deactivateStealth();
   %obj.unmountImage(0); // Unmount weapon
   
   // Clear inventory
   %obj.setInventory(ItemDamper, 0);
   %obj.setInventory(ItemVAMP, 0);
   %obj.setInventory(ItemStealth, 0);
   %obj.setInventory(ItemEtherboard, 0);
   %obj.setInventory(ItemImpShield, 0);
   %obj.setInventory(ItemLauncher, 0);
   %obj.setInventory(ItemBounce, 0);
   %obj.setInventory(ItemG1Launcher, 0);
   
   // Unmount any object mounted to us.
   %n = %obj.getMountedObjectCount();
   for(%i = %n-1; %i >= 0; %i--)
      %obj.unmountObject(%obj.getMountedObject(%i));

   %obj.changeSkin("xa_notc_core_shapes_standardcat_erasemat" SPC
      "xa_notc_core_shapes_standardcat_erasemat");
}

// Called from script
function FrmAlphaDisc::onFlagTaken(%this, %obj)
{
   %obj.zHasFlag = true;
   %this.updateImpulseDamperProperties(%obj);
}

// Called from script
function FrmAlphaDisc::onFlagDropped(%this, %obj)
{
   %obj.zHasFlag = false;
   %this.updateImpulseDamperProperties(%obj);
}
