// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

// Called by script
function MetaSoilTile::setup(%this, %obj)
{
   //if(!%obj.expand)
   //   return;

   if(%obj.setupStage < 7)
   {
      %side = %obj.setupStage;
      while(%obj.groundElevation[%side] !$= "")
         %side++;
      %obj.groundElevation[%side] = %this.computeGroundElevation(%obj, %side);
      %obj.setupStage = %side;
      return false;
   }

   // Adjust own height to ground elevation.
   if(%obj.groundElevation[0] $= "none")
   {
      error("MetaSoilTile::setup(): Tile ID" SPC %obj.getId() SPC "created "
          @ "in invalid position. Aborting!");
      return true;
   }
   //%newpos = setWord(%obj.getPosition(), 2, %obj.groundElevation[0]+0.1);
   //%obj.setTransform(%newpos);

   // Create adjacent tiles.
   for(%side = 1; %side <= 6; %side++)
   {
      if(%obj.adjacent[%side] $= "")
         %obj.adjacent[%side] = %this.createAdjacent(%obj, %side);
   }

   // Link adjacent tiles together & copy already available info
   // about ground elevation.
   if(isObject(%obj.adjacent[1]))
   {
      %obj.adjacent[1].adjacent[3] = %obj.adjacent[2];
      %obj.adjacent[1].adjacent[4] = %obj;
      %obj.adjacent[1].adjacent[5] = %obj.adjacent[6];
      %obj.adjacent[1].groundElevation[3] = %obj.groundElevation[2];
      %obj.adjacent[1].groundElevation[4] = %obj.groundElevation[0];
      %obj.adjacent[1].groundElevation[5] = %obj.groundElevation[6];
      %obj.adjacent[1].groundElevation[0] = %obj.groundElevation[1];
   }
   if(isObject(%obj.adjacent[2]))
   {
      %obj.adjacent[2].adjacent[6] = %obj.adjacent[1];
      %obj.adjacent[2].adjacent[5] = %obj;
      %obj.adjacent[2].adjacent[4] = %obj.adjacent[3];
      %obj.adjacent[2].groundElevation[6] = %obj.groundElevation[1];
      %obj.adjacent[2].groundElevation[5] = %obj.groundElevation[0];
      %obj.adjacent[2].groundElevation[4] = %obj.groundElevation[3];
      %obj.adjacent[2].groundElevation[0] = %obj.groundElevation[2];
   }
   if(isObject(%obj.adjacent[3]))
   {
      %obj.adjacent[3].adjacent[1] = %obj.adjacent[2];
      %obj.adjacent[3].adjacent[6] = %obj;
      %obj.adjacent[3].adjacent[5] = %obj.adjacent[4];
      %obj.adjacent[3].groundElevation[1] = %obj.groundElevation[2];
      %obj.adjacent[3].groundElevation[6] = %obj.groundElevation[0];
      %obj.adjacent[3].groundElevation[5] = %obj.groundElevation[4];
      %obj.adjacent[3].groundElevation[0] = %obj.groundElevation[3];
   }
   if(isObject(%obj.adjacent[4]))
   {
      %obj.adjacent[4].adjacent[2] = %obj.adjacent[3];
      %obj.adjacent[4].adjacent[1] = %obj;
      %obj.adjacent[4].adjacent[6] = %obj.adjacent[5];
      %obj.adjacent[4].groundElevation[2] = %obj.groundElevation[3];
      %obj.adjacent[4].groundElevation[1] = %obj.groundElevation[0];
      %obj.adjacent[4].groundElevation[6] = %obj.groundElevation[5];
      %obj.adjacent[4].groundElevation[0] = %obj.groundElevation[4];
   }
   if(isObject(%obj.adjacent[5]))
   {
      %obj.adjacent[5].adjacent[1] = %obj.adjacent[6];
      %obj.adjacent[5].adjacent[2] = %obj;
      %obj.adjacent[5].adjacent[3] = %obj.adjacent[4];
      %obj.adjacent[5].groundElevation[1] = %obj.groundElevation[6];
      %obj.adjacent[5].groundElevation[2] = %obj.groundElevation[0];
      %obj.adjacent[5].groundElevation[3] = %obj.groundElevation[4];
      %obj.adjacent[5].groundElevation[0] = %obj.groundElevation[5];
   }
   if(isObject(%obj.adjacent[6]))
   {
      %obj.adjacent[6].adjacent[2] = %obj.adjacent[1];
      %obj.adjacent[6].adjacent[3] = %obj;
      %obj.adjacent[6].adjacent[4] = %obj.adjacent[5];
      %obj.adjacent[6].groundElevation[2] = %obj.groundElevation[1];
      %obj.adjacent[6].groundElevation[3] = %obj.groundElevation[0];
      %obj.adjacent[6].groundElevation[4] = %obj.groundElevation[5];
      %obj.adjacent[6].groundElevation[0] = %obj.groundElevation[6];
   }

   return true; // Done
}


