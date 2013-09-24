// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hexagonVolume.h"

#include "Alux3D/grid.h"
#include "platform/platform.h"
#include "collision/boxConvex.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "core/stream/bitStream.h"
#include "core/fileObject.h"
#include "core/resourceManager.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/gfxDrawUtil.h"
#include "lighting/lightQuery.h"
#include "math/mathIO.h"
#include "renderInstance/renderPassManager.h"
#include "scene/sceneRenderState.h"
#include "ts/tsShapeInstance.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/physics/physicsPlugin.h"
#include "T3D/physics/physicsBody.h"
#include "T3D/physics/physicsCollision.h"

bool HexagonVolume::smRenderBounds = false;

// All the objects we care about must be
// derived from ShapeBase and be static!
U32 HexagonVolume::smBaseObjectMask = (ShapeBaseObjectType | StaticObjectType);

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(HexagonVolumeData);

ConsoleDocClass( HexagonVolumeData,
   "@brief Defines shared properties for HexagonVolume objects.\n\n"

   "TODO\n"

   "@see HexagonVolume.\n"
   "@ingroup gameObjects\n"
   "@ingroup Datablocks\n"
);

HexagonVolumeData::HexagonVolumeData()
{
   shapeName = StringTable->insert("");
   mode = 0;
	objectMask = StaticShapeObjectType;
}

bool HexagonVolumeData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

bool HexagonVolumeData::preload(bool server, String &errorStr)
{
   if(!Parent::preload(server, errorStr))
      return false;

   bool shapeError = false;

   if(shapeName && shapeName[0])
	{
      // Resolve shapename
      shape = ResourceManager::get().load(shapeName);
      if(bool(shape) == false)
      {
         errorStr = String::ToString("HexagonVolumeData: Couldn't load shape \"%s\"", shapeName);
         return false;
      }
      if(!server && !shape->preloadMaterialList(shape.getPath()) && NetConnection::filesWereDownloaded())
         shapeError = true;
   }

   return !shapeError;
}

void HexagonVolumeData::initPersistFields()
{
   addGroup("Operation");

      addField("mode", TypeS32, Offset(mode, HexagonVolumeData),
         "@brief How the render volume operates.\n\n"
         "Mode 0: Call prepRenderImage() method for each object.\n"
			"Mode 1: Grab each object's TSShape and render it.\n"
			"Mode 2: Build single TSShape from objects' TSShapes.\n"
			"Mode 3: Render collision geometry within volume.\n"
		);

		addField( "objectMask", TypeS32, Offset(objectMask, HexagonVolumeData),
			"@brief What kind of objects this volume should render.\n\n"
		);

   endGroup("Operation");

   addGroup( "Render" );

      addField( "shapeFile", TypeShapeFilename, Offset(shapeName, HexagonVolumeData),
         "The DTS or DAE model to use for the hexagons" );

   endGroup( "Render" );

   Parent::initPersistFields();
}


//--------------------------------------------------------------------------
void HexagonVolumeData::packData(BitStream* stream)
{
   Parent::packData(stream);
   stream->write(mode);
	stream->write(objectMask);
}

void HexagonVolumeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   stream->read(&mode);
	stream->read(&objectMask);
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(HexagonVolume);

ConsoleDocClass( HexagonVolume,
   "@brief TODO \n\n"
	"TODO\n"
   "@see HexagonVolumeData\n"
   "@ingroup gameObjects\n"
);

HexagonVolume::HexagonVolume()
{
   mNetFlags.set(Ghostable);

   mTypeMask |= StaticObjectType | StaticShapeObjectType;

   mObjScale.set(1, 1, 1);
   mObjToWorld.identity();
   mWorldToObj.identity();

	mDataBlock = NULL;

	mGrid = NULL;

	mHexMap.originGridPos.set(0,0,0);
	mHexMap.width = 0;
	mHexMap.height = 0;
	mHexMap.elevation = NULL;
	mHexMap.shapeNr = NULL;

	mServerShapeId = 0;
	mServerShapeRevision = 0;

	mShapeInstance = NULL;

	mRebuild.state = RebuildProcess::Ready;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.skipCount = 0;
	mRebuild.i = 0;
}

HexagonVolume::~HexagonVolume()
{
}

//-----------------------------------------------------------------------------
void HexagonVolume::consoleInit()
{
   Con::addVariable( "$HexagonVolume::renderBounds", TypeBool, &smRenderBounds,
      "@brief Makes HexagonVolumes render their bounds.\n\n"
      "Used by the Tools and debug render modes.\n"
      "@ingroup gameObjects" );
}

