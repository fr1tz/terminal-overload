// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "gui/core/guiControl.h"
#include "gui/3d/guiTSControl.h"
#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "T3D/player.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"
#include "NOTC/hudInfo.h"

class GuiNamesHud : public GuiControl {
   typedef GuiControl Parent;

   S32 mHudInfoDatasetType_Name;

   // field data
   ColorF   mFillColor;
   ColorF   mFrameColor;
   ColorF   mTextColor;
   ColorF   mLabelFillColor;
   ColorF   mLabelFrameColor;

   F32      mVerticalOffset;
   F32      mDistanceFade;
   bool     mShowFrame;
   bool     mShowFill;
   bool     mShowLabelFrame;
   bool     mShowLabelFill;

   Point2I  mLabelPadding;

protected:
   void showShapeName(GuiTSCtrl* mParent, GameBase* control, HudInfo* hudInfo);
   void drawName(Point2I offset, const char *buf, F32 opacity);

public:
   GuiNamesHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiNamesHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "TODO" );
};


//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiNamesHud);

#if 0
ConsoleDocClass( GuiNamesHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiNamesHud()"
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

/// Default distance for object's information to be displayed.
static const F32 cDefaultVisibleDistance = 500.0f;

GuiNamesHud::GuiNamesHud()
{
   mHudInfoDatasetType_Name = 4;
   mFillColor.set( 0.25f, 0.25f, 0.25f, 0.25f );
   mFrameColor.set( 0, 1, 0, 1 );
   mTextColor.set( 0, 1, 0, 1 );
   mShowFrame = mShowFill = true;
   mVerticalOffset = 0.5f;
   mDistanceFade = 0.1f;
   mLabelPadding.set(0, 0);
}

void GuiNamesHud::initPersistFields()
{
   addGroup("Colors");     
   addField( "fillColor",  TypeColorF, Offset( mFillColor, GuiNamesHud ), "Standard color for the background of the control." );
   addField( "frameColor", TypeColorF, Offset( mFrameColor, GuiNamesHud ), "Color for the control's frame."  );
   addField( "textColor",  TypeColorF, Offset( mTextColor, GuiNamesHud ), "Color for the text on this control." );
   addField( "labelFillColor",  TypeColorF, Offset( mLabelFillColor, GuiNamesHud ), "Color for the background of each shape name label." );
   addField( "labelFrameColor", TypeColorF, Offset( mLabelFrameColor, GuiNamesHud ), "Color for the frames around each shape name label."  );
   endGroup("Colors");     

   addGroup("Misc");       
   addField( "showFill",   TypeBool, Offset( mShowFill, GuiNamesHud ), "If true, we draw the background color of the control." );
   addField( "showFrame",  TypeBool, Offset( mShowFrame, GuiNamesHud ), "If true, we draw the frame of the control."  );
   addField( "showLabelFill",  TypeBool, Offset( mShowLabelFill, GuiNamesHud ), "If true, we draw a background for each shape name label." );
   addField( "showLabelFrame", TypeBool, Offset( mShowLabelFrame, GuiNamesHud ), "If true, we draw a frame around each shape name label."  );
   addField( "labelPadding", TypePoint2I, Offset( mLabelPadding, GuiNamesHud ), "The padding (in pixels) between the label text and the frame." );
   addField( "verticalOffset", TypeF32, Offset( mVerticalOffset, GuiNamesHud ), "Amount to vertically offset the control in relation to the ShapeBase object in focus." );
   addField( "distanceFade", TypeF32, Offset( mDistanceFade, GuiNamesHud ), "Visibility distance (how far the player must be from the ShapeBase object in focus) for this control to render." );
   addField( "hudInfoDatasetType_Name", TypeS32, Offset( mHudInfoDatasetType_Name, GuiNamesHud ),
      "The type of HudInfo dataset that identifies a name." );
   endGroup("Misc");
   Parent::initPersistFields();
}

void GuiNamesHud::onRender( Point2I, const RectI &updateRect)
{
   // Must be in a TS Control
   GuiTSCtrl *parent = dynamic_cast<GuiTSCtrl*>(getParent());
   if (!parent) return;

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
      if(!hudInfo)
         continue;

      String name = hudInfo->getDataSetStringField(mHudInfoDatasetType_Name);
      if(name == String(""))
         continue;

      this->showShapeName(parent, control, hudInfo);
   }

   control->enableCollision();
}

