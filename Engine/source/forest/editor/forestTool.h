// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FOREST_EDITOR_TOOL_H_
#define _FOREST_EDITOR_TOOL_H_

#ifndef _FORESTITEM_H_
#include "forest/forestItem.h"
#endif
#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif
#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif

class Forest;
class ForestEditorCtrl;
class ForestData;
class UndoAction;
class GuiTSCtrl;
class Point3F;
struct Gui3DMouseEvent;


class ForestTool : public SimObject
{
   typedef SimObject Parent;

   protected:

      SimObjectPtr<Forest> mForest;
      ForestEditorCtrl *mEditor;

      void _submitUndo( UndoAction *action );

   public:

      ForestTool();
      virtual ~ForestTool();

      DECLARE_CONOBJECT( ForestTool );

      virtual void setActiveForest( Forest *forest ) { mForest = forest; }
      virtual void setParentEditor( ForestEditorCtrl *editor ) { mEditor = editor; }

      virtual void onActivated( const Gui3DMouseEvent &lastEvent ) {}
      virtual void onDeactivated() {}

      virtual void on3DMouseDown( const Gui3DMouseEvent &evt ) {}
      virtual void on3DMouseUp( const Gui3DMouseEvent &evt ) {}
      virtual void on3DMouseMove( const Gui3DMouseEvent &evt ) {}
      virtual void on3DMouseDragged( const Gui3DMouseEvent &evt ) {}
      virtual void on3DMouseEnter( const Gui3DMouseEvent &evt ) {}
      virtual void on3DMouseLeave( const Gui3DMouseEvent &evt ) {}
      virtual bool onMouseWheel( const GuiEvent &evt ) { return false; }      
      virtual void onRender3D() {}
      virtual void onRender2D() {}      
      virtual void updateGizmo() {}
      virtual bool updateGuiInfo() { return false; }
      virtual void onUndoAction() {}
};


#endif // _FOREST_EDITOR_TOOL_H_



