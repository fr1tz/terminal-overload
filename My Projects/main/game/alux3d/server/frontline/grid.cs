// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GridData::create(%this)
{
   %obj = new Grid() {
      dataBlock = %this;
   };
   return %obj;
}

function Grid::worldToGrid(%this, %pos)
{
   %data = %this.getDataBlock();

   %worldX = getWord(%pos, 0);
   %worldY = getWord(%pos, 1);
   %worldZ = getWord(%pos, 2);

   %originX = getWord(%this.getPosition(), 0);
   %originY = getWord(%this.getPosition(), 1);
   %originZ = getWord(%this.getPosition(), 2);

   %spacingX = getWord(%data.spacing, 0);
   %spacingY = getWord(%data.spacing, 1);
   %spacingZ = getWord(%data.spacing, 2);

   %gridX = (%worldX-%originX) / %spacingX;
   if(%gridX > 0)
   {
      %r = (%gridX*2) % 2;
      if(%r < 1)
         %gridX = mFloor(%gridX);
      else
         %gridX = mCeil(%gridX);
   }
   else
   {
      %r = (%gridX*2) % 2;
      if(%r > 1)
         %gridX = mFloor(%gridX);
      else
         %gridX = mCeil(%gridX);
   }

   %gridY = (%worldY-%originY)/%spacingY;
   if(%gridY > 0)
   {
      %r = (%gridY*2) % 2;
      if(%r < 1)
         %gridY = mFloor(%gridY);
      else
         %gridY = mCeil(%gridY);
   }
   else
   {
      %r = (%gridY*2) % 2;
      if(%r > 1)
         %gridY = mFloor(%gridY);
      else
         %gridY = mCeil(%gridY);
   }
      
   %gridZ = (%worldZ-%originZ)/%spacingZ;
   %gridZ = mCeil(%gridZ);

   return %gridX SPC %gridY SPC %gridZ;
}

function Grid::gridToWorld(%this, %pos)
{
   %data = %this.getDataBlock();

   %gridX = getWord(%pos, 0);
   %gridY = getWord(%pos, 1);
   %gridZ = getWord(%pos, 2);

   %originX = getWord(%this.getPosition(), 0);
   %originY = getWord(%this.getPosition(), 1);
   %originZ = getWord(%this.getPosition(), 2);

   %spacingX = getWord(%data.spacing, 0);
   %spacingY = getWord(%data.spacing, 1);
   %spacingZ = getWord(%data.spacing, 2);

   %worldX = %originX + %gridX * %spacingX;
   %worldY = %originY + %gridY * %spacingY;
   %worldZ = %originZ + %gridZ * %spacingZ;

   return %worldX SPC %worldY SPC %worldZ;
}

function Grid::worldToHexagon(%this, %pos)
{
   %gridPos = %this.worldToGrid(%pos);

   %x = getWord(%gridPos, 0);
   %y = getWord(%gridPos, 1);
   %z = getWord(%gridPos, 2);

   if(((%x & 1) == 0 && (%y & 1) == 1)
   || ((%x & 1) == 1 && (%y & 1) == 0))
   {
      %worldPos1 = MissionSoilGrid.gridToWorld(%x SPC %y + 1 SPC %z);
      %worldPos2 = MissionSoilGrid.gridToWorld(%x SPC %y - 1 SPC %z);
      %dist1 = VectorLen(VectorSub(%worldPos1, %pos));
      %dist2 = VectorLen(VectorSub(%worldPos2, %pos));
      if(%dist1 < %dist2)
         %y += 1;
      else
         %y -= 1;
      %gridPos = setWord(%gridPos, 1, %y);
   }
   
   return %gridPos;
}
