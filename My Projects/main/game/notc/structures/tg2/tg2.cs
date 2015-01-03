// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(TerritoryGenerator2)
{
   category = "Structures";
   shapeFile = "content/xa/notc/core/shapes/tg2/p1/core.dae";
   maxDamage = 1000;
};

datablock StaticShapeData(TerritoryGenerator2_Pins)
{
   shapeFile = "content/xa/notc/core/shapes/tg2/p1/pins.dae";
   ignoreDamage = true;
};

function TerritoryGenerator2::create(%this)
{
   %obj = new StaticShape()
   {
      dataBlock = %this;
   };
   return %obj;
}

function TerritoryGenerator2::onAdd(%this, %obj)
{
   echo("TerritoryGenerator2::onAdd()");
   %obj.setRepairRate(1);
   %obj.zLastUpdatePosition = "";
   %obj.zUpdateAssetsThread = "";
   %obj.zChip = "";
   %obj.zPins = "";
   %obj.zZone = "";
   %obj.zBeam = "";
   %this.updateAssetsThread(%obj);
}

function TerritoryGenerator2::onRemove(%this, %obj)
{
   //echo("TerritoryGenerator2::onRemove()");
   %this.removeAssets(%obj);
}

function TerritoryGenerator2::onDamage(%this, %obj, %delta)
{
   //echo("TerritoryGenerator2::onDamage()");
   Parent::onDamage(%this, %obj, %delta);
   %health = 1 - %obj.getDamagePercent();
   %scale = 6 + 24*%health;
   %obj.zZone.setScale(%scale SPC %scale SPC "32");
   if(%health == 0)
   {
      %this.removeAssets(%obj);
      %obj.schedule(0, "delete");
      
      // Explosion
      %exp = ItemG1LauncherProjectileExplosion;
      %pos = %obj.getPosition();
      %norm = "0 0 1";
      %colorI = %obj.paletteColors[0];
      createExplosion(%exp, %pos, %norm, %colorI);
   }
}

function TerritoryGenerator2::removeAssets(%this, %obj)
{
   //echo("TerritoryGenerator2::removeAssets()");

   if(isObject(%obj.zChip))
      %obj.zChip.delete();
      
   if(isObject(%obj.zPins))
      %obj.zPins.delete();

   if(isObject(%obj.zZone))
      %obj.zZone.delete();
      
   if(isObject(%obj.zBeam))
      %obj.zBeam.delete();
}

function TerritoryGenerator2::updateAssetsThread(%this, %obj)
{
   //echo("TerritoryGenerator2::updateAssetsThread()");

   if(!isObject(%obj))
      return;

   if(%obj.zUpdateAssetsThread !$= "")
   {
      cancel(%obj.zUpdateAssetsThread);
      %obj.zUpdateAssetsThread = "";
   }
   
   %obj.zUpdateAssetsThread = %this.schedule(1000, "updateAssetsThread", %obj);
   
   %pos = %obj.getPosition();
   
   if(%obj.zLastUpdatePosition !$= "" && %pos $= %obj.zLastUpdatePosition)
      return;
      
   %this.removeAssets(%obj);
   
   %obj.zChip = new TSStatic() {
      shapeName = "content/xa/notc/core/shapes/tg2/p1/chip.dae";
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
      shapeName = "content/xa/notc/core/shapes/tg2/p1/beam.dae";
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
   
   %obj.zPins = new StaticShape()
   {
      dataBlock = TerritoryGenerator2_Pins;
      position = %pos;
   };
   
   %obj.zZone = new TacticalZone() {
      dataBlock = "TerritoryZone";
      client = "-1";
      teamId = 0;
      position = %pos;
      rotation = "0 0 1 0";
      scale = "32 32 32";
      canSave = "1";
      canSaveDynamicFields = "1";
      showOnMinimap = "1";
      renderInteriors = "0";
      renderTerrain = "1";
      renderTerrainGrid = "1";
      borderBottom = "1";
      borderLeft = "1";
      borderBack = "1";
      borderFront = "1";
      borderRight = "1";
      borderTop = "1";
   };
   
   %obj.zZone.zGenerator = %obj;
   %obj.zZone.getDataBlock().setZoneOwner(%obj.zZone, %obj.getTeamId());
   copyPalette(%obj.zZone, %obj);
   copyPalette(%obj.zZone, %obj.zChip);
   copyPalette(%obj.zZone, %obj.zPins);
   copyPalette(%obj.zZone, %obj.zBeam);

   %obj.zLastUpdatePosition = %obj.getPosition();
}

function TerritoryGenerator2::onZoneFlicker(%this, %obj, %flickerTime)
{
   %obj.zPins.setFlickerTime(%flickerTime);
}

