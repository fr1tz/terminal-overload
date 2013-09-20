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

	mHexMap.originGridPos.set(0,0,0);
	mHexMap.width = 0;
	mHexMap.height = 0;
	mHexMap.data = NULL;

	mServerShape = NULL;
	mServerShapeId = 0;
	mServerShapeRevision = 0;

	mShapeInstance = NULL;

	mClientPerformRebuild = false;
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
	if(mServerShape) SAFE_DELETE(mServerShape);
	if(mShapeInstance) SAFE_DELETE(mShapeInstance);
   Parent::onRemove();
}

void HexagonVolume::onServerObjectDeleted()
{
	AssertFatal(this->isGhost(), "HexagonVolume::onServerObjectDeleted()"
		"called on non-ghost object");

	TSShapeCache::destroy(mServerShapeId);
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

	if(this->isServerObject())
	{
		mServerShapeRevision++;
		this->rebuildHexMap();
		this->setMaskBits(RebuildMask);
	}

	return this->rebuildMode2();
}

bool HexagonVolume::rebuildHexMap()
{
	if(mHexMap.data)
	{
		delete[] mHexMap.data;
		mHexMap.data = NULL;
	}
	mHexMap.width = 0;
	mHexMap.height = 0;

	if(mHexagons.empty())
		return true;

	Point3I minGridPos = mHexagons[0];
	Point3I maxGridPos = mHexagons[0];

	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		const Point3I& gridPos = mHexagons[i];

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
	mHexMap.data = new U32[n];
	dMemset(mHexMap.data, 0, n*sizeof(U32));

	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		const Point3I& gridPos = mHexagons[i];

		Point2I mapPos;
		mapPos.x = gridPos.x - mHexMap.originGridPos.x;
		mapPos.y = gridPos.y - mHexMap.originGridPos.y;

		U32 idx = (mapPos.y*mHexMap.width) + mapPos.x;
		mHexMap.data[idx] = gridPos.z - mHexMap.originGridPos.z + 1;
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

	for(int i = 0; i < src->indices.size(); i++)
	{
		dest->indices.push_back(src->indices[i]+numVerts);		
	}

	for(int i = 0; i < src->primitives.size(); i++)
	{
		TSDrawPrimitive newPrimitive = src->primitives[i];
		newPrimitive.start += numIndices;
		dest->primitives.push_back(newPrimitive);
	}
}

