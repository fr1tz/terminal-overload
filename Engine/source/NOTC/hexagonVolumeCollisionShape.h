// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HEXAGONVOLUMECOLLISIONSHAPE_H_
#define _HEXAGONVOLUMECOLLISIONSHAPE_H_

#ifndef _STATICSHAPE_H_
#include "T3D/staticShape.h"
#endif

//----------------------------------------------------------------------------

class HexagonVolumeCollisionShape : public ShapeBase
{
   typedef ShapeBase Parent;

   StaticShapeData*  mDataBlock;

protected:
   enum MaskBits {
      PositionMask = Parent::NextFreeMask,	  
      NextFreeMask = Parent::NextFreeMask << 1
   };

public:
   DECLARE_CONOBJECT(HexagonVolumeCollisionShape);

	HexagonVolumeCollisionShape();
   HexagonVolumeCollisionShape(bool onClient);
   ~HexagonVolumeCollisionShape();

	// SimObject
   bool onAdd();
   void onRemove();
   void onEditorEnable();
   void onEditorDisable();

	// NetObject
   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);

	// SceneObject
   void setTransform(const MatrixF &mat);
	void setRenderTransform(const MatrixF &mat);

	// GameBase
   bool onNewDataBlock(GameBaseData *dptr, bool reload);
   void processTick(const Move *move);
   void interpolateTick(F32 delta);

   static void initPersistFields();   
};

#endif // _HEXAGONVOLUMECOLLISIONSHAPE_H_
