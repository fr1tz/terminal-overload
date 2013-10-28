// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(FrmLightPointerShape)
{
   shapeFile = "content/fr1tz/alux1/shapes/light/pointer.dae";
};

datablock LightFlareData(FrmLightLightFlare)
{
   overallScale = "1";
   flareEnabled = true;
   renderReflectPass = true;
   flareTexture = "art/lights/lensFlareSheet1.png";

   elementRect[0] = "512 512 512 512";
   elementDist[0] = 0.0;
   elementScale[0] = 0.5;
   elementTint[0] = "1.0 1.0 1.0";
   elementRotate[0] = true;
   elementUseLightColor[0] = true;

   elementRect[1] = "512 0 512 512";
   elementDist[1] = 0.0;
   elementScale[1] = 2.0;
   elementTint[1] = "0.698039 0.698039 0.698039 1";
   elementRotate[1] = true;
   elementUseLightColor[1] = true;

   elementRect[2] = "1152 0 128 128";
   elementDist[2] = 0.3;
   elementScale[2] = 0.5;
   elementTint[2] = "1.0 1.0 1.0";
   elementRotate[2] = true;
   elementUseLightColor[2] = true;

   elementRect[3] = "1024 0 128 128";
   elementDist[3] = 0.5;
   elementScale[3] = 0.25;
   elementTint[3] = "1.0 1.0 1.0";
   elementRotate[3] = true;
   elementUseLightColor[3] = true;

   elementRect[4] = "1024 128 128 128";
   elementDist[4] = 0.8;
   elementScale[4] = 0.6;
   elementTint[4] = "1.0 1.0 1.0";
   elementRotate[4] = true;
   elementUseLightColor[4] = true;

   elementRect[5] = "1024 0 128 128";
   elementDist[5] = 1.18;
   elementScale[5] = 0.5;
   elementTint[5] = "0.698039 0.698039 0.698039 1";
   elementRotate[5] = true;
   elementUseLightColor[5] = true;

   elementRect[6] = "1152 128 128 128";
   elementDist[6] = 1.25;
   elementScale[6] = 0.35;
   elementTint[6] = "0.8 0.8 0.8";
   elementRotate[6] = true;
   elementUseLightColor[6] = true;

   elementRect[7] = "1024 0 128 128";
   elementDist[7] = 2.0;
   elementScale[7] = 0.25;
   elementTint[7] = "1.0 1.0 1.0";
   elementRotate[7] = true;
   elementUseLightColor[7] = true;
};

//-----------------------------------------------------------------------------

datablock EtherformData(FrmLight)
{
   allowColorization = true;

	//hudImageNameFriendly = "~/client/ui/hud/pixmaps/black.png";
	//hudImageNameEnemy = "~/client/ui/hud/pixmaps/black.png";
	
	thirdPersonOnly = true;

    //category = "Vehicles"; don't appear in mission editor
	//shapeFile = "content/fr1tz/oldshapes/light/p1/shape.dae";
	//emap = true;
 
	cameraDefaultFov = 90.0;
	cameraMinFov     = 60.0;
	cameraMaxFov     = 130.0;
	cameraMinDist    = 2;
	cameraMaxDist    = 3;
	
	//renderWhenDestroyed = false;
	//explosion = FlyerExplosion;
	//defunctEffect = FlyerDefunctEffect;
	//debris = BomberDebris;
	//debrisShapeName = "share/shapes/rotc/vehicles/bomber/vehicle.dts";

	mass = 90;
	drag = 0.99;
	density = 10;

	maxDamage = 0;
	damageBuffer = 100;
	maxEnergy = 100;

	damageBufferRechargeRate = 0;
	damageBufferDischargeRate = 0;
	energyRechargeRate = 0.5;
 
    // collision box...
    boundingBox = "1.0 1.0 1.0";
 
    // etherform movement...
    accelerationForce = 30;

	// impact damage...
	minImpactSpeed = 1;		// If hit ground at speed above this then it's an impact. Meters/second
	speedDamageScale = 0.0;	// Dynamic field: impact damage multiplier

	// damage info eyecandy...
   damageBufferParticleEmitter = FrmLightDamageBufferEmitter;
//	repairParticleEmitter = FrmLightRepairEmitter;
//	bufferRepairParticleEmitter = FrmLightBufferRepairEmitter;

	// laser trail...
	laserTrail[0] = FrmLight_LaserTrailOne;
	laserTrail[1] = FrmLight_LaserTrailTwo;

	// contrail...
	minTrailSpeed = 1;
	//particleTrail = FrmLight_ContrailEmitter;
	
	// various emitters...
	//forwardJetEmitter = FlyerJetEmitter;
	//downJetEmitter = FlyerJetEmitter;

	//
//	jetSound = Team1ScoutFlyerThrustSound;
//	engineSound = EtherformSound;
	softImpactSound = FrmLightImpactSound;
	hardImpactSound = FrmLightImpactSound;
	//wheelImpactSound = WheelImpactSound;
};

