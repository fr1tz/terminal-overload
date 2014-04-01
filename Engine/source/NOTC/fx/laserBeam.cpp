// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#include "game/fx/laserBeam.h"

#include "console/consoleTypes.h"
#include "console/typeValidators.h"
#include "dgl/dgl.h"
#include "platform/platformAudio.h"
#include "audio/audioDataBlock.h"
#include "sceneGraph/sceneGraph.h"
#include "sceneGraph/sceneState.h"
#include "core/bitStream.h"
#include "sim/netConnection.h"
#include "terrain/sky.h"
#include "ts/tsShape.h"
#include "ts/tsShapeInstance.h"
#include "math/mRandom.h"
#include "math/mathIO.h"
#include "math/mathUtils.h"
#include "game/debris.h"
#include "game/gameConnection.h"

//-----

static ColorF cubeColors[8] = {
   ColorF(0, 0, 0), ColorF(1, 0, 0), ColorF(0, 1, 0), ColorF(0, 0, 1),
   ColorF(1, 1, 0), ColorF(1, 0, 1), ColorF(0, 1, 1), ColorF(1, 1, 1)
};

static Point3F cubePoints[8] = {
   Point3F(-1, -1, -1), Point3F(-1, -1,  1), Point3F(-1,  1, -1), Point3F(-1,  1,  1),
   Point3F( 1, -1, -1), Point3F( 1, -1,  1), Point3F( 1,  1, -1), Point3F( 1,  1,  1)
};

static U32 cubeFaces[6][4] = {
   { 0, 2, 6, 4 }, { 0, 2, 3, 1 }, { 0, 1, 5, 4 },
   { 3, 2, 6, 7 }, { 7, 6, 4, 5 }, { 3, 7, 5, 1 }
};

static void wireCube(const Point3F& size, const Point3F& pos)
{
   glDisable(GL_CULL_FACE);

   for(int i = 0; i < 6; i++) {
      glBegin(GL_LINE_LOOP);
      for(int vert = 0; vert < 4; vert++) {
         int idx = cubeFaces[i][vert];
         glVertex3f(cubePoints[idx].x * size.x + pos.x, cubePoints[idx].y * size.y + pos.y, cubePoints[idx].z * size.z + pos.z);
      }
      glEnd();
   }
}

//-----


static MRandomLCG sRandom(0x1);

//-----
//
// LaserBeamData
//
//-----

IMPLEMENT_CO_DATABLOCK_V1(LaserBeamData);

LaserBeamData::LaserBeamData()
{
   hasLine = false;
   lineStartColor    = ColorI(255,0,0,200);
   lineBetweenColor  = ColorI(0,255,0,200);
   lineEndColor      = ColorI(0,0,255,200);
	lineWidth         = 1.0;

   hasInner = false;
   innerStartColor   = ColorI(255,0,0,100);
   innerBetweenColor = innerStartColor;
   innerEndColor     = innerStartColor;
   innerStartWidth   = 0.1;
   innerBetweenWidth = 0.1;
   innerEndWidth     = 0.1;

   hasOuter = false;
   outerStartColor   = ColorI(0,0,255,100);
   outerBetweenColor = outerStartColor;
   outerEndColor     = outerStartColor;
   outerStartWidth   = 0.2;
   outerBetweenWidth = 0.2;
   outerEndWidth     = 0.2;

   bitmap = StringTable->insert("");
   crossBitmap = StringTable->insert("");
   bitmapWidth = 0.2;
   crossBitmapWidth = 0.2;

   betweenFactor = 0.5;
   blendMode = 1;

   textureHandle = NULL;
   crossTextureHandle = NULL;
}

LaserBeamData::~LaserBeamData()
{
   //
}

IMPLEMENT_CONSOLETYPE(LaserBeamData)
IMPLEMENT_GETDATATYPE(LaserBeamData)
IMPLEMENT_SETDATATYPE(LaserBeamData)

//--------------------------------------------------------------------------
void LaserBeamData::initPersistFields()
{
   Parent::initPersistFields();

   addField("hasLine",           TypeBool,    Offset(hasLine,LaserBeamData));
   addField("lineStartColor",    TypeColorF,  Offset(lineStartColor,LaserBeamData));
   addField("lineBetweenColor",  TypeColorF,  Offset(lineBetweenColor,LaserBeamData));
   addField("lineEndColor",      TypeColorF,  Offset(lineEndColor,LaserBeamData));
	addField("lineWidth",			TypeF32,     Offset(lineWidth,LaserBeamData));
   
   addField("hasInner",          TypeBool,    Offset(hasInner,LaserBeamData));
   addField("innerStartColor",   TypeColorF,  Offset(innerStartColor,LaserBeamData));
   addField("innerBetweenColor", TypeColorF,  Offset(innerBetweenColor,LaserBeamData));
   addField("innerEndColor",     TypeColorF,  Offset(innerEndColor,LaserBeamData));
   addField("innerStartWidth",   TypeF32,     Offset(innerStartWidth,LaserBeamData));
   addField("innerBetweenWidth", TypeF32,     Offset(innerBetweenWidth,LaserBeamData));
   addField("innerEndWidth",     TypeF32,     Offset(innerEndWidth,LaserBeamData));

   addField("hasOuter",          TypeBool,    Offset(hasOuter,LaserBeamData));
   addField("outerStartColor",   TypeColorF,  Offset(outerStartColor,LaserBeamData));
   addField("outerBetweenColor", TypeColorF,  Offset(outerBetweenColor,LaserBeamData));
   addField("outerEndColor",     TypeColorF,  Offset(outerEndColor,LaserBeamData));
   addField("outerStartWidth",   TypeF32,     Offset(outerStartWidth,LaserBeamData));
   addField("outerBetweenWidth", TypeF32,     Offset(outerBetweenWidth,LaserBeamData));
   addField("outerEndWidth",     TypeF32,     Offset(outerEndWidth,LaserBeamData));

   addField("bitmap",				TypeFilename,Offset(bitmap,LaserBeamData));
   addField("crossBitmap",			TypeFilename,Offset(crossBitmap,LaserBeamData));
   addField("bitmapWidth",			TypeF32,     Offset(bitmapWidth,LaserBeamData));
	addField("crossBitmapWidth",	TypeF32,     Offset(crossBitmapWidth,LaserBeamData));

   addField("betweenFactor",     TypeF32,     Offset(betweenFactor,LaserBeamData));
   addField("blendMode",         TypeS32,     Offset(blendMode,LaserBeamData));
}


//--------------------------------------------------------------------------
bool LaserBeamData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   //

   return true;
}


bool LaserBeamData::preload(bool server, char errorBuffer[256])
{
	if (Parent::preload(server, errorBuffer) == false)
		return false;

	if(!server)
	{
		if(bitmap && bitmap[0])
			textureHandle = TextureHandle(bitmap, BitmapTexture, true);

		if(crossBitmap && crossBitmap[0])
			crossTextureHandle = TextureHandle(crossBitmap, BitmapTexture, true);
	}

   return true;
}


//--------------------------------------------------------------------------