void HexagonVolume::initPersistFields()
{
   Parent::initPersistFields();
}

//--------------------------------------------------------------------------

bool HexagonVolume::onAdd()
{
   if(!Parent::onAdd())
      return false;

   // Set up a 1x1x1 bounding box
   mObjBox.set( Point3F( -0.5f, -0.5f, -0.5f ),
                Point3F(  0.5f,  0.5f,  0.5f ) );
   this->resetWorldBox();

   this->addToScene();

   if(this->isServerObject())
	{
		mServerShapeId = this->getId();
		mServerShapeRevision = 0;
      scriptOnAdd();
	}
      
   return true;
}

void HexagonVolume::onRemove()
{
   removeFromScene();
	if(this->isServerObject())
		this->onServerObjectDeleted();
	if(mRebuild.shape) SAFE_DELETE(mRebuild.shape);
	if(mShapeInstance) SAFE_DELETE(mShapeInstance);
   Parent::onRemove();
}

void HexagonVolume::onServerObjectDeleted()
{
	TSShape* shapePtr = TSShapeCache::getPtr(mServerShapeId);
	if(shapePtr)
		delete shapePtr;
	TSShapeCache::removePtr(mServerShapeId);
}

bool HexagonVolume::onNewDataBlock( GameBaseData *dptr, bool reload )
{
   mDataBlock = dynamic_cast<HexagonVolumeData*>( dptr );
   if ( !mDataBlock || !Parent::onNewDataBlock( dptr, reload ) )
      return false;

   scriptOnNewDataBlock();
   return true;
}

void HexagonVolume::onDeleteNotify( SimObject *obj )
{
   Parent::onDeleteNotify( obj );
}

void HexagonVolume::inspectPostApply()
{
   Parent::inspectPostApply();
}

//------------------------------------------------------------------------------

void HexagonVolume::setTransform(const MatrixF & mat)
{
   Parent::setTransform(mat);

   if (isServerObject()) {
      MatrixF base(true);
      base.scale(Point3F(1.0/mObjScale.x,
                         1.0/mObjScale.y,
                         1.0/mObjScale.z));
      base.mul(mWorldToObj);
      setMaskBits(TransformMask | RareUpdatesMask);
   }
}

void HexagonVolume::prepRenderImage(SceneRenderState* state)
{
	if(!state->isDiffusePass())
		return;

	if(smRenderBounds || isSelected())
	{
		ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
		ri->renderDelegate.bind(this, &HexagonVolume::renderObjectBounds);
		ri->type = RenderPassManager::RIT_Editor;      
		ri->translucentSort = true;
		ri->defaultKey = 1;
		state->getRenderPass()->addInst(ri);	
	}

	switch(mDataBlock->mode)
	{
		case 0: return this->prepRenderImageMode0(state);
		case 1: return this->prepRenderImageMode1(state);
		case 2: return this->prepRenderImageMode2(state);
		case 3: return this->prepRenderImageMode3(state);
	}
}

void HexagonVolume::prepRenderImageMode0(SceneRenderState* state)
{

}

void HexagonVolume::prepRenderImageMode1(SceneRenderState* state)
{

}

void HexagonVolume::prepRenderImageMode2(SceneRenderState* state)
{
   // Make sure we have a TSShapeInstance
   if(!mShapeInstance)
      return;

   // Calculate the distance of this object from the camera
   Point3F cameraOffset;
   getRenderTransform().getColumn( 3, &cameraOffset );
   cameraOffset -= state->getDiffuseCameraPosition();
   F32 dist = cameraOffset.len();
   if ( dist < 0.01f )
      dist = 0.01f;

   // Set up the LOD for the shape
   F32 invScale = ( 1.0f / getMax( getMax( mObjScale.x, mObjScale.y ), mObjScale.z ) );

   mShapeInstance->setDetailFromDistance( state, dist * invScale );

   // Make sure we have a valid level of detail
   if( mShapeInstance->getCurrentDetail() < 0 )
      return;

   // GFXTransformSaver is a handy helper class that restores
   // the current GFX matrices to their original values when
   // it goes out of scope at the end of the function
   GFXTransformSaver saver;

   // Set up our TS render state      
   TSRenderState rdata;
   rdata.setSceneState( state );
   rdata.setFadeOverride( 1.0f );

   // We might have some forward lit materials
   // so pass down a query to gather lights.
   LightQuery query;
   query.init( getWorldSphere() );
   rdata.setLightQuery( &query );

   // Set the world matrix to the objects render transform
   MatrixF mat = getRenderTransform();
   GFX->setWorldMatrix(mat);

   // Animate the the shape
   mShapeInstance->animate();

   // Allow the shape to submit the RenderInst(s) for itself
   mShapeInstance->render(rdata);
}

