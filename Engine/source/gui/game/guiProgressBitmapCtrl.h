// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GuiProgressBitmapCtrl_H_
#define _GuiProgressBitmapCtrl_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _GUITEXTCTRL_H_
#include "gui/controls/guiTextCtrl.h"
#endif


//FIXME: WTH is this derived from GuiTextCtrl??  should be a GuiControl


/// A control that renders a horizontal progress bar from a repeating bitmap image.
class GuiProgressBitmapCtrl : public GuiTextCtrl
{
   public:
   
      typedef GuiTextCtrl Parent;
      
   protected:

      F32 mProgress;
      StringTableEntry mBitmapName;
      bool mUseVariable;
      bool mTile;
      S32 mNumberOfBitmaps;
      S32 mDim;
      
      static bool _setBitmap( void* object, const char* index, const char* data )
      {
         static_cast< GuiProgressBitmapCtrl* >( object )->setBitmap( data );
         return false;
      }

   public:
         
      GuiProgressBitmapCtrl();

      void setBitmap( const char* name );
      
      //console related methods
      virtual const char *getScriptValue();
      virtual void setScriptValue(const char *value);

      // GuiTextCtrl.
      virtual void onPreRender();
      virtual void onRender( Point2I offset, const RectI &updateRect );
      virtual bool onWake();

      DECLARE_CONOBJECT( GuiProgressBitmapCtrl );
      DECLARE_CATEGORY( "Gui Values" );
      DECLARE_DESCRIPTION( "A control that shows a horizontal progress bar that is rendered\n"
         "by repeating a bitmap." );

      static void initPersistFields();
};

#endif