void LaserBeamData::packData(BitStream* stream)
{
   Parent::packData(stream);

   if( stream->writeFlag(hasLine) )
   {
      stream->writeFloat(lineStartColor.red,7);
      stream->writeFloat(lineStartColor.green,7);
      stream->writeFloat(lineStartColor.blue,7);
      stream->writeFloat(lineStartColor.alpha,7);
      stream->writeFloat(lineBetweenColor.red,7);
      stream->writeFloat(lineBetweenColor.green,7);
      stream->writeFloat(lineBetweenColor.blue,7);
      stream->writeFloat(lineBetweenColor.alpha,7);
      stream->writeFloat(lineEndColor.red,7);
      stream->writeFloat(lineEndColor.green,7);
      stream->writeFloat(lineEndColor.blue,7);
      stream->writeFloat(lineEndColor.alpha,7);
		stream->write(lineWidth);
   }

   if( stream->writeFlag(hasInner) )
   {
      stream->writeFloat(innerStartColor.red,7);
      stream->writeFloat(innerStartColor.green,7);
      stream->writeFloat(innerStartColor.blue,7);
      stream->writeFloat(innerStartColor.alpha,7);
      stream->writeFloat(innerBetweenColor.red,7);
      stream->writeFloat(innerBetweenColor.green,7);
      stream->writeFloat(innerBetweenColor.blue,7);
      stream->writeFloat(innerBetweenColor.alpha,7);
      stream->writeFloat(innerEndColor.red,7);
      stream->writeFloat(innerEndColor.green,7);
      stream->writeFloat(innerEndColor.blue,7);
      stream->writeFloat(innerEndColor.alpha,7);
	  stream->writeFloat(innerStartWidth,10);
	  stream->writeFloat(innerBetweenWidth,10);
	  stream->writeFloat(innerEndWidth,10);
   }

   if( stream->writeFlag(hasOuter) )
   {
      stream->writeFloat(outerStartColor.red,7);
      stream->writeFloat(outerStartColor.green,7);
      stream->writeFloat(outerStartColor.blue,7);
      stream->writeFloat(outerStartColor.alpha,7);
      stream->writeFloat(outerBetweenColor.red,7);
      stream->writeFloat(outerBetweenColor.green,7);
      stream->writeFloat(outerBetweenColor.blue,7);
      stream->writeFloat(outerBetweenColor.alpha,7);
      stream->writeFloat(outerEndColor.red,7);
      stream->writeFloat(outerEndColor.green,7);
      stream->writeFloat(outerEndColor.blue,7);
      stream->writeFloat(outerEndColor.alpha,7);
	  stream->writeFloat(outerStartWidth,10);
	  stream->writeFloat(outerBetweenWidth,10);
	  stream->writeFloat(outerEndWidth,10);
   }

   stream->writeString(bitmap);	
   stream->writeString(crossBitmap);	
   stream->write(bitmapWidth);
	stream->write(crossBitmapWidth);

   stream->writeFloat(betweenFactor,7);
   stream->writeInt(blendMode,8);
}

void LaserBeamData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   if( hasLine = stream->readFlag() )
   {
      lineStartColor.red = stream->readFloat(7);
      lineStartColor.green= stream->readFloat(7);
      lineStartColor.blue = stream->readFloat(7);
      lineStartColor.alpha = stream->readFloat(7);
      lineBetweenColor.red = stream->readFloat(7);
      lineBetweenColor.green= stream->readFloat(7);
      lineBetweenColor.blue = stream->readFloat(7);
      lineBetweenColor.alpha = stream->readFloat(7);
      lineEndColor.red = stream->readFloat(7);
      lineEndColor.green= stream->readFloat(7);
      lineEndColor.blue = stream->readFloat(7);
      lineEndColor.alpha = stream->readFloat(7);
		stream->read(&lineWidth);
   }

   if( hasInner = stream->readFlag() )
   {
      innerStartColor.red = stream->readFloat(7);
      innerStartColor.green= stream->readFloat(7);
      innerStartColor.blue = stream->readFloat(7);
      innerStartColor.alpha = stream->readFloat(7);
      innerBetweenColor.red = stream->readFloat(7);
      innerBetweenColor.green= stream->readFloat(7);
      innerBetweenColor.blue = stream->readFloat(7);
      innerBetweenColor.alpha = stream->readFloat(7);
      innerEndColor.red = stream->readFloat(7);
      innerEndColor.green= stream->readFloat(7);
      innerEndColor.blue = stream->readFloat(7);
      innerEndColor.alpha = stream->readFloat(7);
	  innerStartWidth = stream->readFloat(10);
	  innerBetweenWidth = stream->readFloat(10);
	  innerEndWidth = stream->readFloat(10);
   }

   if( hasOuter = stream->readFlag() )
   {
      outerStartColor.red = stream->readFloat(7);
      outerStartColor.green= stream->readFloat(7);
      outerStartColor.blue = stream->readFloat(7);
      outerStartColor.alpha = stream->readFloat(7);
      outerBetweenColor.red = stream->readFloat(7);
      outerBetweenColor.green= stream->readFloat(7);
      outerBetweenColor.blue = stream->readFloat(7);
      outerBetweenColor.alpha = stream->readFloat(7);
      outerEndColor.red = stream->readFloat(7);
      outerEndColor.green= stream->readFloat(7);
      outerEndColor.blue = stream->readFloat(7);
      outerEndColor.alpha = stream->readFloat(7);
	  outerStartWidth = stream->readFloat(10);
	  outerBetweenWidth = stream->readFloat(10);
	  outerEndWidth = stream->readFloat(10);
   }

   bitmap = StringTable->insert(stream->readSTString());
   crossBitmap = StringTable->insert(stream->readSTString());
   stream->read(&bitmapWidth);
   stream->read(&crossBitmapWidth);

   betweenFactor = stream->readFloat(7);
   blendMode = stream->readInt(8);
}


//-----
//
// LaserBeam
//
//-----

IMPLEMENT_CONOBJECT(LaserBeam);

LaserBeam::LaserBeam()
{
   //mTypeMask |= StaticRenderedObjectType;

   mStart = mBetween = mEnd = Point3F(0,0,0);

   mSource.set(0,0,0);
   mVelocity.set(0,0,0);
   mLength = 0;

   mRender = mFade = false;
   mClip = false;
   mColor.set(1, 1, 1, 1);
   mOpacity = 1.0;

   mLastCalcTime = 0;
   mCrossVec = Point3F(0,0,0);
   mRenderCross = false;
   mRenderCrossX = mRenderCrossY = Point3F(0,0,0);

   setProcessTick(false); // no need to tick until we want to fade... -mg
}

LaserBeam::~LaserBeam()
{
   //
}

void LaserBeam::set_gl_color(const ColorF& color)
{
	ColorF c = color;
	if(mDataBlock->allowColorization)
		c.colorize(this->getSceneObjectColorization());
	glColor4fv(c * mColor);
}

void LaserBeam::setRender(bool _b)
{
   mRender = _b;
}

