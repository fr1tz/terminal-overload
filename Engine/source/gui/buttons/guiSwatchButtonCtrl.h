// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUISWATCHBUTTONCTRL_H_
#define _GUISWATCHBUTTONCTRL_H_

#ifndef _GUIBUTTONBASECTRL_H_
   #include "gui/buttons/guiButtonBaseCtrl.h"
#endif


/// A color swatch button.
///
class GuiSwatchButtonCtrl : public GuiButtonBaseCtrl
{
   public:
      
      typedef GuiButtonBaseCtrl Parent;

   protected:
      
      /// The color to display on the button.
      ColorF mSwatchColor;
      
      /// Bitmap used for mGrid
      String mGridBitmap;

      /// Background texture that will show through with transparent colors.
      GFXTexHandle mGrid;
      
   public:

      GuiSwatchButtonCtrl();

      /// Return the color displayed in the swatch.
      ColorF getColor() { return mSwatchColor; }

      /// Set the color to display in the swatch.
      void setColor( const ColorF &color ) { mSwatchColor = color; }

      // GuiButtonBaseCtrl
      virtual bool onWake();
      virtual void onRender(Point2I offset, const RectI &updateRect);

      static void initPersistFields();

      DECLARE_CONOBJECT( GuiSwatchButtonCtrl );
      DECLARE_DESCRIPTION( "A color swatch button." );
};

#endif // _GUISWATCHBUTTONCTRL_H_
