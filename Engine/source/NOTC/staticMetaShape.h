// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _STATICMETASHAPE_H_
#define _STATICMETASHAPE_H_

#ifndef _STATICSHAPE_H_
#include "T3D/staticShape.h"
#endif

//----------------------------------------------------------------------------

class StaticMetaShape: public ShapeBase
{
   typedef ShapeBase Parent;

   StaticShapeData*  mDataBlock;
   bool              mPowered;

   void onUnmount(ShapeBase* obj,S32 node);

protected:
   enum MaskBits {
      PositionMask = Parent::NextFreeMask,	  
      NextFreeMask = Parent::NextFreeMask << 1
   };

public:
   DECLARE_CONOBJECT(StaticMetaShape);

   StaticMetaShape();
   ~StaticMetaShape();

	// SimObject
   bool onAdd();
   void onRemove();
   void onEditorEnable();
   void onEditorDisable();

	// SceneObject
   void setTransform(const MatrixF &mat);

	// GameBase
   bool onNewDataBlock(GameBaseData *dptr, bool reload);
   void processTick(const Move *move);
   void interpolateTick(F32 delta);


   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);

   // power
   void setPowered(bool power)      {mPowered = power;}
   bool isPowered()                 {return(mPowered);}

   static void initPersistFields();   
};

#endif // _STATICMETASHAPE_H_
