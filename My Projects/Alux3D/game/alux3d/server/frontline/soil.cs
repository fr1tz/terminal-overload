// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(SoilTile)
{
   shapeFile = "content/alux3d/release1/shapes/soil/soil.dae";
   emap = true;
};

// Called by script
function SoilTile::damage(%this, %obj, %source, %position, %amount, %damageType)
{
   %obj.schedule(0, "delete");
}

function SoilTile::onAdd(%this, %obj)
{
   Game.soilSet.add(%obj);
   //%obj.expand = false;
   //%this.tickThread(%obj);
}



function Soil::updateNeighbours(%this, %obj)
{
   for(%i = 0; %i < 6; %i++)
      %obj.zNeighbour[%i] = "";
      
   %pos = %obj.getWorldBoxCenter();
   %posx = getWord(%pos, 0);
   %posy = getWord(%pos, 1);
   %radius = 3;
   %typeMask =  $TypeMasks::StaticObjectType;
	InitContainerRadiusSearch(%pos, %radius, %typeMask);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(%srchObj == %obj)
         continue;
         
      if(!%srchObj.isMethod("getDataBlock"))
         continue;
         
      if(%srchObj.getDataBlock() != %this.getId())
         continue;

      %nx = getWord(%srchObj.getPosition(), 0);
      %ny = getWord(%srchObj.getPosition(), 1);
      
      if(%ny > %posy)
      {
         if(mAbs(%nx - %posx) < 1)
            %n = 1;
         else if(%nx > %posx)
            %n = 2;
         else
            %n = 0;
      }
      else
      {
         if(mAbs(%nx - %posx) < 1)
            %n = 4;
         else if(%nx > %posx)
            %n = 3;
         else
            %n = 5;
      }
      
      %obj.zNeighbour[%n] = %srchObj;
	}
}

function Soil::findMinHeight(%this, %obj, %top, %hexheight)
{
   // Find min. height for neighbour.
   // (Brought to you by the Close Enough (tm)
   //  dept. of Algorithms -- fr1tz)
   
   %topx = getWord(%top, 0);
   %topy = getWord(%top, 1);
   %topz = getWord(%top, 2);
   %minHeight = "none";
   
   // Temporarily hide existing soil so it doesn't mess with the raycasting.
   %hidden = new SimSet();
	InitContainerRadiusSearch(%top, 6, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.getDataBlock() != %this.getId())
         continue;
         
      %srchObj.setHidden(true);
      %hidden.add(%srchObj);
	}

   for(%y = -1.25; %y <= 1.25; %y += 0.25)
   {
      for(%x = -1.5; %x <= 1.5; %x += 0.25)
      {
         // Try to see if something is blocking.
         %startPos = %top;
         %endPos = %topx+%x SPC %topy+%y SPC %topz;
         %col = ContainerRayCast(%startPos, %endPos, $TypeMasks::StaticObjectType);
         %colObj = getWord(%col, 0);
         if(%colObj != 0)
         {
            error("blocked");
            %minHeight = "none";
            break;
         }
      
         // Cast to ground.
         %typeMask = $TypeMasks::TerrainObjectType
                   | $TypeMasks::StaticObjectType;
         %startPos = %topx+%x SPC %topy+%y SPC %topz+%hexheight;
         %endPos = setWord(%startPos, 2, %topz-%hexheight);
         %col = ContainerRayCast(%startPos, %endPos, %typeMask);
         %colObj = getWord(%col, 0);
         if(%colObj == 0)
         {
            error("missing ground");
            %minHeight = "none";
            break;
         }
         %colZ = getWord(%col, 3);
         if(%colZ > %topz+%this.maxHeightDiff)
         {
            error("ground to high:" SPC %colZ SPC ">" SPC %topz SPC "-0.1");
            %minHeight = "none";
            break;
         }
         if(%colZ > %minHeight || %minHeight $= "none")
            %minHeight = %colZ;
      }
      if(%minHeight $= "none")
         break;
   }
   
   // Unhide hidden soil.
	for(%idx = %hidden.getCount()-1; %idx >= 0; %idx-- )
	{
		%soil = %hidden.getObject(%idx);
      %soil.setHidden(false);
   }
   %hidden.delete();

   return %minHeight;
}

