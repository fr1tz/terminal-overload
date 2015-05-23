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
   S32 mHudInfoDataSetType;
   ColorF   mFrameColor;
   StringTableEntry mText;
   Point2I mTextOffset;

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
   mHudInfoDataSetType = 1;
   mFrameColor.set( 1, 1, 1, 1 );
   mText = StringTable->insert("");
   mCurrTick = 0;
}

void GuiDiscTargetsHud::initPersistFields()
{
   addGroup("Colors");     
   addField( "frameColor", TypeColorF, Offset( mFrameColor, GuiDiscTargetsHud ), "Color for the control's frame."  );
   endGroup("Colors");     

   addGroup("Misc");       
   addField( "discTargetHudInfoDataSetType",   TypeS32, Offset( mHudInfoDataSetType, GuiDiscTargetsHud ),
      "The type of HudInfo data set that identifies a disc target." );
   addField( "text", TypeString, Offset( mText, GuiDiscTargetsHud ), "Text to display per target."  );
   addField( "textOffset", TypePoint2I, Offset( mTextOffset, GuiDiscTargetsHud ), "Offset to render text at."  );
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
		if(hudInfo && hudInfo->getDataSetBoolField(mHudInfoDataSetType))
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

      S32 offset = s/4;
      if( offset < 6 ) offset = 6;

      F32 ulOffset = 0.5f - GFX->getFillConventionOffset();
      Point2F upperLeft(-offset,-offset);
      Point2F lowerRight(offset,offset);
      Point2F nw(-1,-1); /*  \  */
      Point2F ne(1,-1); /*  /  */

      F32 time = Sim::getCurrentTime();
      F32 rot = (time/250.0);
      MatrixF rotMatrix(EulerF(0.0, 0.0, -rot));
      Point3F center(targetPos2D.x, targetPos2D.y, 0.0 );

      GFXVertexBufferHandle<GFXVertexPC> verts(GFX, 10, GFXBufferTypeVolatile);
      verts.lock();
      verts[0].point.set( upperLeft.x + ulOffset + nw.x, upperLeft.y + ulOffset + nw.y, 0.0f );
      verts[1].point.set( upperLeft.x + ulOffset - nw.x, upperLeft.y + ulOffset - nw.y, 0.0f );
      verts[2].point.set( lowerRight.x + ne.x, upperLeft.y + ulOffset + ne.y, 0.0f );
      verts[3].point.set( lowerRight.x - ne.x, upperLeft.y + ulOffset - ne.y, 0.0f );
      verts[4].point.set( lowerRight.x - nw.x, lowerRight.y - nw.y, 0.0f );
      verts[5].point.set( lowerRight.x + nw.x, lowerRight.y + nw.y, 0.0f );
      verts[6].point.set( upperLeft.x + ulOffset - ne.x, lowerRight.y - ne.y, 0.0f );
      verts[7].point.set( upperLeft.x + ulOffset + ne.x, lowerRight.y + ne.y, 0.0f );
      verts[8].point.set( upperLeft.x + ulOffset + nw.x, upperLeft.y + ulOffset + nw.y, 0.0f ); // same as 0
      verts[9].point.set( upperLeft.x + ulOffset - nw.x, upperLeft.y + ulOffset - nw.y, 0.0f ); // same as 1
      for (S32 i=0; i<10; i++)
         verts[i].color = mProfile->mFontColor;
      for(S32 i = 0; i < 10; i++)
      {
         rotMatrix.mulP(verts[i].point);
         verts[i].point += center;
      }
      verts.unlock();

      GFX->setVertexBuffer( verts );
      GFX->setupGenericShaders();
      GFX->drawPrimitive( GFXTriangleStrip, 0, 8 );

      if(mCurrTick % 2)
         return;
      offset = s;
      if( offset < 24 ) offset = 24;
      Point2I ul(targetPos2D.x-offset/2,targetPos2D.y-offset/2);
      extent.set(offset,offset);
      RectI rect(ul,extent);
      Point2I textPos = ul;
      if(mTextOffset.y > 0)
         textPos.y += extent.y;
      textPos.x += extent.x/2;
      textPos += mTextOffset;
      ColorF color = mProfile->mFontColor;
      GFX->getDrawUtil()->setBitmapModulation(color);
      GFX->getDrawUtil()->drawText(mProfile->mFont, textPos, mText);
      GFX->getDrawUtil()->clearBitmapModulation();
   }
}

