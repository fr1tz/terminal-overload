// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/buttons/guiButtonCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"

IMPLEMENT_CONOBJECT(GuiButtonCtrl);

ConsoleDocClass( GuiButtonCtrl,
   "@brief The most widely used button class.\n\n"
   
   "GuiButtonCtrl renders seperately of, but utilizes all of the functionality of GuiBaseButtonCtrl.\n" 
   "This grants GuiButtonCtrl the versatility to be either of the 3 button types.\n\n"

   "@tsexample\n"
   "// Create a PushButton GuiButtonCtrl that calls randomFunction when clicked\n"
   "%button = new GuiButtonCtrl()\n"
   "{\n"
   "   profile    = \"GuiButtonProfile\";\n"
   "   buttonType = \"PushButton\";\n"
   "   command    = \"randomFunction();\";\n"
   "};\n"
   "@endtsexample\n\n"
   
   "@ingroup GuiButtons"
);


//-----------------------------------------------------------------------------

GuiButtonCtrl::GuiButtonCtrl()
{
   setExtent(140, 30);
   mButtonText = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

bool GuiButtonCtrl::onWake()
{
   if( !Parent::onWake() )
      return false;

   // Button Theme?
   if( mProfile->constructBitmapArray() >= 36 )
      mHasTheme = true;
   else
      mHasTheme = false;

   return true;

}

//-----------------------------------------------------------------------------

void GuiButtonCtrl::onRender(Point2I      offset,
                             const RectI& updateRect)
{
   bool highlight = mMouseOver;
   bool depressed = mDepressed;

   ColorI fontColor   = mActive ? ( highlight ? mProfile->mFontColorHL : mProfile->mFontColor ) : mProfile->mFontColorNA;
   ColorI fillColor   = mActive ? ( highlight ? mProfile->mFillColorHL : mProfile->mFillColor ) : mProfile->mFillColorNA;
   ColorI borderColor = mActive ? ( highlight ? mProfile->mBorderColorHL : mProfile->mBorderColor ) : mProfile->mBorderColorNA;

   RectI boundsRect(offset, getExtent());

   if( !mHasTheme )
   {
      if( mProfile->mBorder != 0 )
         renderFilledBorder( boundsRect, borderColor, fillColor, mProfile->mBorderThickness );
      else
         GFX->getDrawUtil()->drawRectFill( boundsRect, fillColor );
   }
   else
   {
      S32 indexMultiplier = 1;
      
      if( !mActive )
         indexMultiplier = 4;
      else if ( mDepressed || mStateOn )
         indexMultiplier = 2;
      else if ( mMouseOver )
         indexMultiplier = 3;

      renderSizableBitmapBordersFilled( boundsRect, indexMultiplier, mProfile );
   }

   Point2I textPos = offset;
   if( depressed )
      textPos += Point2I( 1, 1 );

   GFX->getDrawUtil()->setBitmapModulation( fontColor );
   renderJustifiedText( textPos, getExtent(), mButtonText );

   //render the children
   renderChildControls( offset, updateRect);
}