// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function Spawn_Brick(%transform, %teamId)
{
   //echo("Spawn_Brick("@%transform@","@%teamId@")");
   
   %pos = getWords(%transform, 0, 2);

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
      %volume.zNumBricks = 0;
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
   else
   {
      %gridPos = %gridPosX SPC %gridPosY SPC %gridPosZ + 1;
   }
   %amount = %volume.getHexagonAmount(%gridPos2D);
   %volume.setHexagon(%gridPos, %teamId, %amount + 1);
   %volume.zNumBricks++;
   %volume.rebuild();

   %gridPos = setWord(%gridPos, 2, %amount + 1);
   %worldPos = MissionSoilGrid.gridToWorld(%gridPos);
   %spawnFx = new StaticShape() {
	  dataBlock = FrmBrickSpawnEffectShape;
	  client = %obj.client;
     teamId = %obj.client.team.teamId;
   };
   MissionCleanup.add(%spawnFx);
   %spawnFx.setTransform(%worldPos);
   %spawnFx.startFade(1000, 0, true);
   %spawnFx.schedule(1000, "delete");
   serverPlay3D(FrmBrickSpawnSound, %worldPos);
   
   return "";
}
