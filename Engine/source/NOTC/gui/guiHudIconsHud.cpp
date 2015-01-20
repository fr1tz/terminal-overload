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

class GuiHudIconsHud : public GuiControl
{
   typedef GuiControl Parent;

   struct Color {
      S32 id;
      ColorI color;
   };

   struct Icon {
      S32 id;
      GFXTexHandle tex;
      U32 size;
   };

   GuiTSCtrl* mParent;

   // Field data
   S32 mHudInfoDatasetType_Color;
   S32 mHudInfoDatasetType_Icon;

   Vector<Color*> mColors;
   Vector<Icon*> mIcons;

protected:
   void drawInfo(GameBase* control, HudInfo* hudInfo);

public:
   GuiHudIconsHud();
   ~GuiHudIconsHud();

   // GuiControl
   virtual bool onWake();
   virtual void onSleep();
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // ITickable
   void processTick();
   void interpolateTick(F32 delta) {};
   void advanceTime(F32 timeDelta) {};

   // GuiHudIconsHud
   void clearColors();
   void addColor(S32 id, ColorI color);
   void clearIcons();
   void addIcon(S32 id, String bitmap, U32 size);

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiHudIconsHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays icons from HudInfo objects on the HUD.\n"
      "Must be a child of a GuiTSCtrl and a server connection must be present." );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiHudIconsHud);

#if 0
ConsoleDocClass( GuiHudIconsHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiHudIconsHud()"
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

GuiHudIconsHud::GuiHudIconsHud()
{
   mParent = NULL;
   mHudInfoDatasetType_Color = 2;
   mHudInfoDatasetType_Icon = 3;
}

GuiHudIconsHud::~GuiHudIconsHud()
{
   this->clearColors();
   this->clearIcons();
}

void GuiHudIconsHud::initPersistFields()
{
   addGroup("Main");
   addField( "hudInfoDatasetType_Color", TypeS32, Offset( mHudInfoDatasetType_Color, GuiHudIconsHud ),
      "The type of HudInfo dataset that identifies a color." );
   addField( "hudInfoDatasetType_Icon", TypeS32, Offset( mHudInfoDatasetType_Icon, GuiHudIconsHud ),
      "The type of HudInfo dataset that identifies an icon." );
   endGroup("Main"); 

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

bool GuiHudIconsHud::onWake()
{
   if(!Parent::onWake())
      return false;

   return true;
}

void GuiHudIconsHud::onSleep()
{
   Parent::onSleep();
}

void GuiHudIconsHud::onRender( Point2I, const RectI &updateRect)
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

void GuiHudIconsHud::clearColors()
{
   for(U32 i = 0; i < mColors.size(); i++)
      delete mColors[i];
   mColors.clear();
}

void GuiHudIconsHud::addColor(S32 id, ColorI color)
{
   Color* c = new Color;
   c->id = id;
   c->color = color;
   mColors.push_back(c);
}

//----------------------------------------------------------------------------

void GuiHudIconsHud::clearIcons()
{
   for(U32 i = 0; i < mIcons.size(); i++)
      delete mIcons[i];
   mIcons.clear();
}

void GuiHudIconsHud::addIcon(S32 id, String bitmap, U32 size)
{
   Icon* icon = new Icon;
   icon->id = id;
   icon->tex.set(bitmap, &GFXDefaultGUIProfile, avar("%s() - Icon.tex (line %d)", __FUNCTION__, __LINE__) );
   icon->size = size;
   mIcons.push_back(icon);
}

//----------------------------------------------------------------------------

void GuiHudIconsHud::drawInfo(GameBase* control, HudInfo* hudInfo)
{
   SceneObject* obj = hudInfo->getObject();

   // Ignore our control object.
   if(obj == control)
      return;

   // Grab icon ID
   S32 iconID = hudInfo->getDataSetIntField(mHudInfoDatasetType_Icon);
   if(!iconID)
      return;

   // Map icon ID to icon
   const Icon* icon = NULL;
   for(U32 i = 0; i < mIcons.size(); i++)
   {
      if(mIcons[i]->id == iconID)
      {
         icon = mIcons[i];
         break;
      }
   }

   if(icon == NULL)
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
      Point3F targetPos2D;
      if(!mParent->projectLR(controlPos,targetPos,&targetPos2D))
         return;

      U32 offset = icon->size;
      if(offset == 0)
      {
         Point2I A(a.x,a.y);
         Point2I B(b.x,b.y);

         offset = Point2I(B-A).len();
         if( offset < 24 ) offset = 24;
      }

      Point2I upperLeft(targetPos2D.x-offset/2,targetPos2D.y-offset/2);
      Point2I extent(offset,offset);
      RectI rect(upperLeft,extent);

      if(!rect.isValidRect())
         return;

      // Determine color of icon
      GFX->getDrawUtil()->clearBitmapModulation();
      S32 colorID = hudInfo->getDataSetIntField(mHudInfoDatasetType_Color);
      if(colorID)
      {
         for(U32 i = 0; i < mColors.size(); i++)
         {
            if(mColors[i]->id == colorID)
            {
               GFX->getDrawUtil()->setBitmapModulation(mColors[i]->color);
               break;
            }
         }
      }

      // Render icon
      GFX->getDrawUtil()->drawBitmapStretch(icon->tex, rect,
         GFXBitmapFlip_None, GFXTextureFilterLinear, false);

      GFX->getDrawUtil()->clearBitmapModulation();
   }
}

//----------------------------------------------------------------------------

DefineEngineMethod( GuiHudIconsHud, clearColors, void, (),,
   "@brief Clear all color mappings.\n\n")
{
   object->clearColors();
}

DefineEngineMethod( GuiHudIconsHud, addColor, void, (S32 id, ColorI color),,
   "@brief Add color mapping.\n\n"
   "@param id ID of the color.\n"
   "@param color The color.\n")
{
   object->addColor(id, color);
}

DefineEngineMethod( GuiHudIconsHud, clearIcons, void, (),,
   "@brief Clear all icon mappings.\n\n")
{
   object->clearIcons();
}

DefineEngineMethod( GuiHudIconsHud, addIcon, void, (S32 id, String bitmap, U32 size),,
   "@brief Add icon mapping.\n\n"
   "@param id ID of the icon.\n"
   "@param bitmap The bitmap to use.\n"
   "@param size The width/height of the icon, 0 = auto.\n")
{
   object->addIcon(id, bitmap, size);
}