void HexagonVolume::prepRenderImageMode3(SceneRenderState* state)
{
   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &HexagonVolume::renderObjectMode3);
   ri->type = RenderPassManager::RIT_Editor;      
   ri->translucentSort = true;
   ri->defaultKey = 1;
   state->getRenderPass()->addInst(ri);
}

void HexagonVolume::renderObjectMode3(ObjectRenderInst* ri,
	SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if(overrideMat)
      return;

	mPolyList.render();

	if(!smRenderBounds && !isSelected())
		return;
}

void HexagonVolume::renderObjectBounds(ObjectRenderInst*  ri,
	SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if(overrideMat)
      return;

   GFXStateBlockDesc desc;
   desc.setZReadWrite(true, false);
   desc.setBlend(true);
   desc.fillMode = GFXFillWireframe;

   GFXDrawUtil *drawer = GFX->getDrawUtil();

	Point3F scale = this->getScale();
	Box3F box = this->getObjBox();
	box.minExtents.convolve(scale);
	box.maxExtents.convolve(scale);

	drawer->drawCube(desc, box, ColorI(0, 0, 100), &mRenderObjToWorld );
}

bool HexagonVolume::rebuild()
{
	if(!mDataBlock)
		return false;

	if(mRebuild.state != RebuildProcess::Ready)
	{
		mRebuild.skipCount++;
		return false;
	}

	if(this->isServerObject())
	{
		mServerShapeRevision++;
		this->rebuildHexMap();
		this->setMaskBits(RebuildMask);
	}

	if(this->isGhost())
		mRebuild.state = RebuildProcess::Init;

	return true;
}

void HexagonVolume::clearHexMap()
{
	mHexMap.width = 0;
	mHexMap.height = 0;
	if(mHexMap.elevation)
		delete[] mHexMap.elevation;
	mHexMap.elevation = NULL;
	if(mHexMap.shapeNr) 
		delete[] mHexMap.shapeNr;
	mHexMap.shapeNr = NULL;
}

bool HexagonVolume::rebuildHexMap()
{
	this->clearHexMap();

	if(mHexagons.empty())
		return true;

	Point3I minGridPos = mHexagons[0].gridPos;
	Point3I maxGridPos = mHexagons[0].gridPos;

	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		const Point3I& gridPos = mHexagons[i].gridPos;

		if(gridPos.x < minGridPos.x)
			minGridPos.x = gridPos.x;
		if(gridPos.y < minGridPos.y)
			minGridPos.y = gridPos.y;
		if(gridPos.z < minGridPos.z)
			minGridPos.z = gridPos.z;

		if(gridPos.x > maxGridPos.x)
			maxGridPos.x = gridPos.x;
		if(gridPos.y > maxGridPos.y)
			maxGridPos.y = gridPos.y;
		if(gridPos.z > maxGridPos.z)
			maxGridPos.z = gridPos.z;
	}

	mHexMap.originGridPos = minGridPos;
	mHexMap.width = maxGridPos.x - minGridPos.x + 1;
	mHexMap.height = maxGridPos.y - minGridPos.y + 1;

	U32 n = mHexMap.width*mHexMap.height;
	mHexMap.elevation = new U32[n];
	mHexMap.shapeNr = new U32[n];
	dMemset(mHexMap.elevation, 0, n*sizeof(U32));
	dMemset(mHexMap.shapeNr, 0, n*sizeof(U32));

	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		const Point3I& gridPos = mHexagons[i].gridPos;

		Point2I mapPos;
		mapPos.x = gridPos.x - mHexMap.originGridPos.x;
		mapPos.y = gridPos.y - mHexMap.originGridPos.y;

		U32 idx = (mapPos.y*mHexMap.width) + mapPos.x;
		mHexMap.elevation[idx] = gridPos.z - mHexMap.originGridPos.z + 1;
		mHexMap.shapeNr[idx] = mHexagons[i].shapeNr;
	}

	return true;
}

void HexagonVolume::rebuildMode2MoveMeshVerts(TSMesh* mesh, Point3F vec)
{
	// Note: Mesh must be disassembled!
	for(int i = 0; i < mesh->verts.size(); i++)
		mesh->verts[i] += vec;
}

