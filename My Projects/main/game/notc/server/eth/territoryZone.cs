// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//
// the following dynamic fields can be added to the TacticalZone *objects*...
//	 initialOwner:  team id set on reset
//	 initiallyProtected: protected on reset?
//

function TacticalZoneData::create(%data)
{
	// The mission editor invokes this method when it wants to create
	// an object of the given datablock type.  For the mission editor
	%obj = new TacticalZone() {
		dataBlock = %data;
		initialOwner = 0;
		initiallyProtected = false;
	};
	return %obj;
}

//------------------------------------------------------------------------------
// Territory Zones

function TerritoryZone_find(%name)
{
	%group = nameToID("TerritoryZones");

	if (%group != -1)
	{
		%count = %group.getCount();
		if(%count != 0)
		{
				for (%i = 0; %i < %count; %i++)
				{
					%zone = %group.getObject(%i);
					if(%zone.getName() $= %name)
						return %zone;
				}
		}
		else
			error("TerritoryZones_call():" SPC
				"no TacticalZones found in TerritoryZones group!");
	}
	else
		error("TerritoryZones_call(): missing TerritoryZones group!");

	return -1;
}

//------------------------------------------------------------------------------

function TerritoryZones_enableRepair(%shape)
{
	if(%shape.isCAT)
		return;

	if(%shape.getTeamId() == Game.team1.teamId)
	{
		if(!Game.team1.repairObjects.isMember(%shape))
			Game.team1.repairObjects.add(%shape);
	}
	else if(%shape.getTeamId() == Game.team2.teamId)
	{
		if(!Game.team2.repairObjects.isMember(%shape))
			Game.team2.repairObjects.add(%shape);
	}
}

function TerritoryZones_disableRepair(%shape)
{
	if(%shape.isCAT)
		return;

	if(%shape.getTeamId() == Game.team1.teamId)
	{
		if(Game.team1.repairObjects.isMember(%shape))
			Game.team1.repairObjects.remove(%shape);
	}
	else if(%shape.getTeamId() == Game.team2.teamId)
	{
		if(Game.team2.repairObjects.isMember(%shape))
			Game.team2.repairObjects.remove(%shape);
	}
	
	%shape.setRepairRate(0);
}

//------------------------------------------------------------------------------

function TerritoryZones_repairTick()
{
   //echo("TerritoryZones_repairTick()");

	cancel($TerritoryZones_repairTickThread);
 
    if(!isObject(Game.team1.repairObjects) || !isObject(Game.team2.repairObjects))
        return;

	%count = Game.team1.repairObjects.getCount();
	if(%count != 0)
	{
		%repair = Game.team1.repairSpeed / %count;
		for (%i = 0; %i < %count; %i++)
		{
			%obj = Game.team1.repairObjects.getObject(%i);
         %client = %obj.client;
         %slot = %client.zActiveLoadout;
         %progress = %client.zLoadoutProgress[%slot] + %repair;
         %client.zLoadoutProgress[%slot] = %progress;
         %client.LoadoutHud_UpdateSlot(%slot, "", "", %progress);
			//%obj.setRepairRate(%repair);
		}
	}

	%count = Game.team2.repairObjects.getCount();
	if(%count != 0)
	{
		%repair = Game.team2.repairSpeed / %count;
		for (%i = 0; %i < %count; %i++)
		{
			%obj = Game.team2.repairObjects.getObject(%i);
         %client = %obj.client;
         %slot = %client.zActiveLoadout;
         %progress = %client.zLoadoutProgress[%slot] + %repair;
         %client.zLoadoutProgress[%slot] = %progress;
         %client.LoadoutHud_UpdateSlot(%slot, "", "", %progress);
			//%obj.setRepairRate(%repair);
		}
	}

	$TerritoryZones_repairTickThread =
		schedule(500, 0, "TerritoryZones_repairTick");
}

//-----------------------------------------------------------------------------

// to reset all the territory zones...
function TerritoryZones_reset()
{
   Game.team1.numTerritoryZones = 0;
   Game.team2.numTerritoryZones = 0;

	%group = nameToID("TerritoryZones");

	if (%group != -1)
	{
		%count = %group.getCount();
		if (%count != 0)
		{
				for (%i = 0; %i < %count; %i++)
				{
					%zone = %group.getObject(%i);
               %zone.setTeamId(3);
     
               if(%i > 0)
               {
                  %z = %group.getObject(%i-1);
                  %zone.zNeighbour[0] = %z;
               }
               
               if(%i < %count - 1)
               {
                  %z = %group.getObject(%i+1);
                  %zone.zNeighbour[1] = %z;
               }
               
               %zone.zNeighbour[2] = -1;
               %zone.zNeighbour[3] = -1;
     
         		if( %zone.initialOwner != 0 )
         			%zone.getDataBlock().setZoneOwner(%zone, %zone.initialOwner);
         		else
         			%zone.getDataBlock().setZoneOwner(%zone, 0);

         		%zone.zProtected = %zone.initiallyProtected;

         		%zone.getDataBlock().updateOwner(%zone);
				}
				TerritoryZones_repairTick();
		}
		else
			error("TerritoryZones_reset():" SPC
				"no TacticalZones found in TerritoryZones group!");
	}
	else
		error("TerritoryZones_reset(): missing TerritoryZones group!");
}

