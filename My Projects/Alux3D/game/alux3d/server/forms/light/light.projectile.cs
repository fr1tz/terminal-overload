// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


datablock MultiNodeLaserBeamData(FrmLightProjectile_LaserTrailOne)
{
   allowColorization = true;

	hasLine = false;
	lineColor	= "1.00 1.00 1.00 0.7";

	hasInner = true;
	innerColor = "1.0 1.0 1.0 0.5";
	innerWidth = "0.20";

	hasOuter = false;
	outerColor = "1.00 0.00 1.00 0.1";
	outerWidth = "0.10";

	//bitmap = "share/shapes/rotc/vehicles/team1scoutflyer/lasertrail";
	//bitmapWidth = 1;

	blendMode = 1;
	fadeTime = 500;
};

//-----------------------------------------------------------------------------
// projectile datablock...

datablock ProjectileData(FrmLightProjectile)
{
   allowColorization = true;

	stat = "lightform";

	// script damage properties...
	impactDamage       = 0;
	impactImpulse      = 0;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;
	bypassDamageBuffer = false;
	
	maxTrackingAbility = 10;
	trackingAgility = 2;
	
	explodesNearEnemies			= false;
	explodesNearEnemiesRadius	= 2;
	explodesNearEnemiesMask	  = $TypeMasks::PlayerObjectType;

	sound = FrmLightProjectileSound;
 
   projectileShapeName = "share/shapes/alux/light2.dts";

//	explosion             = FrmLightProjectileExplosion;
//	bounceExplosion       = RedAssaultRifleProjectileBounceExplosion;
//	hitEnemyExplosion     = RedAssaultRifleProjectileExplosion;
//	nearEnemyExplosion    = RedAssaultRifleProjectileExplosion;
//	hitTeammateExplosion  = RedAssaultRifleProjectileExplosion;
//	hitDeflectorExplosion = DiscDeflectedEffect;

//	missEnemyEffectRadius = 10;
//	missEnemyEffect = AssaultRifleProjectileMissedEnemyEffect;

//	particleEmitter = FrmLightProjectileEmitter;
//	laserTrail[0]   = FrmLightProjectile_LaserTrailOne;
//	laserTrail[1]   = FrmLight_LaserTrailTwo;
//	laserTail	    = RedAssaultRifleProjectileLaserTail;
//	laserTailLen    = 2;

	energyDrain = 0;
	muzzleVelocity	= 25 * $Server::Game.slowpokemod;
	velInheritFactor = 0.0 * $Server::Game.slowpokemod;
	
	isBallistic			= false;
	//gravityMod			 = 5.0 * $Server::Game.slowpokemod;

	armingDelay			= 0;
	lifetime				= 1000*10;
	fadeDelay			= 1000*10;
	
   unlimitedBounces = true;
//	numBounces = 2;
	
	hasLight	 = true;
	lightRadius = 2.0;
	lightColor  = "1.0 1.0 1.0";
};

function FrmLightProjectile::onRemove(%this, %obj)
{
   if(isObject(%obj.proxy)) %obj.proxy.delete();
   Parent::onRemove(%this, %obj);
}

function FrmLightProjectile::onBounce(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   %dist = VectorLen(VectorSub(%pos, %obj.zTargetPosition));
   if(%dist < 2)
      %obj.explode();
}

function FrmLightProjectile::onExplode(%this,%obj,%pos,%normal,%fade,%dist,%expType)
{
   %client = %obj.client;

   %transform = %obj.proxy.getTransform();
   %form = %obj.proxy.getDataBlock().form;

   %obj.proxy.delete();
   %obj.proxy = "";

   %error = %form.canMaterialize(%client, %pos, %normal, %transform);
   if(%error !$= "")
      return;

   %player = %form.materialize(%client, %pos, %normal, %this.camera.getTransform());
   %player.setTransform(%transform);
   %player.setLoadoutCode(%obj.loadoutCode);
   %player.inv[1] = getWord(%obj.loadoutCode, 4);

   createExplosion(FrmCrateMaterializeExplosion, %player.getPosition(), "0 0 1");
   %player.getDataBlock().materializeFx(%player);

   %player.zBlocked = true;
   %player.schedule(%form.btime, "setFieldValue", "zBlocked", false);
}

function FrmLightProjectile::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{


   return;

   %client = %obj.client;
	%ownTeamId = %client.player.getTeamId();

	%inOwnZone = false;
	%inOwnTerritory = false;
	%inEnemyZone = false;

	InitContainerRadiusSearch(%pos, 0.0001, $TypeMasks::TacticalSurfaceObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
		// object actually in this zone?
		//%inSrchZone = false;
		//for(%i = 0; %i < %srchObj.getNumObjects(); %i++)
		//{
      //   error(%srchObj.getObject(%i).getDataBlock().getName());
		//	if(%srchObj.getObject(%i) == %this.player)
		//	{
		//		%inSrchZone = true;
		//		break;
		//	}
		//}
		//if(!%inSrchZone)
		//	continue;

		%zoneTeamId = %srchObj.getTeamId();
		%zoneBlocked = %srchObj.zBlocked;

		if(%zoneTeamId != %ownTeamId && %zoneTeamId != 0)
		{
			%inEnemyZone = true;
			break;
		}
		else if(%zoneTeamId == %ownTeamId)
		{
			%inOwnZone = true;
			if(%srchObj.getDataBlock().getName() $= "TerritorySurface"
			|| %srchObj.getDataBlock().isTerritoryZone)
				%inOwnTerritory = true;
		}
	}

   %spawn = true;
	if(%inEnemyZone)
	{
		%client.beepMsg("You cannot materialize on an enemy's surface!");
		%spawn = false;
	}
	else if(%inOwnZone && !%inOwnTerritory)
	{
		%client.beepMsg("This surface can't be used to materialize!");
		%spawn = false;
	}
	else if(!%inOwnZone)
	{
		%client.beepMsg("You can only materialize on your team's surfaces!");
		%spawn = false;
	}
	else if(%zoneBlocked)
	{
		%client.beepMsg("This surface is currently blocked!");
		%spawn = false;
	}

   if(%spawn)
   {
      %form = $Server::Game.form[getWord(%client.activeLoadout, 0)];
      if(!isObject(%form))
         %spawn = false;
   }

   if(%spawn)
   {
      %player = %form.materialize(%client, %pos, %normal, %client.camera.getTransform());
      %player.setTransform(%client.proxy.getTransform());
      %client.proxy.removeClientFromGhostingList(%client);
      %client.proxy.setTransform("0 0 0");
      $aiTarget = %player;

      %player.inv[1] = getWord(%client.activeLoadout, 4);
   }
   else
   {
		%data = %client.getEtherformDataBlock();
		%player = new Etherform() {
			dataBlock = %data;
			client = %client;
			teamId = %client.team.teamId;
		};
      MissionCleanup.add(%player);
      %player.setTransform(%pos);

   }
   %client.player = %player;
   %client.control(%player);
}