// callback function: called by engine
function FrmLight::onAdd(%this, %obj)
{
	Parent::onAdd(%this,%obj);
 
   %obj.mode = "posess";
 
   // Setup view & hearing
   %obj.fovDelta = 0;
   %obj.viewHud = "LightHud";
   %obj.viewIrisSizeX = 8;
   %obj.viewIrisSizeY = 8;
   %obj.viewIrisDtX = 0;
   %obj.viewIrisDtY = 0;
   %obj.viewMotionBlurActive = false;
   %obj.hearingDeafness = 0.75;
   %obj.hearingDeafnessDt = 0;
   %obj.hearingTinnitusEnabled = false;
   
   // Setup pointer.
   %this.createPointer(%obj);

	// start singing...
	%obj.playAudio(1, EtherformSingSound);

   %obj.updateVisuals();

	// Make sure grenade ammo bar is not visible...
	messageClient(%obj.client, 'MsgGrenadeAmmo', "", 1);

	// lights...
	if(%obj.getTeamId() == 1)
		%obj.mountImage(RedEtherformLightImage, 3);
	else
		%obj.mountImage(BlueEtherformLightImage, 3);

	%obj.client.inventoryMode = "show";
	%obj.client.displayInventory();

	if($Server::NewbieHelp && isObject(%obj.client))
	{
		%client = %obj.client;
		if(!%client.newbieHelpData_HasManifested)
		{
			%client.setNewbieHelp("You are in etherform! Press @bind34 inside a" SPC
				(%client.team == $Team1 ? "red" : "blue") SPC "zone to change into CAT form.");
		}
		else if(%client.newbieHelpData_NeedsRepair && !%client.newbieHelpData_HasRepaired)
		{
			%client.setNewbieHelp("If you don't have enough health to change into CAT form," SPC
				"fly into one of your team's zones to regain your health.");
		}
		else
		{
			%client.setNewbieHelp("random", false);
		}
	}
 
   %obj.light = new PointLight() {
      radius = "5";
      isEnabled = "1";
      color = "1 1 1 1";
      brightness = "1";
      castShadows = "0";
      flareType = "FrmLightLightFlare";
      flareScale = "1";
   };
   MissionCleanup.add(%obj.light);
   %obj.mountObject(%obj.light, 0);
}

// callback function: called by engine
function FrmLight::onRemove(%this, %obj)
{
   %obj.pointer.delete();
   %obj.light.delete();
}

