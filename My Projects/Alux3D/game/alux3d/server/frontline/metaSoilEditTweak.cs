// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

// Called by script
function MetaSoilTile::tweak(%this, %obj)
{
   // Gather some info about our adjacents.
   %obj.numAdjacents = 0;
   for(%side = 1; %side <= 6; %side++)
   {
      %adjacent = %obj.adjacent[%side];
      if(!isObject(%adjacent))
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


