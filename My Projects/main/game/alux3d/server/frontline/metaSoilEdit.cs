// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metasoil.txt for documentation

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
   if(!isObject(MissionSoilGrid))
   {
      error("Missing MissionSoilGrid!");
      return;
   }
   
	for(%idx = 0; %idx < MissionSoilBounds.getCount(); %idx++)
	{
		%obj = MissionSoilBounds.getObject(%idx);
      if(%obj.getDataBlock() == SoilVolume.getId())
         %obj.setName("MissionSoilVolume" @ %idx);
   }

   if(!isObject(MissionMetaSoilTiles))
   {
      // Note: The MissionMetaSoilTiles is part of the mission group!
      new SimGroup(MissionMetaSoilTiles);
      MissionGroup.add(MissionMetaSoilTiles);
   }
   
   MetaSoil::clear();
   
   %tile = new StaticMetaShape() {
      dataBlock = MetaSoilTile;
   };
   %tile.isRenderEnabled = false;
   %tile.gridPos = "0 0 0";
   %tile.setTransform(MissionSoilGrid.gridToWorld(%tile.gridPos));
   
   if(!MetaSoil::initWorkerSet("setup"))
      return;
   MetaSoil::workerSet().add(%tile);
   MetaSoil::workerThread();
}

function MetaSoil::tweak()
{
   if(!MetaSoil::initWorkerSet("tweak"))
      return;
	for(%idx = 0; %idx < MissionMetaSoilTiles.getCount(); %idx++)
	{
		%tile = MissionMetaSoilTiles.getObject(%idx);
      MetaSoil::workerSet().add(%tile);
   }
   MetaSoil::workerThread();
}