// *** Callback function: called by engine
function FrmLight::onTrigger(%this, %obj, %triggerNum, %val)
{
   if(%val || %triggerNum > 0)
      return;
      
   if(%obj.mode $= "posess")
      %this.posess(%obj);
   else if(%obj.mode $= "transform")
      %this.materializeFDV(%obj);
   else if(%obj.mode $= "build")
      %this.build(%obj);

   return;

	if(%triggerNum == 0 && %val)
	{
      if(%obj.client.spawnError !$= "")
      {
         %obj.client.play2D(BeepMessageSound);
         return;
      }

      %pos = %obj.getWorldBoxCenter();
      %vec = %obj.getEyeVector();
      %vec = "0 0 1";
 		%vel = VectorScale(%vec, FrmLightProjectile.muzzleVelocity);

		// create the projectile object...
		%p = new Projectile() {
			dataBlock       = FrmLightProjectile;
			teamId          = %obj.teamId;
			initialVelocity = %vel;
			initialPosition = %pos;
			sourceObject    = %obj;
			sourceSlot      =  0;
			client	       = %obj.client;
		};
		MissionCleanup.add(%p);

      %p.setLoadoutCode(%obj.client.activeLoadout);
      %p.setTargetPosition(%obj.client.proxy.basePos);
      %p.zTargetPosition = %obj.client.proxy.basePos;

      %proxy = new StaticShape() {
	      dataBlock = $Server::Game.form[getWord(%p.loadoutCode, 0)].proxy;
	      client = %obj.client;
         teamId = %obj.client.team.teamId;
      };
      MissionCleanup.add(%proxy);

      %proxy.setTransform(%obj.client.proxy.getTransform());

      %proxy.setGhostingListMode("GhostOnly");
      %proxy.addClientToGhostingList(%obj.client);
      %proxy.getHudInfo().setActive(false);
      %proxy.setCollisionsDisabled(true);

      %proxy.startFade(0, 0, true);

      %proxy.shapeFxSetTexture(0, 0);
      %proxy.shapeFxSetColor(0, 3);
      %proxy.shapeFxSetBalloon(0, 1.0, 0.0);
      %proxy.shapeFxSetFade(0, 0.5, 0.0);
      %proxy.shapeFxSetActive(0, true, true);

      %p.proxy = %proxy;

      return;



      %obj.client.spawnForm();

      return;

      %pos = %obj.getWorldBoxCenter();
      %vec = %obj.getEyeVector();
 		%vel = VectorScale(%vec, FrmLightProjectile.muzzleVelocity);

		// create the projectile object...
		%p = new Projectile() {
			dataBlock       = FrmLightProjectile;
			teamId          = %obj.teamId;
			initialVelocity = %vel;
			initialPosition = %pos;
			sourceObject    = %obj;
			sourceSlot      =  0;
			client	       = %obj.client;
		};
		MissionCleanup.add(%p);

      %obj.client.camera.setOrbitMode(%p, %obj.getTransform(), 0, 10, 10, true);
      %obj.client.camera.setTransform(%obj.getTransform());
      %obj.client.control(%obj.client.camera);
      %obj.client.player = %p;

      %obj.schedule(0, "delete");
	}

	if(%triggerNum == 1 && %val)
      %obj.setVelocity("0 0 0");
}

// Called by script
function FrmLight::createPointer(%this, %obj)
{
   if(isObject(%obj.pointer))
      %obj.pointer.delete();

   %obj.pointer = new StaticShape() {
	  dataBlock = FrmLightPointerShape;
	  client = %obj.client;
     teamId = %obj.client.team.teamId;
   };
   MissionCleanup.add(%obj.pointer);
   //%obj.pointer.setGhostingListMode("GhostOnly");
   //%obj.pointer.getHudInfo().setActive(true);
   //%obj.pointer.setCollisionsDisabled(true);
   
   %this.updatePointerThread(%obj);
}