void LaserBeam::update(Point3F _from, Point3F _to)
{
	if(mClip)
	{
		F32 lenSE = Point3F( _from - _to ).len();
		F32 lenCE = Point3F( mSource - _to ).len();
		if( lenCE < lenSE )
			_from = mSource;
	}

   mStart     = _from;
   mEnd       = _to;
   mBetween   = mStart+mDataBlock->betweenFactor*(mEnd-mStart);

   // update object box...
    Point3F vec = mEnd - mStart;
	Point3F origin(0,0,0);
	Point3F a = origin - vec;
	Point3F b = origin;
	if( a.x > b.x )
		{ mObjBox.max.x = a.x; mObjBox.min.x = b.x; }
	else
		{ mObjBox.max.x = b.x; mObjBox.min.x = a.x; }
	if( a.y > b.y )
		{ mObjBox.max.y = a.y; mObjBox.min.y = b.y; }
	else
		{ mObjBox.max.y = b.y; mObjBox.min.y = a.y; }
	if( a.z > b.z )
		{ mObjBox.max.z = a.z; mObjBox.min.z = b.z; }
	else
		{ mObjBox.max.z = b.z; mObjBox.min.z = a.z; }

   MatrixF xform(true);
   xform.setPosition(mEnd);
   this->setTransform(xform);
}

void LaserBeam::fadeAndDelete(U32 _fadeTime)
{
   mFade = true;
   mFadeTime = _fadeTime;

   setProcessTick(true); // we need to get ticked in order to fade -mg
}

void LaserBeam::setColor(const ColorF& color)
{
	mColor = color;
}

void LaserBeam::makeDisappear(const Point3F& src, const Point3F& pos,
	const Point3F& vel, F32 len)
{
	Point3F vec = -vel; vec.normalize();

	mClip = true;
	mClipPlane.set(pos, vec);
	mLength = len;
	mVelocity = vel;
	mSource = src;

	this->update(pos + vec*len, pos);

	setProcessTick(true); // we need to get ticked in order to disappear
}

//--------------------------------------------------------------------------
void LaserBeam::initPersistFields()
{
   Parent::initPersistFields();

   //
}

void LaserBeam::consoleInit()
{
   //
}

//--------------------------------------------------------------------------
bool LaserBeam::onAdd()
{
   // first check if we have a server connection, if we dont then this is on the server
   //  and we should exit, then check if the parent fails to add the object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if(!conn || !Parent::onAdd())
      return false;

   gClientContainer.addObject(this);
   gClientSceneGraph->addObjectToScene(this);

   removeFromProcessList();
   gClientProcessList.addObject(this);

   conn->addObject(this);

   return true;
}


void LaserBeam::onRemove()
{
   if (mSceneManager != NULL)
      mSceneManager->removeObjectFromScene(this);
   if (getContainer() != NULL)
      getContainer()->removeObject(this);

   Parent::onRemove();
}

bool LaserBeam::onNewDataBlock(GameBaseData* dptr)
{
   mDataBlock = dynamic_cast<LaserBeamData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr))
      return false;

   scriptOnNewDataBlock();

   return true;
}

//--------------------------------------------------------------------------

bool LaserBeam::prepRenderImage(SceneState* state, const U32 stateKey,
                                const U32 /*startZone*/, const bool /*modifyBaseState*/)
{
   if (isLastState(state, stateKey))
      return false;
   setLastState(state, stateKey);

   // This should be sufficient for most objects that don't manage zones, and
   //  don't need to return a specialized RenderImage...
   if (state->isObjectRendered(this)) {
      SceneRenderImage* image = new SceneRenderImage;
      image->obj = this;
      image->isTranslucent = true;
      image->sortType = SceneRenderImage::Point;
      state->insertRenderImage(image);
   }

   return false;
}

void LaserBeam::renderObject(SceneState* state, SceneRenderImage*)
{
   AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on entry");

   RectI viewport;
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   dglGetViewport(&viewport);

   state->setupObjectProjection(this);

   if(mClip)
   {
	  GLdouble planeEQ[4];
      planeEQ[0] = mClipPlane.x;
      planeEQ[1] = mClipPlane.y;
      planeEQ[2] = mClipPlane.z;
      planeEQ[3] = mClipPlane.d;
      glClipPlane(GL_CLIP_PLANE1, planeEQ);
      glEnable(GL_CLIP_PLANE1);
   }

   render( &state->getCameraPosition() );

   if(mClip)
   {
      glDisable(GL_CLIP_PLANE1);
   }

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   dglSetViewport(viewport);

   AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on exit");
}


