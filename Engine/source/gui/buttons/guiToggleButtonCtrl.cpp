// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/buttons/guiToggleButtonCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"

IMPLEMENT_CONOBJECT(GuiToggleButtonCtrl);

ConsoleDocClass( GuiToggleButtonCtrl,
   "@brief Deprecated gui control.\n\n"
   
   "@deprecated GuiToggleButtonCtrl's functionality is solely based on GuiButtonBaseCtrl's ButtonTypeCheck type.\n\n"
   
   "@see GuiButtonCtrl\n"
   "@see GuiCheckBoxCtrl\n"
   
   "@ingroup GuiButtons"
);

//-----------------------------------------------------------------------------

GuiToggleButtonCtrl::GuiToggleButtonCtrl()
{
   setExtent(140, 30);
   mButtonText = StringTable->insert("");
   mStateOn = false;
   mButtonType = ButtonTypeCheck;
}

void GuiToggleButtonCtrl::onPreRender()
{
   Parent::onPreRender();

   // If we have a script variable, make sure we're in sync
   if ( mConsoleVariable[0] )
   	mStateOn = Con::getBoolVariable( mConsoleVariable );
}

void GuiToggleButtonCtrl::onRender(Point2I      offset,
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
   else if( mHasTheme )
   {
      S32 indexMultiplier = 1;
      if ( !mActive )
         indexMultiplier = 4;
      else if ( mDepressed || mStateOn )
         indexMultiplier = 2;
      else if ( mMouseOver )
         indexMultiplier = 3;


      renderSizableBitmapBordersFilled( boundsRect, indexMultiplier, mProfile );
   }

   Point2I textPos = offset;
   if(depressed)
      textPos += Point2I(1,1);

   GFX->getDrawUtil()->setBitmapModulation( fontColor );
   renderJustifiedText(textPos, getExtent(), mButtonText);

   //render the children
   renderChildControls( offset, updateRect);
}