// Called by script
function FrmLight::updatePointerThread(%this, %obj)
{
   %this.schedule(32, "updatePointerThread", %obj);

   if(!isObject(%obj))
      return;

   %obj.pointer.setMeshHidden("hexagon", true);
   %obj.pointer.setTransform("0 0 0");
   
   if(%obj.mode !$= "build")
      return;

   %prevSpawnError = %client.spawnError;

   //%vec = %obj.getEyeVector();
   %vec = "0 0 -4";
   %start = %obj.getEyePoint();
   %end = VectorAdd(%start, %vec);
   %c = containerRayCast(%start, %end, $TypeMasks::StaticObjectType, %obj);
   if(!%c)
   {
      %obj.buildError = "No surface in range";
      //%client.spawnError = "No surface in range";
      //%client.proxy.removeClientFromGhostingList(%client);
      //%client.proxy.setTransform("0 0 0");
      //%client.pointer.removeClientFromGhostingList(%client);
      //%obj.pointer.setTransform("0 0 0");
      //%client.pointer.getHudInfo().setActive(false);
      return;
   }


   %pos = getWords(%c, 1, 3);
   %vec = VectorNormalize(VectorSub(%pos, %start));
   %pos = VectorAdd(%pos, VectorScale(%vec, 0.1));
   
   %normal = getWords(%c, 4, 6);

   %obj.pointer.basePos = %pos;

   //%transform = createOrientFromDir(%normal);
   //%pos = VectorAdd(%pos, VectorScale(%normal, 0.25));
   //%transform = setWord(%transform, 0, getWord(%pos, 0));
   //%transform = setWord(%transform, 1, getWord(%pos, 1));
   //%transform = setWord(%transform, 2, getWord(%pos, 2));
   
   %gridPos = MissionSoilGrid.worldToGrid(%pos);
   //error(%gridPos);
   
   %x = getWord(%gridPos, 0);
   %y = getWord(%gridPos, 1);
   %z = getWord(%gridPos, 2);
   
//   if(false)
   if(((%x & 1) == 0 && (%y & 1) == 1)
   || ((%x & 1) == 1 && (%y & 1) == 0))
   {
      %worldPos1 = MissionSoilGrid.gridToWorld(%x SPC %y + 1 SPC %z);
      %worldPos2 = MissionSoilGrid.gridToWorld(%x SPC %y - 1 SPC %z);
      %dist1 = VectorLen(VectorSub(%worldPos1, %pos));
      %dist2 = VectorLen(VectorSub(%worldPos2, %pos));
      if(%dist1 < %dist2)
         %y += 1;
      else
         %y -= 1;
      %gridPos = setWord(%gridPos, 1, %y);
   }
   
   %gridPos2D = %x SPC %y;
   //echo(%gridPos2D);
   
   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);
   
   %obj.buildError = "Invalid surface";
	InitContainerRadiusSearch(%worldPos, 0.1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(%srchObj.getClassName() $= "HexagonVolume")
      {
         %volume = %srchObj;
         %shapeNr = %volume.getHexagonShapeNr(%gridPos2D);
         if(%shapeNr != %obj.teamId)
            continue;
            
         %obj.buildError = "";
         %elevation = %volume.getHexagonElevation(%gridPos2D);
         %amount = %volume.getHexagonAmount(%gridPos2D);
         %top = %elevation + %amount - 1;
         
         if(%top > %z)
            %z = %top;
      }
	}
 
   if(%obj.buildError !$= "")
      return;
 
   %gridPos = %x SPC %y SPC %z;
   
   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);
   
   //%obj.pointer.addClientToGhostingList(%client);
   %obj.pointer.setMeshHidden("hexagon", false);
   %obj.pointer.setTransform(%worldPos);
   //%obj.pointer.getHudInfo().setActive(true);

   return;
   

   if(%y > 0)
   {
      //%r = %y - mFloor(%y);
      if((%y & 1) == 0)
      {
         %r = %y % 2;
         if(%r < 1)
            %y = mCeil(%y);
         else
            %y = mFloor(%y);
      }
   }
   else
   {
      //%r = %y - mFloor(%y);
      %r = %y % 2;
      if(%r > 1)
         %y = mCeil(%y);
      else
         %y = mFloor(%y);
   }
   %gridPos = setWord(%gridPos, 1, %y);

   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);

   //%obj.pointer.addClientToGhostingList(%client);
   %obj.pointer.setTransform(%worldPos);
   //%obj.pointer.getHudInfo().setActive(true);
      
   return;

   if(isObject(%client.pointer))
   {

   }

   if(%obj.getEnergyLevel() < 0) // %obj.maxEnergy)
   {
      %client.spawnError = "Not enough energy to materialize.";
      %client.proxy.shapeFxSetColor(0, 2);
      %client.proxy.shapeFxSetColor(1, 2);
   }
   else
      %client.spawnError = "";

   %x = getWord(%c,1);
   if(%x > 0)
   {
      //%r = %x - mFloor(%x);
      %r = %x % 2;
      if(%r < 1)
         %x = mCeil(%x);
      else
         %x = mFloor(%x);
   }
   else
   {
      %r = %x % 2;
      if(%r > 1)
         %x = mCeil(%x);
      else
         %x = mFloor(%x);
   }
   %y = getWord(%c,2);
   if(%y > 0)
   {
      //%r = %y - mFloor(%y);
      %r = %y % 2;
      if(%r < 1)
         %y = mCeil(%y);
      else
         %y = mFloor(%y);
   }
   else
   {
      //%r = %y - mFloor(%y);
      %r = %y % 2;
      if(%r > 1)
         %y = mCeil(%y);
      else
         %y = mFloor(%y);
   }
   %z = getWord(%c,3);
   %pos = %x SPC %y SPC %z;
   %normal = getWords(%c, 4, 6);
   if(%pos $= %client.proxy.getPosition()
   && (%client.spawnError $= %prevSpawnError))
      return;

   %transform = %pos SPC %normal SPC "0";
   if(%client.proxy.getDataBlock().isMethod("adjustTransform"))
   {
      %transform = %client.proxy.getDataBlock().adjustTransform(
         %pos, %normal, %eyeVec);
   }
   %client.proxy.addClientToGhostingList(%client);
   %client.proxy.setTransform(%transform);

   if(%obj.getEnergyLevel() < %obj.maxEnergy)
      return;

   %pieces = sLoadoutcode2Pieces(%client.activeLoadout);
   %missing = "";
   for(%f = 0; %f < getFieldCount(%pieces); %f++)
   {
      %field = getField(%pieces, %f);
      %piece = getWord(%field, 0);
      %count = getWord(%field, 1);

      %used = %client.inventory.pieceUsed[%piece];
      %free = %client.inventory.pieceCount[%piece] - %used;

      %piecestring = sPiece2String(%piece);

      if(%free < %count)
      {
         if(%missing !$= "")
            %missing = %missing @ " and ";
         %missing = %missing @ %piecestring;
      }
   }
   if(%missing !$= "")
      %client.spawnError = "Bank is missing" SPC %missing SPC "piece";


   if(%client.spawnError $= "")
   {
      if(%client.proxy.getDataBlock().form.isMethod("canMaterialize"))
      {
         %client.spawnError = %client.proxy.getDataBlock().form.canMaterialize(
            %client, %pos, %normal, %transform);
      }
   }

   if(%client.spawnError $= "")
   {
      %client.proxy.shapeFxSetColor(0, 3);
      %client.proxy.shapeFxSetColor(1, 3);
   }
   else
   {
      %client.proxy.shapeFxSetColor(0, 1);
      %client.proxy.shapeFxSetColor(1, 1);
   }
}

