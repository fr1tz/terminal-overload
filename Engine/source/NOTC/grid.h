// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GRID_H_
#define _GRID_H_

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

class GridData : public ShapeBaseData
{
	typedef ShapeBaseData Parent;

 public:
	Point3F spacing;

	GridData();
   
	DECLARE_CONOBJECT(GridData);

	bool onAdd();
	static void initPersistFields();
	virtual void packData(BitStream* stream);
	virtual void unpackData(BitStream* stream);
};

class Grid : public ShapeBase
{
   private:
      typedef ShapeBase Parent;

   protected:
      enum MaskBits {
         PositionMask = Parent::NextFreeMask,
         NextFreeMask = Parent::NextFreeMask << 1
      };
      GridData* mDataBlock;
      bool mAddedToScene;

   public:
      Grid();

      // NetObject
      U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
      void unpackUpdate(NetConnection *conn,           BitStream *stream);

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

		// Grid
		Point3F gridToWorld(Point3I gridPos);
		Point3I worldToGrid(Point3F worldPos);

      DECLARE_CONOBJECT(Grid);
      static void initPersistFields();
};


#endif // _GRID_H_