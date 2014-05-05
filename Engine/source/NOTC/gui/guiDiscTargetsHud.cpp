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

class GuiDiscTargetsHud : public GuiControl, public virtual ITickable
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   // Field data
   S32 mHudInfoType;
   ColorF   mFrameColor;

   U32 mCurrTick;

protected:
   void drawTarget(GameBase* control, HudInfo* hudInfo);

public:
   GuiDiscTargetsHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiDiscTargetsHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays disc targets.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiDiscTargetsHud);

#if 0
ConsoleDocClass( GuiDiscTargetsHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiDiscTargetsHud()"
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

GuiDiscTargetsHud::GuiDiscTargetsHud()
{
   mParent = NULL;
   mHudInfoType = 1;
   mFrameColor.set( 1, 1, 1, 1 );
   mCurrTick = 0;
}

void GuiDiscTargetsHud::initPersistFields()
{
   addGroup("Colors");     
   addField( "frameColor", TypeColorF, Offset( mFrameColor, GuiDiscTargetsHud ), "Color for the control's frame."  );
   endGroup("Colors");     

   addGroup("Misc");       
   addField( "hudInfoType",   TypeS32, Offset( mHudInfoType, GuiDiscTargetsHud ), "The type of HudInfo objects to render." );
   endGroup("Misc");

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

void GuiDiscTargetsHud::onRender( Point2I, const RectI &updateRect)
{
   // Must be in a TS Control
   mParent = dynamic_cast<GuiTSCtrl*>(getParent());
   if(!mParent) 
      return;

   if(mCurrTick % 2)
      return;

   // Must have a connection and control object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn) return;
   GameBase * control = dynamic_cast<GameBase*>(conn->getControlObject());
   if (!control) return;

	control->disableCollision();

	SimSet* hudInfoSet = Sim::getClientHudInfoSet();
	for(SimObject** itr = hudInfoSet->begin(); itr != hudInfoSet->end(); itr++)
	{
		HudInfo* hudInfo = dynamic_cast<HudInfo*>(*itr);
		if(hudInfo && hudInfo->getType() == mHudInfoType)
		{  
			drawTarget(control, hudInfo);			
		}
	}

	control->enableCollision();
}

void GuiDiscTargetsHud::processTick()
{
   mCurrTick++;
}

//----------------------------------------------------------------------------

void GuiDiscTargetsHud::drawTarget(GameBase* control, HudInfo* hudInfo)
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

      GFX->getDrawUtil()->drawRect(rect, mFrameColor);
   }
}

