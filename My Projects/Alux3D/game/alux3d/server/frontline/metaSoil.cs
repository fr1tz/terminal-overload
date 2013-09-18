// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

datablock StaticShapeData(MetaSoilTile)
{
   shapeFile = "content/alux3d/release1/shapes/soil/metasoil.dae";

   // Script fields:
   maxExpandHeight = 0.5;
   maxHeightDiff = 0.4;
   
   adjacentGridOffset[0] = "0 0 0";
   adjacentGridOffset[1] = "-1 0 0";
   adjacentGridOffset[2] = "0 1 0";
   adjacentGridOffset[3] = "1 0 0";
   adjacentGridOffset[4] = "1 -1 0";
   adjacentGridOffset[5] = "0 -1 0";
   adjacentGridOffset[6] = "-1 -1 0";
};

function MetaSoilTile::onAdd(%this, %obj)
{
   %obj.setupStage = 0;
   %obj.setName("MissionMetaSoilTile" @ MissionMetaSoilTiles.getCount());
   MissionMetaSoilTiles.add(%obj);
}

