// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hexagonGrid.h"

#include "console/consoleTypes.h"
#include "core/color.h"
#include "console/engineAPI.h"

extern bool gEditingMission;

IMPLEMENT_CO_DATABLOCK_V1(HexagonGridData);

ConsoleDocClass( HexagonGridData,
   "@brief TODO\n\n"
);

HexagonGridData::HexagonGridData()
{
	spacing.set(1.0625, 1.25, 0.25);
}

bool HexagonGridData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void HexagonGridData::initPersistFields()
{
   addGroup("Grid");

		addField( "spacing", TypePoint3F, Offset(spacing, HexagonGridData),
			"@brief The spacing of the grid nodes\n\n"
		);

   endGroup("Grid");

   Parent::initPersistFields();
}

void HexagonGridData::packData(BitStream* stream)
{
   Parent::packData(stream);
	mathWrite(*stream, spacing); 
}

void HexagonGridData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
	mathRead(*stream, &spacing); 
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(HexagonGrid);

ConsoleDocClass( HexagonGrid,
   "@brief TODO\n\n"
);

HexagonGrid::HexagonGrid()
{
   mTypeMask |= StaticObjectType;
   mDataBlock = NULL;
   mNetFlags.set(Ghostable | ScopeAlways);
}

bool HexagonGrid::onAdd()
{
   if(!Parent::onAdd() || !mDataBlock)
      return(false);

   this->addToScene();
	this->setRenderEnabled(gEditingMission);

   return true;
}

void HexagonGrid::onRemove()
{
	removeFromScene();
	Parent::onRemove();
}

void HexagonGrid::inspectPostApply()
{
   Parent::inspectPostApply();
}

void HexagonGrid::onEditorEnable()
{
	this->setRenderEnabled(true);
}

void HexagonGrid::onEditorDisable()
{
	this->setRenderEnabled(false);
}

bool HexagonGrid::onNewDataBlock( GameBaseData *dptr, bool reload )
{
   mDataBlock = dynamic_cast<HexagonGridData*>( dptr );
   if ( !mDataBlock || !Parent::onNewDataBlock( dptr, reload ) )
      return(false);
   scriptOnNewDataBlock();
   return(true);
}

void HexagonGrid::setTransform(const MatrixF& mat)
{
   Parent::setTransform(mat);
   setMaskBits(PositionMask);
}

U32 HexagonGrid::packUpdate(NetConnection * con, U32 mask, BitStream * stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);
   if(stream->writeFlag(mask & PositionMask))
   {
      stream->writeAffineTransform(mObjToWorld);
      mathWrite(*stream, mObjScale);
   }

   return(retMask);
}

void HexagonGrid::unpackUpdate(NetConnection * con, BitStream * stream)
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

void HexagonGrid::initPersistFields()
{
   Parent::initPersistFields();
}