void HexagonVolume::rebuildMode2MergeMesh(TSMesh* dest, TSMesh* src)
{
	// Note: Both meshes must be disassembled!
	U32 numVerts = dest->verts.size();
	U32 numIndices = dest->indices.size();

	dest->verts.merge(src->verts);
	dest->norms.merge(src->norms);
	dest->tverts.merge(src->tverts);
	dest->tangents.merge(src->tangents);
	dest->tverts2.merge(src->tverts2);
	dest->colors.merge(src->colors);

	dest->indices.reserve(dest->indices.size() + src->indices.size());
	for(int i = 0; i < src->indices.size(); i++)
	{
		dest->indices.push_back(src->indices[i]+numVerts);		
	}

	dest->primitives.reserve(dest->primitives.size() + src->primitives.size());
	for(int i = 0; i < src->primitives.size(); i++)
	{
		TSDrawPrimitive newPrimitive = src->primitives[i];
		newPrimitive.start += numIndices;
		dest->primitives.push_back(newPrimitive);
	}
}

void HexagonVolume::rebuildMode2Init()
{
	if(mRebuild.shape)
		delete mRebuild.shape;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.skipCount = 0;
	mRebuild.i = 0;

	// No geometry to rebuild?
	if(mHexMap.elevation == NULL)
	{
		if(mShapeInstance)
			SAFE_DELETE(mShapeInstance);
		this->rebuildMode2Done();
		return;
	}

	if(!mDataBlock || !mDataBlock->shape)
	{
		Con::errorf("HexagonVolume: Impossible to rebuild!");
		this->rebuildMode2Done();
		return;
	}

	mGrid = NULL;
	{
		Vector<SceneObject*> grids;
		this->getContainer()->findObjectList(GridObjectType, &grids);
		mGrid = (Grid*)grids[0];
	}

	if(mGrid == NULL)
	{
		Con::errorf("HexagonVolume: No grid, can't rebuild!");
		this->rebuildMode2Done();
		return;
	}

	if(this->isClientObject())
	{
		TSShape* cachedShape = TSShapeCache::getPtr(mServerShapeId);
		if(cachedShape)
		{
			if(cachedShape->revision == mServerShapeRevision)
			{
				//Con::printf("Have up-to-date cached shape.");
				if(mShapeInstance)
					SAFE_DELETE(mShapeInstance);
				mShapeInstance = new TSShapeInstance(cachedShape, this->isClientObject());
				mShapeInstance->initMaterialList();
				mRebuild.state = RebuildProcess::Ready;
				return;
			}
			else
			{
				//Con::printf("Have out-of-date cached shape.");
			}
		}
		else
		{
			//Con::printf("Don't have cached shape.");
		}
	}

	mRebuild.shape = new TSShape();
	mRebuild.shape->revision = mServerShapeRevision;
	mRebuild.shape->createEmptyShape();
	mRebuild.shape->init();
	mRebuild.shape->materialList = new TSMaterialList(mDataBlock->shape->materialList);

	mRebuild.state = RebuildProcess::Merge;
}

