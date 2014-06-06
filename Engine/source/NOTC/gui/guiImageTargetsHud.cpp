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

class GuiImageTargetsHud : public GuiControl
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   // Field data
   ColorF mColor;
   S32 mBlinkTime;

public:
   GuiImageTargetsHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

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
   if(!conn)
      return;
   ShapeBase* control = dynamic_cast<ShapeBase*>(conn->getControlObject());
   if(!control)
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
