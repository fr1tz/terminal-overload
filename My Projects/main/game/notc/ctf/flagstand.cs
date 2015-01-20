// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(ctfFlagStand)
{
   category = "CTF";
   shapeFile = "content/xa/notc/core/shapes/flagstand/p1/shape.dae";
   ignoreDamage = true;
};

function ctfFlagStand::create(%this)
{
   %obj = new StaticShape()
   {
      dataBlock = %this;
   };
   return %obj;
}

function ctfFlagStand::onAdd(%this, %obj)
{
   //echo("ctfFlagStand::onAdd()");
   Parent::onAdd(%this, %obj);
   
   %obj.zShapeBaseHudInfo.setDatasetType(0, $HudInfoDatasetType::TeamID);
   %obj.zShapeBaseHudInfo.setDatasetIntField(0, %obj.getTeamId());
   %obj.zShapeBaseHudInfo.setDatasetBoolField(0, true);
   %obj.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %obj.zShapeBaseHudInfo.setDatasetIntField(2, 129);
   
   %obj.zFlag = new Item()
   {
      dataBlock = ctfFlag;
      static = false;
      rotate = false;
      teamId = %obj.teamId;
      zFlagstand = %obj;
   };
   copyPalette(%obj, %obj.zFlag);
   %this.returnFlag(%obj);
}

function ctfFlagStand::onRemove(%this, %obj)
{
   //echo("ctfFlagStand::onRemove()");
   if(isObject(%obj.zFlag))
      %obj.zFlag.delete();
}

function ctfFlagStand::onPaletteChange(%this, %obj, %slot, %colorI)
{
   //echo("ctfFlagStand::onPaletteChange()");
   changePalette(%obj.zFlag, %slot, %colorI);
}

function ctfFlagStand::returnFlag(%this, %obj)
{
   //echo("ctfFlagStand::returnFlag()");
   %mat = MatrixCreate("0 0 0.5", "0 0 1 0");
   %obj.mountObject(%obj.zFlag, 0, %mat);
}

