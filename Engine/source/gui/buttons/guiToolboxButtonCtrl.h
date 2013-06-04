// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUITOOLBOXBUTTON_H_
#define _GUITOOLBOXBUTTON_H_

#ifndef _GUIBUTTONCTRL_H_
#include "gui/buttons/guiButtonCtrl.h"
#endif
#ifndef GFX_Texture_Manager_H_
#include "gfx/gfxTextureManager.h"
#endif

class GuiToolboxButtonCtrl : public GuiButtonCtrl
{
private:
   typedef GuiButtonCtrl Parent;

protected:
   StringTableEntry mNormalBitmapName;
   StringTableEntry mLoweredBitmapName;
   StringTableEntry mHoverBitmapName;

   GFXTexHandle mTextureNormal;
   GFXTexHandle mTextureLowered;
   GFXTexHandle mTextureHover;

   void renderButton(GFXTexHandle &texture, Point2I &offset, const RectI& updateRect);
   void renderStateRect( GFXTexHandle &texture, const RectI& rect );

public:   
   DECLARE_CONOBJECT(GuiToolboxButtonCtrl);
   GuiToolboxButtonCtrl();

   static void initPersistFields();

   //Parent methods
   bool onWake();
   void onSleep();
   void inspectPostApply();

   void setNormalBitmap( StringTableEntry bitmapName );
   void setLoweredBitmap( StringTableEntry bitmapName );
   void setHoverBitmap( StringTableEntry bitmapName );
   

   void onRender(Point2I offset, const RectI &updateRect);
};


#endif //_GUITOOLBOXBUTTON_H_