bool HexagonVolume::rebuildMode2()
{
	if(!mDataBlock || !mDataBlock->shape)
		return false;

	if(mHexMap.data == NULL)
	{
		if(mShapeInstance)
			SAFE_DELETE(mShapeInstance);
		return true;
	}

	if(this->isClientObject())
	{
		TSShape* cachedShape = TSShapeCache::get(mServerShapeId);
		if(cachedShape)
		{
			if(cachedShape->revision == mServerShapeRevision)
			{
				//Con::printf("Have up-to-date cached shape.");
				if(mShapeInstance)
					SAFE_DELETE(mShapeInstance);
				mShapeInstance = new TSShapeInstance(cachedShape, this->isClientObject());
				mShapeInstance->initMaterialList();
				return true;
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

	Grid* grid = NULL;
	{
		Vector<SceneObject*> grids;
		this->getContainer()->findObjectList(GridObjectType, &grids);
		grid = (Grid*)grids[0];
	}

	if(grid == NULL)
	{
		Con::errorf("HexagonVolume: No grid, can't rebuild!");
		return false;
	}

	Point3F adjustPos(0,0,0);
	S32 nodeIndex = mDataBlock->shape->findNode("Mesh");
	if(nodeIndex >= 0)
	{
		adjustPos = mDataBlock->shape->defaultTranslations[nodeIndex];
		//adjustPos *= 0.5;
	}

	TSShape* shapePtr;
	if(this->isServerObject())
	{
		if(mServerShape) 
			delete mServerShape;
		mServerShape = new TSShape();
		shapePtr = mServerShape;
	}
	else
	{
		TSShapeCache::destroy(mServerShapeId);
		TSShapeCache::allocate(mServerShapeId);
		shapePtr = TSShapeCache::get(mServerShapeId);
	}

	shapePtr->revision = mServerShapeRevision;
	shapePtr->createEmptyShape();
	shapePtr->init();
	shapePtr->materialList = new TSMaterialList(mDataBlock->shape->materialList);
	TSMesh* mesh = NULL;
	TSShape::smTSAlloc.setWrite();

	U32 numMeshes = 0;
	U32 numHexagons = mHexMap.width * mHexMap.height;
	//Con::printf("Have %ix%i map", mHexMap.width, mHexMap.height);

	for(U32 idx = 0; idx < numHexagons; idx++)
	{
		if(mHexMap.data[idx] == 0)
			continue;

		char newMeshName[256];
		dSprintf(newMeshName, sizeof(newMeshName), "Object%iMesh2", idx);
		if(shapePtr->addMesh(mDataBlock->shape, "Mesh2", newMeshName))
		{
			Point3I mapPos;
			mapPos.y = idx / mHexMap.width;
			mapPos.x = idx - (mapPos.y*mHexMap.width);
			mapPos.z = mHexMap.data[idx];

			Point3I gridPos;
			gridPos.x = mHexMap.originGridPos.x + mapPos.x;
			gridPos.y = mHexMap.originGridPos.y + mapPos.y;
			gridPos.z = mHexMap.originGridPos.z + mapPos.z - 1;

			Point3F worldPos = grid->gridToWorld(gridPos);
			Point3F meshPos = worldPos - this->getPosition() + adjustPos;

			//Con::printf("Hexagon grid pos: %i %i %i", gridPos.x, gridPos.y, gridPos.z);
			//Con::printf("Hexagon world pos: %f %f %f", worldPos.x, worldPos.y, worldPos.z);
			//Con::printf("Mesh pos: %f %f %f", meshPos.x, meshPos.y, meshPos.z);

			if(mesh == NULL)
			{
				//Con::printf("Added initial mesh %s", newMeshName);
				mesh = shapePtr->findMesh(newMeshName);
				if(mesh)
				{
					mesh->disassemble();
					rebuildMode2MoveMeshVerts(mesh, meshPos);
					numMeshes++;
				}
				else
				{
					Con::errorf("HexagonVolume: Unable to find mesh %s", newMeshName);
				}
			}
			else
			{
				//Con::printf("Added temporary mesh %s", newMeshName);
				TSMesh* tmp = shapePtr->findMesh(newMeshName);
				if(tmp)
				{
					tmp->disassemble();
					rebuildMode2MoveMeshVerts(tmp, meshPos);
					rebuildMode2MergeMesh(mesh, tmp);
					shapePtr->removeMesh(newMeshName);
					//Con::printf("Merged and removed temporary mesh %s", newMeshName);
					numMeshes++;
				}
				else
				{
					Con::errorf("HexagonVolume: Unable to find mesh %s", newMeshName);
				}
			}
		}
	}

	if(numMeshes == 0)
	{
		Con::errorf("HexagonVolume: Merging meshes failed somehow!");
		return false;
	}
	else
	{
		//Con::printf("Merged %i meshes", numMeshes);
	}

	if(mesh)
	{
		mesh->mVertexData.setReady(false);
		mesh->disassemble();
		mesh->computeBounds();
		mesh->createTangents(mesh->verts, mesh->norms);
		mesh->convertToAlignedMeshData();
	}
	shapePtr->updateSmallestVisibleDL();
	shapePtr->init();

	if(mShapeInstance)
		SAFE_DELETE(mShapeInstance);
	mShapeInstance = new TSShapeInstance(shapePtr, this->isClientObject());
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

	return true;
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

bool HexagonVolume::addHexagon(Point3I gridpos)
{
	for(U32 i = 0; i < mHexagons.size(); i++)
		if(mHexagons[i] == gridpos)
			return false;

	mHexagons.push_back(gridpos);
	return true;
}

bool HexagonVolume::removeHexagon(Point3I gridpos)
{
	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		if(mHexagons[i] == gridpos)
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

	if(mClientPerformRebuild)
	{
		if(this->rebuild())
			mClientPerformRebuild = false;
	}
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
				U32 elevation = mHexMap.data[i];
				if(stream->writeFlag(elevation != 0))
					stream->writeInt(elevation, 4);
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
		stream->read(&mServerShapeRevision);
		if(stream->readFlag())
		{
			mathRead(*stream, &mHexMap.originGridPos);
			stream->read(&mHexMap.width);
			stream->read(&mHexMap.height);

			if(mHexMap.data)
			{
				delete[] mHexMap.data;
				mHexMap.data = NULL;
			}

			U32 n = mHexMap.width*mHexMap.height;
			if(n > 0)
			{
				mHexMap.data = new U32[n];
				for(U32 i = 0; i < n; i++)
				{
					if(stream->readFlag())
						mHexMap.data[i] = stream->readInt(4);
					else
						mHexMap.data[i] = 0;
				}
			}
		}
		mClientPerformRebuild = true;
	}
}

//--------------------------------------------------------------------------

DefineEngineMethod(HexagonVolume, clearHexagons, void, (),,
   "@brief Removes all hexagons from the volume.\n\n"
)
{
   object->clearHexagons();
}


DefineEngineMethod(HexagonVolume, addHexagon, bool, (Point3I pos),,
   "@brief Add a hexagon to the volume.\n\n"

   "@param Position of the new hexagon\n"
)
{
   return object->addHexagon(pos);
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