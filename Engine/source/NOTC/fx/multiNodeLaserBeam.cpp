// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "multiNodeLaserBeam.h"

#include "console/consoleTypes.h"
#include "core/stream/bitStream.h"
#include "collision/boxConvex.h"
#include "gfx/gfxDevice.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxStateBlock.h"
#include "math/mathIO.h"
#include "math/mathUtils.h"
#include "scene/sceneRenderState.h"
#include "terrain/terrData.h"
#include "terrain/terrRender.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/gameBase/gameProcess.h"
#include "T3D/fx/particleEmitter.h"
#include "materials/materialManager.h"
#include "materials/baseMatInstance.h"
#include "renderInstance/renderPassManager.h"
#include "lighting/lightQuery.h"

static MRandomLCG sRandom(0x1);

IMPLEMENT_CO_DATABLOCK_V1(MultiNodeLaserBeamData);

MultiNodeLaserBeamData::MultiNodeLaserBeamData()
{
   materialInst = NULL;

	width = 0.2;

	renderMode = FaceViewer;

	windCoefficient = 0.0f;

	nodeMoveMode[0] = nodeMoveMode[1] = nodeMoveMode[2] = None;
	nodeMoveSpeed[0] = nodeMoveSpeed[1] = nodeMoveSpeed[2] = 0.0f;
	nodeMoveSpeedAdd[0] = nodeMoveSpeedAdd[1] = nodeMoveSpeedAdd[2] = 0.0f;

	nodeDistance = 0.0f;

	fadeTime = 1000;
}

MultiNodeLaserBeamData::~MultiNodeLaserBeamData()
{
   if(materialInst)
      SAFE_DELETE(materialInst);
}

