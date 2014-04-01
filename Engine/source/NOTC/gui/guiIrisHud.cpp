// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "gui/core/guiControl.h"
#include "gui/controls/guiBitmapCtrl.h"
#include "gui/3d/guiTSControl.h"
#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"
#include "math/mathUtils.h"

class GuiIrisHud : public GuiBitmapCtrl
{
   typedef GuiBitmapCtrl Parent;

	F32 mSizeX;
	F32 mSizeY;

protected:


public:
   GuiIrisHud();

   void onRender( Point2I, const RectI &);
   static void initPersistFields();
   DECLARE_CONOBJECT( GuiIrisHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "TODO" );
};

/// Valid object types for which the cross hair will render, this
/// should really all be script controlled.
static const U32 ObjectMask = PlayerObjectType | VehicleObjectType;

// The following function works pretty similar to GuiTSCtrl::project().
// it's purpose is to convert a 3d point in the world to a 2d point on
// the hud.
// The big difference is that this function should be able to project
// points that are too far away to work with GuiTSCtrl::project();
extern bool longRangeProject(GuiTSCtrl* ctrl, const Point3F& pov, const Point3F& point, Point3F* dest);

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT( GuiIrisHud );

ConsoleDocClass( GuiIrisHud,
	"TODO"
);

GuiIrisHud::GuiIrisHud()
{

}

void GuiIrisHud::initPersistFields()
{
	addField( "sizeX", TypeF32, Offset( mSizeX, GuiIrisHud ), "Horizontal size of iris" );
	addField( "sizeY", TypeF32, Offset( mSizeY, GuiIrisHud ), "Vertical size of iris" );

   Parent::initPersistFields();
}


//-----------------------------------------------------------------------------

void GuiIrisHud::onRender(Point2I offset, const RectI &updateRect)
{
   if(!mTextureObject)
		return;

	// No need to render anything if iris it completely open
	//if(mSizeH >= 1)
	//	return;

	ColorI color(0,0,0,255);

	// Just fill screen if iris is completely closed
	if(mSizeX <= 0 && mSizeY <= 0)
	{
		GFX->getDrawUtil()->drawRectFill(offset, getExtent()+offset, color);
		return;
	}

	S32 w = updateRect.extent.x;
	S32 h = updateRect.extent.y;
	S32 centerx = offset.x + w/2;
	S32 centery = offset.y + h/2;
	S32 radius = ((w > h) ? h : w)/2;

	S32 bitmapWidth = mSizeX * radius;
	S32 bitmapHeight = mSizeY * radius;
	Point2I upperLeft, lowerRight;

	// Draw bitmap
	RectI rect(centerx-bitmapWidth/2, centery-bitmapHeight/2, bitmapWidth, bitmapHeight);
   GFX->getDrawUtil()->setBitmapModulation(color);
   GFX->getDrawUtil()->drawBitmapStretch(mTextureObject, rect, GFXBitmapFlip_None, GFXTextureFilterLinear, false);
	GFX->getDrawUtil()->clearBitmapModulation();

	// Fill space to left of bitmap
	upperLeft.set(updateRect.point.x, updateRect.point.y);
	lowerRight.set(centerx-bitmapWidth/2, updateRect.point.y+h);
	GFX->getDrawUtil()->drawRectFill(upperLeft, lowerRight, color);

	// Fill space to right of bitmap
	upperLeft.set(centerx+bitmapWidth/2, updateRect.point.y);
	lowerRight.set(updateRect.point.x+w, updateRect.point.y+h);
	GFX->getDrawUtil()->drawRectFill(upperLeft, lowerRight, color);

	// Fill space above bitmap
	upperLeft.set(centerx-bitmapWidth/2, updateRect.point.y);
	lowerRight.set(centerx+bitmapWidth/2, centery-bitmapHeight/2);
	GFX->getDrawUtil()->drawRectFill(upperLeft, lowerRight, color);

	// Fill space below bitmap
	upperLeft.set(centerx-bitmapWidth/2, centery+bitmapHeight/2);
	lowerRight.set(centerx+bitmapWidth/2, updateRect.point.y+h);
	GFX->getDrawUtil()->drawRectFill(upperLeft, lowerRight, color);
}
