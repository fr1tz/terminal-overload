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

class GuiDynamicCrossHairHud : public GuiBitmapCtrl
{
   typedef GuiBitmapCtrl Parent;

	F32 mSize;
	F32 mAlphaFactor;

protected:


public:
   GuiDynamicCrossHairHud();

   void onRender( Point2I, const RectI &);
   static void initPersistFields();
   DECLARE_CONOBJECT( GuiDynamicCrossHairHud );
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
bool longRangeProject(GuiTSCtrl* ctrl, const Point3F& pov, const Point3F& point, Point3F* dest)
{
   // first try to project using GuiTSCtrl::project()...
	bool success =	ctrl->project(point,dest);
	
	if(success)
		return true;
	else
	{
		// If the projection failed, simply try to pull the point nearer to the point of view.
		// note: only do this if the point is "pretty far" away, because if it
		// isn't, using GuiTSCtrl::project() wouldn't have failed in the first place.
		F32 visDistance = gClientSceneGraph->getVisibleDistance();
		F32 dist = (pov-point).len();
		if( dist > visDistance*0.9 )
		{
			Point3F newPoint = point-pov;
			newPoint.normalize(); newPoint *= visDistance*0.9;
			newPoint = pov+newPoint;

			success = ctrl->project(newPoint,dest);
			if(success)
			   return true;
			else 
			   return false;
		}
		else
			return false;
	}

	return false;
}


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT( GuiDynamicCrossHairHud );

ConsoleDocClass( GuiDynamicCrossHairHud,
	"TODO"
);

GuiDynamicCrossHairHud::GuiDynamicCrossHairHud()
{

}

void GuiDynamicCrossHairHud::initPersistFields()
{
	addField( "size", TypeF32, Offset( mSize, GuiDynamicCrossHairHud ), "Size of the bitmap. Anything other than 0 mean static size." );
	addField( "alphaFactor", TypeF32, Offset( mAlphaFactor, GuiDynamicCrossHairHud ), "TODO" );

   Parent::initPersistFields();
}


//-----------------------------------------------------------------------------

void GuiDynamicCrossHairHud::onRender(Point2I offset, const RectI &updateRect)
{
   // Must be in a TS Control
   GuiTSCtrl* parent = dynamic_cast<GuiTSCtrl*>(this->getParent());
   if(!parent) return;

   // Must have a connection and player control object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn)
      return;
   ShapeBase* control = dynamic_cast<ShapeBase*>(conn->getControlObject());
   if (!control || !(control->getTypeMask() & ObjectMask) || !conn->isFirstPerson())
      return;

	S32 w = updateRect.extent.x;
	S32 h = updateRect.extent.y;
	S32 centerx = offset.x + w/2;
	S32 centery = offset.y + h/2;
	S32 radius = ((w > h) ? h : w)/2;

	F32 crosshairAlpha = 1.0;
	F32 crosshairOffset = mSize/4;

	ShapeBase::MountedImage* image = control->getImageStruct(0);
	if(image && image->dataBlock)
	{
	   F32 r = image->inaccuracy.enabled ? image->inaccuracy.radius : 0;
      if(mSize == 0)
		{
			Point3F muzzlePoint, muzzleVector;
			control->getRenderMuzzlePoint(0, &muzzlePoint);
			control->getRenderMuzzleVector(0, &muzzleVector);
			muzzleVector.normalize();
			MatrixF mat = MathUtils::createOrientFromDir(muzzleVector);
			Point3F zv; mat.getColumn(2, &zv);
			zv.normalize();
			Point3F c = muzzlePoint + muzzleVector*image->inaccuracy.distance;
			Point3F e = c + zv*r;
			control->getEyeTransform(&mat);
			Point3F pov = mat.getPosition();
			longRangeProject(parent, pov, c, &c);
			longRangeProject(parent, pov, e, &e);
			crosshairOffset = mAbs(e.y - c.y);
		}
		if(mAlphaFactor != 0)
			crosshairAlpha = mClampF(1.0 - r/mAlphaFactor, 0, 1);
		//Con::printf("%f -> %f", crosshairOffset, crosshairAlpha);
		//Con::printf("crosshairOffset: %f", crosshairOffset);
	}


   if (mTextureObject)
   {
		ColorI cmod(255, 255, 255, crosshairAlpha*255.0); 
		F32 off = crosshairOffset*2;
		RectI rect(centerx-off, centery-off, off*2, off*2);
      GFX->getDrawUtil()->setBitmapModulation(cmod);
      GFX->getDrawUtil()->drawBitmapStretch(mTextureObject, rect, GFXBitmapFlip_None, GFXTextureFilterLinear, false);
		GFX->getDrawUtil()->clearBitmapModulation();
	}
}