void GuiNamesHud::showShapeName(GuiTSCtrl* mParent, GameBase* control, HudInfo* hudInfo)
{
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn) return;

   SceneObject* obj = hudInfo->getObject();

	// Don't draw ourself.
	if(obj && obj == control)
		return;

   // Get control camera info
   MatrixF cam;
   Point3F camPos;
   VectorF camDir;
   conn->getControlCameraTransform(0,&cam);
   cam.getColumn(3, &camPos);
   cam.getColumn(1, &camDir);

   F32 camFov;
   conn->getControlCameraFov(&camFov);
   camFov = mDegToRad(camFov) / 2;

   // Visible distance info & name fading
   F32 visDistance = gClientSceneGraph->getVisibleDistance();
   F32 visDistanceSqr = visDistance * visDistance;
   F32 fadeDistance = visDistance * 0.5;

   // Collision info. We're going to be running LOS tests and we
   // don't want to collide with the control object.
   static U32 losMask = TerrainObjectType | ShapeBaseObjectType;

	// Target pos to test, if it's a player run the LOS to his eye
	// point, otherwise we'll grab the generic box center.
	Point3F pos;
	if(obj && obj->getTypeMask() & PlayerObjectType)
   {
      Player* player = static_cast<Player*>(obj);
		MatrixF eye;

		// Use the render eye transform, otherwise we'll see jittering
		player->getRenderEyeTransform(&eye);
		eye.getColumn(3, &pos);
	} 
   else
   {
		pos = hudInfo->getPosition();
	}

	VectorF dir = pos - camPos;

	// Test to see if it's in range
	F32 dist = dir.lenSquared();
	if(dist == 0 || dist > visDistanceSqr)
		return;
	dist = mSqrt(dist);

	// Test to see if it's within our viewcone, this test doesn't
	// actually match the viewport very well, should consider
	// projection and box test.
	dir.normalize();
	F32 dot = mDot(dir, camDir);
	if (dot < camFov)
		return;

	// Test to see if it's behind something, and we want to
	// ignore anything it's mounted on when we run the LOS.
	if(obj)
   {
		obj->disableCollision();
		SceneObject* mount = obj->getObjectMount();
		if(mount)
			mount->disableCollision();
   }

	RayInfo info;
   bool los = !gClientContainer.castRay(camPos, pos ,losMask, &info);

	if(obj)
   {
		obj->enableCollision();
		SceneObject* mount = obj->getObjectMount();
		if(mount)
			mount->enableCollision();
   }

   if(!los)
			return;

	// Project the shape pos into screen space and calculate
	// the distance opacity used to fade the labels into the
	// distance.
	Point3F projPnt;
	//shapePos.z += mVerticalOffset;
	if(!mParent->projectLR(camPos, pos, &projPnt))
		return;
		/*
	F32 opacity = (shapeDist < fadeDistance)? 1.0:
		1.0 - (shapeDist - fadeDistance) / (visDistance - fadeDistance);
		*/
	F32 opacity = 1.0;

	// move the point up a bit...
	projPnt.y -= 12;

	// Render name
   String name = hudInfo->getDataSetStringField(mHudInfoDatasetType_Name);
	drawName(Point2I((S32)projPnt.x, (S32)projPnt.y), name, opacity);
}


void GuiNamesHud::drawName(Point2I offset, const char *name, F32 opacity)
{
   F32 width = mProfile->mFont->getStrWidth((const UTF8 *)name) + mLabelPadding.x * 2;
   F32 height = mProfile->mFont->getHeight() + mLabelPadding.y * 2;
   Point2I extent = Point2I(width, height);

   // Center the name
   offset.x -= width / 2;
   offset.y -= height / 2;

   // Background fill first
   if (mShowLabelFill)
      GFX->getDrawUtil()->drawRectFill(RectI(offset, extent), mLabelFillColor);

   // Deal with opacity and draw.
   ColorF color = mProfile->mFontColor;
   color.alpha = opacity;
   GFX->getDrawUtil()->setBitmapModulation(color);
   GFX->getDrawUtil()->drawText(mProfile->mFont, offset + mLabelPadding, name);
   GFX->getDrawUtil()->clearBitmapModulation();

   // Border last
   if (mShowLabelFrame)
      GFX->getDrawUtil()->drawRect(RectI(offset, extent), mLabelFrameColor);
}

