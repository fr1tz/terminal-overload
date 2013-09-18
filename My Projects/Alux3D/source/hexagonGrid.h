// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HEXAGONGRID_H_
#define _HEXAGONGRID_H_

#ifndef _BITSTREAM_H_
#include "core/stream/bitStream.h"
#endif
#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif
#ifndef _SHAPEBASE_H_
#include "T3D/shapeBase.h"
#endif
#ifndef _MATHIO_H_
#include "math/mathIO.h"
#endif
#ifndef _COLOR_H_
#include "core/color.h"
#endif

class HexagonGridData : public ShapeBaseData
{
	typedef ShapeBaseData Parent;

 public:
	Point3F spacing;

	HexagonGridData();
   
	DECLARE_CONOBJECT(HexagonGridData);

	bool onAdd();
	static void initPersistFields();
	virtual void packData(BitStream* stream);
	virtual void unpackData(BitStream* stream);
};

class HexagonGrid : public ShapeBase
{
   private:
      typedef ShapeBase Parent;

   protected:
      enum MaskBits {
         PositionMask = Parent::NextFreeMask,
         NextFreeMask = Parent::NextFreeMask << 1
      };
      HexagonGridData* mDataBlock;
      bool mAddedToScene;

   public:
      HexagonGrid();

      // GameBase
      bool onNewDataBlock( GameBaseData *dptr, bool reload );

      // SceneObject
      void setTransform(const MatrixF &mat);

      // SimObject
      bool onAdd();
      void onRemove();
      void onEditorEnable();
      void onEditorDisable();

      void inspectPostApply();

      // NetObject
      U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
      void unpackUpdate(NetConnection *conn,           BitStream *stream);

      DECLARE_CONOBJECT(HexagonGrid);
      static void initPersistFields();
};


#endif // _HEXAGONGRID_H_