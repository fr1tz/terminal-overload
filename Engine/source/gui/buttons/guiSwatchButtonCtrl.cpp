// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/buttons/guiSwatchButtonCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"

IMPLEMENT_CONOBJECT( GuiSwatchButtonCtrl );

ConsoleDocClass( GuiSwatchButtonCtrl,
   "@brief A button that is used to represent color; often used in correlation with a color picker.\n\n"
   
   "A swatch button is a push button that uses its color field to designate the color drawn over an image, on top of a button.\n\n"
   
   "The color itself is a float value stored inside the GuiSwatchButtonCtrl::color field. The texture path that represents\n"
   "the image underlying the color is stored inside the GuiSwatchButtonCtrl::gridBitmap field.\n"
   "The default value assigned toGuiSwatchButtonCtrl::color is \"1 1 1 1\"( White ). The default/fallback image assigned to \n"
   "GuiSwatchButtonCtrl::gridBitmap is \"tools/gui/images/transp_grid\".\n\n"
   
   "@tsexample\n"
   "// Create a GuiSwatchButtonCtrl that calls randomFunction with its current color when clicked\n"
   "%swatchButton = new GuiSwatchButtonCtrl()\n"
   "{\n"
   "   profile = \"GuiInspectorSwatchButtonProfile\";\n"
   "   command = \"randomFunction( $ThisControl.color );\";\n"
   "};\n"
   "@endtsexample\n\n"
   
   "@ingroup GuiButtons"
);

//-----------------------------------------------------------------------------

GuiSwatchButtonCtrl::GuiSwatchButtonCtrl()
 : mSwatchColor( 1, 1, 1, 1 )
{
   mButtonText = StringTable->insert( "" );   
   setExtent(140, 30);
   
   static StringTableEntry sProfile = StringTable->insert( "profile" );
   setDataField( sProfile, NULL, "GuiInspectorSwatchButtonProfile" );

   mGridBitmap = "tools/gui/images/transp_grid";
}

void GuiSwatchButtonCtrl::initPersistFields()
{
   addField( "color", TypeColorF, Offset( mSwatchColor, GuiSwatchButtonCtrl ), "The foreground color of GuiSwatchButtonCtrl" );

   addField( "gridBitmap", TypeString, Offset( mGridBitmap, GuiSwatchButtonCtrl ), "The bitmap used for the transparent grid" );
   
   Parent::initPersistFields();
}

bool GuiSwatchButtonCtrl::onWake()
{      
   if ( !Parent::onWake() )
      return false;

   if ( mGrid.isNull() )
      mGrid.set( mGridBitmap, &GFXDefaultGUIProfile, avar("%s() - mGrid (line %d)", __FUNCTION__, __LINE__) );

   return true;
}

void GuiSwatchButtonCtrl::onRender( Point2I offset, const RectI &updateRect )
{
   bool highlight = mMouseOver;

   ColorI backColor   = mSwatchColor;
   ColorI borderColor = mActive ? ( highlight ? mProfile->mBorderColorHL : mProfile->mBorderColor ) : mProfile->mBorderColorNA;

   RectI renderRect( offset, getExtent() );
   if ( !highlight )
      renderRect.inset( 1, 1 );      

   GFXDrawUtil *drawer = GFX->getDrawUtil();
   drawer->clearBitmapModulation();

   // Draw background transparency grid texture...
   if ( mGrid.isValid() )
      drawer->drawBitmapStretch( mGrid, renderRect );

   // Draw swatch color as fill...
   drawer->drawRectFill( renderRect, mSwatchColor );

   // Draw any borders...
   drawer->drawRect( renderRect, borderColor );
}

//-----------------------------------------------------------------------------

DefineEngineMethod( GuiSwatchButtonCtrl, setColor, void, ( const char* newColor ),,
   "Set the color of the swatch control.\n"
   "@param newColor The new color string given to the swatch control in float format \"r g b a\".\n"
   "@note It's also important to note that when setColor is called causes\n"
   "the control's altCommand field to be executed." )
{
   object->setField( "color", newColor );
   object->execAltConsoleCallback();
}
