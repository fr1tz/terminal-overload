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
#include "NOTC/tacticalZone.h"
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

	bool mRotate;
	F32 mRadius;			//  Radar Range
	F32 mZoomAngle;		//  Viewing Angle

	Point3F mCameraPos;
   Point3F mCenter;
	F32 mCameraAngle;
	F32 mHW;

public:
   GuiMiniMapHud();

   // GuiControl
   virtual void onRender(Point2I offset, const RectI &updateRect);

   // GuiMiniMapHud
   Point3F project(const Point3F& point);
   F32 scale(F32 len);
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
}

void GuiMiniMapHud::initPersistFields()
{
   addGroup("Main");
   addField("rotate",	    TypeBool, Offset( mRotate, GuiMiniMapHud ) );
   addField("visRadius",   TypeF32, Offset( mRadius, GuiMiniMapHud ) );
   endGroup("Main");

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
   GFX->drawPrimitive( GFXTriangleList, 0, 3 );
}

//----------------------------------------------------------------------------


