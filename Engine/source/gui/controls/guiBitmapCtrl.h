// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIBITMAPCTRL_H_
#define _GUIBITMAPCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

/// Renders a bitmap.
class GuiBitmapCtrl : public GuiControl
{
   public:
   
      typedef GuiControl Parent;

   protected:
   
      /// Name of the bitmap file.  If this is 'texhandle' the bitmap is not loaded
      /// from a file but rather set explicitly on the control.
      String mBitmapName;
      
      /// Loaded texture.
      GFXTexHandle mTextureObject;
      
      Point2I mStartPoint;
      
      /// If true, bitmap tiles inside control.  Otherwise stretches.
      bool mWrap;

      static bool setBitmapName( void *object, const char *index, const char *data );
      static const char *getBitmapName( void *obj, const char *data );

   public:
      
      GuiBitmapCtrl();
      static void initPersistFields();

      void setBitmap(const char *name,bool resize = false);
      void setBitmapHandle(GFXTexHandle handle, bool resize = false);

      // GuiControl.
      bool onWake();
      void onSleep();
      void inspectPostApply();

      void updateSizing();

      void onRender(Point2I offset, const RectI &updateRect);
      void setValue(S32 x, S32 y);

      DECLARE_CONOBJECT( GuiBitmapCtrl );
      DECLARE_CATEGORY( "Gui Images" );
      DECLARE_DESCRIPTION( "A control that displays a single, static image from a file.\n"
                           "The bitmap can either be tiled or stretched inside the control." );
};

#endif
