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

class GuiFriendOrFoeHud : public GuiControl
{
   typedef GuiControl Parent;

   GuiTSCtrl* mParent;

   // Field data
   S32 mHudInfoDatasetType_TeamID;
   String mFriendBitmap;
   GFXTexHandle mFriendTex;
   String mFoeBitmap;
   GFXTexHandle mFoeTex;

protected:
   void drawInfo(GameBase* control, HudInfo* hudInfo);

public:
   GuiFriendOrFoeHud();

   // GuiControl
   virtual bool onWake();
   virtual void onSleep();
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiFriendOrFoeHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Identifies friendlies and foes.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiFriendOrFoeHud);

#if 0
ConsoleDocClass( GuiFriendOrFoeHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiFriendOrFoeHud()"
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

GuiFriendOrFoeHud::GuiFriendOrFoeHud()
{
   mParent = NULL;
   mHudInfoDatasetType_TeamID = 2;
   mFriendTex = NULL;
   mFoeTex = NULL;
}

void GuiFriendOrFoeHud::initPersistFields()
{
   addGroup("Rendering");   
   addField( "hudInfoDatasetType_TeamID", TypeS32, Offset( mHudInfoDatasetType_TeamID, GuiFriendOrFoeHud ),
      "The type of HudInfo dataset that contains a team ID." );
   addField("friendBitmap", TypeImageFilename, Offset( mFriendBitmap, GuiFriendOrFoeHud ), "Bitmap used for friendlies."  );
   addField("foeBitmap", TypeImageFilename, Offset( mFoeBitmap, GuiFriendOrFoeHud ), "Bitmap used for foes."  );
   endGroup("Rendering");     

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

bool GuiFriendOrFoeHud::onWake()
{
   if(!Parent::onWake())
      return false;

   if(mFriendBitmap.isNotEmpty())
      mFriendTex.set(mFriendBitmap, &GFXDefaultGUIProfile, avar("%s() - mFriendBitmap (line %d)", __FUNCTION__, __LINE__) );
   else
      mFriendTex = NULL;

   if(mFoeBitmap.isNotEmpty())
      mFoeTex.set(mFoeBitmap, &GFXDefaultGUIProfile, avar("%s() - mFoeBitmap (line %d)", __FUNCTION__, __LINE__) );
   else
      mFoeTex = NULL;

   return true;
}

void GuiFriendOrFoeHud::onSleep()
{
   mFriendTex = NULL;
   mFoeTex = NULL;

   Parent::onSleep();
}

void GuiFriendOrFoeHud::onRender( Point2I, const RectI &updateRect)
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

   SimSet* hudInfoSet = Sim::getClientHudInfoSet();
   for(SimObject** itr = hudInfoSet->begin(); itr != hudInfoSet->end(); itr++)
   {
      HudInfo* hudInfo = dynamic_cast<HudInfo*>(*itr);
      if(!hudInfo)
         continue;

      this->drawInfo(control, hudInfo);
   }
}

//----------------------------------------------------------------------------

void GuiFriendOrFoeHud::drawInfo(GameBase* control, HudInfo* hudInfo)
{
   // Grab team ID
   S32 teamID = hudInfo->getDataSetIntField(mHudInfoDatasetType_TeamID);
   if(!teamID)
      return;

   // Check if we should ignore this HudInfo object
   if(hudInfo->getDataSetBoolField(mHudInfoDatasetType_TeamID))
      return;

   SceneObject* obj = hudInfo->getObject();

   // Ignore our control object.
   if(obj == control)
      return;

   Point3F targetPos = obj ? obj->getRenderWorldBox().getCenter() : hudInfo->getPosition();
   Point3F controlPos = control->getRenderWorldBox().getCenter();

   F32 targetDist = Point3F(targetPos - controlPos).len();

   Point3F targetVec = targetPos - controlPos;
   MatrixF mat = MathUtils::createOrientFromDir(targetVec);

   Box3F box(-1, -1, -1, 1, 1, 1); 
   if(obj)
      box = obj->getRenderWorldBox();

   F32 len = box.len_x() > box.len_z() ? box.len_x()/2 : box.len_z()/2;

   Point3F x; mat.getColumn(0,&x); x.normalize(); x *= len; 
   Point3F z; mat.getColumn(2,&z); z.normalize(); z *= len;

   Point3F a = targetPos - x + z;
   Point3F b = targetPos + x - z;

   if(mParent->projectLR(controlPos,a,&a) && mParent->projectLR(controlPos,b,&b))
   {
      Point2I A(a.x,a.y);
      Point2I B(b.x,b.y);

      F32 s = Point2I(B-A).len();

      Point2I extent(b.x-a.x,b.y-a.y);

      Point3F targetPos2D;
      if(!mParent->projectLR(controlPos,targetPos,&targetPos2D))
         return;

      U32 offset = s;
      if( offset < 24 ) offset = 24;

      Point2I upperLeft(targetPos2D.x-offset/2,targetPos2D.y-offset/2);
      extent.set(offset,offset);
      RectI rect(upperLeft,extent);

      if(!rect.isValidRect())
         return;

      //GFX->getDrawUtil()->drawRect(rect, ColorI(0, 255, 0, 255));

	   ColorI color = mProfile->mFontColor;
      color.alpha = 255;
      if(obj && obj->getTypeMask() & ShapeBaseObjectType)
      {
         ShapeBase* shape = static_cast<ShapeBase*>(obj);
         color.alpha -= shape->getDamageValue() * 230.0f;
      }
      GFX->getDrawUtil()->setBitmapModulation(color);

      if(teamID == control->getTeamId() && mFriendTex)
      {
         GFX->getDrawUtil()->drawBitmapStretch(mFriendTex, rect,
            GFXBitmapFlip_None, GFXTextureFilterLinear, false);
      }
      else if(mFoeTex)
      {
         GFX->getDrawUtil()->drawBitmapStretch(mFoeTex, rect,
            GFXBitmapFlip_None, GFXTextureFilterLinear, false);
      }
      GFX->getDrawUtil()->clearBitmapModulation();
   }
}

