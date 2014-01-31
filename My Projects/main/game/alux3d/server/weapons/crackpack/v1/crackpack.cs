// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(WpnCrackpackStaticShape)
{
   shapeFile = "content/fr1tz/alux1/shapes/crackpack/p1/shape.dae";
   
   maxDamage = 100;
};

// Called by engine whenever the object's damage level changes
function WpnCrackpackStaticShape::onDamage(%this, %obj, %delta)
{
	%totalDamage = %obj.getDamageLevel();
	if(%totalDamage >= %this.maxDamage)
	{
      createExplosion(WpnCrackpackDestroyedExplosion, %obj.getPosition(), "0 0 1");
      Game.onUnitDestroyed(%obj);
      %obj.schedule(0, "delete");
	}
}

function WpnCrackpackStaticShape::activate(%this, %obj)
{
   if(!isObject(%obj))
      return;

   %pos = %obj.getPosition();
   %radius = 4;
   %enemyShapeNr = "";
   
   %destroyedSet = new SimSet();

	%targets = new SimSet();
	InitContainerRadiusSearch(%pos, %radius, $TypeMasks::StaticObjectType);
	while((%targetObject = containerSearchNext()) != 0)
		%targets.add(%targetObject);
 	for(%idx = %targets.getCount()-1; %idx >= 0; %idx-- )
	{
		%targetObject = %targets.getObject(%idx);

      if(%targetObject.getClassName() $= "HexagonVolume")
         %targetObject.getDataBlock().destroy(%targetObject, %pos, %radius, %obj.teamId, %destroyedSet);

   }
	%targets.delete();

   serverPlay3D(WpnCrackpackCrackSound, %pos);
   createExplosion(WpnCrackpackActivationExplosion, %pos, "0 0 1");
   Game.onUnitDestroyed(%obj);
   %obj.schedule(0, "delete");
   
   %msg = "";
 	for(%idx = %destroyedSet.getCount()-1; %idx >= 0; %idx-- )
	{
		%s = %destroyedSet.getObject(%idx);
      %msg = %msg @ %s.gridPos @ " " @ %s.amount @ " ";
      %s.delete();
      
      if(strlen(%msg) > 128 || %idx == 0)
      {
   	   for(%i = 0; %i < ClientGroup.getCount(); %i++)
	      {
   	   	%client = ClientGroup.getObject(%i);
   	   	if(%client.ingame $= "")
   		   	continue;
         
            %grid = %client.getGhostID(MissionSoilGrid.getId());
            %datablock = WpnCrackpackActivationExplosion.getId();
      
            commandToClient(%client, 'GridCreateExplosions',
               %grid, %datablock, %msg);
   	   }
         %msg = "";
      }
   }
   %destroyedSet.delete();
}
