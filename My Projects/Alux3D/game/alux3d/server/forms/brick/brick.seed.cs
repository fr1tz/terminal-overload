// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ProjectileData(FrmBrickSeed)
{
   //projectileShapeName = "content/fr1tz/oldshapes/siberion/projectile/p1/shape.dae";
   
	maxTrackingAbility = 40;
	trackingAgility = 0;

   explosion           = BulletDirtExplosion;
   decal               = BulletHoleDecal;

   muzzleVelocity      = 40;
   velInheritFactor    = 0;

   armingDelay         = 0;
	lifetime            = 1000*10;
	fadeDelay           = 1000*10;
   isBallistic         = false;
   gravityMod          = 1;
};

function FrmBrickSeed::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
    
   %obj.light = new PointLight() {
      radius = "2";
      isEnabled = "1";
      color = "1 1 1 1";
      brightness = "1";
      castShadows = "0";
      flareType = "FrmLightLightFlare";
      flareScale = "0.5";
   };
   MissionCleanup.add(%obj.light);
   %obj.mountObject(%obj.light, 0);
}

function FrmBrickSeed::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
   %obj.light.delete();
}

function FrmBrickSeed::onCollision(%data, %proj, %col, %fade, %pos, %normal)
{
   //echo("FrmBrickSeed::onCollision("@%data.getName()@", "@%proj@", "@%col.getClassName()@", "@%fade@", "@%pos@", "@%normal@")");

   %volume = "";
	InitContainerRadiusSearch(%pos, 0.1, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;
      if(%srchObj.getDataBlock() == BrickVolume.getId())
      {
         %volume = %srchObj;
         break;
      }
	}
 
   if(%volume $= "")
   {
      %volume = new HexagonVolume() {
         dataBlock = "BrickVolume";
         client = "-1";
         teamId = "0";
         position = %pos;
         rotation = "1 0 0 0";
         scale = "10 10 10";
      };
      MissionCleanup.add(%volume);
      %volume.init();
   }

   %gridPos = MissionSoilGrid.worldToGrid(%pos);
   %gridPosX = getWord(%gridPos, 0);
   %gridPosY = getWord(%gridPos, 1);
   %gridPosZ = getWord(%gridPos, 2);
   %gridPos2D = %gridPosX SPC %gridPosY;
   %shapeNr = %volume.getHexagonShapeNr(%gridPos2D);
   if(%shapeNr > 0)
   {
      %elevation = %volume.getHexagonElevation(%gridPos2D);
      %gridPos = %gridPosX SPC %gridPosY SPC %elevation;
   }
   %amount = %volume.getHexagonAmount(%gridPos2D);
   %volume.setHexagon(%gridPos, %proj.teamId, %amount + 1);
   %volume.rebuild();
}
