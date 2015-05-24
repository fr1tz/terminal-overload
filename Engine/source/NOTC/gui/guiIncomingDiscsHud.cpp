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
   S32 mRotSpeed;
   String mBitmap;
   GFXTexHandle mTex;

protected:
   void drawDisc(ShapeBase* control, NortDisc* disc);

public:
   GuiIncomingDiscsHud();

   // GuiControl
   virtual bool onWake();
   virtual void onSleep();
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
   mRotSpeed = 200;
}

void GuiIncomingDiscsHud::initPersistFields()
{
   addGroup("Rendering");     
   addField("rotSpeed", TypeS32, Offset( mRotSpeed, GuiIncomingDiscsHud ), "How fast the bitmap over the disc rotates"  );
   addField("bitmap", TypeImageFilename, Offset( mBitmap, GuiIncomingDiscsHud ), "Bitmap drawn over discs."  );
   endGroup("Rendering");     

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

bool GuiIncomingDiscsHud::onWake()
{
   if(!Parent::onWake())
      return false;

   if(mBitmap.isNotEmpty())
      mTex.set(mBitmap, &GFXDefaultGUIProfile, avar("%s() - mBitmap (line %d)", __FUNCTION__, __LINE__) );
   else
      mTex = NULL;

   return true;
}

void GuiIncomingDiscsHud::onSleep()
{
   mTex = NULL;

   Parent::onSleep();
}

void GuiIncomingDiscsHud::onRender( Point2I, const RectI &updateRect)
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

   Point3F targetPos = disc->getRenderPosition();
   Point3F shapePos = control->getBoxCenter();

   Point3F targetPos2D;
   if(!mParent->projectLR(shapePos,targetPos,&targetPos2D))
      return;

   Point3F center(targetPos2D.x, targetPos2D.y, 0);

   Point2I upperLeft(-32, -32);
   Point2I extent(64, 64);
   RectI rect(upperLeft, extent);

   GFX->pushWorldMatrix();

   F32 time = Sim::getCurrentTime();
   F32 rot = 0;
   if(mRotSpeed > 0)
      rot = (time/mRotSpeed);
   MatrixF rotMat(EulerF(0.0, 0.0, -rot), center);

   GFX->multWorld(rotMat);

   if(mTex)
   {
      GFX->getDrawUtil()->setBitmapModulation(mProfile->mFillColor);
      GFX->getDrawUtil()->drawBitmapStretch(mTex, rect,
         GFXBitmapFlip_None, GFXTextureFilterLinear, false);
      GFX->getDrawUtil()->clearBitmapModulation();
   }
   else
   {
      GFX->getDrawUtil()->drawRect(rect, mProfile->mFillColor);
   }

   GFX->popWorldMatrix();
}

