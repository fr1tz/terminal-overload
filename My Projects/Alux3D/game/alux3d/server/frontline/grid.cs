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
      %gridX = mCeil(%gridX);
   else
      %gridX = mFloor(%gridX);
   %gridY = (%worldY-%originY)/%spacingY;
   if(%gridY > 0)
      %gridY = mCeil(%gridY);
   else
      %gridY = mFloor(%gridY);
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

