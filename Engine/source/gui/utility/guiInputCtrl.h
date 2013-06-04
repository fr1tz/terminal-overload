// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIINPUTCTRL_H_
#define _GUIINPUTCTRL_H_

#ifndef _GUIMOUSEEVENTCTRL_H_
   #include "gui/utility/guiMouseEventCtrl.h"
#endif


/// A control that locks the mouse and reports all keyboard input events
/// to script.  This is useful for implementing custom keyboard handling code.
class GuiInputCtrl : public GuiMouseEventCtrl
{
   public:

      typedef GuiMouseEventCtrl Parent;
   
      // GuiControl.
      virtual bool onWake();
      virtual void onSleep();

      virtual bool onInputEvent( const InputEventInfo &event );
      
      static void initPersistFields();

      DECLARE_CONOBJECT(GuiInputCtrl);
      DECLARE_CATEGORY( "Gui Other Script" );
      DECLARE_DESCRIPTION( "A control that locks the mouse and reports all keyboard input events to script." );

	  DECLARE_CALLBACK( void, onInputEvent, ( const char* device, const char* action, bool state ));
};

#endif // _GUI_INPUTCTRL_H