void HexagonVolume::rebuildMode2Merge()
{
	U32 idx = mRebuild.i++;
	U32 numHexagons = mHexMap.width * mHexMap.height;
	if(idx >= numHexagons)
	{
		mRebuild.state = RebuildProcess::Finish;
		return;
	}

	//Con::printf("Have %ix%i map", mHexMap.width, mHexMap.height);

	if(mHexMap.elevation[idx] == 0)
		return;

	U32 shapeNr = mHexMap.shapeNr[idx];
	char shapeNodeName[256];
	char shapeMeshName[256];
	char newMeshName[256];

	dSprintf(shapeNodeName, sizeof(shapeNodeName), "shape%imesh", shapeNr);
	dSprintf(shapeMeshName, sizeof(shapeMeshName), "shape%imesh2", shapeNr);
	dSprintf(newMeshName, sizeof(newMeshName), "hexmap%imesh2", idx);

	if(mRebuild.shape->addMesh(mDataBlock->shape, shapeMeshName, newMeshName))
	{
		Point3F adjustPos(0,0,0);
		S32 nodeIndex = mDataBlock->shape->findNode(shapeNodeName);
		if(nodeIndex >= 0)
			adjustPos = mDataBlock->shape->defaultTranslations[nodeIndex];

		Point3I mapPos;
		mapPos.y = idx / mHexMap.width;
		mapPos.x = idx - (mapPos.y*mHexMap.width);
		mapPos.z = mHexMap.elevation[idx];

		Point3I gridPos;
		gridPos.x = mHexMap.originGridPos.x + mapPos.x;
		gridPos.y = mHexMap.originGridPos.y + mapPos.y;
		gridPos.z = mHexMap.originGridPos.z + mapPos.z - 1;

		Point3F worldPos = mGrid->gridToWorld(gridPos);
		Point3F meshPos = worldPos - this->getPosition() + adjustPos;

		//Con::printf("Hexagon grid pos: %i %i %i", gridPos.x, gridPos.y, gridPos.z);
		//Con::printf("Hexagon world pos: %f %f %f", worldPos.x, worldPos.y, worldPos.z);
		//Con::printf("Mesh pos: %f %f %f", meshPos.x, meshPos.y, meshPos.z);

		TSShape::smTSAlloc.setWrite();

		if(mRebuild.mesh == NULL)
		{
			//Con::printf("Added initial mesh %s", newMeshName);
			mRebuild.mesh = mRebuild.shape->findMesh(newMeshName);
			if(mRebuild.mesh)
			{
				mRebuild.mesh->disassemble();
				rebuildMode2MoveMeshVerts(mRebuild.mesh, meshPos);
			}
			else
			{
				Con::errorf("HexagonVolume: Unable to find mesh %s", newMeshName);
			}
		}
		else
		{
			//Con::printf("Added temporary mesh %s", newMeshName);
			TSMesh* tmp = mRebuild.shape->findMesh(newMeshName);
			if(tmp)
			{
				tmp->disassemble();
				rebuildMode2MoveMeshVerts(tmp, meshPos);
				rebuildMode2MergeMesh(mRebuild.mesh, tmp);
				mRebuild.shape->removeMesh(newMeshName);
				//Con::printf("Merged and removed temporary mesh %s", newMeshName);
			}
			else
			{
				Con::errorf("HexagonVolume: Unable to find mesh %s", newMeshName);
			}
		}
	}
}

void HexagonVolume::rebuildMode2Finish()
{
	if(mRebuild.mesh == NULL)
	{
		Con::errorf("HexagonVolume: Merging meshes failed somehow!");
		this->rebuildMode2Done();
		return;
	}

	mRebuild.mesh->mVertexData.setReady(false);
	mRebuild.mesh->disassemble();
	mRebuild.mesh->computeBounds();
	mRebuild.mesh->createTangents(mRebuild.mesh->verts, mRebuild.mesh->norms);
	mRebuild.mesh->convertToAlignedMeshData();
	
	mRebuild.shape->updateSmallestVisibleDL();
	mRebuild.shape->init();

	TSShape* oldShape = TSShapeCache::getPtr(mServerShapeId);
	if(oldShape)
		delete oldShape;
	TSShape* newShape = mRebuild.shape;
	mRebuild.shape = NULL;
	TSShapeCache::insertPtr(mServerShapeId, newShape);

	if(mShapeInstance)
		SAFE_DELETE(mShapeInstance);
	mShapeInstance = new TSShapeInstance(newShape, this->isClientObject());
	if(this->isGhost())
		mShapeInstance->initMaterialList();

#if 0
	// Save shape to file so it can be debugged in shape editor.
	FileStream stream;
   stream.open("content/test.dts", Torque::FS::File::Write);
   if(stream.getStatus() != Stream::Ok )
   {
      Con::errorf("HexagonVolume::rebuildShape() - Could not open file");
      return;
   }
	shapePtr->write(&stream);
	stream.close();
#endif

	this->rebuildMode2Done();
}

void HexagonVolume::rebuildMode2Done()
{
	mRebuild.state = RebuildProcess::Ready;
	if(mRebuild.shape)
		delete mRebuild.shape;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.skipCount = 0;
	mRebuild.i = 0;
}

void HexagonVolume::rebuildMode3()
{
	Point3F scale = this->getScale();
	Box3F box = this->getObjBox();
	box.minExtents.convolve(scale);
	box.maxExtents.convolve(scale);
	MatrixF mat = this->getTransform();
	mat.mul(box);

	mPolyList.clear();
	this->getContainer()->buildPolyList(
		PLC_Collision,
		box,
		mDataBlock->objectMask,
		&mPolyList
	);
}

//--------------------------------------------------------------------------

void HexagonVolume::clearHexagons()
{
	mHexagons.clear();
}

