// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

// Called by script
function MetaSoilTile::tweak(%this, %obj)
{
   // Snap to soil grid.
   %oldPos = %obj.getPosition();
   %obj.gridPos = MissionSoilGrid.worldToGrid(%obj.getPosition());
   %obj.setTransform(MissionSoilGrid.gridToWorld(%obj.gridPos));
   %newPos = %obj.getPosition();
   echo(%oldPos SPC "->" SPC %newPos);
   
   // Find out to which volume we belong.
   %obj.volumeName = "";
	InitContainerRadiusSearch(%obj.getPosition(), 0.1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;
      if(%srchObj.getDataBlock() == SoilVolume.getId())
      {
         %obj.volumeName = %srchObj.getName();
         break;
      }
	}
   if(%obj.volumeName $= "")
   {
      error("MetaSoilTile::tweak(): Tile ID" SPC %obj.getId() SPC "not "
          @ "inside a soil volume!");
   }
   
   // Gather some info about our adjacents.
   %obj.numAdjacents = 0;
   for(%side = 1; %side <= 6; %side++)
   {
      %adjacent = %obj.adjacent[%side];
      if(%adjacent $= "None")
         continue;
         
      %obj.numAdjacents++;

      %z1 = getWord(%obj.getPosition(), 2);
      %z2 = getWord(%adjacent.getPosition(), 2);
      %altDiff = mAbs(%z1 - %z2);
      
      %altDiffTotal += %altDiff;
      if(%altDiff < %altDiffMin || %altDiffMin $= "")
         %altDiffMin = %altDiff;
      if(%altDiffMax > %altDiffMax || %altDiffMax $= "")
         %altDiffMax = %altDiff;
   }
   %obj.altDiffTotal = %altDiffTotal;
   %obj.altDiffMin = %altDiffMin;
   %obj.altDiffMax = %altDiffMax;
   
   return true;
}