function Soil::createNeighbour(%this, %obj, %index)
{
   %offset[0] = "-2.125 1.25 0";
   %offset[1] = "0 2.5 0";
   %offset[2] = "2.125 1.25 0";
   %offset[3] = "2.125 -1.25 0";
   %offset[4] = "0 -2.5 0";
   %offset[5] = "-2.125 -1.25 0";
   
   %hexheight = getWord(%obj.getObjectBox(),5) - getWord(%obj.getObjectBox(),2);
   
   %topx = getWord(%obj.getWorldBoxCenter(),0) + getWord(%offset[%index],0);
   %topy = getWord(%obj.getWorldBoxCenter(),1) + getWord(%offset[%index],1);
   %topz = getWord(%obj.getWorldBoxCenter(),2) + %hexheight/2;
   
   %minHeight = %obj.zNeighbourMinHeight[%index];
   if(%minHeight $= "")
   {
      %top = %topx SPC %topy SPC %topz;
      %minHeight = %this.findMinHeight(%obj, %top, %hexheight);
      %obj.zNeighbourMinHeight[%index] = %minHeight;
   }
   
   if(%minHeight $= "none")
      return -1;

   %pos = %topx SPC %topy SPC %minHeight+0.1;

   %neighbour = new StaticShape()
   {
      dataBlock = Soil;
   };
   MissionCleanup.add(%neighbour);

   //%neighbour.setTransform(%obj.getTransform());
   %neighbour.setTransform(%pos);



   %neighbour.startFade(2000, 0, false);

   return %neighbour;
      
   
   //%pos = VectorAdd(%obj.getTransform(), %offset[%index]);
   
   %blocked = false;
   %radius = 1;
   %typeMask = $TypeMasks::TerrainObjectType
             | $TypeMasks::InteriorObjectType
             | $TypeMasks::StaticObjectType;
	InitContainerRadiusSearch(%pos, %radius, %typeMask);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(%srchObj == %obj)
         continue;
      if(%srchObj.getClassName() $= "Sun")
         continue;
      if(%srchObj.getClassName() $= "WaterPlane")
         continue;
      if(%srchObj.getType() & $TypeMasks::TerrainObjectType)
      {
         %haveSurface = true;
         continue;
      }

      
      echo(%srchObj.getClassName());
      %blocked = true;
   }
   
   error(%haveSurface SPC %blocked);
   
   if(!%haveSurface || %blocked)
      return "";
   
   %neighbour = new StaticShape()
   {
      dataBlock = Soil;
   };
   MissionCleanup.add(%neighbour);

   %neighbour.setTransform(%obj.getTransform());
   %neighbour.setTransform(%pos);


   
   %neighbour.startFade(2000, 0, false);
   
   return %neighbour;
}

function Soil::tickThread(%this, %obj)
{
   if(!isObject(%obj))
      return;
   if(%obj.zTickThread !$= "")
   {
      cancel(%obj.zTickThread);
      %obj.zTickThread = "";
   }
   %obj.zTickThread = %this.schedule(2000, "tickThread", %obj);
   
   //return;
   
   // Setup
   if(%obj.age $= "") %obj.age = 0;
   if(%obj.expand $= "") %obj.expand = false;
   
   %obj.age++;
   if(%obj.age > 1)
      %obj.expand = true;
   
   if(!%obj.expand)
      return;

   // Check if we've lost a neighbour
   %updateNeighbours = true;
   for(%i = 0; %i < 6; %i++)
   {
      %neighbour = %obj.zNeighbour[%i];
      if(%neighbour == -1)
         continue; // there can never be a neighbour there
      if(!isObject(%neighbour))
      {
         %updateNeighbours = true;
         break;
      }
   }
   if(%updateNeighbours)
      %this.updateNeighbours(%obj);
      
   // Check if we can create a new neighbour
   for(%i = 0; %i < 6; %i++)
   {
      %neighbour = %obj.zNeighbour[%i];
      if(%neighbour $= "")
         %obj.zNeighbour[%i] = %this.createNeighbour(%obj, %i);
   }
}

function soiltile(%metasoiltile)
{
   if(!isObject(Game.soilSet))
      Game.soilSet = new SimSet(); // All pieces
      
   %tile = new StaticShape()
   {
      dataBlock = SoilTile;
   };
   MissionCleanup.add(%tile);
   %tile.metaSoilTile = %metasoiltile;
   %pos = VectorAdd(%metasoiltile.getPosition(), "0 0 1.0");
   %tile.setTransform(%pos);
   %metasoiltile.soilPiece = %tile;
}

function Soil::clear()
{
	for(%idx = Game.soilSet.getCount()-1; %idx >= 0; %idx-- )
	{
		%tile = Game.soilSet.getObject(%idx);
      %tile.delete();
   }
}

function Soil::test(%radius)
{
   Soil::clear();
   
   %pos = MissionMetaSoilTile1.getPosition();
   if(%radius $= "")
      %radius = 5;
   
   // Scan for existing tile.
	InitContainerRadiusSearch(%pos, %radius, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.getDataBlock() == MetaSoilTile.getId())
      {
         soiltile(%srchObj);
      }
	}
   
}
