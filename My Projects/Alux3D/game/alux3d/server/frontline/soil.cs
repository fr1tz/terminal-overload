// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock HexagonVolumeData(SoilVolume)
{
   category = "Frontline Game Mode"; // For the mission editor
   shapeFile = "content/alux3d/release1/shapes/soil/soil.dae";
   mode = 2;
};

datablock GridData(SoilGrid)
{
   category = "Frontline Game Mode"; // For the mission editor
   shapeFile = "core/art/shapes/octahedron.dts";
   spacing = "1.0625 0.625 0.2";
};

datablock StaticShapeData(MetaSoilTile)
{
   shapeFile = "content/alux3d/release1/shapes/soil/metasoil.dae";

   // Script fields:
   maxExpandHeight = 0.5;
   maxHeightDiff = 0.4;

   adjacentGridOffset[0] = "0 0 0";
   adjacentGridOffset[1] = "-1 1 0";
   adjacentGridOffset[2] = "0 2 0";
   adjacentGridOffset[3] = "1 1 0";
   adjacentGridOffset[4] = "1 -1 0";
   adjacentGridOffset[5] = "0 -2 0";
   adjacentGridOffset[6] = "-1 -1 0";
};

function MetaSoilTile::onAdd(%this, %obj)
{
   %obj.setupStage = 0;
   %obj.setName("MissionMetaSoilTile" @ MissionMetaSoilTiles.getCount());
   MissionMetaSoilTiles.add(%obj);
}

function Soil::clear()
{
	for(%idx = Game.unfinishedSoilTileSet.getCount()-1; %idx >= 0; %idx-- )
	{
		%unfinishedTile = Game.unfinishedSoilTileSet.getObject(%idx);
      %unfinishedTile.delete();
   }
   Game.unfinishedSoilTileSet.clear();

	for(%idx = MissionMetaSoilTiles.getCount()-1; %idx >= 0; %idx-- )
	{
		%tile = MissionMetaSoilTiles.getObject(%idx);
      %tile.zUnfinishedTile = "";
      %tile.zFinished = false;
   }

	for(%idx = MissionSoilBounds.getCount()-1; %idx >= 0; %idx--)
	{
	   %volume = MissionSoilBounds.getObject(%idx);
      %volume.clearHexagons();
      %volume.rebuild();
   }
   Game.soilVolumeDirtySet.clear();
}

function Soil::reset()
{
   Soil::clear();
   Soil::finishTile(MissionMetaSoilTiles.startTileTeam[1], 1);
   Soil::finishTile(MissionMetaSoilTiles.startTileTeam[2], 2);
   Soil::rebuildDirtyThread();
}

function Soil::buildAdjacent(%tile, %side)
{
   %adjacentTile = %tile.adjacent[%side];

   if(!isObject(%adjacentTile))
      return false;
   
   if(%adjacentTile $= "None")
      return false;
      
   if(%adjacentTile.zFinished)
      return false;
      
   if(isObject(%adjacentTile.zUnfinishedTile))
      return false;
      
   %unfinishedTile = new StaticShape()
   {
      dataBlock = UnfinishedSoilTile;
      teamId = %tile.teamId;
   };
   MissionCleanup.add(%unfinishedTile);
   %unfinishedTile.metaSoilTile = %adjacentTile;
   %unfinishedTile.setTransform(%adjacentTile.getPosition());
   %unfinishedTile.getDataBlock().startBuild(%unfinishedTile);
   
   %adjacentTile.teamId = %tile.teamId;
   %adjacentTile.zUnfinishedTile = %unfinishedTile;
   
   return true;
}

function Soil::buildAdjacents(%tile)
{
   for(%side = 1; %side <= 6; %side++)
      Soil::buildAdjacent(%tile, %side);
}

function Soil::finishTile(%tile, %teamId)
{
   echo("Finishing tile" SPC %tile.getName() SPC "(team" @ %teamId @ ")");
   if(isObject(%tile.zUnfinishedTile))
   {
      error("Deleting unfinished tile for" SPC %tile.getName());
      %tile.zUnfinishedTile.delete();
      %tile.zUnfinishedTile = "";
   }
   %tile.teamId = %teamId;
   %tile.zFinished = true;
   %volume = %tile.volumeName;
   if(%volume.addHexagon(%tile.gridPos, %tile.teamId))
      Game.soilVolumeDirtySet.add(%volume);
   schedule(0, Game, "Soil::buildAdjacents", %tile);
}

function Soil::finishRadius(%tile, %teamId, %radius)
{
   if(%radius $= "")
      %radius = 1;
   
   // Scan for existing tile.
   %pos = %tile.getPosition();
	InitContainerRadiusSearch(%pos, %radius, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.getDataBlock() == MetaSoilTile.getId())
         Soil::finishTile(%srchObj, %teamId);
	}
}

function Soil::test(%radius)
{
   Soil::clear();
   Soil::finishRadius(MissionMetaSoilTile1, 1, %radius);
   Soil::rebuildDirtyThread();
}

function Soil::rebuildDirtyThread()
{
   if(Game.soilRebuildDirtyThread !$= "")
   {
      cancel(Game.soilRebuildDirtyThread);
      Game.soilRebuildDirtyThread = "";
   }
   Game.soilRebuildDirtyThread = schedule(32, Game, "Soil::rebuildDirtyThread");

   if(Game.soilVolumeDirtySet.getCount() == 0)
      return;

	for(%idx = Game.soilVolumeDirtySet.getCount()-1; %idx >= 0; %idx--)
	{
	   %volume = Game.soilVolumeDirtySet.getObject(%idx);
      %volume.rebuild();
   }
   
   Game.soilVolumeDirtySet.clear();
}