// Called by script
function MetaSoilTile::computeGroundElevation(%this, %obj, %side)
{
   // (Brought to you by the Close Enough(tm)
   //  dept. of Algorithms -- fr1tz)
   
   %topx = getWord(%obj.getWorldBoxCenter(),0) + getWord(%this.adjacentOffset[%side],0);
   %topy = getWord(%obj.getWorldBoxCenter(),1) + getWord(%this.adjacentOffset[%side],1);
   %topz = getWord(%obj.getWorldBoxCenter(),2);
   %top = %topx SPC %topy SPC %topz;
   
   %elevation = "none";
   for(%y = -0.625; %y <= 0.625; %y += 0.625)
   {
      for(%x = -0.75; %x <= 0.75; %x += 0.75)
      {
         // Try to see if something is blocking.
         %startPos = %topx+%x SPC %topy+%y SPC %topz+%this.maxExpandHeight;
         %endPos = %topx SPC %topy SPC %topz+%this.maxExpandHeight;
         %col = ContainerRayCast(%startPos, %endPos, $TypeMasks::StaticObjectType);
         %colObj = getWord(%col, 0);
         if(%colObj != 0)
         {
            error("blocked");
            return "none";
         }

         // Cast to ground.
         %endPos = setWord(%startPos, 2, %topz-%this.maxExpandHeight*2);
         %col = ContainerRayCast(%startPos, %endPos, $TypeMasks::StaticObjectType);
         %colObj = getWord(%col, 0);
         if(%colObj == 0)
         {
            error("missing ground");
            return "none";
         }
         %colZ = getWord(%col, 3);
         if(%colZ > %topz+%this.maxExpandHeight - 0.05)
         {
            error("ground to high:" SPC %colZ SPC ">" SPC %topz SPC "- 0.05");
            return "none";
         }
         if(%colZ > %elevation || %elevation $= "none")
            %elevation = %colZ;
      }
   }

   return %elevation;
}

// Called by script
function MetaSoilTile::createAdjacent(%this, %obj, %side)
{
   if(%obj.groundElevation[%side] $= "none")
      return "-1";
      
   %x = getWord(%obj.getWorldBoxCenter(),0) + getWord(%this.adjacentOffset[%side],0);
   %y = getWord(%obj.getWorldBoxCenter(),1) + getWord(%this.adjacentOffset[%side],1);
   %z = %obj.groundElevation[%side];
   %pos = %x SPC %y SPC %z;

   // Scan for existing tile.
	InitContainerRadiusSearch(%pos, 0.1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(%srchObj == %obj)
      {
         error("MetaSoilTile::createAdjacent(): Tile ID" SPC %obj.getId()
               SPC "found itself. This should not happen.");
         continue;
      }

      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.getDataBlock() == %this.getId())
      {
         echo("found existing tile");
         return %srchObj;
      }
	}

   %tile = new StaticShape() {
      dataBlock = MetaSoilTile;
   };
   %tile.isRenderEnabled = false;
   %tile.setTransform(%pos);
   MetaSoil::workerSet().add(%tile);
   
   return %tile;
}