void LaserBeam::render( const Point3F* camPos )
{
   if(mRender)
   {   
		if( mLastCalcTime == 0 || mAbs(Platform::getRealMilliseconds()-mLastCalcTime) > 50 )
		{
			Point3F dirFromCam = mEnd - *camPos;
			mCross(dirFromCam, mEnd - mStart, &mCrossVec);
			mCrossVec.normalize();

			Point3F c = dirFromCam;  c.normalize();
			Point3F d = mEnd-mStart; d.normalize();
			F32 dot = mFabs(mDot(c,d));
			//Con::printf("%f", dot);
			mRenderCross = dot > 0.9999;				

			if(mRenderCross)
			{
				Point3F vec = mEnd - mStart;
				MatrixF mat = MathUtils::createOrientFromDir(vec);
				mat.getColumn(0,&mRenderCrossX); mRenderCrossX.normalize();
				mat.getColumn(2,&mRenderCrossY); mRenderCrossY.normalize();
			}

			mLastCalcTime = Platform::getRealMilliseconds();
		}


	   glDepthMask(GL_FALSE);
	   glEnable(GL_BLEND);

	   //
	   // blend mode...
	   //
	   switch( mDataBlock->blendMode )
	   {
	      case 1:
	         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			 break;
	      case 2:
             glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
			 break;
			default:
	         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			 break;
	   }

	   ColorF color;

	   //
	   // line...
	   //
	   if( mDataBlock->hasLine )
	   {
			glEnable(GL_POINT_SIZE);
			glEnable(GL_POINT_SMOOTH);
			glPointSize(mDataBlock->lineWidth/2); 
			glBegin(GL_POINTS);  

				if( mFade )
					color = ColorF(mDataBlock->lineStartColor.red,mDataBlock->lineStartColor.green,mDataBlock->lineStartColor.blue,mOpacity);
				else
					color = mDataBlock->lineStartColor;
				this->set_gl_color(color);
				glVertex3f((F32)mStart.x, (F32)mStart.y, (F32)mStart.z);

				if( mFade )
					color = ColorF(mDataBlock->lineBetweenColor.red,mDataBlock->lineBetweenColor.green,mDataBlock->lineBetweenColor.blue,mOpacity);
				else
					color = mDataBlock->lineBetweenColor;
				  this->set_gl_color(color);
				glVertex3f((F32)mBetween.x, (F32)mBetween.y, (F32)mBetween.z);

				if( mFade )
					color = ColorF(mDataBlock->lineEndColor.red,mDataBlock->lineEndColor.green,mDataBlock->lineEndColor.blue,mOpacity);
				else
					color = mDataBlock->lineEndColor;
				this->set_gl_color(color);
				glVertex3f((F32)mEnd.x, (F32)mEnd.y, (F32)mEnd.z);

			glEnd();
			glPointSize(1.0);
			glDisable(GL_POINT_SMOOTH);
			glDisable(GL_POINT_SIZE);

			glEnable(GL_LINE_WIDTH);
         glEnable(GL_LINE_SMOOTH);
			glLineWidth(mDataBlock->lineWidth); 
	      glBegin(GL_LINE_STRIP);  		

				 if( mFade )
					color = ColorF(mDataBlock->lineStartColor.red,mDataBlock->lineStartColor.green,mDataBlock->lineStartColor.blue,mOpacity);
				else
					color = mDataBlock->lineStartColor;
				  this->set_gl_color(color);
				glVertex3f((F32)mStart.x, (F32)mStart.y, (F32)mStart.z);

				 if( mFade )
					color = ColorF(mDataBlock->lineBetweenColor.red,mDataBlock->lineBetweenColor.green,mDataBlock->lineBetweenColor.blue,mOpacity);
				else
					color = mDataBlock->lineBetweenColor;
				  this->set_gl_color(color);
				glVertex3f((F32)mBetween.x, (F32)mBetween.y, (F32)mBetween.z);

				 if( mFade )
					color = ColorF(mDataBlock->lineEndColor.red,mDataBlock->lineEndColor.green,mDataBlock->lineEndColor.blue,mOpacity);
				else
					color = mDataBlock->lineEndColor;
				this->set_gl_color(color);
				glVertex3f((F32)mEnd.x, (F32)mEnd.y, (F32)mEnd.z);

	      glEnd();
			glLineWidth(1.0);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_LINE_WIDTH);
	   }

	   //
	   // inner...
	   //
	   if( mDataBlock->hasInner )
	   {
		  Point3F vec;
		  glEnable(GL_POLYGON_SMOOTH);
		  glBegin(GL_QUADS);    
		  // ------------------------------------------------------------------------
		   vec = mCrossVec * mDataBlock->innerStartWidth * 0.5; 
		   color = mDataBlock->innerStartColor;
           this->set_gl_color(color);
		   glVertex3fv( mStart - vec );
          //
		   color = mDataBlock->innerStartColor;
           this->set_gl_color(color);
		   glVertex3fv( mStart + vec );
          //
			vec = mCrossVec * mDataBlock->innerBetweenWidth * 0.5; 
		   color = mDataBlock->innerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween + vec );
          //
		   color = mDataBlock->innerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween - vec );
		  // ------------------------------------------------------------------------
		   color = mDataBlock->innerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween - vec );
          //
			vec = mCrossVec * mDataBlock->innerEndWidth * 0.5;
		   color = mDataBlock->innerEndColor;
           this->set_gl_color(color);
		   glVertex3fv( mEnd - vec );
          //  
		   color = mDataBlock->innerEndColor;
           this->set_gl_color(color);
		   glVertex3fv( mEnd + vec );
          //
			vec = mCrossVec * mDataBlock->innerBetweenWidth * 0.5; 
		   color = mDataBlock->innerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween + vec );
		  // ------------------------------------------------------------------------
		  glEnd();
		  glDisable(GL_POLYGON_SMOOTH);
	   }

	   //
	   // outer...
	   //
	   if( mDataBlock->hasOuter )
	   {
		  Point3F vec;
		  glEnable(GL_POLYGON_SMOOTH);
		  glBegin(GL_QUADS);    
		  // ------------------------------------------------------------------------
			vec = mCrossVec * mDataBlock->outerStartWidth * 0.5; 
		   color = mDataBlock->outerStartColor;
           this->set_gl_color(color);
		   glVertex3fv( mStart - vec );
          //
		   color = mDataBlock->outerStartColor;
           this->set_gl_color(color);
		   glVertex3fv( mStart + vec );
          //
			vec = mCrossVec * mDataBlock->outerBetweenWidth * 0.5;
		   color = mDataBlock->outerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween + vec );
          //
		   color = mDataBlock->outerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween - vec );
		  // ------------------------------------------------------------------------
		   color = mDataBlock->outerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween - vec );
          //
			vec = mCrossVec * mDataBlock->outerEndWidth * 0.5;
		   color = mDataBlock->outerEndColor;
           this->set_gl_color(color);
		   glVertex3fv( mEnd - vec );
          //  
		   color = mDataBlock->outerEndColor;
           this->set_gl_color(color);
		   glVertex3fv( mEnd + vec );
          //
			vec = mCrossVec * mDataBlock->outerBetweenWidth * 0.5;
		   color = mDataBlock->outerBetweenColor;
           this->set_gl_color(color);
		   glVertex3fv( mBetween + vec );
		  // ------------------------------------------------------------------------
		  glEnd();
		  glDisable(GL_POLYGON_SMOOTH);
	   }

	   //
	   // bitmap...
	   //
		if(mDataBlock->textureHandle)
		{
		   Point3F vec = mCrossVec * mDataBlock->bitmapWidth * 0.5;
	      glEnable(GL_TEXTURE_2D);

	      TextureObject* texture = (TextureObject*)mDataBlock->textureHandle;
	      glBindTexture(GL_TEXTURE_2D, texture->texGLName);
	      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		  glColor4fv(mColor);

		  glEnable(GL_POLYGON_SMOOTH);
		  glBegin(GL_POLYGON);    
       		 // ------------------------------------------------------------------------
			 glTexCoord2f(0,0);
			 glVertex3fv( mStart - vec );
			//
			 glTexCoord2f(0,1);
			 glVertex3fv( mStart + vec );
			//  
			 glTexCoord2f(1,1);
			 glVertex3fv( mEnd + vec );
			//
			 glTexCoord2f(1,0);
			 glVertex3fv( mEnd - vec );
			// ------------------------------------------------------------------------
		  glEnd();
		  glDisable(GL_POLYGON_SMOOTH);


		  glDisable(GL_TEXTURE_2D);
		}


	   //
	   // crossBitmap...
	   //
       if(mDataBlock->crossTextureHandle)
		{
			if( mRenderCross )
			{		
		      glEnable(GL_TEXTURE_2D);

		      TextureObject* texture = (TextureObject*)mDataBlock->crossTextureHandle;
		      glBindTexture(GL_TEXTURE_2D, texture->texGLName);
		      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				Point3F vecX = mRenderCrossX * mDataBlock->crossBitmapWidth * 0.5;
				Point3F vecY = mRenderCrossY * mDataBlock->crossBitmapWidth * 0.5;
				glEnable(GL_POLYGON_SMOOTH);
				glBegin(GL_POLYGON);    
       		// ------------------------------------------------------------------------
				 glTexCoord2f(0,0);
				 glVertex3fv( mBetween - vecX);
				//
				 glTexCoord2f(0,1);
				 glVertex3fv( mBetween + vecY);
				//  
				 glTexCoord2f(1,1);
				 glVertex3fv( mBetween + vecX);
				//
				 glTexCoord2f(1,0);
				 glVertex3fv( mBetween - vecY);
				// ------------------------------------------------------------------------
				glEnd();
				glDisable(GL_POLYGON_SMOOTH);


				glDisable(GL_TEXTURE_2D);
			}
		}

		glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
	}

   // Debugging Bounding Box
   if(false)
   {
      glDisable(GL_DEPTH_TEST);
      Point3F box;
      glPushMatrix();
      dglMultMatrix(&getRenderTransform());
      box = (mObjBox.min + mObjBox.max) * 0.5;
      glTranslatef(box.x,box.y,box.z);
      box = (mObjBox.max - mObjBox.min) * 0.5;
      glScalef(box.x,box.y,box.z);
      glColor3f(1, 0, 1);
      wireCube(Point3F(1,1,1),Point3F(0,0,0));
      glPopMatrix();

      glPushMatrix();
      box = (mWorldBox.min + mWorldBox.max) * 0.5;
      glTranslatef(box.x,box.y,box.z);
      box = (mWorldBox.max - mWorldBox.min) * 0.5;
      glScalef(box.x,box.y,box.z);
      glColor3f(0, 1, 1);
      wireCube(Point3F(1,1,1),Point3F(0,0,0));
      glPopMatrix();
	  glEnable(GL_DEPTH_TEST);
   }
}

