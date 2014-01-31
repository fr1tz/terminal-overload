// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(UnfinishedSoilTile)
{
   shapeFile = "content/fr1tz/oldshapes/soil/unfinished1.dae";
   emap = true;
   //dynamicType = $TypeMasks::NextFreeObjectType;
};

// Called by script
function UnfinishedSoilTile::damage(%this, %obj, %source, %position, %amount, %damageType)
{
   //%obj.schedule(0, "delete");
}

function UnfinishedSoilTile::onAdd(%this, %obj)
{
   Game.unfinishedSoilTileSet.add(%obj);
   //%obj.expand = false;
   //%this.tickThread(%obj);
}

function UnfinishedSoilTile::onRemove(%this, %obj)
{
   if(%obj.zBuildThread !$= "")
      cancel(%obj.zBuildThread);
}

function UnfinishedSoilTile::startBuild(%this, %obj)
{
   if(!isObject(%obj)) return;
   %obj.startFade(5000, 0, false);
   %obj.zBuildThread = %this.schedule(5000, "buildFinished", %obj);
}

function UnfinishedSoilTile::buildFinished(%this, %obj)
{
   if(!isObject(%obj)) return;
   %tile = %obj.metaSoilTile;
   if(isObject(%tile))
      Soil::finishTile(%tile, %tile.teamId);
}

function UnfinishedSoilTile::tickThread(%this, %obj)
{
   if(!isObject(%obj)) return;
   if(%obj.zTickThread !$= "")
   {
      cancel(%obj.zTickThread);
      %obj.zTickThread = "";
   }
   %obj.zTickThread = %this.schedule(32, "tickThread", %obj);
}
