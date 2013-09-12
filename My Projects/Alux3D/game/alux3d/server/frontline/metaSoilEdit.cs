// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metasoil.txt for documentation

datablock MissionMarkerData(MetaSoilRootMarker)
{
   category = "Frontline Game Mode";
   shapeFile = "core/art/shapes/octahedron.dts";
};

function MetaSoil::clear()
{
	for(%idx = MissionMetaSoilTiles.getCount()-1; %idx >= 0; %idx-- )
	{
		%tile = MissionMetaSoilTiles.getObject(%idx);
      %tile.delete();
   }
}

function MetaSoil::setup()
{
   if(!isObject(MetaSoilRoot))
   {
      error("Missing MetaSoilRoot!");
      return;
   }

   if(!isObject(MissionMetaSoilTiles))
   {
      // Note: The MissionMetaSoilTiles is part of the mission group!
      new SimGroup(MissionMetaSoilTiles);
      MissionGroup.add(MissionMetaSoilTiles);
   }
   
   MetaSoil::clear();
   
   %tile = new StaticShape() {
      dataBlock = MetaSoilTile;
   };
   %tile.isRenderEnabled = false;
   %tile.setTransform(MetaSoilRoot.getPosition());
   
   if(!MetaSoil::initWorkerSet("setup"))
      return;
   MetaSoil::workerSet().add(%tile);
   MetaSoil::workerThread();
}

function MetaSoil::tweak()
{
   return;
   MetaSoil::initWorkerSet("tweak");
	for(%idx = 0; %idx < MissionMetaSoilTiles.getCount(); %idx++)
	{
		%tile = MissionMetaSoilTiles.getObject(%idx);
      MetaSoil::workerSet().add(%tile);
   }
   MetaSoil::workerThread();
}
