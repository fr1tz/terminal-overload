// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIMOUSEEVENTCTRL_H_
#define _GUIMOUSEEVENTCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif


class GuiMouseEventCtrl : public GuiControl
{
   private:
      typedef  GuiControl     Parent;
      void sendMouseEvent(const char * name, const GuiEvent &);

      // field info
      bool        mLockMouse;

   public:

      GuiMouseEventCtrl();

	  DECLARE_CALLBACK( void, onMouseDown, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
  	  DECLARE_CALLBACK( void, onMouseUp, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
  	  DECLARE_CALLBACK( void, onMouseMove, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
  	  DECLARE_CALLBACK( void, onMouseDragged, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
  	  DECLARE_CALLBACK( void, onMouseEnter, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
  	  DECLARE_CALLBACK( void, onMouseLeave, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
	  DECLARE_CALLBACK( void, onRightMouseDown, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
	  DECLARE_CALLBACK( void, onRightMouseUp, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));
	  DECLARE_CALLBACK( void, onRightMouseDragged, ( U8 modifier, Point2I mousePoint,U8 mouseClickCount ));

      // GuiControl
      void onMouseDown(const GuiEvent & event);
      void onMouseUp(const GuiEvent & event);
      void onMouseMove(const GuiEvent & event);
      void onMouseDragged(const GuiEvent & event);
      void onMouseEnter(const GuiEvent & event);
      void onMouseLeave(const GuiEvent & event);
      void onRightMouseDown(const GuiEvent & event);
      void onRightMouseUp(const GuiEvent & event);
      void onRightMouseDragged(const GuiEvent & event);

      static void initPersistFields();

      DECLARE_CONOBJECT( GuiMouseEventCtrl );
      DECLARE_CATEGORY( "Gui Other Script" );
      DECLARE_DESCRIPTION( "A control that relays all mouse events to script." );
};

#endif
