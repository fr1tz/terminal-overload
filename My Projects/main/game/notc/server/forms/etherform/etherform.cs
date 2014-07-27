// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------

datablock EtherformData(FrmEtherform)
{
	//hudImageNameFriendly = "~/client/ui/hud/pixmaps/black.png";
	//hudImageNameEnemy = "~/client/ui/hud/pixmaps/black.png";
	
	thirdPersonOnly = true;

    //category = "Vehicles"; don't appear in mission editor
	shapeFile = "content/xa/notc/core/shapes/etherform/p2/shape.dae";
	//emap = true;
 
	cameraDefaultFov = 90.0;
	cameraMinFov     = 90.0;
	cameraMaxFov     = 90.0;
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
	damageBuffer = 0;
	maxEnergy = 100;

	damageBufferRechargeRate = 0.15;
	damageBufferDischargeRate = 0.05;
	rechargeRate = 0.4;
 
    // collision box...
    boundingBox = "1.0 1.0 1.0";
 
    // etherform movement...
    accelerationForce = 100;

	// impact damage...
	minImpactSpeed = 1;		// If hit ground at speed above this then it's an impact. Meters/second
	speedDamageScale = 0.0;	// Dynamic field: impact damage multiplier

	// damage info eyecandy...
// damageBufferParticleEmitter = FrmEtherformDamageBufferEmitter;
   repairParticleEmitter = FrmEtherformRepairEmitter;
//	bufferRepairParticleEmitter = FrmEtherformBufferRepairEmitter;

	// laser trail...
	laserTrail[0] = FrmEtherformLaserTrail0;

	// contrail...
	minTrailSpeed = 1;
	//particleTrail = FrmEtherform_ContrailEmitter;
	
	// various emitters...
	//forwardJetEmitter = FlyerJetEmitter;
	//downJetEmitter = FlyerJetEmitter;

	//
//	jetSound = Team1ScoutFlyerThrustSound;
//	engineSound = EtherformSound;
	softImpactSound = FrmEtherformImpactSound;
	hardImpactSound = FrmEtherformImpactSound;
	//wheelImpactSound = WheelImpactSound;
};

// callback function: called by engine
function FrmEtherform::onAdd(%this, %obj)
{
	Parent::onAdd(%this,%obj);
 
   %obj.mode = "posess";
   
   // Play spawn sound and start singing
   %obj.playAudio(0, FrmEtherformSpawnSound);
   %obj.playAudio(1, FrmEtherformSingSound);
 
   // Setup view & hearing
   %obj.fovDelta = 0;
   %obj.viewHud = "EtherformGui";
   %obj.viewIrisSizeX = 8;
   %obj.viewIrisSizeY = 8;
   %obj.viewIrisDtX = 0;
   %obj.viewIrisDtY = 0;
   %obj.viewMotionBlurActive = false;
   %obj.hearingDeafness = 0.0;
   %obj.hearingDeafnessDt = 0;
   %obj.hearingTinnitusEnabled = false;
   
   // Setup light
   %obj.light = new PointLight() {
      radius = "10";
      isEnabled = "1";
      color = "1 1 1 1";
      brightness = "2";
      castShadows = "0";
      flareType = "FrmEtherformLightFlare";
      flareScale = "2";
   };
   MissionCleanup.add(%obj.light);
   %obj.mountObject(%obj.light, 0);
   
   // Player view spawn effect
   if(isObject(%obj.client))
   {
      //%max = "-0.02 0 0.02";
      //%mode = "0 0 0";
      //%dt = "0.02 0 0.02";
      //%dt = "0 0 0";
      //%rnd = "0.04 0.04 0.04";
      //commandToClient(%obj.client, 'EnableChromaticLens', %max, %mode, %dt, %rnd);
      %obj.setWhiteOut(1);
   }
   
   return;
   
   // Setup pointer.
   //%this.createPointer(%obj);

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
 
   %emitterData = "";
   if(%obj.teamId == 1)
      %emitterData = FrmEtherformTeam1ParticleEmitter;
   else if(%obj.teamId == 2)
      %emitterData = FrmEtherformTeam2ParticleEmitter;
      
   if(%emitterData !$= "")
   {
      %obj.emitter = new ParticleEmitterNode()
      {
         datablock = FrmEtherformParticleEmitterNode;
         position = "0 0 0";
         rotation = "0 0 1 0";
         emitter = %emitterData;
         velocity = 1;
      };
      MissionCleanup.add(%obj.emitter);
      %obj.mountObject(%obj.emitter, 0);
   }
 
   return;
 

}

// callback function: called by engine
function FrmEtherform::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);

   if(isObject(%obj.pointer))
      %obj.pointer.delete();
   if(isObject(%obj.emitter))
      %obj.emitter.delete();
   if(isObject(%obj.light))
      %obj.light.delete();
}

// Called by Etherform::updateVisuals() script function
function FrmEtherform::updateVisuals(%this, %obj)
{
   %client = %obj.client;
   if(!isObject(%client))
      return;

   %used = %client.inventory.pieceUsed[0];
   %free = %client.inventory.pieceCount[0] - %used;

   //%obj.setDamageBufferLevel(%free >= 1 ? 200 : 0);
}

// Called by ShapeBase::impulse() script function
function FrmEtherform::impulse(%this, %obj, %position, %impulseVec, %src)
{
   return; // ignore impulses
}

function FrmEtherform::onTrigger(%this, %obj, %triggerNum, %val)
{
  
}

