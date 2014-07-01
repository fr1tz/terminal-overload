// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "core/iTickable.h"
#include "gui/core/guiControl.h"
#include "gui/3d/guiTSControl.h"
#include "math/mathUtils.h"
#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "NOTC/nortdisc.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

class GuiIncomingDiscsHud : public GuiControl
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   // Field data
   ColorF mColor;
   S32 mRotSpeed;

protected:
   void drawDisc(ShapeBase* control, NortDisc* disc);

public:
   GuiIncomingDiscsHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiIncomingDiscsHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays incoming discs.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiIncomingDiscsHud);

#if 0
ConsoleDocClass( GuiIncomingDiscsHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiIncomingDiscsHud()"
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

GuiIncomingDiscsHud::GuiIncomingDiscsHud()
{
   mParent = NULL;
   mColor.set( 1, 1, 1, 1 );
   mRotSpeed = 200;
}

void GuiIncomingDiscsHud::initPersistFields()
{
   addGroup("Rendering");     
   addField("color", TypeColorF, Offset( mColor, GuiIncomingDiscsHud ), "Color for the control"  );
   addField("flickerTime", TypeS32, Offset( mRotSpeed, GuiIncomingDiscsHud ), "Speed of blinking when target is aquired."  );
   endGroup("Rendering");     

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

void GuiIncomingDiscsHud::onRender( Point2I, const RectI &updateRect)
{
   U32 time = Platform::getRealMilliseconds();
   if((time/mRotSpeed) % 2 == 0)
      return;

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

   for(SimSetIterator itr(conn); *itr; ++itr) 
   {
		NortDisc* disc = dynamic_cast<NortDisc*>(*itr);
      if(disc)
         this->drawDisc(control, disc);
   }
}

//----------------------------------------------------------------------------

void GuiIncomingDiscsHud::drawDisc(ShapeBase* control, NortDisc* disc)
{
	if(disc->getTarget() != control)
		return;

	if(disc->state() != NortDisc::Attacking)
		return;

   Point3F targetPos = disc->getPosition();
   Point3F shapePos = control->getBoxCenter();

   F32 targetDist = Point3F(targetPos - control->getPosition()).len();

   Point3F targetVec = targetPos - shapePos;
   MatrixF mat = MathUtils::createOrientFromDir(targetVec);

   Point3F targetPos2D;
   if(!mParent->projectLR(shapePos,targetPos,&targetPos2D))
      return;

   U32 offset = 32;

   Point2I upperLeft(targetPos2D.x-offset/2,targetPos2D.y-offset/2);
   Point2I extent(offset,offset);
   RectI rect(upperLeft, extent);

   if(!rect.isValidRect())
      return;

   GFX->getDrawUtil()->drawRectFill(rect, mColor);

#if 0
	Point3F shapePos = control->getBoxCenter();
	Point3F targetPos = disc->getRenderPosition();

	if( longRangeProject(mParent,shapePos,targetPos,&targetPos) )	
	{
		Point2F pos(targetPos.x, targetPos.y);
		F32 rotation = rotateFunc();
		glLineWidth(4.0);
		glColor4ub(mProfile->mFillColor.red,
			mProfile->mFillColor.green,
			mProfile->mFillColor.blue,
			mProfile->mFillColor.alpha);
		drawAdditiveCircle(pos, 32, 3, rotation, true);
		glLineWidth(2.0);
		glColor4ub(mProfile->mFillColor.red,
			mProfile->mFillColor.green,
			mProfile->mFillColor.blue,
			mProfile->mFillColor.alpha);
		drawAdditiveCircle(pos, 32, 3, rotation, true);
		bool isLocked = false;
		for(int i = 0; i < ShapeBase::MaxMountedImages - 1; i++)
		{
			ShapeBase::MountedImage* image = control->getImageStruct(i); 
			if(!image->dataBlock || !image->state->target || !image->currTarget) continue;
			if(!image->targetState == ShapeBase::MountedImage::TargetAquired) continue;
			if(image->currTarget == disc)
			{
				glLineWidth(1.0);
				glColor4ub(mProfile->mFontColor.red,
					mProfile->mFontColor.green,
					mProfile->mFontColor.blue,
					mProfile->mFontColor.alpha);
				drawAdditiveCircle(pos, 32, 3, rotation, true);
				isLocked = true;
				break;
			}
		}
		if(!isLocked)
		{
			glLineWidth(1.0);
			glColor4ub(mProfile->mFillColor.red,
				mProfile->mFillColor.green,
				mProfile->mFillColor.blue,
				mProfile->mFillColor.alpha);
			drawAdditiveCircle(pos, 32, 3, rotation, true);
		}
	}	

	glLineWidth(1.0);
#endif
}

