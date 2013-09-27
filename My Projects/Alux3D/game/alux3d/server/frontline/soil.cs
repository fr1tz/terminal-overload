// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(SoilVolumeCollisionShape)
{
   shapeFile = "content/alux3d/release1/shapes/soil/soilpiece1-collision.dae";
};

datablock HexagonVolumeData(SoilVolume)
{
   category = "Frontline Game Mode"; // For the mission editor
   renderShapeFile[0] = "content/alux3d/release1/shapes/soil/soil.dae";
   renderShapeFile[1] = "content/alux3d/release1/shapes/soil/soilpiece1-team1.dae";
   renderShapeFile[2] = "content/alux3d/release1/shapes/soil/soilpiece1-team2.dae";
   collisionShape[0] = SoilVolumeCollisionShape;
   collisionShape[1] = SoilVolumeCollisionShape;
   collisionShape[2] = SoilVolumeCollisionShape;
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
      if(isObject(%tile.zBuildEmitter))
         %tile.zBuildEmitter.delete();
      %tile.zBuildEmitter = "";
      %tile.zChangeSet = "";
      %tile.zCompletion = 0;
      %tile.zBuildEmitter = "";
      %tile.zLastUpdateTime = 0;
      %tile.teamId = 0;
   }

	for(%idx = MissionSoilBounds.getCount()-1; %idx >= 0; %idx--)
	{
	   %volume = MissionSoilBounds.getObject(%idx);
      %volume.init();
   }
   Game.soilVolumeDirtySet.clear();
   Game.soilTileDirtySet.clear();
}

function Soil::updateAdjacents(%tile, %set)
{
   for(%side = 1; %side <= 6; %side++)
   {
      %adjacentTile = %tile.adjacent[%side];
      if(%adjacentTile $= "None")
         continue;
      if(!isObject(%adjacentTile))
         continue;
      %adjacentTile.zLastUpdateTime = getSimTime();
      Game.soilTileDirtySet.add(%adjacentTile);
   }
}

function Soil::finishTile(%tile, %teamId)
{
   echo("Finishing tile" SPC %tile.getName() SPC "(team" @ %teamId @ ")");
   if(isObject(%tile.zBuildEmitter))
      %tile.zBuildEmitter.delete();
   %tile.zBuildEmitter = "";
   %tile.teamId = %teamId;
   %tile.zCompletion = 1;
   %volume = %tile.volumeName;
   if(%volume.addHexagon(%tile.gridPos, %tile.teamId))
      Game.soilVolumeDirtySet.add(%volume);
   %pos = VectorAdd(%tile.getPosition(), "0 0 -0.4");
   createExplosion(SoilPopupExplosion, %pos, "0 0 1");
   Soil::updateAdjacents(%tile);
}

function Soil::destroyTile(%tile)
{
   if(isObject(%tile.zBuildEmitter))
      %tile.zBuildEmitter.delete();
   %tile.zBuildEmitter = "";
   %tile.teamId = 0;
   %tile.zCompletion = 0;
   %volume = %tile.volumeName;
   if(%volume.removeHexagon(%tile.gridPos))
   {
      echo("yay");
      Game.soilVolumeDirtySet.add(%volume);
   }
   //%pos = VectorAdd(%tile.getPosition(), "0 0 -0.4");
   //createExplosion(SoilPopupExplosion, %pos, "0 0 1");
   Soil::updateAdjacents(%tile);
}

