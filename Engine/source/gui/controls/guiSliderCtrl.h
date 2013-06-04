// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUISLIDERCTRL_H_
#define _GUISLIDERCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif


/// A slider control that selects out of a floating-point value range.
class GuiSliderCtrl : public GuiControl
{
   public:
   
      typedef GuiControl Parent;

   protected:

      Point2F mRange;
      U32  mTicks;
      bool mSnap;
      F32  mValue;
      RectI   mThumb;
      Point2I mThumbSize;
      S32 mShiftPoint;
      S32 mShiftExtent;
      F32 mIncAmount;
      bool mDisplayValue;
      bool mDepressed;
      bool mMouseOver;
      bool mMouseDragged;
      bool mHasTexture;

      enum
      {
         SliderLineLeft = 0,
         SliderLineCenter,
         SliderLineRight,
         SliderButtonNormal,
         SliderButtonHighlight,
         NumBitmaps
      };
         RectI *mBitmapBounds;

      F32 _getThumbValue( const GuiEvent& event );
      void _updateThumb( F32 value, bool snap = true, bool onWake = false, bool doCallback = true );
      
      /// @name Callbacks
      /// @{
      
      DECLARE_CALLBACK( void, onMouseDragged, () );
      
      /// @}
      
      static bool _setValue( void* object, const char* index, const char* data ) { static_cast< GuiSliderCtrl* >( object )->setValue( dAtof( data ) ); return false; }

   public:
         
      GuiSliderCtrl();
      
      bool isThumbBeingDragged() const { return mDepressed; }
         
      const Point2F& getRange() const { return mRange; }

      // GuiControl.
      bool onWake();

      void onMouseDown(const GuiEvent &event);
      void onMouseDragged(const GuiEvent &event);
      void onMouseUp(const GuiEvent &);
      void onMouseLeave(const GuiEvent &);
      void onMouseEnter(const GuiEvent &);
      bool onMouseWheelUp(const GuiEvent &event);
      bool onMouseWheelDown(const GuiEvent &event);
      
      void setActive( bool value );

      F32 getValue() const { return mValue; }
      void setScriptValue(const char *val) { setValue(dAtof(val)); }
      void setValue(F32 val, bool doCallback=false);

      void onRender(Point2I offset, const RectI &updateRect);
      
      virtual bool resize( const Point2I& newSize, const Point2I& newExtent );
      virtual void parentResized( const RectI& oldParentRect, const RectI& newParentRect );

      static void initPersistFields();

      DECLARE_CONOBJECT(GuiSliderCtrl);
      DECLARE_CATEGORY( "Gui Values" );
      DECLARE_DESCRIPTION( "A control that implements a horizontal or vertical slider to\n"
                           "select/represent values in a certain range." )
};

#endif
