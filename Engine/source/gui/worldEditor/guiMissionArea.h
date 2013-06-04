// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIMISSIONAREA_H_
#define _GUIMISSIONAREA_H_

#ifndef _GUIBITMAPCTRL_H_
#include "gui/controls/guiBitmapCtrl.h"
#endif
#ifndef _GUITYPES_H_
#include "gui/guiTypes.h"
#endif
#ifndef _MISSIONAREA_H_
#include "T3D/missionArea.h"
#endif
#ifndef _UNDO_H_
#include "util/undo.h"
#endif

class GBitmap;
class TerrainBlock;

class GuiMissionAreaCtrl : public GuiBitmapCtrl
{
   typedef GuiBitmapCtrl Parent;

protected:
   enum HandleInfo
   {
      // Handle in use
      Handle_None    = 0,
      Handle_Left    = BIT(0),
      Handle_Right   = BIT(1),
      Handle_Top     = BIT(2),
      Handle_Bottom  = BIT(3),
      Handle_Middle  = BIT(4),   // Used to drag the whole area

      Handle_Pixel_Size = 3,
   };

   SimObjectPtr<MissionArea>  mMissionArea;
   SimObjectPtr<TerrainBlock> mTerrainBlock;

   GFXStateBlockRef  mBlendStateBlock;
   GFXStateBlockRef  mSolidStateBlock;

   StringTableEntry  mHandleBitmap;
   GFXTexHandle      mHandleTexture;
   Point2I           mHandleTextureSize;
   Point2F           mHandleTextureHalfSize;

   ColorI   mMissionBoundsColor;
   ColorI   mCameraColor;

   bool     mSquareBitmap;

   VectorF  mScale;
   Point2F  mCenterPos;

   S32      mLastHitMode;
   Point2I  mLastMousePoint;
   bool     mSavedDrag;

   void submitUndo( const UTF8 *name = "Action" );

   TerrainBlock * getTerrainObj();
   GBitmap * createTerrainBitmap();
   void updateTerrainBitmap();

   //void onUpdate();

   void setupScreenTransform(const Point2I & offset);

   Point2F worldToScreen(const Point2F &);
   Point2F screenToWorld(const Point2F &);

   Point2I worldToScreen(const Point2I &);
   Point2I screenToWorld(const Point2I &);

   Point2I screenDeltaToWorldDelta(const Point2I &screenPoint);

   void getScreenMissionArea(RectI & rect);
   void getScreenMissionArea(RectF & rect);

   Point2I convertOrigin(const Point2I &);

   void drawHandle(const Point2F & pos);
   void drawHandles(RectI & box);

   bool testWithinHandle(const Point2I & testPoint, S32 handleX, S32 handleY);
   S32 getHitHandles(const Point2I & mousePnt, const RectI & box);

public:
   GuiMissionAreaCtrl();
   virtual ~GuiMissionAreaCtrl();

   DECLARE_CONOBJECT(GuiMissionAreaCtrl);

   // SimObject
   bool onAdd();
   static void initPersistFields();

   // GuiControl
   void onRender(Point2I offset, const RectI &updateRect);
   bool onWake();
   void onSleep();

   virtual void onMouseUp(const GuiEvent & event);
   virtual void onMouseDown(const GuiEvent & event);
   virtual void onMouseMove(const GuiEvent & event);
   virtual void onMouseDragged(const GuiEvent & event);
   virtual void onMouseEnter(const GuiEvent & event);
   virtual void onMouseLeave(const GuiEvent & event);

   void setMissionArea( MissionArea* area );
   void updateTerrain();

   const RectI & getArea();
   void setArea(const RectI & area);
};

class GuiMissionAreaUndoAction : public UndoAction
{
   public:

      GuiMissionAreaUndoAction( const UTF8* actionName ) : UndoAction( actionName )
      {
      }

      GuiMissionAreaCtrl *mMissionAreaEditor;

      SimObjectId mObjId;
      RectI mArea;

      virtual void undo();
      virtual void redo() { undo(); }
};

#endif // _GUIMISSIONAREA_H_