bool HexagonVolume::addHexagon(Point3I gridPos, U32 shapeNr)
{
	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		if(mHexagons[i].gridPos == gridPos)
		{
			if(mHexagons[i].shapeNr != shapeNr)
			{
				mHexagons[i].shapeNr = shapeNr;
				return true;
			}
			else
				return false;
		}
	}

	Hexagon newHexagon;
	newHexagon.gridPos = gridPos;
	newHexagon.shapeNr = shapeNr;

	mHexagons.push_back(newHexagon);
	return true;
}

bool HexagonVolume::removeHexagon(Point3I gridPos)
{
	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		if(mHexagons[i].gridPos == gridPos)
		{
			mHexagons.erase(i);
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------

void HexagonVolume::processTick(const Move* move)
{
   Parent::processTick(move);

	if(mRebuild.state == RebuildProcess::Init)
		this->rebuildMode2Init();
	else if(mRebuild.state == RebuildProcess::Merge)
		this->rebuildMode2Merge();
	else if(mRebuild.state == RebuildProcess::Finish)
		this->rebuildMode2Finish();
}

//--------------------------------------------------------------------------

U32 HexagonVolume::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);

   if(stream->writeFlag(mask & InitialUpdateMask))
   {
      stream->write(mServerShapeId);
   }

   if(stream->writeFlag(mask & TransformMask))
   {
      stream->writeAffineTransform(mObjToWorld);
   }

   if(stream->writeFlag(mask & RebuildMask))
   {
		stream->write(mServerShapeRevision);
		if(stream->writeFlag(mHexagons.size() > 0))
		{
			mathWrite(*stream, mHexMap.originGridPos);
			stream->write(mHexMap.width);
			stream->write(mHexMap.height);

			U32 n = mHexMap.width*mHexMap.height;
			for(U32 i = 0; i < n; i++)
			{
				U32 elevation = mHexMap.elevation[i];
				U32 shapeNr = mHexMap.shapeNr[i];
				if(stream->writeFlag(elevation != 0))
				{
					stream->writeInt(elevation, 4);
					stream->writeInt(shapeNr, 2);
				}
			}
		}
   }

   return retMask;
}

void HexagonVolume::unpackUpdate(NetConnection* con, BitStream* stream)
{
   Parent::unpackUpdate(con, stream);

   // Initial update
   if(stream->readFlag())
   {
		stream->read(&mServerShapeId);
	}

   // Transform
   if(stream->readFlag())
   {
      MatrixF temp;
      stream->readAffineTransform(&temp);
      setTransform(temp);
   }

	// Rebuild
	if(stream->readFlag())
	{
		this->clearHexMap();
		stream->read(&mServerShapeRevision);
		if(stream->readFlag())
		{
			mathRead(*stream, &mHexMap.originGridPos);
			stream->read(&mHexMap.width);
			stream->read(&mHexMap.height);

			U32 n = mHexMap.width*mHexMap.height;
			if(n > 0)
			{
				mHexMap.elevation = new U32[n];
				mHexMap.shapeNr = new U32[n];
				dMemset(mHexMap.elevation, 0, n*sizeof(U32));
				dMemset(mHexMap.shapeNr, 0, n*sizeof(U32));
				for(U32 i = 0; i < n; i++)
				{
					if(stream->readFlag())
					{
						mHexMap.elevation[i] = stream->readInt(4);
						mHexMap.shapeNr[i] = stream->readInt(2);
					}
				}
			}
		}
		this->rebuild();
	}
}

//--------------------------------------------------------------------------

DefineEngineMethod(HexagonVolume, clearHexagons, void, (),,
   "@brief Removes all hexagons from the volume.\n\n"
)
{
   object->clearHexagons();
}


DefineEngineMethod(HexagonVolume, addHexagon, bool, (Point3I gridPos, U32 shapeNr),,
   "@brief Add a hexagon to the volume.\n\n"

   "@param Grid position of the new hexagon\n"
	"@param Shape number of the hexagon\n"
)
{
   return object->addHexagon(gridPos, shapeNr);
}

DefineEngineMethod(HexagonVolume, removeHexagon, bool, (Point3I pos),,
   "@brief Add a hexagon to the volume.\n\n"

   "@param Position of the new hexagon\n"
)
{
   return object->removeHexagon(pos);
}

DefineEngineMethod(HexagonVolume, rebuild, void, (),,
   "@brief Rebuild render geometry.\n\n"
)
{
   object->rebuild();
}