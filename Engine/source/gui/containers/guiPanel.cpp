// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/containers/guiPanel.h"

#include "console/consoleTypes.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDrawUtil.h"


//-----------------------------------------------------------------------------
// GuiPanel
//-----------------------------------------------------------------------------

ConsoleDocClass( GuiPanel,
	"@brief The GuiPanel panel is a container that when opaque will "
	"draw a left to right gradient using its profile fill and "
	"fill highlight colors.\n\n"

	"@tsexample\n"
	"// Mandatory GuiDefaultProfile\n"
	"// Contains the fill color information required by a GuiPanel\n"
	"// Some values left out for sake of this example\n"
	"new GuiControlProfile (GuiDefaultProfile)\n"
	"{\n"
	"	// fill color\n"
	"	opaque = false;\n"
	"	fillColor = \"242 241 240\";\n"
	"	fillColorHL =\"228 228 235\";\n"
	"	fillColorSEL = \"98 100 137\";\n"
	"	fillColorNA = \"255 255 255 \";\n"
	"};\n\n"
	"new GuiPanel(TestPanel)\n"
	"{\n"
	"	position = \"45 33\";\n"
	"	extent = \"342 379\";\n"
	"	minExtent = \"16 16\";\n"
	"	horizSizing = \"right\";\n"
	"	vertSizing = \"bottom\";\n"
	"	profile = \"GuiDefaultProfile\"; // Color fill info is in this profile\n"
	"	isContainer = \"1\";\n"
	"};\n"
	"@endtsexample\n\n"

	"@see GuiControlProfile\n"

	"@ingroup GuiContainers\n");

GuiPanel::GuiPanel()
{
   setMinExtent( Point2I( 16,16 ) );
   setDocking( Docking::dockNone );
   
   mIsContainer = true;
}

GuiPanel::~GuiPanel()
{
}

IMPLEMENT_CONOBJECT(GuiPanel);


void GuiPanel::onRender(Point2I offset, const RectI &updateRect)
{
   if ( !mProfile->mOpaque )
   {
      RectI ctrlRect = getClientRect();
      ctrlRect.point += offset;

      // Draw border.

      if( mProfile->mBorder != 0 )
      {
         GFX->getDrawUtil()->drawRectFill( ctrlRect, mProfile->mBorderColor );
         ctrlRect.inset( mProfile->mBorderThickness, mProfile->mBorderThickness );
      }

      // Draw a gradient left to right.

      PrimBuild::begin( GFXTriangleStrip, 4 );
         PrimBuild::color( mProfile->mFillColorHL );
         PrimBuild::vertex2i( ctrlRect.point.x, ctrlRect.point.y );
         PrimBuild::vertex2i( ctrlRect.point.x, ctrlRect.point.y + ctrlRect.extent.y );

         PrimBuild::color( mProfile->mFillColor );
         PrimBuild::vertex2i( ctrlRect.point.x + ctrlRect.extent.x, ctrlRect.point.y);
         PrimBuild::vertex2i( ctrlRect.point.x + ctrlRect.extent.x, ctrlRect.point.y + ctrlRect.extent.y );
      PrimBuild::end();
   }

   Parent::onRender( offset, updateRect );
}