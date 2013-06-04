// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIRIVEREDITORCTRL_H_
#define _GUIRIVEREDITORCTRL_H_

#ifndef _EDITTSCTRL_H_
#include "gui/worldEditor/editTSCtrl.h"
#endif
#ifndef _UNDO_H_
#include "util/undo.h"
#endif
#ifndef _RIVER_H_
#include "environment/river.h"
#endif
#ifndef _GIZMO_H_
#include "gui/worldEditor/gizmo.h"
#endif

struct ObjectRenderInst;
class SceneManager;
class SceneRenderState;
class BaseMatInstance;


class GuiRiverEditorCtrl : public EditTSCtrl
{
   typedef EditTSCtrl Parent;

   public:
   
      friend class GuiRiverEditorUndoAction;

      //static StringTableEntry smNormalMode;
      //static StringTableEntry smAddNodeMode;
		
		String mSelectRiverMode;
		String mAddRiverMode;
		String mAddNodeMode;
		String mInsertPointMode;
		String mRemovePointMode;
		String mMovePointMode;
		String mScalePointMode;
		String mRotatePointMode;

      GuiRiverEditorCtrl();
      ~GuiRiverEditorCtrl();

      DECLARE_CONOBJECT(GuiRiverEditorCtrl);

      // SimObject
      bool onAdd();
      static void initPersistFields();

      // GuiControl
      virtual void onSleep();
      virtual void onRender(Point2I offset, const RectI &updateRect);

      // EditTSCtrl      
		bool onKeyDown(const GuiEvent& event);
      void get3DCursor( GuiCursor *&cursor, bool &visible, const Gui3DMouseEvent &event_ );
      void on3DMouseDown(const Gui3DMouseEvent & event);
      void on3DMouseUp(const Gui3DMouseEvent & event);
      void on3DMouseMove(const Gui3DMouseEvent & event);
      void on3DMouseDragged(const Gui3DMouseEvent & event);
      void on3DMouseEnter(const Gui3DMouseEvent & event);
      void on3DMouseLeave(const Gui3DMouseEvent & event);
      void on3DRightMouseDown(const Gui3DMouseEvent & event);
      void on3DRightMouseUp(const Gui3DMouseEvent & event);
      void updateGuiInfo();      
      void renderScene(const RectI & updateRect);

      // GuiRiverEditorCtrl      
      bool getStaticPos( const Gui3DMouseEvent & event, Point3F &tpos );
      void deleteSelectedNode();
      void deleteSelectedRiver( bool undoAble = true );
      
      void setMode( String mode, bool sourceShortcut  );
      String getMode() { return mMode; }

      //void setGizmoMode( Gizmo::Mode mode ) { mGizmo->setMode( mode ); }

      void setSelectedRiver( River *river );
      River* getSelectedRiver() { return mSelRiver; };
      void setSelectedNode( S32 node );

      F32 getNodeWidth();
      void setNodeWidth( F32 width );

      F32 getNodeDepth();
      void setNodeDepth( F32 depth );

		Point3F getNodePosition();
		void setNodePosition( Point3F pos );

		VectorF getNodeNormal();
      void setNodeNormal( const VectorF &normal );

   protected:

      void _renderSelectedRiver( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *matInst );
      void _prepRenderImage( SceneManager* sceneGraph, const SceneRenderState* sceneState );
      void _drawRiverSpline( River *river, const ColorI &color );
      void _drawRiverControlNodes( River *river, const ColorI &color );
      void _process3DMouseDown( const Gui3DMouseEvent& event );

      void submitUndo( const UTF8 *name = "Action" );

      GFXStateBlockRef mZDisableSB;
      GFXStateBlockRef mZEnableSB;

      bool mSavedDrag;
      bool mIsDirty;

      SimSet *mRiverSet;
      S32 mSelNode;
      S32 mHoverNode;
      U32 mAddNodeIdx;
      SimObjectPtr<River> mSelRiver;      
      SimObjectPtr<River> mHoverRiver;

      String mMode;

      F32 mDefaultWidth;
      F32 mDefaultDepth;
      VectorF mDefaultNormal;
      S32 mInsertIdx;

      F32 mStartHeight;
      F32 mStartWidth;
      S32 mStartX;
      Point3F mStartWorld;

      Point2I mNodeHalfSize;

      //Gizmo mGizmo;

      Gui3DMouseEvent mLastMouseEvent;

      F32 mNodeSphereRadius;
      ColorI mNodeSphereFillColor;
      ColorI mNodeSphereLineColor;

      ColorI mHoverSplineColor;
      ColorI mSelectedSplineColor;
      ColorI mHoverNodeColor;

      #define InvalidMousePoint Point2I(-100,-100)
      Point2I mStartDragMousePoint;

      Point3F mStartDragNodePos;

      //GuiCursor *mMoveNodeCursor;
      //GuiCursor *mAddNodeCursor;
      //GuiCursor *mInsertNodeCursor;
      //GuiCursor *mResizeNodeCursor;
};

class GuiRiverEditorUndoAction : public UndoAction
{
   public:

      GuiRiverEditorUndoAction( const UTF8* actionName ) : UndoAction( actionName )
      {
      }

      GuiRiverEditorCtrl *mRiverEditor;         

      Vector<RiverNode> mNodes;

      SimObjectId mObjId;
      F32 mMetersPerSegment;
      U32 mSegmentsPerBatch;

      virtual void undo();
      virtual void redo() { undo(); }
};

#endif