//-----------------------------------------------------------------------------

function TerritoryZones_call(%func)
{
	%group = nameToID("TerritoryZones");

	if (%group != -1)
	{
		%count = %group.getCount();
		if (%count != 0)
		{
				for (%i = 0; %i < %count; %i++)
				{
					%zone = %group.getObject(%i);
					call(%func, %zone);
				}
		}
		else
			error("TerritoryZones_call():" SPC
				"no TacticalZones found in TerritoryZones group!");
	}
	else
		error("TerritoryZones_call(): missing TerritoryZones group!");
}

function TerritoryZones_objectUpdateZone(%obj, %enterZone, %leftZone)
{
	%ownTeamId = %obj.getTeamId();

	%inZone = false;
	%inOwnZone = false;
	%inEnemyZone = false;
    %zoneTeamId = -1;

	%obj.zCurrentZone = -1;

   %pos = %obj.getPosition();
   InitContainerRadiusSearch(%pos, 0.0001, $TypeMasks::TacticalZoneObjectType);
   while( (%srchObj = %enterZone) != 0 || (%srchObj = containerSearchNext()) != 0)
   {
      %inSrchZone = false;
      if(%srchObj == %enterZone)
      {
         %inSrchZone = true;
      }
      else if(%srchObj != %leftZone)
      {
         // object actually in this zone?
         for(%i = 0; %i < %srchObj.getNumObjects(); %i++)
         {
            if(%srchObj.getObject(%i) == %obj)
            {
               %inSrchZone = true;
               break;
            }
         }
      }

      %enterZone = 0;

      if(!%inSrchZone)
         continue;

      %inZone = true;
      %obj.zCurrentZone = %srchObj;

      %zoneTeamId = %srchObj.getTeamId();

      if(%zoneTeamId != %ownTeamId && %zoneTeamId != 0)
      {
         %inEnemyZone = true;
      }
      else if(%zoneTeamId == %ownTeamId)
      {
         %inOwnZone = true;
      }
   }
   
   if(%obj.beingRemoved
   || %obj.isCAT
   || !%inOwnZone
   || %inEnemyZone
   //|| %obj.getDamageLevel() == 0
   )
      TerritoryZones_disableRepair(%obj);
   else
      TerritoryZones_enableRepair(%obj);

   if(%inZone)
   {
      //echo(" in zone");
      %obj.getDataBlock().onEnterMissionArea(%obj);
   }
   else
   {
      //echo(" not in zone");
      %obj.getDataBlock().onLeaveMissionArea(%obj);
   }

   // save these...
   %obj.zInZone = %inZone;
   %obj.zInOwnZone = %inOwnZone;
   %obj.zInEnemyZone = %inEnemyZone;
}

//-----------------------------------------------------------------------------
// Territory Zone Sounds

datablock SFXProfile(ZoneAquiredSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/events/zone.aquired";
   description = AudioGui;
   preload = true;
};

datablock SFXProfile(ZoneAttackedSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/events/zone.attacked";
   description = AudioGui;
   preload = true;
};

//-----------------------------------------------------------------------------
// Territory Zone

datablock TacticalZoneData(TerritoryZone)
{
	category = "Tactical Zones"; // for the mission editor

	// The period is value is used to control how often the console
	// onTick callback is called while there are any objects
	// in the zone.  The default value is 100 MS.
	tickPeriodMS = 200;

	colorChangeTimeMS = 400;

   terrainMaterial = "xa_notc_core_shapes_territoryzone_terrainmat";
   borderMaterial = "xa_notc_core_shapes_territoryzone_bordermat";
   otherMaterial = "xa_notc_core_shapes_territoryzone_othermat";
};

function TerritoryZone::onAdd(%this, %zone)
{
	%zone.teamId = 0;

	%zone.zNumReds = 0;
	%zone.zNumBlues = 0;
}

function TerritoryZone::onEnter(%this,%zone,%obj)
{
	//echo("TerritoryZone::onEnter()");
	
	if(!%obj.getType() & $TypeMasks::ShapeBaseObjectType)
		return;

   %this.onTick(%zone);
   
   TerritoryZones_objectUpdateZone(%obj, %zone);
	//%obj.getDataBlock().updateZone(%obj, %zone);
}

function TerritoryZone::onLeave(%this,%zone,%obj)
{
	//echo("TerritoryZone::onLeave()");

	// note that this function does not get called immediately when an
	// object leaves the zone but when the zone registers the object's
	// absence when the zone ticks.

	if(!%obj.getType() & $TypeMasks::ShapeBaseObjectType)
		return;
		
	%this.onTick(%zone);

   TerritoryZones_objectUpdateZone(%obj, 0);
	//%obj.getDataBlock().updateZone(%obj, 0);
}