function Soil::updateTile(%tile, %dt)
{
   //echo(%tile.getName() SPC %dt);
   
   if(%tile.zCompletion == 1)
      return true;

   %numAdjacents = 0;
   %numTeam1Adjacents = 0;
   %numTeam2Adjacents = 0;
   for(%side = 1; %side <= 6; %side++)
   {
      %adjacentTile = %tile.adjacent[%side];
      if(!isObject(%adjacentTile))
         continue;
      if(%adjacentTile.zCompletion != 1)
         continue;
      %numAdjacents++;
      if(%adjacentTile.teamId == 1)
         %numTeam1Adjacents++;
      if(%adjacentTile.teamId == 2)
         %numTeam2Adjacents++;
   }
   
   %emitterData = "";
   if(%numTeam1Adjacents > 0 && %numTeam2Adjacents > 0)
   {
      %tile.teamId = 0;
      %tile.zCompletion = 0;
      %emitterData = SoilBuildEmitterTeam0;
   }
   else if(%numTeam1Adjacents > 0)
   {
      if(%tile.teamId != 1)
      {
         %tile.teamId = 1;
         %tile.zCompletion = 0;
      }
      %emitterData = SoilBuildEmitterTeam1;
      %tile.zCompletion += 0.5 * %dt;
   }
   else if(%numTeam2Adjacents > 0)
   {
      if(%tile.teamId != 2)
      {
         %tile.teamId = 2;
         %tile.zCompletion = 0;
      }
      %emitterData = SoilBuildEmitterTeam2;
      %tile.zCompletion += 0.5 * %dt;
   }

   
   if(%emitterData !$= "")
   {
      if(isObject(%tile.zBuildEmitter))
      {
         //echo(%tile.zBuildEmitter.emitter SPC "->" SPC %emitterData);
         if(%tile.zBuildEmitter.emitter.getId() != %emitterData.getId())
         {
            %tile.zBuildEmitter.delete();
            %tile.zBuildEmitter = new ParticleEmitterNode()
            {
               datablock = SoilBuildEmitterNode;
               position = %tile.getPosition();
               rotation = "0 0 1 0";
               emitter = %emitterData;
               velocity = 1;
            };
            MissionCleanup.add(%tile.zBuildEmitter);
         }
      }
      else
      {
         %tile.zBuildEmitter = new ParticleEmitterNode()
         {
            datablock = SoilBuildEmitterNode;
            position = %tile.getPosition();
            rotation = "0 0 1 0";
            emitter = %emitterData;
            velocity = 1;
         };
         MissionCleanup.add(%tile.zBuildEmitter);
      }
   }
   else
   {
      if(isObject(%tile.zBuildEmitter))
         %tile.zBuildEmitter.delete();
      %tile.zBuildEmitter = "";
   }

   if(%tile.zCompletion >= 1)
   {
      Soil::finishTile(%tile, %tile.teamId);
      return true;
   }

   return false;
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

function Soil::test(%radius, %tile)
{
   if(%tile $= "")
      %tile = MissionMetaSoilTile1;

   Soil::clear();
   Soil::finishRadius(%tile, 1, %radius);
   Soil::rebuild();
}

function Soil::reset()
{
   Soil::clear();
   Soil::finishTile(MissionMetaSoilTiles.startTileTeam[1], 1);
   Soil::finishTile(MissionMetaSoilTiles.startTileTeam[2], 2);
   Soil::updateThread();
   Soil::rebuildThread();
}

function Soil::rebuild()
{
   if(Game.soilVolumeDirtySet.getCount() == 0)
      return;

   error("rebuilding...");

	for(%idx = Game.soilVolumeDirtySet.getCount()-1; %idx >= 0; %idx--)
	{
	   %volume = Game.soilVolumeDirtySet.getObject(%idx);
      %volume.rebuild();
   }
   Game.soilVolumeDirtySet.clear();
}

function Soil::update()
{
   if(Game.soilTileDirtySet.getCount() == 0)
      return;

   //error("updating...");

   %time = getSimTime();

   %count = Game.soilTileDirtySet.getCount();
   if(%count > 1)
      %count = 1;

	for(%idx = 0; %idx < %count; %idx++)
	{
	   %tile = Game.soilTileDirtySet.getObject(%idx);
      Game.soilTileDirtySet.remove(%tile);
      %delta = 0;
      if(%tile.zLastUpdateTime !$= "")
         %delta = (%time - %tile.zLastUpdateTime)/1000;
      if(!Soil::updateTile(%tile, %delta))
         Game.soilTileDirtySet.add(%tile);
      %tile.zLastUpdateTime = %time;
   }
}

function Soil::rebuildThread()
{
   if(Game.soilRebuildThread !$= "")
      cancel(Game.soilRebuildThread);
   Game.soilRebuildThread = schedule(512, Game, "Soil::rebuildThread");
   Soil::rebuild();
}

function Soil::updateThread()
{
   if(Game.soilUpdateThread !$= "")
      cancel(Game.soilUpdateThread);
   Game.soilUpdateThread = schedule(32, Game, "Soil::updateThread");
   Soil::update();
}

