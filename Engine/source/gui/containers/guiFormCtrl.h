// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIFORMCTRL_H_
#define _GUIFORMCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _GUI_PANEL_H_
#include "gui/containers/guiPanel.h"
#endif

#ifndef _GUIMENUBAR_H_
#include "gui/editor/guiMenuBar.h"
#endif

#ifndef _GUICANVAS_H_
#include "gui/core/guiCanvas.h"
#endif

#include "console/console.h"
#include "console/consoleTypes.h"

class GuiMenuBar;


/// @addtogroup gui_container_group Containers
///
/// @ingroup gui_group Gui System
/// @{
class GuiFormCtrl : public GuiPanel
{
private:
   typedef GuiPanel Parent;

   Resource<GFont>  mFont;
   String           mCaption;
   bool             mCanMove;
   bool             mUseSmallCaption;
   String           mSmallCaption;
   StringTableEntry mContentLibrary;
   StringTableEntry mContent;

   Point2I          mThumbSize;

   bool             mHasMenu;
   GuiMenuBar*      mMenuBar;

   bool mMouseMovingWin;

   Point2I mMouseDownPosition;
   RectI mOrigBounds;
   RectI mStandardBounds;

   RectI mCloseButton;
   RectI mMinimizeButton;
   RectI mMaximizeButton;

   bool mMouseOver;
   bool mDepressed;
   
   static bool _setHasMenu( void *object, const char *index, const char *data );

protected:
   /// @name Callbacks
   /// @{
   DECLARE_CALLBACK( void, onResize, () );
   /// @}

public:
   GuiFormCtrl();
   virtual ~GuiFormCtrl();

   void setCaption( const char* caption ) { mCaption = caption; }
   void setHasMenu( bool value );

   bool resize(const Point2I &newPosition, const Point2I &newExtent);
   void onRender(Point2I offset, const RectI &updateRect);

   bool onWake();
   void onSleep();

   virtual void addObject( SimObject *object );
   virtual void removeObject( SimObject* object );
   virtual bool acceptsAsChild( SimObject* object ) const;

   void onMouseDown(const GuiEvent &event);
   void onMouseUp(const GuiEvent &event);
   void onMouseMove(const GuiEvent &event);
   void onMouseLeave(const GuiEvent &event);
   void onMouseEnter(const GuiEvent &event);

   U32  getMenuBarID();

   static void initPersistFields();
   DECLARE_CONOBJECT(GuiFormCtrl);
};
/// @}

#endif