//--------------------------------------------------------------------------

void LaserBeam::processTick(const Move* move)
{
	Parent::processTick(move);

	if(mClip)
	{
		Point3F vec = -mVelocity; vec.normalize();
		Point3F newEnd = mEnd + mVelocity * (F32(TickMs)/1000.0f);
		Point3F newStart = newEnd + vec*mLength;
		if(mClipPlane.distToPlane(newStart) < 0)
		{
			this->deleteObject();
			return;
		}
		this->update(newStart, newEnd);
	}


#if 0
	if(mDisappearSpeed > 0)
	{
		F32 dist = mDisappearSpeed * (F32(TickMs)/1000.0f);
		mTexShift += dist/mLength;
		if(mTexShift > 1)
			this->deleteObject();
	}
#endif

	if( mFade ) 
	{
		if( mOpacity > 0 )
			mOpacity -= 1.0f / mFadeTime;
		else
			deleteObject();
	}
}

void LaserBeam::interpolateTick(F32 dt)
{
   Parent::interpolateTick(dt);
}


void LaserBeam::advanceTime(F32 dt)
{
   Parent::advanceTime(dt);
}

//-----
//
// MultiNodeLaserBeamData
//
//-----

IMPLEMENT_CO_DATABLOCK_V1(MultiNodeLaserBeamData);

MultiNodeLaserBeamData::MultiNodeLaserBeamData()
{
	hasLine    = false;
	lineColor  = ColorI(255,0,0,200);
	lineWidth  = 1.0;

	hasInner   = false;
	innerColor = ColorI(255,0,0,100);
	innerWidth = 0.1;

	hasOuter   = false;
	outerColor = ColorI(0,0,255,100);
	outerWidth = 0.2;

	bitmap = StringTable->insert("");
	bitmapWidth = 0.2;

	blendMode = 1;

	renderMode = FaceViewer;

	windCoefficient = 0.0f;

	nodeMoveMode[0] = nodeMoveMode[1] = nodeMoveMode[2] = None;
	nodeMoveSpeed[0] = nodeMoveSpeed[1] = nodeMoveSpeed[2] = 0.0f;
	nodeMoveSpeedAdd[0] = nodeMoveSpeedAdd[1] = nodeMoveSpeedAdd[2] = 0.0f;

	nodeDistance = 0.0f;

	fadeTime = 1000;

	textureHandle = NULL;
}

MultiNodeLaserBeamData::~MultiNodeLaserBeamData()
{
   //
}

IMPLEMENT_CONSOLETYPE(MultiNodeLaserBeamData)
IMPLEMENT_GETDATATYPE(MultiNodeLaserBeamData)
IMPLEMENT_SETDATATYPE(MultiNodeLaserBeamData)

//--------------------------------------------------------------------------
void MultiNodeLaserBeamData::initPersistFields()
{
	Parent::initPersistFields();

	addField("hasLine",     TypeBool,     Offset(hasLine,MultiNodeLaserBeamData));
	addField("lineColor",   TypeColorF,   Offset(lineColor,MultiNodeLaserBeamData));
	addField("lineWidth",	TypeF32,      Offset(lineWidth,MultiNodeLaserBeamData));

	addField("hasInner",    TypeBool,     Offset(hasInner,MultiNodeLaserBeamData));
	addField("innerColor",  TypeColorF,   Offset(innerColor,MultiNodeLaserBeamData));
	addField("innerWidth",  TypeF32,      Offset(innerWidth,MultiNodeLaserBeamData));

	addField("hasOuter",    TypeBool,     Offset(hasOuter,MultiNodeLaserBeamData));
	addField("outerColor",  TypeColorF,   Offset(outerColor,MultiNodeLaserBeamData));
	addField("outerWidth",  TypeF32,      Offset(outerWidth,MultiNodeLaserBeamData));

	addField("bitmap",      TypeFilename, Offset(bitmap,MultiNodeLaserBeamData));
	addField("bitmapWidth", TypeF32,      Offset(bitmapWidth,MultiNodeLaserBeamData));

	addField("blendMode",   TypeS32,      Offset(blendMode,MultiNodeLaserBeamData));	

	addField("renderMode",  TypeS32,      Offset(renderMode,MultiNodeLaserBeamData));

	addField("windCoefficient", TypeF32, Offset(windCoefficient, MultiNodeLaserBeamData));

	addField("nodeMoveMode",     TypeS32, Offset(nodeMoveMode,     MultiNodeLaserBeamData), 3);
	addField("nodeMoveSpeed",    TypeF32, Offset(nodeMoveSpeed,    MultiNodeLaserBeamData), 3);
	addField("nodeMoveSpeedAdd", TypeF32, Offset(nodeMoveSpeedAdd, MultiNodeLaserBeamData), 3);

	addField("nodeDistance", TypeF32, Offset(nodeDistance, MultiNodeLaserBeamData));

	addField("fadeTime",    TypeS32,      Offset(fadeTime, MultiNodeLaserBeamData));
}

void MultiNodeLaserBeamData::consoleInit()
{
	Con::setIntVariable("$MultiNodeLaserBeamRenderMode::FaceViewer",FaceViewer);
	Con::setIntVariable("$MultiNodeLaserBeamRenderMode::Horizontal",Horizontal);
	Con::setIntVariable("$MultiNodeLaserBeamRenderMode::Vertical",Vertical);

	Con::setIntVariable("$NodeMoveMode::None", None);
	Con::setIntVariable("$NodeMoveMode::ConstantSpeed", ConstantSpeed);
	Con::setIntVariable("$NodeMoveMode::DynamicSpeed", DynamicSpeed);
}


//--------------------------------------------------------------------------
bool MultiNodeLaserBeamData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   //

   return true;
}


bool MultiNodeLaserBeamData::preload(bool server, char errorBuffer[256])
{
   if (Parent::preload(server, errorBuffer) == false)
      return false;

   if(bitmap && bitmap[0])
      textureHandle = TextureHandle(bitmap, BitmapTexture, true);

   return true;
}


//--------------------------------------------------------------------------

