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
#include "NOTC/tacticalzone.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDebugEvent.h"

class GuiMiniMapHud : public GuiControl
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

	bool mRotate;
	F32 mRadius;			//  Radar Range
	F32 mZoomAngle;		//  Viewing Angle

   S32 mHudInfoDatasetType_Color;
   S32 mHudInfoDatasetType_Icon;

	Point3F mCameraPos;
   Point3F mCenter;
	F32 mCameraAngle;
	F32 mHW;

   Vector<Color*> mColors;
   Vector<Icon*> mIcons;

public:
   GuiMiniMapHud();
   ~GuiMiniMapHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // GuiMiniMapHud
   Point3F project(const Point3F& point);
   F32 scale(F32 len);
   void clearColors();
   void addColor(S32 id, ColorI color);
   void clearIcons();
   void addIcon(S32 id, String bitmap, U32 size);
   void drawTacticalZone(TacticalZone* obj);

   static void initPersistFields();
   DECLARE_CONOBJECT( GuiMiniMapHud );
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Displays a minimap." );
};

static float Vector3dToDegree(Point3F vector)
{
   float angle;
   if(vector.x == 0.0F)
   {
      if (vector.y > 0.0F)
         return 0.0F;
      else if (vector.y == 0.0F)
         return -1.0F;
      else
         return 180.0F;
   }
   if(vector.y == 0.0F)
   {
      if (vector.x < 0.0F)
         return 270.0F;
      else
         return 90.0F;
   }
   angle = atanf((vector.x) / (-vector.y)) * (180.0F / M_PI);
   if ((-vector.y) < 0.0F)
      return angle + 180.0F;
   else
   {
      if (vector.x > 0.0F)
         return angle;
      else
         return angle + 360.0F;
   }
}

static void DegreeToVector2d(float angle, float length, Point3F &vector)
{
   angle = (angle / 180.0F) * M_PI;
   vector.x = length * (sin(angle) );
   vector.y = length * (-cos(angle) );
}

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiMiniMapHud);

