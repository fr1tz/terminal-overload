// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIICONBUTTON_H_
#define _GUIICONBUTTON_H_

#ifndef _GUIBUTTONCTRL_H_
#include "gui/buttons/guiButtonCtrl.h"
#endif
#ifndef GFX_Texture_Manager_H_
#include "gfx/gfxTextureManager.h"
#endif


/// The GuiIconButtonCtrl draws an icon and text caption within a normal
/// button control with several layout options.
///
class GuiIconButtonCtrl : public GuiButtonCtrl
{
private:
   typedef GuiButtonCtrl Parent;

protected:

   StringTableEntry  mBitmapName;
   GFXTexHandle      mTextureNormal;
   S32               mIconLocation;
   S32               mTextLocation;
   S32               mTextMargin;
   Point2I           mButtonMargin;
   
   /// Make the bitmap fill the button extent.
   bool mFitBitmapToButton;
   
   /// Keep a square aspect ration on the icon.
   bool mMakeIconSquare;

   /// Calculate extent based on icon size, text width, and layout options.
   bool mAutoSize;          

   //  Optional bitmap to be displayed when the proper bitmap cannot be found
   StringTableEntry mErrorBitmapName;
   GFXTexHandle mErrorTextureHandle;

   void renderButton( Point2I &offset, const RectI& updateRect);

   enum 
   {
      stateNormal,
      stateMouseOver,
      statePressed,
      stateDisabled,
   };

   void renderBitmapArray(RectI &bounds, S32 state);

public:   
   enum TextLocation
   {
      TextLocNone,
      TextLocBottom,
      TextLocRight,
      TextLocTop,
      TextLocLeft,
      TextLocCenter,
   };

   enum IconLocation
   {
      IconLocNone,
      IconLocLeft,
      IconLocRight,
      IconLocCenter      
   };


   DECLARE_CONOBJECT(GuiIconButtonCtrl);
   DECLARE_DESCRIPTION( "A button control that displays an icon on the button in addition\n"
                        "to the optional text label." );
                        
   GuiIconButtonCtrl();

   static void initPersistFields();

   //Parent methods
   bool onWake();
   void onSleep();
   void inspectPostApply();
   void onStaticModified(const char* slotName, const char* newValue = NULL);
   bool resize(const Point2I &newPosition, const Point2I &newExtent);

   void setBitmap(const char *name);

   //  Used to set the optional error bitmap
   void setErrorBitmap(const char *name);

   void onRender(Point2I offset, const RectI &updateRect);
};

typedef GuiIconButtonCtrl::TextLocation GuiIconButtonTextLocation;
typedef GuiIconButtonCtrl::IconLocation GuiIconButtonIconLocation;

DefineEnumType( GuiIconButtonTextLocation );
DefineEnumType( GuiIconButtonIconLocation );

#endif //_GUIICONBUTTON_H_