void MultiNodeLaserBeamData::packData(BitStream* stream)
{
	Parent::packData(stream);

	if( stream->writeFlag(hasLine) )
	{
		stream->writeFloat(lineColor.red,7);
		stream->writeFloat(lineColor.green,7);
		stream->writeFloat(lineColor.blue,7);
		stream->write(lineColor.alpha);
		stream->write(lineWidth);
	}

	if( stream->writeFlag(hasInner) )
	{
		stream->writeFloat(innerColor.red,7);
		stream->writeFloat(innerColor.green,7);
		stream->writeFloat(innerColor.blue,7);
		stream->write(innerColor.alpha);
		stream->writeFloat(innerWidth,10);
	}

	if( stream->writeFlag(hasOuter) )
	{
		stream->writeFloat(outerColor.red,7);
		stream->writeFloat(outerColor.green,7);
		stream->writeFloat(outerColor.blue,7);
		stream->write(outerColor.alpha);
		stream->writeFloat(outerWidth,10);
	}

	stream->writeString(bitmap);	
	stream->write(bitmapWidth);

	stream->writeInt(blendMode,8);

	stream->writeInt(renderMode,8);

	if(stream->writeFlag(windCoefficient != 0.0f))
		stream->write(windCoefficient);

	for(int i = 0; i < 3; i++)
	{
		if(stream->writeFlag(nodeMoveMode[i] != None))
		{
			stream->writeInt(nodeMoveMode[i]-1, 1);
			stream->write(nodeMoveSpeed[i]);
			stream->write(nodeMoveSpeedAdd[i]);
		}
	}

	if(stream->writeFlag(nodeDistance != 0.0f))
		stream->write(nodeDistance);
	
	stream->writeInt(fadeTime >> 5, 10);
}

void MultiNodeLaserBeamData::unpackData(BitStream* stream)
{
	Parent::unpackData(stream);

	if( hasLine = stream->readFlag() )
	{
		lineColor.red = stream->readFloat(7);
		lineColor.green= stream->readFloat(7);
		lineColor.blue = stream->readFloat(7);
		stream->read(&lineColor.alpha);
		stream->read(&lineWidth);
	}

	if( hasInner = stream->readFlag() )
	{
		innerColor.red = stream->readFloat(7);
		innerColor.green= stream->readFloat(7);
		innerColor.blue = stream->readFloat(7);
		stream->read(&innerColor.alpha);
		innerWidth = stream->readFloat(10);
	}

	if( hasOuter = stream->readFlag() )
	{
		outerColor.red = stream->readFloat(7);
		outerColor.green= stream->readFloat(7);
		outerColor.blue = stream->readFloat(7);
		stream->read(&outerColor.alpha);
		outerWidth = stream->readFloat(10);
	}

	bitmap = StringTable->insert(stream->readSTString());
	stream->read(&bitmapWidth);

	blendMode = stream->readInt(8);

	renderMode = stream->readInt(8);

	if(stream->readFlag())
		stream->read(&windCoefficient);
	else
		windCoefficient = 0.0f;

	for(int i = 0; i < 3; i++)
	{
		if(stream->readFlag())
		{
			nodeMoveMode[i] = stream->readInt(1)+1;
			stream->read(&nodeMoveSpeed[i]);
			stream->read(&nodeMoveSpeedAdd[i]);
		}
	}

	if(stream->readFlag())
		stream->read(&nodeDistance);
	else
		nodeDistance = 0.0f;

	fadeTime = stream->readInt(10) << 5;
}


//-----
//
// MultiNodeLaserBeam
//
//-----

IMPLEMENT_CONOBJECT(MultiNodeLaserBeam);

MultiNodeLaserBeam::MultiNodeLaserBeam()
{
   mTypeMask |= StaticRenderedObjectType;

   mRender = mFade = false;
   mFadeMode = 0;

	mCurrTick = 0;
	mDeleteOnFadeout = false;

	mLastCalcTime = 0;
	mCrossVec = Point3F(0,0,0);
}

MultiNodeLaserBeam::~MultiNodeLaserBeam()
{
   //
}

void MultiNodeLaserBeam::setRender(bool b)
{
   mRender = b;
}

void MultiNodeLaserBeam::addNode(Point3F pos)
{
	LaserBeamNode newNode;
	newNode.pos   = pos;
	newNode.alpha = 1.0f;

	for(int i = 0; i < 3; i++)
	{
		if(mDataBlock->nodeMoveMode[i] == MultiNodeLaserBeamData::ConstantSpeed)
			newNode.vel[i] = mDataBlock->nodeMoveSpeed[i] + mDataBlock->nodeMoveSpeedAdd[i] * sRandom.randF();
	}

	mNodes.push_back(newNode);
}

bool MultiNodeLaserBeam::addNodes(Point3F endpos)
{
	if(mNodes.size() == 0 || mDataBlock->nodeDistance == 0.0f)
		this->addNode(endpos);
	else
	{
		Point3F startpos = this->getLastNodePos();
		Point3F vec = endpos - startpos;
		F32 numNodes = vec.len() / mDataBlock->nodeDistance;
		if((int)numNodes == 0)
			return true;
		vec /= numNodes;
		Point3F pos = startpos + vec;
		int n = (int)numNodes - 1;
		while(n-- > 0)
		{
			this->addNode(pos);
			pos += vec;
		}
		this->addNode(endpos);
	}

	// update object box...
	Point3F vec = mNodes[mNodes.size()-1].pos - mNodes[0].pos;
	Point3F origin(0,0,0);
	Point3F a = origin - vec;
	Point3F b = origin;
	if( a.x > b.x )
		{ mObjBox.max.x = a.x; mObjBox.min.x = b.x; }
	else
		{ mObjBox.max.x = b.x; mObjBox.min.x = a.x; }
	if( a.y > b.y )
		{ mObjBox.max.y = a.y; mObjBox.min.y = b.y; }
	else
		{ mObjBox.max.y = b.y; mObjBox.min.y = a.y; }
	if( a.z > b.z )
		{ mObjBox.max.z = a.z; mObjBox.min.z = b.z; }
	else
		{ mObjBox.max.z = b.z; mObjBox.min.z = a.z; }

	// update object transform...
	MatrixF xform(true);
	xform.setPosition(endpos);
	this->setTransform(xform);

	return true;
}

void MultiNodeLaserBeam::setLastNodePos(Point3F pos)
{
	if( !mNodes.empty() )
		mNodes[mNodes.size()-1].pos = pos;
}

Point3F MultiNodeLaserBeam::getLastNodePos()
{
	if( !mNodes.empty() )
		return mNodes[mNodes.size()-1].pos;

	return Point3F(0,0,0);
}

bool MultiNodeLaserBeam::deleteLastNode()
{
	// never pop first node...
	if( mNodes.size() > 1 )
	{
		mNodes.pop_back();
		return true;
	}

	return false;
}

void MultiNodeLaserBeam::fade()
{
   mFade = true;
}

//--------------------------------------------------------------------------
void MultiNodeLaserBeam::initPersistFields()
{
   Parent::initPersistFields();

   //
}

void MultiNodeLaserBeam::consoleInit()
{
	//
}