function TerritoryZone::onTick(%this, %zone)
{
	%zone.zNumReds = 0;
	%zone.zNumBlues = 0;
	
	for(%i = 0; %i < %zone.getNumObjects(); %i++)
	{
		%obj = %zone.getObject(%i);
		if(%obj.getType() & $TypeMasks::PlayerObjectType
		&& %obj.isCAT)
		{
            if(%zone.zProtected && %obj.getTeamId() != %zone.getTeamId())
                %obj.kill();
            else if(%obj.getTeamId() == Game.team1.teamId)
				%zone.zNumReds++;
			else if(%obj.getTeamId() == Game.team2.teamId)
				%zone.zNumBlues++;
		}
	}

	%this.updateOwner(%zone);
}

function TerritoryZone::updateOwner(%this, %zone)
{
	%numConnections = 0;
	%connectedToRed = false;
	%connectedToBlue = false;

	for(%i = 0; %i < 4; %i++)
	{
		%z = %zone.zNeighbour[%i];
		if(isObject(%z))
		{
			%numConnections++;
			if(%z.getTeamId() == 1)
				%connectedToRed = true;
			if(%z.getTeamId() == 2)
				%connectedToBlue = true;
		}
	}

	if(%zone.zNumReds > 0 && %zone.zNumBlues == 0
	&& %connectedToRed)
	{
		%this.setZoneOwner(%zone, 1);
	}
	else if(%zone.zNumBlues > 0 && %zone.zNumReds == 0
	&& %connectedToBlue)
	{
		%this.setZoneOwner(%zone, 2);
	}
	else if(%zone.zNumReds > 0 && %zone.zNumBlues > 0
	&& %connectedToRed && %connectedToBlue)
	{
		%this.setZoneOwner(%zone, 0);		
	}
	else if(%numConnections == 1)
	{
		if(%zone.getTeamId() != 1 && %connectedToRed) // blue end zone
		{
			if(%zone.zNumReds > 0)
				%this.setZoneOwner(%zone, 0);
			else if(%zone.zNumBlues > 0)
				%this.setZoneOwner(%zone, 2);
		}
		else if(%zone.getTeamId() != 2 && %connectedToBlue) // red end zone
		{
			if(%zone.zNumBlues > 0)
				%this.setZoneOwner(%zone, 0);
			else if(%zone.zNumReds > 0)
				%this.setZoneOwner(%zone, 1);
		}			
	}

	%zone.zBlocked = false;
	if(%zone.getTeamId() == 2 && %zone.zNumReds != 0)
		%zone.zBlocked = true;
	else if(%zone.getTeamId() == 1 && %zone.zNumBlues != 0)
		%zone.zBlocked = true;
   %zone.setFlicker(%zone.zBlocked ? 200 : 0);
}

function TerritoryZone::setZoneOwner(%this, %zone, %teamId)
{
	%oldTeamId = %zone.getTeamId();
	
	if(%teamId == %oldTeamId)
		return;
		
	if(%oldTeamId == 1)
		Game.team1.numTerritoryZones--;
	else if(%oldTeamId == 2)
		Game.team2.numTerritoryZones--;
  
   // Base color
   %colorF = Game.team[%teamId].color;
   
   // Flash base color
   %zone.flash(%colorF SPC "1");
   
   // First palette slot
   %mod = 50;
   if(%teamId == 0)
      %mod = 25;
   %colorI = getWord(%colorF, 0)*%mod SPC
             getWord(%colorF, 1)*%mod SPC
             getWord(%colorF, 2)*%mod SPC
             255;
   %zone.paletteColors[0] = %colorI;
   //echo(%colorF SPC "->" SPC %colorI);
   
   // Second palette slot
   %mod = 100;
   if(%teamId == 0)
      %mod = 25;
   %colorI = getWord(%colorF, 0)*%mod SPC
             getWord(%colorF, 1)*%mod SPC
             getWord(%colorF, 2)*%mod SPC
             255;
   %zone.paletteColors[1] = %colorI;
   //echo(%colorF SPC "->" SPC %colorI);

	%zone.setTeamId(%teamId);
	if(%teamId == 1)
		Game.team1.numTerritoryZones++;
	else if(%teamId == 2)
		Game.team2.numTerritoryZones++;

	for(%idx = 0; %idx < ClientGroup.getCount(); %idx++)
	{
		%client = ClientGroup.getObject(%idx);
	
		%sound = 0;

		if(%client.team == Game.team1)
		{
			if(%teamId == 1)
				%sound = ZoneAquiredSound;
			else if(%teamId == 2)
				%sound = ZoneAttackedSound;
		}
		else if(%client.team == Game.team2)
		{
			if(%teamId == 2)
				%sound = ZoneAquiredSound;
			else if(%teamId == 1)
				%sound = ZoneAttackedSound;
		}

		if(isObject(%sound))
			%client.play2D(%sound);
	}
	
	for(%i = 0; %i < %zone.getNumObjects(); %i++)
	{
		%obj = %zone.getObject(%i);
		if(%obj.getType() & $TypeMasks::ShapeBaseObjectType)
         TerritoryZones_objectUpdateZone(%obj, 0);
	}
		
	echo("Number of zones:" SPC
		Game.team1.numTerritoryZones SPC "red /" SPC
		Game.team2.numTerritoryZones SPC "blue");
		
	ETH::checkRoundEnd();
}


