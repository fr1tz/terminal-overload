// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "core/iTickable.h"
#include "gui/core/guiControl.h"
#include "gui/3d/guiTSControl.h"
#include "math/mathUtils.h"
#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "NOTC/hudInfo.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

class GuiImageTargetsHud : public GuiControl, public virtual ITickable
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   // Field data
   ColorF mColor;
   S32 mBlinkTime;

   U32 mCurrTick;

protected:
   void drawTarget(GameBase* control, HudInfo* hudInfo);

public:
   GuiImageTargetsHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiImageTargetsHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays disc targets.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiImageTargetsHud);

#if 0
ConsoleDocClass( GuiImageTargetsHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiImageTargetsHud()"
		"{\n"
		"	fillColor = \"0.0 1.0 0.0 1.0\"; // Fills with a solid green color\n"
		"	frameColor = \"1.0 1.0 1.0 1.0\"; // Solid white frame color\n"
		"	textColor = \"1.0 1.0 1.0 1.0\"; // Solid white text Color\n"
		"	showFill = \"true\";\n"
		"	showFrame = \"true\";\n"
		"	labelFillColor = \"0.0 1.0 0.0 1.0\"; // Fills with a solid green color\n"
		"	labelFrameColor = \"1.0 1.0 1.0 1.0\"; // Solid white frame color\n"
		"	showLabelFill = \"true\";\n"
		"	showLabelFrame = \"true\";\n"
		"	verticalOffset = \"0.15\";\n"
		"	distanceFade = \"15.0\";\n"
		"};\n"
   "@endtsexample\n\n"
   
   "@ingroup GuiGame\n"
);
#endif

GuiImageTargetsHud::GuiImageTargetsHud()
{
   mParent = NULL;
   mColor.set( 1, 1, 1, 1 );
   mBlinkTime = 200;
   mCurrTick = 0;
}

void GuiImageTargetsHud::initPersistFields()
{
   addGroup("Rendering");     
   addField("color", TypeColorF, Offset( mColor, GuiImageTargetsHud ), "Color for the control"  );
   addField("blinkTime", TypeS32, Offset( mBlinkTime, GuiImageTargetsHud ), "Speed of blinking when target is aquired."  );
   endGroup("Rendering");     

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

void GuiImageTargetsHud::onRender( Point2I, const RectI &updateRect)
{
   // Must be in a TS Control
   mParent = dynamic_cast<GuiTSCtrl*>(getParent());
   if(!mParent) 
      return;

   // Must have a connection and control object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn)
      return;
   ShapeBase* control = dynamic_cast<ShapeBase*>(conn->getControlObject());
   if (!control)
      return;

	for(int i = 0; i < ShapeBase::MaxMountedImages - 1; i++)
	{
		ShapeBase::MountedImage* image = control->getImageStruct(i); 
		if(!image->dataBlock)
         continue;
		if(!image->state->target)
         continue;
      if(!image->currTarget)
         continue;
		if(image->targetState == ShapeBase::MountedImage::NoTarget)
         continue;

		Point3F shapePos = control->getBoxCenter();
		Point3F targetPos = image->currTarget->getBoxCenter();

		if(mParent->projectLR(shapePos,targetPos,&targetPos) )	
		{
			Point2F pos(targetPos.x, targetPos.y);

			F32 radius = 0;
			if(image->targetState == ShapeBase::MountedImage::TargetLocked)
         {
            U32 time = Platform::getRealMilliseconds();
            if((time/mBlinkTime) % 2 == 0)
               return;
         }
         else
            radius = (image->remainingLockTime/image->initialLockTime)*100;

         Point2F a, b;

         a = pos + Point2F(-1,-1)*(radius);
         b = pos + Point2F(-1,-1)*(radius+32);
         GFX->getDrawUtil()->drawLine(a, b, mColor);

         a = pos + Point2F(-1,1)*(radius);
         b = pos + Point2F(-1,1)*(radius+32);
         GFX->getDrawUtil()->drawLine(a, b, mColor);

         a = pos + Point2F(1,-1)*(radius);
         b = pos + Point2F(1,-1)*(radius+32);
         GFX->getDrawUtil()->drawLine(a, b, mColor);

         a = pos + Point2F(1,1)*(radius);
         b = pos + Point2F(1,1)*(radius+32);
         GFX->getDrawUtil()->drawLine(a, b, mColor);
		}	
	}
}

void GuiImageTargetsHud::processTick()
{
   mCurrTick++;
}

//----------------------------------------------------------------------------

void GuiImageTargetsHud::drawTarget(GameBase* control, HudInfo* hudInfo)
{
   SceneObject* obj = hudInfo->getObject();

   Point3F targetPos = obj ? obj->getBoxCenter() : hudInfo->getPosition();

   Point3F shapePos = control->getBoxCenter();

   F32 targetDist = Point3F(targetPos - control->getPosition()).len();

   Point3F targetVec = targetPos - shapePos;
   MatrixF mat = MathUtils::createOrientFromDir(targetVec);

   Box3F box(-1, -1, -1, 1, 1, 1); 
   if(obj)
      box = obj->getRenderWorldBox();

   F32 len = box.len_x() > box.len_z() ? box.len_x()/2 : box.len_z()/2;

   Point3F x; mat.getColumn(0,&x); x.normalize(); x *= len; 
   Point3F z; mat.getColumn(2,&z); z.normalize(); z *= len;

   Point3F a = targetPos - x + z;
   Point3F b = targetPos + x - z;

   if(mParent->projectLR(shapePos,a,&a) && mParent->projectLR(shapePos,b,&b))
   {
      Point2I A(a.x,a.y);
      Point2I B(b.x,b.y);

      F32 s = Point2I(B-A).len();

      Point2I extent(b.x-a.x,b.y-a.y);

      Point3F targetPos2D;
      if(!mParent->projectLR(shapePos,targetPos,&targetPos2D))
         return;

      U32 offset = s;
      if( offset < 24 ) offset = 24;

      Point2I upperLeft(targetPos2D.x-offset/2,targetPos2D.y-offset/2);
      extent.set(offset,offset);
      RectI rect(upperLeft,extent);

      if(!rect.isValidRect())
         return;

      GFX->getDrawUtil()->drawRect(rect, mColor);
   }
}

