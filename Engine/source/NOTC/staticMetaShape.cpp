// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "NOTC/staticMetaShape.h"

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

IMPLEMENT_CO_NETOBJECT_V1(StaticMetaShape);

ConsoleDocClass( StaticMetaShape,
	"@brief TODO\n\n"
);

StaticMetaShape::StaticMetaShape()
{
	mNetFlags.clear(Ghostable);
   mTypeMask |= StaticShapeObjectType | StaticObjectType;
   mDataBlock = 0;
}

StaticMetaShape::~StaticMetaShape()
{
}


//----------------------------------------------------------------------------

void StaticMetaShape::initPersistFields()
{
   Parent::initPersistFields();
}

bool StaticMetaShape::onAdd()
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

void StaticMetaShape::onRemove()
{
   scriptOnRemove();
   removeFromScene();
   Parent::onRemove();
}

//----------------------------------------------------------------------------

void StaticMetaShape::onEditorEnable()
{
   mNetFlags.set(Ghostable);
}

//----------------------------------------------------------------------------

void StaticMetaShape::onEditorDisable()
{
   mNetFlags.clear(Ghostable);
}

//----------------------------------------------------------------------------

bool StaticMetaShape::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<StaticShapeData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   scriptOnNewDataBlock();
   return true;
}

void StaticMetaShape::processTick(const Move* move)
{
   Parent::processTick(move);
}

void StaticMetaShape::interpolateTick(F32 delta)
{

}

void StaticMetaShape::setTransform(const MatrixF& mat)
{
   Parent::setTransform(mat);
   setMaskBits(PositionMask);
}

void StaticMetaShape::onUnmount(ShapeBase*,S32)
{
   // Make sure the client get's the final server pos.
   setMaskBits(PositionMask);
}


//----------------------------------------------------------------------------

U32 StaticMetaShape::packUpdate(NetConnection *connection, U32 mask, BitStream *bstream)
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

   // powered?
   bstream->writeFlag(mPowered);

   if (mLightPlugin) 
   {
      retMask |= mLightPlugin->packUpdate(this, ExtendedInfoMask, connection, mask, bstream);
   }

   return retMask;
}

void StaticMetaShape::unpackUpdate(NetConnection *connection, BitStream *bstream)
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

   // powered?
   mPowered = bstream->readFlag();

   if (mLightPlugin)
   {
      mLightPlugin->unpackUpdate(this, connection, bstream);
   }
}


//----------------------------------------------------------------------------
// This appears to be legacy T2 stuff
// Marked internal, as this is flagged to be deleted
// [8/1/2010 mperry]
ConsoleMethod( StaticMetaShape, setPoweredState, void, 3, 3, "(bool isPowered)"
			  "@internal")
{
   if(!object->isServerObject())
      return;
   object->setPowered(dAtob(argv[2]));
}

ConsoleMethod( StaticMetaShape, getPoweredState, bool, 2, 2, "@internal")
{
   if(!object->isServerObject())
      return(false);
   return(object->isPowered());
}