#if 0
ConsoleDocClass( GuiMiniMapHud,
   "@brief Displays name and damage of ShapeBase objects in its bounds. Must be a child of a GuiTSCtrl and a server connection must be present.\n\n"
   "This control displays the name and damage value of all named ShapeBase objects on the client. "
   "The name and damage of objects within the control's display area are overlayed above the object.\n\n"
   "This GUI control must be a child of a TSControl, and a server connection and control object must be present. "
   "This is a stand-alone control and relies only on the standard base GuiControl.\n\n"
   
   "@tsexample\n"
		"\n new GuiMiniMapHud()"
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

GuiMiniMapHud::GuiMiniMapHud()
{
   mRotate = true;

   mRadius = 2000.0F;			
   mZoomAngle = 0;				

   mCameraAngle = 0;
   mHW = 0;

   mHudInfoDatasetType_Color = 2;
   mHudInfoDatasetType_Icon = 3;
}

GuiMiniMapHud::~GuiMiniMapHud()
{
   this->clearColors();
   this->clearIcons();
}

void GuiMiniMapHud::initPersistFields()
{
   addGroup("Main");
   addField("rotate",	    TypeBool, Offset( mRotate, GuiMiniMapHud ) );
   addField("visRadius",   TypeF32, Offset( mRadius, GuiMiniMapHud ) );
   addField( "hudInfoDatasetType_Color", TypeS32, Offset( mHudInfoDatasetType_Color, GuiMiniMapHud ),
      "The type of HudInfo dataset that identifies a color." );
   addField( "hudInfoDatasetType_Icon", TypeS32, Offset( mHudInfoDatasetType_Icon, GuiMiniMapHud ),
      "The type of HudInfo dataset that identifies an icon." );
   endGroup("Main");

   addGroup("Misc");       
   endGroup("Misc");

   Parent::initPersistFields();
}

//----------------------------------------------------------------------------

Point3F GuiMiniMapHud::project(const Point3F& point)
{
	// NOTE: if the point lies outside our visible radius, we'll put
	// it closer to mCameraPos, but still outside the visible radius...
	Point3F newPoint;
	if( (point-mCameraPos).len() > mRadius*2 )
	{
		Point3F vec = point-mCameraPos;
		vec.normalize();
		vec *= mRadius*2;
		newPoint = mCameraPos+vec;
	}
	else
	{
		newPoint = point;
	}
	newPoint.x -= mCameraPos.x;
	newPoint.y -= mCameraPos.y;
   newPoint.y = -newPoint.y;
	newPoint.z = 0;

	// Adjust object's vector to represent rotation of camera
	float objectAngle = Vector3dToDegree(newPoint);
	float length = newPoint.len()*mHW/mRadius;
	DegreeToVector2d( ( (360-objectAngle)+(mCameraAngle) ), length, newPoint);
	newPoint.x = -newPoint.x;

   // Adjust for control's position
   newPoint += mCenter;

	return newPoint;
}

F32 GuiMiniMapHud::scale(F32 len)
{
	F32 length = len*mHW/mRadius;
	return length;
}

void GuiMiniMapHud::onRender( Point2I, const RectI &updateRect)
{
   // Must have a connection
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn) return;
   // Must have controlled object
   GameBase* control = conn->getControlObject();
   if (!control) return;

	mHW = this->getExtent().y;
   mCenter.set(this->getExtent().x / 2, this->getExtent().y / 2, 0); 
	mCenter.x += this->getPosition().x; 
	mCenter.y += this->getPosition().y; 

	// get angle that camera is facing
	if(mRotate)
	{
		MatrixF cam;
		VectorF camDir;
		Point3F cameraRot;

		conn->getControlCameraTransform(0,&cam); // store camera information
		cam.getColumn(3, &mCameraPos); // get camera position
		cam.getColumn(1, &camDir); // get camera vector
		cam.getRow(1,&cameraRot); // get camera rotation
		cameraRot.neg(); // bug forces us to need to invert camera rotation angle

		conn->getControlCameraFov(&mZoomAngle);  //  Get Camera FOV

		mCameraAngle = Vector3dToDegree(cameraRot);
	}
	else
	{
		mCameraPos.set(0,0,0);
		mZoomAngle = 0;
		mCameraAngle = 0;
	}

   for(SimSetIterator itr(conn); *itr; ++itr) 
   {
      //if((*itr)->getTypeMask() & TacticalZoneObjectType)
      {
			TacticalZone* tZone = dynamic_cast<TacticalZone*>(*itr);
         if(tZone)
            this->drawTacticalZone(tZone);
      }
   }

   SimSet* hudInfoSet = Sim::getClientHudInfoSet();
   for(SimObject** itr = hudInfoSet->begin(); itr != hudInfoSet->end(); itr++)
   {
      HudInfo* hudInfo = dynamic_cast<HudInfo*>(*itr);
      if(!hudInfo)
         continue;

      // Grab icon ID
      S32 iconID = hudInfo->getDataSetIntField(mHudInfoDatasetType_Icon);
      if(!iconID)
         continue;

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

      if(!icon)
         continue;

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
      Point3F c = this->project(hudInfo->getPosition());
      Point2I offset(c.x-icon->size/2, c.y-icon->size/2);
      Point2I extent(icon->size, icon->size);
      RectI rect(offset, extent);
      GFX->getDrawUtil()->drawBitmapStretch(icon->tex, rect,
         GFXBitmapFlip_None, GFXTextureFilterLinear, false);
   }
}

//----------------------------------------------------------------------------

void GuiMiniMapHud::clearColors()
{
   for(U32 i = 0; i < mColors.size(); i++)
      delete mColors[i];
   mColors.clear();
}