// Called by Etherform::updateVisuals() script function
function FrmLight::updateVisuals(%this, %obj)
{
   %client = %obj.client;
   if(!isObject(%client))
      return;

   %used = %client.inventory.pieceUsed[0];
   %free = %client.inventory.pieceCount[0] - %used;

   %obj.setDamageBufferLevel(%free >= 1 ? 200 : 0);
}

// Called by ShapeBase::impulse() script function
function FrmLight::impulse(%this, %obj, %position, %impulseVec, %src)
{
   return; // ignore impulses
}

// Called by script
function FrmLight::clientAction(%this, %obj, %nr)
{
   if(%nr < 10)
   {
      %obj.mode = "build";
      %obj.client.selectLoadout(%nr);
   }
   else if(%nr < 18)
   {
      %obj.mode = "transform";
      %obj.client.selectLoadout(%nr-10+51);
   }
   else if(%nr == 19)
   {
      %obj.mode = "posess";
   }
}

// Called by script
function FrmLight::posess(%this, %obj)
{
   %client = %obj.client;

   %eyeVec = %obj.getEyeVector();
   %startPos = %obj.getEyePoint();
   %endPos = VectorAdd(%startPos, VectorScale(%eyeVec, 2));

   %target = ContainerRayCast(%startPos, %endPos, $TypeMasks::ShapeBaseObjectType);
   
   if(!isObject(%target))
      return;
   if(%target.getTeamId() != %obj.getTeamId())
      return;
   if(isObject(%target.getControllingClient()))
      return;
   if(!isObject(%target.getDataBlock()))
      return;
   if(!%target.getDataBlock().isMethod("dematerialize"))
      return;
      
   if(isObject(%client.proxy))
   {
  //%this.proxy.delete();
      %client.proxy.removeClientFromGhostingList(%client);
      %client.proxy.setTransform("0 0 0");
      %client.pointer.removeClientFromGhostingList(%client);
      %client.pointer.setTransform("0 0 0");
      %client.pointer.getHudInfo().setActive(false);
   }
   %client.player = %target;
   %client.control(%target);
   if(%target.getDataBlock().isMethod("onLightEnter"))
      %target.getDataBlock().onLightEnter(%target);
   %obj.schedule(0, "delete");
}

// Called by script
function FrmLight::materializeFDV(%this, %obj)
{
   %client = %obj.client;

   %pieces = sLoadoutcode2Pieces(%client.activeLoadout);
   //for(%f = 0; %f < getFieldCount(%pieces); %f++)
   if(false)
   {
      %field = getField(%pieces, %f);
      %piece = getWord(%field, 0);
      %count = getWord(%field, 1);

      %used = %client.inventory.pieceUsed[%piece];
      %free = %client.inventory.pieceCount[%piece] - %used;

      if(%free < %count)
      {
         %client.play2D(BeepMessageSound);
         return;
      }
   }

	%player = FrmSoldierpod.materialize(%client);
   %player.setLoadoutCode(%client.loadoutCode[%nr]);
   %player.setTransform(%obj.getTransform());
   
   createExplosion(FrmCrateDematerializeExplosion, %player.getPosition(), "0 0 1");

   %client.control(%player);
   %client.player = %player;
   %obj.schedule(0, "delete");

   %client.inventoryMode = "";
   %client.displayInventory();
}

// Called by script
function FrmLight::build(%this, %obj)
{
   if(%obj.buildError !$= "" || !isObject(%obj.pointer))
      return;

   %targetPos = %obj.pointer.getPosition();

   FrmSpawn::spawnBrick(%targetPos, %obj.teamId);
}