//--------------------------------------------------------------------------
bool MultiNodeLaserBeam::onAdd()
{
   // first check if we have a server connection, if we dont then this is on the server
   //  and we should exit, then check if the parent fails to add the object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if(!conn || !Parent::onAdd())
      return false;

   // set object box...
   mObjBox.min = Point3F(-1,-1,-1);
   mObjBox.max = Point3F(1,1,1);
   resetWorldBox();
	setRenderTransform(mObjToWorld);

   gClientContainer.addObject(this);
   gClientSceneGraph->addObjectToScene(this);

   removeFromProcessList();
   gClientProcessList.addObject(this);

   conn->addObject(this);

   return true;
}


void MultiNodeLaserBeam::onRemove()
{
   if (mSceneManager != NULL)
      mSceneManager->removeObjectFromScene(this);
   if (getContainer() != NULL)
      getContainer()->removeObject(this);

   Parent::onRemove();
}

bool MultiNodeLaserBeam::onNewDataBlock(GameBaseData* dptr)
{
   mDataBlock = dynamic_cast<MultiNodeLaserBeamData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr))
      return false;

   scriptOnNewDataBlock();

   return true;
}

void MultiNodeLaserBeam::processTick(const Move* move)
{
	Parent::processTick(move);

	mCurrTick++;

	if( mFade ) 
	{
		bool visibleNodes = false;
		for(int i=0; i<mNodes.size(); i++ )
		{
			if( mNodes[i].alpha > 0 )
			{
				visibleNodes = true;
				break;
			}
		}

		//if( mDeleteOnFadeout && mNodes[mNodes.size()-1].alpha <= 0 )
		if( mDeleteOnFadeout && !visibleNodes )
		{
			mDeleteOnFadeout = false;
			deleteObject();
			return;
		}

		// remove invisible nodes, but leave at least 2 nodes...
		//if( mNodes.size() > c+1 )
		//	for( int i = 0; i < c; i++ )
		//		mNodes.pop_front();

		// Remove invisible nodes
		if(mNodes.size() > 64)
		{
			if(mFadeMode == 1)
			{
				while(mNodes.size() >= 2 && mNodes[mNodes.size()-1].alpha <= 0)
				{
					if(mNodes[mNodes.size()-2].alpha <= 0)
						mNodes.pop_back();
					else 
						break;
				}				
			}
			else
			{
				while(mNodes.size() >= 2 && mNodes[0].alpha <= 0)
				{
					if(mNodes[1].alpha <= 0)
						mNodes.pop_front();
					else 
						break;
				}
			}
			//Con::printf("Num nodes: %i", mNodes.size());
		}
	}
}

void MultiNodeLaserBeam::interpolateTick(F32 dt)
{
	Parent::interpolateTick(dt);
}


void MultiNodeLaserBeam::advanceTime(F32 dt)
{
	Parent::advanceTime(dt);

	// check if we can bail early and don't have to iterate over every node...
	if(!mFade
	&& mDataBlock->windCoefficient == 0.0f
	&& mDataBlock->nodeMoveMode[0] == MultiNodeLaserBeamData::None
	&& mDataBlock->nodeMoveMode[1] == MultiNodeLaserBeamData::None
	&& mDataBlock->nodeMoveMode[2] == MultiNodeLaserBeamData::None)
		return;

	F32 fadedelta = 1000.0/mDataBlock->fadeTime * dt;
	Sky* sky = gClientSceneGraph->getCurrentSky();
	Point3F windVec = sky ? -sky->getWindVelocity() *  mDataBlock->windCoefficient : VectorF( 0.0f, 0.0f, 0.0f );

	int s = mNodes.size();
	for(int i=0; i<s; i++ )
	{
		// fading
		F32 d = fadedelta;
		if(mFadeMode == 1)
		{
#if 0
			F32 n = s;
			F32 x = i;
			F32 f = (n-x);
			d = fadedelta*f;
#endif
			d *= mNodes[i].alpha;
		}
		if(d > 0) 
		{
			mNodes[i].alpha -= d;
			if(mNodes[i].alpha < 0.01)
				mNodes[i].alpha = 0;
		}

		// wind
		if(mDataBlock->windCoefficient != 0.0f && i > 0) 
		{
			mNodes[i].pos += windVec * dt;
		}

		// node movement
		for(int j = 0; j < 3; j++) 
		{
			// update node velocity?...
			if(mDataBlock->nodeMoveMode[j] == MultiNodeLaserBeamData::DynamicSpeed)
				mNodes[i].vel[j] = mDataBlock->nodeMoveSpeed[j] + mDataBlock->nodeMoveSpeedAdd[j] * sRandom.randF();

			// update node position...
			if(mDataBlock->nodeMoveMode[j] != MultiNodeLaserBeamData::None)
			{
				mNodes[i].pos[j] += mNodes[i].vel[j] * dt;
			}
		}
	}
}

//--------------------------------------------------------------------------

bool MultiNodeLaserBeam::prepRenderImage(SceneState* state, const U32 stateKey,
                                const U32 /*startZone*/, const bool /*modifyBaseState*/)
{
   if (isLastState(state, stateKey))
      return false;
   setLastState(state, stateKey);

   // This should be sufficient for most objects that don't manage zones, and
   //  don't need to return a specialized RenderImage...
   if (state->isObjectRendered(this)) {
      SceneRenderImage* image = new SceneRenderImage;
      image->obj = this;
      image->isTranslucent = true;
      image->sortType = SceneRenderImage::Point;
	  state->setImageRefPoint(this, image);
      state->insertRenderImage(image);
   }

   return false;
}

void MultiNodeLaserBeam::renderObject(SceneState* state, SceneRenderImage*)
{
   AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on entry");

   RectI viewport;
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   dglGetViewport(&viewport);

   state->setupObjectProjection(this);

   render( &state->getCameraPosition() );

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   dglSetViewport(viewport);

   AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on exit");
}