void GuiMiniMapHud::addColor(S32 id, ColorI color)
{
   Color* c = new Color;
   c->id = id;
   c->color = color;
   mColors.push_back(c);
}

//----------------------------------------------------------------------------

void GuiMiniMapHud::clearIcons()
{
   for(U32 i = 0; i < mIcons.size(); i++)
      delete mIcons[i];
   mIcons.clear();
}

void GuiMiniMapHud::addIcon(S32 id, String bitmap, U32 size)
{
   Icon* icon = new Icon;
   icon->id = id;
   icon->tex.set(bitmap, &GFXDefaultGUIProfile, avar("%s() - Icon.tex (line %d)", __FUNCTION__, __LINE__) );
   icon->size = size;
   mIcons.push_back(icon);
}

//----------------------------------------------------------------------------

void GuiMiniMapHud::drawTacticalZone(TacticalZone* obj)
{
   if(!obj->showOnMinimap())
      return;

   ColorF color = obj->getZoneColor();

   Point3F pos = obj->getBoxCenter();
   MatrixF mat = obj->getTransform();

   F32 xLen = obj->getScale().x;
   F32 yLen = obj->getScale().y;

   Point3F xVec; mat.getColumn(0,&xVec); xVec.normalize(); xVec *= xLen; 
   Point3F yVec; mat.getColumn(1,&yVec); yVec.normalize(); yVec *= yLen;

   Point3F a = pos + yVec - xVec; a = project(a);
   Point3F b = pos + yVec + xVec; b = project(b);
   Point3F c = pos - yVec + xVec; c = project(c);
   Point3F d = pos - yVec - xVec; d = project(d);

   GFX->getDrawUtil()->drawLine(a, b, color);
   GFX->getDrawUtil()->drawLine(b, c, color);
   GFX->getDrawUtil()->drawLine(c, d, color);
   GFX->getDrawUtil()->drawLine(d, a, color);

   GFXStateBlockDesc rectFill;
   rectFill.setCullMode(GFXCullNone);
   rectFill.setZReadWrite(false);
   rectFill.setBlend(true, GFXBlendSrcAlpha, GFXBlendOne);
   GFXStateBlockRef rectFillSB = GFX->createStateBlock(rectFill);

   GFXVertexBufferHandle<GFXVertexPC> verts( GFX, 6, GFXBufferTypeVolatile );
   verts.lock();

   verts[0].point = a;
   verts[0].color = color;
   verts[1].point = b;
   verts[1].color = color;
   verts[2].point = c;
   verts[2].color = color;

   verts[3].point = a;
   verts[3].color = color;
   verts[4].point = c;
   verts[4].color = color;
   verts[5].point = d;
   verts[5].color = color;

   verts.unlock();

   GFX->setVertexBuffer( verts );
   GFX->setStateBlock( rectFillSB );
   GFX->setupGenericShaders();
   GFX->drawPrimitive( GFXTriangleList, 0, 2 );
}

//----------------------------------------------------------------------------

DefineEngineMethod( GuiMiniMapHud, clearColors, void, (),,
   "@brief Clear all color mappings.\n\n")
{
   object->clearColors();
}

DefineEngineMethod( GuiMiniMapHud, addColor, void, (S32 id, ColorI color),,
   "@brief Add color mapping.\n\n"
   "@param id ID of the color.\n"
   "@param color The color.\n")
{
   object->addColor(id, color);
}

DefineEngineMethod( GuiMiniMapHud, clearIcons, void, (),,
   "@brief Clear all icon mappings.\n\n")
{
   object->clearIcons();
}

DefineEngineMethod( GuiMiniMapHud, addIcon, void, (S32 id, String bitmap, U32 size),,
   "@brief Add icon mapping.\n\n"
   "@param id ID of the icon.\n"
   "@param bitmap The bitmap to use.\n"
   "@param size The width/height of the icon.\n")
{
   object->addIcon(id, bitmap, size);
}
