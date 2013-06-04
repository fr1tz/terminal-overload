// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GUI_SPLTCONTAINER_H_
#define _GUI_SPLTCONTAINER_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif
#ifndef _GUICONTAINER_H_
#include "gui/containers/guiContainer.h"
#endif
#ifndef _GUI_PANEL_H_
#include "gui/containers/guiPanel.h"
#endif
#ifndef _PLATFORMINPUT_H_
#include "platform/platformInput.h"
#endif



/// @addtogroup gui_container_group Containers
///
/// @ingroup gui_group Gui System
/// @{
class  GuiSplitContainer : public GuiContainer
{
   typedef GuiContainer Parent;
public:

   enum Orientation
   {
      Vertical = 0,
      Horizontal = 1
   };

   enum FixedPanel
   {
      None = 0,
      FirstPanel = 1,
      SecondPanel
   };   

   GuiSplitContainer();

   DECLARE_CONOBJECT( GuiSplitContainer );
   DECLARE_DESCRIPTION( "A container that splits its area between two child controls.\n"
                        "The split ratio can be dynamically adjusted with a handle control between the two children.\n"
                        "Splitting can be either horizontal or vertical." );

   // ConsoleObject
   static void initPersistFields();
   virtual bool onAdd();

   // GuiControl   
   virtual bool onWake();
   virtual void parentResized(const RectI &oldParentRect, const RectI &newParentRect);
   virtual bool resize( const Point2I &newPosition, const Point2I &newExtent );   
   virtual void onRender(Point2I offset, const RectI &updateRect);
   virtual void onMouseDown(const GuiEvent &event);
   virtual void onMouseUp(const GuiEvent &event);
   virtual void onMouseDragged(const GuiEvent &event); 

   virtual bool layoutControls( RectI &clientRect );
   virtual void getCursor(GuiCursor *&cursor, bool &showCursor, const GuiEvent &lastGuiEvent);
   virtual inline Point2I getSplitPoint() { return mSplitPoint; };
   /// The Splitters entire Client Rectangle, this takes into account padding of this control
   virtual inline RectI getSplitRect() { return mSplitRect; };
   virtual void solvePanelConstraints( Point2I newDragPos, GuiContainer * firstPanel, GuiContainer * secondPanel, RectI clientRect );   
   virtual Point2I getMinExtent() const;   

protected:

   S32         mFixedPanel; 
   S32         mFixedPanelSize;
   S32         mOrientation;
   S32         mSplitterSize;
   Point2I     mSplitPoint;
   RectI       mSplitRect;
   bool        mDragging;

};

typedef GuiSplitContainer::Orientation GuiSplitOrientation;
typedef GuiSplitContainer::FixedPanel GuiSplitFixedPanel;

DefineEnumType( GuiSplitOrientation );
DefineEnumType( GuiSplitFixedPanel );

/// @}

#endif // _GUI_SPLTCONTAINER_H_