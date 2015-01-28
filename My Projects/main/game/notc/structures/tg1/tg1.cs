// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(TerritoryGenerator1)
{
   category = "Structures";
   shapeFile = "core/art/shapes/octahedron.dts";
};

function TerritoryGenerator1::create(%this)
{
   %obj = new StaticMetaShape()
   {
      dataBlock = %this;
   };
   return %obj;
}

function TerritoryGenerator1::onAdd(%this, %obj)
{
   //echo("TerritoryGenerator1::onAdd()");
   %obj.zLastUpdatePosition = "";
   %obj.zUpdateAssetsThread = "";
   %obj.zTower = "";
   %obj.zBeam = "";
   %obj.zZone = "";
   %this.updateAssetsThread(%obj);
}

function TerritoryGenerator1::onRemove(%this, %obj)
{
   //echo("TerritoryGenerator1::onRemove()");
   %this.removeAssets(%obj);
}

function TerritoryGenerator1::removeAssets(%this, %obj)
{
   //echo("TerritoryGenerator1::removeAssets()");

   if(isObject(%obj.zTower))
      %obj.zTower.delete();
      
   if(isObject(%obj.zBeam))
      %obj.zBeam.delete();

   if(isObject(%obj.zZone))
      %obj.zZone.delete();
}

function TerritoryGenerator1::updateAssetsThread(%this, %obj)
{
   //echo("TerritoryGenerator1::updateAssetsThread()");

   if(!isObject(%obj))
      return;

   if(%obj.zUpdateAssetsThread !$= "")
   {
      cancel(%obj.zUpdateAssetsThread);
      %obj.zUpdateAssetsThread = "";
   }
   
   %obj.zUpdateAssetsThread = %this.schedule(1000, "updateAssetsThread", %obj);
   
   %pos = %obj.getPosition();

   if(%pos $= %obj.zLastUpdatePosition)
      return;
      
   %this.removeAssets(%obj);
   
   %obj.zTower = new TSStatic() {
      shapeName = "content/xa/notc/core/shapes/tg1/p1/shape.dae";
      playAmbient = "1";
      meshCulling = "0";
      originSort = "0";
      collisionType = "Visible Mesh";
      decalType = "Visible Mesh";
      allowPlayerStep = "1";
      renderNormals = "0";
      forceDetail = "-1";
      position = %pos;
      rotation = "1 0 0 0";
      scale = "1 1 1";
      canSave = "1";
      canSaveDynamicFields = "1";
   };
   
   %obj.zBeam = new TSStatic() {
      shapeName = "content/xa/notc/core/shapes/tg1/p1/beam.dae";
      playAmbient = "1";
      meshCulling = "0";
      originSort = "0";
      collisionType = "Collision Mesh";
      decalType = "Collision Mesh";
      allowPlayerStep = "1";
      renderNormals = "0";
      forceDetail = "-1";
      position = %pos;
      rotation = "1 0 0 0";
      scale = "0.25 0.25 5000";
      canSave = "1";
      canSaveDynamicFields = "1";
   };
   
   %obj.zZone = new TacticalZone() {
      dataBlock = "TerritoryZone";
      client = "-1";
      teamId = %obj.teamId;
      position = %pos;
      rotation = "0 0 1 0";
      scale = "22 22 32";
      canSave = "1";
      canSaveDynamicFields = "1";
      showOnMinimap = "1";
      renderInteriors = "0";
      renderTerrain = "1";
      renderTerrainGrid = "1";
      borderBottom = "2";
      borderLeft = "2";
      borderBack = "2";
      borderFront = "2";
      borderRight = "2";
      borderTop = "2";
   };
   
   %obj.zZone.zGenerator = %obj;
   %obj.zZone.zUnblockable = true;
   %obj.zZone.getDataBlock().setZoneOwner(%obj.zZone, %obj.getTeamId());
   copyPalette(%obj.zZone, %obj.zTower);
   copyPalette(%obj.zZone, %obj.zBeam);

   %obj.zLastUpdatePosition = %obj.getPosition();
}

function TerritoryGenerator1::onPaletteChange(%this, %obj, %slot, %colorI)
{
   //echo("TerritoryGenerator1::onPaletteChange()");
   changePalette(%obj.zTower, %slot, %colorI);
   changePalette(%obj.zBeam, %slot, %colorI);
   changePalette(%obj.zZone, %slot, %colorI);
   if(%slot == 0)
      changePalette(%obj.zZone, 1, %colorI);
}
