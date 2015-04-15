// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "core/iTickable.h"
#include "gui/core/guiControl.h"
#include "gui/3d/guiTSControl.h"
#include "math/mathUtils.h"
#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "T3D/projectile.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

class notcGuiProjectilesHud : public GuiControl
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   S32 mRotSpeed;
   F32 mTargetDist;

protected:
   void drawProjectileBox(ShapeBase* control, Projectile* prj);
   void drawProjectileLine(ShapeBase* control, Projectile* prj);

public:
   notcGuiProjectilesHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   static void initPersistFields();
   DECLARE_CONOBJECT( notcGuiProjectilesHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays overlays over the players projectiles.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(notcGuiProjectilesHud);

#if 0
ConsoleDocClass( notcGuiProjectilesHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new notcGuiProjectilesHud()"
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

notcGuiProjectilesHud::notcGuiProjectilesHud()
{
   mParent = NULL;
   mRotSpeed = 200;
   mTargetDist = 0;
}

void notcGuiProjectilesHud::initPersistFields()
{
   addGroup("Rendering");     
   addField("flickerTime", TypeS32, Offset( mRotSpeed, notcGuiProjectilesHud ), "Speed of blinking when target is aquired."  );
   addField("targetDist", TypeF32, Offset( mTargetDist, notcGuiProjectilesHud ), "Distance to target."  );
   endGroup("Rendering");     

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

void notcGuiProjectilesHud::onRender( Point2I, const RectI &updateRect)
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
		Projectile* prj = dynamic_cast<Projectile*>(*itr);
      if(prj && prj->mSourceObject == control && prj->isAlive())
      {
         this->drawProjectileBox(control, prj);
         this->drawProjectileLine(control, prj);
      }
   }
}

//----------------------------------------------------------------------------

void notcGuiProjectilesHud::drawProjectileBox(ShapeBase* control, Projectile* prj)
{
   Point3F pos = prj->getRenderPosition();
   Point3F controlPos = control->getBoxCenter();
   F32 projectileDist = Point3F(pos - controlPos).len();

   Point3F vec = pos - controlPos;
   MatrixF mat = MathUtils::createOrientFromDir(vec);

   F32 len = 0.25;
   Point3F x; mat.getColumn(0,&x); x.normalize(); x *= len; 
   Point3F z; mat.getColumn(2,&z); z.normalize(); z *= len;

   Point3F pos2D;
   if(!mParent->projectLR(controlPos,pos,&pos2D))
      return;

   Point3F a = pos - x + z;
   mParent->projectLR(controlPos,a,&a);

   Point3F b = pos + x - z;
   mParent->projectLR(controlPos,b,&b);

   Point2I A(a.x,a.y);
   Point2I B(b.x,b.y);

   F32 s = Point2I(B-A).len();

   U32 offset = s;
   if( offset < 2 ) offset = 2;

   Point2I upperLeft(pos2D.x-offset/2,pos2D.y-offset/2);
   Point2I extent(offset,offset);
   RectI rect(upperLeft,extent);

   if(!rect.isValidRect())
      return;

   ColorI color = mProfile->mFillColor;
   if(mTargetDist != 0 && projectileDist > mTargetDist)
      color = mProfile->mFillColorNA;

   //GFX->getDrawUtil()->drawRectFill(rect, color);

   U32 time = Platform::getRealMilliseconds();
   F32 spin = time % 360;
   GFX->getDrawUtil()->setBitmapModulation(color);
   GFX->getDrawUtil()->draw2DSquare(Point2F(pos2D.x, pos2D.y), offset, spin);
   GFX->getDrawUtil()->clearBitmapModulation();
}

void notcGuiProjectilesHud::drawProjectileLine(ShapeBase* control, Projectile* prj)
{
   Point3F vec = prj->mCurrVelocity; vec.normalize(); vec *= 5;
   Point3F p1 = prj->getRenderPosition();
   Point3F p2 = p1 - vec;
   Point3F controlPos = control->getBoxCenter();
   F32 projectileDist = Point3F(p1 - controlPos).len();

   if(!mParent->projectLR(controlPos,p1,&p1))
      return;

   if(!mParent->projectLR(controlPos,p2,&p2))
      p2 = p1;

   ColorI color = mProfile->mFillColor;
   if(mTargetDist != 0 && projectileDist > mTargetDist)
      color = mProfile->mFillColorNA;

   GFX->getDrawUtil()->drawLine(p1.x, p1.y, p2.x, p2.y, color);
}