//--------------------------------------------------------------------------
void MultiNodeLaserBeamData::initPersistFields()
{
	Parent::initPersistFields();

   addField( "material",    TypeMaterialName, Offset(materialString, MultiNodeLaserBeamData),
      "The name of the material used to render the beam." );

	addField("width",  TypeF32,      Offset(width, MultiNodeLaserBeamData));

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


bool MultiNodeLaserBeamData::preload(bool server, String &errorStr)
{
   if(Parent::preload(server, errorStr) == false)
      return false;

   if(server)
      return true;

   if(!materialString.isEmpty())
   {
      SAFE_DELETE(materialInst);
      materialInst = MATMGR->createMatInstance(materialString, getGFXVertexFormat<MultiNodeLaserBeam::VertexType>());
      if(!materialInst)
         Con::errorf( "MultiNodeLaserBeamData::preload - no Material called '%s'", materialString.c_str() );
   }

   return true;
}


//--------------------------------------------------------------------------

void MultiNodeLaserBeamData::packData(BitStream* stream)
{
	Parent::packData(stream);

   stream->write(materialString);

	stream->write(width);

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

   stream->read(&materialString);

	stream->read(&width);

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


//-------------------------------------------------------------------

IMPLEMENT_CONOBJECT(MultiNodeLaserBeam);

MultiNodeLaserBeam::MultiNodeLaserBeam()
{
   //mTypeMask |= StaticRenderedObjectType;
   mNetFlags.set(IsGhost);

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
		{ mObjBox.maxExtents.x = a.x; mObjBox.minExtents.x = b.x; }
	else
		{ mObjBox.maxExtents.x = b.x; mObjBox.minExtents.x = a.x; }
	if( a.y > b.y )
		{ mObjBox.maxExtents.y = a.y; mObjBox.minExtents.y = b.y; }
	else
		{ mObjBox.maxExtents.y = b.y; mObjBox.minExtents.y = a.y; }
	if( a.z > b.z )
		{ mObjBox.maxExtents.z = a.z; mObjBox.minExtents.z = b.z; }
	else
		{ mObjBox.maxExtents.z = b.z; mObjBox.minExtents.z = a.z; }

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
   mObjBox.minExtents = Point3F(-1,-1,-1);
   mObjBox.maxExtents = Point3F(1,1,1);
   resetWorldBox();
	setRenderTransform(mObjToWorld);

   gClientSceneGraph->addObjectToScene(this);

   this->removeFromProcessList();
   ClientProcessList::get()->addObject(this);

   NetConnection* pNC = NetConnection::getConnectionToServer();
   AssertFatal(pNC != NULL, "Error, must have a connection to the server!");
   pNC->addObject(this);

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

bool MultiNodeLaserBeam::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<MultiNodeLaserBeamData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
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
	Point3F windVec = ParticleEmitter::mWindVelocity * mDataBlock->windCoefficient;

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

void MultiNodeLaserBeam::prepRenderImage(SceneRenderState* state)
{
   // Get a handy pointer to our RenderPassmanager
   RenderPassManager* renderPass = state->getRenderPass();

   this->updateRenderData(state->getCameraPosition());

   const Frustum &frustum = state->getCameraFrustum();

   //for(U32 i = 0; i < NumRenderParts; i++)
   {
      RenderData* renderData = &mRenderData;

      if(renderData->numVerts == 0)
         return;

      BaseMatInstance* matInst;

      matInst = mDataBlock->materialInst;

      if(!matInst)
         return;

      // If we don't have a material instance after the override then
      // we can skip rendering all together.
      matInst = state->getOverrideMaterial(matInst);
      if(!matInst)
         return;

      // Allocate an MeshRenderInst so that we can submit it to the RenderPassManager
      MeshRenderInst* ri = renderPass->allocInst<MeshRenderInst>();

      // Set palette.
      ri->palette = this->getPalette();

      // Set our RenderInst as a standard mesh render
      ri->type = RenderPassManager::RIT_Mesh;

      //If our material has transparency set on this will redirect it to proper render bin
      if(matInst->getMaterial()->isTranslucent())
      {
         ri->type = RenderPassManager::RIT_Translucent;
         ri->translucentSort = true;
      }

      // Calculate our sorting point
      if ( state )
      {
         // Calculate our sort point manually.
         const Box3F& rBox = getRenderWorldBox();
         ri->sortDistSq = rBox.getSqDistanceToPoint( state->getCameraPosition() );
      }
      else
         ri->sortDistSq = 0.0f;

      // Set up our transforms
      MatrixF objectToWorld = getRenderTransform();
      objectToWorld.scale( getScale() );

      ri->objectToWorld = &MatrixF::Identity;
      ri->worldToCamera = renderPass->allocSharedXform(RenderPassManager::View);
      ri->projection = renderPass->allocSharedXform(RenderPassManager::Projection);

	   // If our material needs lights then fill the RIs
      // light vector with the best lights.
      if(matInst->isForwardLit())
      {
         LightQuery query;
         query.init( getWorldSphere() );
		   query.getLights( ri->lights, 8 );
      }

      // Make sure we have an up-to-date backbuffer in case
      // our Material would like to make use of it
      // NOTICE: SFXBB is removed and refraction is disabled!
      //ri->backBuffTex = GFX->getSfxBackBuffer();

      // Set our Material
      ri->matInst = matInst;

      // Set up our vertex buffer and primitive buffer
      ri->vertBuff = &renderData->vertBuf;
      ri->primBuff = &renderData->primBuf;

      ri->prim = renderPass->allocPrim();
      ri->prim->type = renderData->primType;
      ri->prim->minIndex = 0;
      ri->prim->startIndex = 0;
      ri->prim->numPrimitives = renderData->numPrims;
      ri->prim->startVertex = 0;
      ri->prim->numVertices = renderData->numVerts;

      // We sort by the material then vertex buffer
      ri->defaultKey = matInst->getStateHint();
      ri->defaultKey2 = (U32)ri->vertBuff; // Not 64bit safe!

      // Submit our RenderInst to the RenderPassManager
      state->getRenderPass()->addInst(ri);
   }
}

void MultiNodeLaserBeam::updateRenderData(const Point3F& camPos)
{
   RenderData* dst = &mRenderData;

   dst->primType = GFXTriangleList;

   if(!mRender || mNodes.size() < 2 )
   {     
      dst->numVerts = 0;
      dst->numPrims = 0;
      return;
   }

   //if(Platform::getRealMilliseconds() > mLastCalcTime + 250 || mLastCalcTime == 0 )
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
				Point3F dirFromCam = mNodes[0].pos - camPos;
				mCross(dirFromCam, mNodes[0].pos - mNodes[mNodes.size()-1].pos, &mCrossVec);
				mCrossVec.normalize(); 
				break;
		}

		mLastCalcTime = Platform::getRealMilliseconds();
	}

   dst->numPrims = (mNodes.size()-1)*2;
   dst->numVerts = dst->numPrims*3;

   dst->primBuf.set( GFX, dst->numVerts, dst->numPrims, GFXBufferTypeStatic );
   dst->vertBuf.set(GFX, dst->numVerts, GFXBufferTypeStatic );

   U32 idx = 0;

   VertexType* pVert = dst->vertBuf.lock();
   U16* pIdx = NULL; dst->primBuf.lock(&pIdx);

   Point3F vec = mCrossVec * mDataBlock->width * 0.5;
   for(int i=0; i<mNodes.size()-1; i++ )
   {
	   LaserBeamNode node = mNodes[i];
	   LaserBeamNode nextNode = mNodes[i+1];

      ColorF color1(1, 1, 1, node.alpha);
      ColorF color2(1, 1, 1, nextNode.alpha);

      pVert[idx].point    = node.pos - vec;
      pVert[idx].color    = color1;
      pVert[idx].texCoord = Point2F(0, 0);
      pIdx[idx] = idx;
      idx++;
      pVert[idx].point    = node.pos + vec;
      pVert[idx].color    = color1;
      pVert[idx].texCoord = Point2F(0, 1);
      pIdx[idx] = idx;
      idx++;
      pVert[idx].point    = nextNode.pos - vec;
      pVert[idx].color    = color2;
      pVert[idx].texCoord = Point2F(1, 0);
      pIdx[idx] = idx;
      idx++;

      pVert[idx].point    = node.pos + vec;
      pVert[idx].color    = color1;
      pVert[idx].texCoord = Point2F(0, 1);
      pIdx[idx] = idx;
      idx++;
      pVert[idx].point    = nextNode.pos + vec;
      pVert[idx].color    = color2;
      pVert[idx].texCoord = Point2F(1, 1);
      pIdx[idx] = idx;
      idx++;
      pVert[idx].point    = nextNode.pos - vec;
      pVert[idx].color    = color2;
      pVert[idx].texCoord = Point2F(1, 0);
      pIdx[idx] = idx;
      idx++;
   }

   dst->primBuf.unlock();
   dst->vertBuf.unlock();
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