void MultiNodeLaserBeam::render( const Point3F* camPos )
{
   if( mRender && mNodes.size() > 1 ) // no use to render a 1 node beam
   {     
		if( Platform::getRealMilliseconds() > mLastCalcTime + 250 || mLastCalcTime == 0 )
		{
			switch(mDataBlock->renderMode)
			{
				case MultiNodeLaserBeamData::Horizontal:
				{
					Point3F vec = mNodes[1].pos-mNodes[0].pos;
					MatrixF mat = MathUtils::createOrientFromDir(vec);
					mat.getColumn(0,&mCrossVec);
					mCrossVec.normalize();
					break;
				}

				case MultiNodeLaserBeamData::Vertical:
				{
					Point3F vec = mNodes[1].pos-mNodes[0].pos;
					MatrixF mat = MathUtils::createOrientFromDir(vec);
					mat.getColumn(2,&mCrossVec);
					mCrossVec.normalize();
					break;
				}

				default: // FaceViewer
					Point3F dirFromCam = mNodes[0].pos - *camPos;
					mCross(dirFromCam, mNodes[0].pos - mNodes[mNodes.size()-1].pos, &mCrossVec);
					mCrossVec.normalize(); 
					break;
			}

			mLastCalcTime = Platform::getRealMilliseconds();
		}

		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);

	   //
	   // blend mode...
	   //
	   switch( mDataBlock->blendMode )
	   {
	      case 1:
	         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
	      case 2:
            glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
				break;
	      case 3:
            glBlendFunc(GL_ONE, GL_ONE);
				break;
			case 4:
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				break;
			default:
	         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
	   }

		ColorF color;
 
		// line...
		if( mDataBlock->hasLine )
		{
			color = mDataBlock->lineColor;
			if(mDataBlock->allowColorization)
				color.colorize(this->getSceneObjectColorization());

			glEnable(GL_LINE_WIDTH);
			glEnable(GL_LINE_SMOOTH);
			glLineWidth(mDataBlock->lineWidth); 

			glBegin(GL_LINE_STRIP); 

			for(int i=0; i<mNodes.size(); i++ )
			{
				LaserBeamNode node = mNodes[i];
				glColor4f( color.red, color.green, color.blue, color.alpha*node.alpha );
				glVertex3f(node.pos.x, node.pos.y, node.pos.z);				
			}

			glEnd();
			
			glLineWidth(1.0);
			glDisable(GL_LINE_SMOOTH);	
			glDisable(GL_LINE_WIDTH);
		}

		// inner...
		if( mDataBlock->hasInner )
		{
			color = mDataBlock->innerColor;
			if(mDataBlock->allowColorization)
				color.colorize(this->getSceneObjectColorization());

			glEnable(GL_POLYGON_SMOOTH);
			glBegin(GL_QUADS);

			Point3F vec = mCrossVec * mDataBlock->innerWidth * 0.5;
			for(int i=0; i<mNodes.size()-1; i++ )
			{
				LaserBeamNode node = mNodes[i];
				LaserBeamNode nextNode = mNodes[i+1];

				glColor4f( color.red, color.green, color.blue, color.alpha*node.alpha );
				glVertex3fv( node.pos - vec );
				glVertex3fv( node.pos + vec );
				glColor4f( color.red, color.green, color.blue, color.alpha*nextNode.alpha );
				glVertex3fv( nextNode.pos + vec );
				glVertex3fv( nextNode.pos - vec );
			}

			glEnd();
			glDisable(GL_POLYGON_SMOOTH);
		}

		// outer...
		if( mDataBlock->hasOuter )
		{
			color = mDataBlock->outerColor;
			if(mDataBlock->allowColorization)
				color.colorize(this->getSceneObjectColorization());

			glEnable(GL_POLYGON_SMOOTH);
			glBegin(GL_QUADS);

			Point3F vec = mCrossVec * mDataBlock->outerWidth * 0.5;
			for(int i=0; i<mNodes.size()-1; i++ )
			{
				LaserBeamNode node = mNodes[i];
				LaserBeamNode nextNode = mNodes[i+1];

				glColor4f( color.red, color.green, color.blue, color.alpha*node.alpha );
				glVertex3fv( node.pos - vec );
				glVertex3fv( node.pos + vec );
				glColor4f( color.red, color.green, color.blue, color.alpha*nextNode.alpha );
				glVertex3fv( nextNode.pos + vec );
				glVertex3fv( nextNode.pos - vec );
			}

			glEnd();
			glDisable(GL_POLYGON_SMOOTH);
		}

		// bitmap...
		if(mDataBlock->textureHandle)
		{
			glEnable(GL_TEXTURE_2D);

			TextureObject* texture = (TextureObject*)mDataBlock->textureHandle;
			glBindTexture(GL_TEXTURE_2D, texture->texGLName);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDepthMask(GL_FALSE);

			glEnable(GL_POLYGON_SMOOTH);
			glBegin(GL_QUADS);

			Point3F vec = mCrossVec * mDataBlock->bitmapWidth * 0.5;
			for(int i=0; i<mNodes.size()-1; i++ )
			{
				LaserBeamNode node = mNodes[i];
				LaserBeamNode nextNode = mNodes[i+1];

				color.set(1, 1, 1, node.alpha);
				if(mDataBlock->allowColorization)
					color.colorize(this->getSceneObjectColorization());
				glColor4fv(color); 

				glTexCoord2f(0,0);
				glVertex3fv( node.pos - vec );
				glTexCoord2f(0,1);
				glVertex3fv( node.pos + vec );
				color.alpha = nextNode.alpha;
				glColor4fv(color); 
				glTexCoord2f(1,1);
				glVertex3fv( nextNode.pos + vec );
				glTexCoord2f(1,0);
				glVertex3fv( nextNode.pos - vec );
			}

			glEnd();
			glDisable(GL_POLYGON_SMOOTH);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glDepthMask(GL_TRUE);
			glDisable(GL_TEXTURE_2D);
		}

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
   }

   // Debugging Bounding Box
   if(false)
   {
      glDisable(GL_DEPTH_TEST);
      Point3F box;
      glPushMatrix();
      dglMultMatrix(&getRenderTransform());
      box = (mObjBox.min + mObjBox.max) * 0.5;
      glTranslatef(box.x,box.y,box.z);
      box = (mObjBox.max - mObjBox.min) * 0.5;
      glScalef(box.x,box.y,box.z);
      glColor3f(1, 0, 1);
      wireCube(Point3F(1,1,1),Point3F(0,0,0));
      glPopMatrix();

      glPushMatrix();
      box = (mWorldBox.min + mWorldBox.max) * 0.5;
      glTranslatef(box.x,box.y,box.z);
      box = (mWorldBox.max - mWorldBox.min) * 0.5;
      glScalef(box.x,box.y,box.z);
      glColor3f(0, 1, 1);
      wireCube(Point3F(1,1,1),Point3F(0,0,0));
      glPopMatrix();
	  glEnable(GL_DEPTH_TEST);
   }
}

void MultiNodeLaserBeam::smooth()
{
	int s = mNodes.size();
	if(s < 2)
		return;
	F32 dt = 1.0 / (s-1);
	for(int i=0; i<s; i++ )
		mNodes[i].alpha = dt * i;
}

void MultiNodeLaserBeam::smoothDist(F32 dist)
{
	int s = mNodes.size();
	if(s < 2)
		return;
	F32 d = 0;
	mNodes[0].alpha = 0;
	for(int i=1; i<s; i++ )
	{
		d += (mNodes[i].pos - mNodes[i-1].pos).len();
		mNodes[i].alpha = mClamp((d/dist),0,1);
	}
}

void MultiNodeLaserBeam::smoothReverse()
{
	mFadeMode = 1;
	int s = mNodes.size();
	if(s < 2)
		return;
	F32 dt = 1.0 / (s-1);
	for(int i=0; i<s; i++ )
		mNodes[i].alpha = 1 - dt*i;
}

void MultiNodeLaserBeam::smoothReverseDist(F32 dist)
{
	int s = mNodes.size();

	if(s < 2)
		return;

	F32 d = 0;

	F32 dt = 1.0 / (s-1);

	mNodes[0].alpha = 1;
	for(int i=1; i<s; i++ )
	{
		d += (mNodes[i].pos - mNodes[i-1].pos).len();
		mNodes[i].alpha = 1 - (d/dist);
	}

	mFadeMode = 1;
}

#endif // BORQUE_NEEDS_PORTING
