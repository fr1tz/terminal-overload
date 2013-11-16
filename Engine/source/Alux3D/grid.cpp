// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "grid.h"

#include "console/consoleTypes.h"
#include "core/color.h"
#include "console/engineAPI.h"

extern bool gEditingMission;

IMPLEMENT_CO_DATABLOCK_V1(GridData);

ConsoleDocClass( GridData,
   "@brief TODO\n\n"
);

GridData::GridData()
{
	spacing.set(1.0625, 1.25, 0.25);
}

bool GridData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void GridData::initPersistFields()
{
   addGroup("Grid");

		addField( "spacing", TypePoint3F, Offset(spacing, GridData),
			"@brief The spacing of the grid nodes\n\n"
		);

   endGroup("Grid");

   Parent::initPersistFields();
}

void GridData::packData(BitStream* stream)
{
   Parent::packData(stream);
	mathWrite(*stream, spacing); 
}

void GridData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
	mathRead(*stream, &spacing); 
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(Grid);

ConsoleDocClass( Grid,
   "@brief TODO\n\n"
);

Grid::Grid()
{
   mTypeMask |= (StaticObjectType | GridObjectType);
   mDataBlock = NULL;
   mNetFlags.set(Ghostable | ScopeAlways);
}

bool Grid::onAdd()
{
   if(!Parent::onAdd() || !mDataBlock)
      return(false);

   this->addToScene();
	this->setRenderEnabled(gEditingMission);

   return true;
}

void Grid::onRemove()
{
	removeFromScene();
	Parent::onRemove();
}

void Grid::inspectPostApply()
{
   Parent::inspectPostApply();
}

void Grid::onEditorEnable()
{
	this->setRenderEnabled(true);
}

void Grid::onEditorDisable()
{
	this->setRenderEnabled(false);
}

bool Grid::onNewDataBlock( GameBaseData *dptr, bool reload )
{
   mDataBlock = dynamic_cast<GridData*>( dptr );
   if ( !mDataBlock || !Parent::onNewDataBlock( dptr, reload ) )
      return(false);
   scriptOnNewDataBlock();
   return(true);
}

void Grid::setTransform(const MatrixF& mat)
{
   Parent::setTransform(mat);
   setMaskBits(PositionMask);
}

U32 Grid::packUpdate(NetConnection * con, U32 mask, BitStream * stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);
   if(stream->writeFlag(mask & PositionMask))
   {
      stream->writeAffineTransform(mObjToWorld);
      mathWrite(*stream, mObjScale);
   }

   return(retMask);
}

void Grid::unpackUpdate(NetConnection * con, BitStream * stream)
{
   Parent::unpackUpdate(con, stream);
   if(stream->readFlag())
   {
      MatrixF mat;
      stream->readAffineTransform(&mat);
      Parent::setTransform(mat);

      Point3F scale;
      mathRead(*stream, &scale);
      setScale(scale);
   }
}

void Grid::initPersistFields()
{
   Parent::initPersistFields();
}

Point3F Grid::gridToWorld(Point3I gridPos)
{
	Point3F worldPos;

	Point3F origin = this->getPosition();
	worldPos.x = origin.x + gridPos.x * mDataBlock->spacing.x;
	worldPos.y = origin.y + gridPos.y * mDataBlock->spacing.y;
	worldPos.z = origin.z + gridPos.z * mDataBlock->spacing.z;
   
   return worldPos;
}

Point3I Grid::worldToGrid(Point3F worldPos)
{
	Point3I gridPos;

	Point3F origin = this->getPosition();

	gridPos.x = (worldPos.x-origin.x) / mDataBlock->spacing.x;
	if(gridPos.x > 0)
		gridPos.x = mCeil(gridPos.x);
	else
		gridPos.x = mFloor(gridPos.x);

	gridPos.y = (worldPos.y-origin.y) / mDataBlock->spacing.y;
	if(gridPos.y > 0)
		gridPos.y = mCeil(gridPos.y);
	else
		gridPos.y = mFloor(gridPos.y);

	gridPos.z = (worldPos.z-origin.z) / mDataBlock->spacing.z;
	gridPos.z = mCeil(gridPos.z);

	return gridPos;
}

DefineEngineMethod(Grid, gridToWorld, Point3F, (Point3I gridPos),,
   "@brief Transform grid position into world position.\n\n"
   "@param 3D grid position\n"
)
{
   return object->gridToWorld(gridPos);
}

DefineEngineMethod(Grid, worldToGrid, Point3I, (Point3F worldPos),,
   "@brief Transform world position into grid position.\n\n"
   "@param 3D world position\n"
)
{
   return object->worldToGrid(worldPos);
}
