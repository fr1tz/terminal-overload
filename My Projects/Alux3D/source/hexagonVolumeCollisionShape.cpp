// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hexagonVolumeCollisionShape.h"

#include "platform/platform.h"
#include "core/dnet.h"
#include "core/stream/bitStream.h"
#include "app/game.h"
#include "math/mMath.h"
#include "console/simBase.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "T3D/gameBase/moveManager.h"
#include "ts/tsShapeInstance.h"
#include "math/mathIO.h"
#include "sim/netConnection.h"
#include "scene/sceneObjectLightingPlugin.h"

extern void wireCube(F32 size,Point3F pos);

static const U32 sgAllowedDynamicTypes = 0xffffff;

//----------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(HexagonVolumeCollisionShape);

ConsoleDocClass( HexagonVolumeCollisionShape,
	"@brief TODO\n\n"
);

HexagonVolumeCollisionShape::HexagonVolumeCollisionShape()
{
	mNetFlags.clear();
	mTypeMask |= StaticShapeObjectType | StaticObjectType;
   mDataBlock = 0;
}

HexagonVolumeCollisionShape::HexagonVolumeCollisionShape(bool onClient)
{
	mNetFlags.clear();
	mTypeMask |= StaticShapeObjectType | StaticObjectType;
   mDataBlock = 0;
	if(onClient)
		mNetFlags.set(IsGhost);
}

HexagonVolumeCollisionShape::~HexagonVolumeCollisionShape()
{
}


//----------------------------------------------------------------------------

void HexagonVolumeCollisionShape::initPersistFields()
{
   Parent::initPersistFields();
}

bool HexagonVolumeCollisionShape::onAdd()
{
   if(!Parent::onAdd() || !mDataBlock)
      return false;

	// Don't tick
	this->setProcessTick(false);

   // We need to modify our type mask based on what our datablock says...
   mTypeMask |= (mDataBlock->dynamicTypeField & sgAllowedDynamicTypes);

   addToScene();

   if (isServerObject())
      scriptOnAdd();
   return true;
}

void HexagonVolumeCollisionShape::onRemove()
{
   scriptOnRemove();
   removeFromScene();
   Parent::onRemove();
}

//----------------------------------------------------------------------------

void HexagonVolumeCollisionShape::onEditorEnable()
{

}

//----------------------------------------------------------------------------

void HexagonVolumeCollisionShape::onEditorDisable()
{

}

//----------------------------------------------------------------------------

void HexagonVolumeCollisionShape::setTransform(const MatrixF &mat)
{
	Parent::setTransform(mat);
}

void HexagonVolumeCollisionShape::setRenderTransform(const MatrixF &mat)
{
	Parent::setRenderTransform(mat);
}

//----------------------------------------------------------------------------

bool HexagonVolumeCollisionShape::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<StaticShapeData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   scriptOnNewDataBlock();
   return true;
}

void HexagonVolumeCollisionShape::processTick(const Move* move)
{
   Parent::processTick(move);
}

void HexagonVolumeCollisionShape::interpolateTick(F32 delta)
{

}

//----------------------------------------------------------------------------

U32 HexagonVolumeCollisionShape::packUpdate(NetConnection *connection, U32 mask, BitStream *bstream)
{
   U32 retMask = Parent::packUpdate(connection,mask,bstream);
   if (bstream->writeFlag(mask & PositionMask | ExtendedInfoMask))
   {

      // Write the transform (do _not_ use writeAffineTransform.  Since this is a static
      //  object, the transform must be RIGHT THE *&)*$&^ ON or it will goof up the
      //  synchronization between the client and the server.
      mathWrite(*bstream,mObjToWorld);
      mathWrite(*bstream, mObjScale);
   }

   if (mLightPlugin) 
   {
      retMask |= mLightPlugin->packUpdate(this, ExtendedInfoMask, connection, mask, bstream);
   }

   return retMask;
}

void HexagonVolumeCollisionShape::unpackUpdate(NetConnection *connection, BitStream *bstream)
{
   Parent::unpackUpdate(connection,bstream);
   if (bstream->readFlag())
   {
      MatrixF mat;
      mathRead(*bstream,&mat);
      Parent::setTransform(mat);
      Parent::setRenderTransform(mat);

      VectorF scale;
      mathRead(*bstream, &scale);
      setScale(scale);
   }

   if (mLightPlugin)
   {
      mLightPlugin->unpackUpdate(this, connection, bstream);
   }
}
