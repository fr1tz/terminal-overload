// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnCrackpackImage)
{
   // Basic Item properties
   shapeFile = "content/fr1tz/alux1/shapes/crackpack/p1/shape.dae";
   shapeFileFP = "content/fr1tz/alux1/shapes/crackpack/p1/image.fp.dae";
   emap = true;

   imageAnimPrefix = "ProxMine";
   imageAnimPrefixFP = "ProxMine";

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

   //ammoSource = "Magazine";
   //minEnergy = 0;

   //projectile = WpnRaptorProjectile;

   //casing = WpnRaptorProjectileShell;
   //shellExitDir        = "1.0 0.3 1.0";
   //shellExitOffset     = "0.15 -0.56 -0.1";
   //shellExitVariance   = 15.0;
   //shellVelocity       = 3.0;

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
   item = WpnCrackpack;
   //ammo = WpnRaptorAmmo;
   //clip = WpnRaptorClip;
   //magazineCapacity = 30;

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
   stateTransitionOnNoAmmo[5]       = "NoAmmo";
   stateTransitionGeneric0In[5]     = "SprintEnter";
   //stateTransitionOnTimeout[5]      = "Fire";
   //stateTimeoutValue[5]             = 0.096;
   stateFire[5]                     = true;
   //stateFireProjectile[5]           = WpnRaptorProjectile;
   //stateRecoil[5]                   = "LightRecoil";
   stateAllowImageChange[5]         = true;
   stateSequence[5]                 = "fire";
   stateScaleAnimation[5]           = false;
   stateSequenceNeverTransition[5]  = true;
   //stateSequenceRandomFlash[5]      = true;        // use muzzle flash sequence
   stateScript[5]                   = "fire";
   //stateSound[5]                    = WpnRaptorFireSound;
   //stateEmitter[5]                  = WpnRaptorFireSmokeEmitter;
   //stateEmitterTime[5]              = 0.025;
   //stateEjectShell[5]               = true;

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

function WpnCrackpackImage::onMount(%this, %obj, %slot)
{
   %obj.setImageAmmo(%slot, true);
}

function WpnCrackpackImage::onUnmount(%this, %obj, %slot)
{

}

function WpnCrackpackImage::fire(%this, %obj, %slot)
{
   %start = %obj.getMuzzlePoint(%slot);
   %vec = VectorScale(%obj.getMuzzleVector(%slot), 2);
   %end = VectorAdd(%start, %vec);
   %c = containerRayCast(%start, %end, $TypeMasks::StaticObjectType, %obj);
   if(!%c)
      return;

   %worldPos = getWords(%c, 1, 3);
   %gridPos = MissionSoilGrid.worldToHexagon(%worldPos);

   %x = getWord(%gridPos, 0);
   %y = getWord(%gridPos, 1);
   %z = getWord(%gridPos, 2);

   %gridPos2D = %x SPC %y;
   //echo(%gridPos2D);

   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);

   %proceed = false;
	InitContainerRadiusSearch(%worldPos, 1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(%srchObj.getClassName() $= "HexagonVolume")
      {
         %volume = %srchObj;
         %shapeNr = %volume.getHexagonShapeNr(%gridPos2D);
         if(%shapeNr == 0 || %shapeNr == %obj.teamId)
            continue;

         %proceed = true;
         %elevation = %volume.getHexagonElevation(%gridPos2D);
         %amount = %volume.getHexagonAmount(%gridPos2D);
         %top = %elevation + %amount - 1;

         if(%top > %z)
            %z = %top;
      }
	}
   
   if(!%proceed)
      return;

   %gridPos = %x SPC %y SPC %z - 1;
   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);

   %shape = new StaticShape() {
	  dataBlock = WpnCrackpackStaticShape;
	  client = %obj.client;
     teamId = %obj.client.team.teamId;
   };
   MissionCleanup.add(%shape);
   %shape.setTransform(%worldPos);
   %shape.playAudio(0, WpnCrackpackDeploySound);
   %shape.schedule(4000, "playAudio", 0, WpnCrackpackActivateSound);
   %shape.fuseThread = WpnCrackpackStaticShape.schedule(5000, "activate", %shape);
   
   %obj.decInventory(WpnCrackpack, 1);
}

