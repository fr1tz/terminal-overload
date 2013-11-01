// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(BrickVolumeCollisionShape)
{
   shapeFile = "content/fr1tz/alux1/shapes/brick/brick-team1.dae";
};

datablock HexagonVolumeData(BrickVolume)
{
   renderShapeFile[0] = "content/fr1tz/alux1/shapes/brick/brick.dae";
   renderShapeFile[1] = "content/fr1tz/alux1/shapes/brick/brick-team1.dae";
   renderShapeFile[2] = "content/fr1tz/alux1/shapes/brick/brick-team2.dae";
   collisionShape[0] = BrickVolumeCollisionShape;
   collisionShape[1] = BrickVolumeCollisionShape;
   collisionShape[2] = BrickVolumeCollisionShape;
   mode = 2;
};

function BrickVolume::destroyStack(%this, %volume, %gridPos2D, %pos, %radius)
{
   %shapeNr = %volume.getHexagonShapeNr(%gridPos2D);
   %elevation = %volume.getHexagonElevation(%gridPos2D);
   %amount = %volume.getHexagonAmount(%gridPos2D);
   for(%i = 0; %i < %amount; %i++)
   {
      %gridPosZ = %elevation + %i;
      %gridPos = %gridPos2D SPC %gridPosZ;
      %worldPos = MissionSoilGrid.gridToWorld(%gridPos);
      %dist = VectorLen(VectorSub(%worldPos, %pos));
      if(%dist <= %radius)
      {
         %gridPos = %gridPos2D SPC %elevation;
         %newAmount = %gridPosZ - %elevation;
         %volume.setHexagon(%gridPos, %shapeNr, %newAmount);
         %volume.zNumBricks -= (%amount - %newAmount);
         break;
      }
   }
}

function BrickVolume::destroy(%this, %volume, %pos, %radius)
{
   %numBricksStor = %volume.zNumBricks;

   %vScale = %volume.getScale();
   %vScaleX = getWord(%vScale, 0);
   %vScaleY = getWord(%vScale, 1);
   
   %vPos = %volume.getPosition();
   %vPosX = getWord(%vPos, 0);
   %vPosY = getWord(%vPos, 1);
   %vPosZ = getWord(%vPos, 2);

   %x = %vPosX - %vScaleX/2;
   %y = %vPosY - %vScaleY/2;
   %gridPos = MissionSoilGrid.worldToGrid(%x SPC %y SPC %vPosZ);
   %gridPosX = getWord(%gridPos, 0)+1;
   %gridPosY = getWord(%gridPos, 1)+1;

   %x = 0;
   %y = 0;
   while(true)
   {
      %gridPos2D = %gridPosX + %x SPC %gridPosY + %y;
      %shapeNr = %volume.getHexagonShapeNr(%gridPos2D);
      if(%shapeNr == -1)
      {
         if(%x == 0)
         {
            break;
         }
         else
         {
            %x = 0;
            %y++;
            continue;
         }
      }
      else if(%shapeNr > 0)
      {
         %this.destroyStack(%volume, %gridPos2D, %pos, %radius);
      }
      
      %x++;
   }
   
   if(%volume.zNumBricks == 0)
      %volume.delete();
   else if(%volume.zNumBricks != %numBricksStor)
      %volume.rebuild();
}
