// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIBUTTONBASECTRL_H_
#define _GUIBUTTONBASECTRL_H_

#ifndef _GUICONTROL_H_
   #include "gui/core/guiControl.h"
#endif


/// Base class for all button controls.  Subclasses are mostly for specific
/// rendering types.
///
class GuiButtonBaseCtrl : public GuiControl
{
   public:
   
      typedef GuiControl Parent;

      enum ButtonType
      {
         ButtonTypePush,
         ButtonTypeCheck,
         ButtonTypeRadio,
      };

   protected:
   
      StringTableEntry mButtonText;
      StringTableEntry mButtonTextID;
      bool mDepressed;
      bool mMouseOver;
      bool mStateOn;
      S32 mButtonType;
      S32 mRadioGroup;
      bool mUseMouseEvents;
      
      /// Point where left mouse button was pressed down.  Used to find when to start
      /// a mouse drag.
      Point2I mMouseDownPoint;
      
      ///
      bool mMouseDragged;
      
	   /// @name Callbacks
	   /// @{

      DECLARE_CALLBACK( void, onMouseDown, () );   
	   DECLARE_CALLBACK( void, onMouseUp, () );
	   DECLARE_CALLBACK( void, onClick, () );
	   DECLARE_CALLBACK( void, onRightClick, () );
	   DECLARE_CALLBACK( void, onDoubleClick, () );    
	   DECLARE_CALLBACK( void, onMouseEnter, () );   
	   DECLARE_CALLBACK( void, onMouseLeave, () );      
	   DECLARE_CALLBACK( void, onMouseDragged, () );   

      /// @}

   public:

      GuiButtonBaseCtrl();
      bool onWake();

      DECLARE_CONOBJECT( GuiButtonBaseCtrl );
      DECLARE_CATEGORY( "Gui Buttons" );
      DECLARE_DESCRIPTION( "A basic button control." );
      
      static void initPersistFields();

      void setText(const char *text);
      void setTextID(S32 id);
      void setTextID(const char *id);
      const char *getText();
      void setStateOn( bool bStateOn );
      bool getStateOn() const { return mStateOn; }

      void setDepressed( bool depressed ) { mDepressed = depressed; }
      void resetState() {mDepressed = false; mMouseOver = false;}

      void acceleratorKeyPress(U32 index);
      void acceleratorKeyRelease(U32 index);

      void onMouseDown(const GuiEvent &);
      void onMouseUp(const GuiEvent &);
      void onMouseDragged( const GuiEvent& event );
      void onRightMouseUp(const GuiEvent &);

      void onMouseEnter(const GuiEvent &);
      void onMouseLeave(const GuiEvent &);

      bool onKeyDown(const GuiEvent &event);
      bool onKeyUp(const GuiEvent &event);

      void setScriptValue(const char *value);
      const char *getScriptValue();

      void onMessage(GuiControl *,S32 msg);
      void onAction();
      
      bool usesMouseEvents() const { return mUseMouseEvents; }
      void setUseMouseEvents( bool val ) { mUseMouseEvents = val; }
};

typedef GuiButtonBaseCtrl::ButtonType GuiButtonType;
DefineEnumType( GuiButtonType );

#endif
