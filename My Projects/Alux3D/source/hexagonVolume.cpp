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
	for(int i = 0; i < MaxShapes; i++)
	{
		renderShapeName[i] = StringTable->insert("");
		renderShapeInstance[i] = NULL;
	}
   dMemset(collisionShapeData, 0, sizeof(collisionShapeData));
	dMemset(collisionShapeDataID, 0, sizeof(collisionShapeDataID));

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

	for(int i = 0; i < MaxShapes; i++)
	{
		if(renderShapeName[i] && renderShapeName[i][0])
		{
			// Resolve shapename
			renderShape[i] = ResourceManager::get().load(renderShapeName[i]);
			if(bool(renderShape[i]) == false)
			{
				errorStr = String::ToString("HexagonVolumeData: Couldn't load shape \"%s\"", renderShapeName[i]);
				return false;
			}
			if(!server)
			{
				if(renderShape[i]->preloadMaterialList(renderShape[i].getPath()))
				{
					renderShapeInstance[i] = new TSShapeInstance(renderShape[i], !server);
					renderShapeInstance[i]->initMaterialList();
				}
				else
					shapeError = true;
			}
		}

		if(!collisionShapeData[i] && collisionShapeDataID[i] != 0 )
			if(!Sim::findObject(collisionShapeDataID[i], collisionShapeData[i]))
				Con::errorf(ConsoleLogEntry::General, "HexagonVolumeData::preload - Invalid packet, bad datablockId(collisionShape): 0x%x", collisionShapeDataID[i]);
	}

   return !shapeError;
}

void HexagonVolumeData::initPersistFields()
{
   addGroup("Operation");

		addField("collisionShape", TYPEID<StaticShapeData>(), Offset(collisionShapeData, HexagonVolumeData), MaxShapes,
			"The datablock to use for the collision object."
		);

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

      addField( "renderShapeFile", TypeShapeFilename, Offset(renderShapeName, HexagonVolumeData), MaxShapes,
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
	for(U32 i = 0; i < MaxShapes; i++)
	{
		if(stream->writeFlag(renderShapeName[i] && renderShapeName[i][0]))
			stream->writeString(renderShapeName[i]);
      if(stream->writeFlag(collisionShapeData[i]))
         stream->writeRangedU32(collisionShapeData[i]->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);
	}
}

void HexagonVolumeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   stream->read(&mode);
	stream->read(&objectMask);
	for(U32 i = 0; i < MaxShapes; i++)
	{
		if(stream->readFlag())
			renderShapeName[i] = stream->readSTString();
		if(stream->readFlag())
			collisionShapeDataID[i] = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
	}
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
	mHexMap.hexArray = NULL;

	mRebuild.state = RebuildProcess::Ready;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.idx = 0;
	mClientStartRebuild = false;

	mServerShapeId = 0;
	mServerShapeRevision = 0;

	mShapeInstance = NULL;
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
	this->deleteCollisionObjects();
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

   if(this->isServerObject())
	{
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
	if(!mGrid)
		return;

	if(mRebuild.state == RebuildProcess::Ready)
	{
		if(!mShapeInstance)
			return;
	}

   // Calculate the distance of this object from the camera
   Point3F cameraOffset;
   getRenderTransform().getColumn( 3, &cameraOffset );
   cameraOffset -= state->getDiffuseCameraPosition();
   F32 dist = cameraOffset.len();
   if ( dist < 0.01f )
      dist = 0.01f;

   // Set up the LOD for the shape
   F32 invScale = ( 1.0f / getMax( getMax( mObjScale.x, mObjScale.y ), mObjScale.z ) ); 

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

	if(mRebuild.state == RebuildProcess::Ready)
	{
		mShapeInstance->setDetailFromDistance( state, dist * invScale );
		if(mShapeInstance->getCurrentDetail() >= 0)
		{
		   // Set the world matrix to the objects render transform
			MatrixF mat = getRenderTransform();
			GFX->setWorldMatrix(mat);

			//mShapeInstance->animate();
			mShapeInstance->render(rdata);
		}
	}
	else
	{
		for(int i = 0; i < HexagonVolumeData::MaxShapes; i++)
		{
			if(mDataBlock->renderShapeInstance[i])
				mDataBlock->renderShapeInstance[i]->setDetailFromDistance( state, dist * invScale );
		}

		U32 n = mHexMap.width * mHexMap.height;
		for(U32 idx = 0; idx < n; idx++)
		{
			const HexMap::Hex& hex = mHexMap.hexArray[idx];

			if(hex.shapeNr == 0)
				continue;

			TSShapeInstance* shapeInstance = mDataBlock->renderShapeInstance[hex.shapeNr];
			if(!shapeInstance)
				continue;

			if(shapeInstance->getCurrentDetail() < 0)
				continue;

			// Set the world matrix to the hexagon's render transform
			MatrixF mat(true);
			mat.setPosition(mGrid->gridToWorld(mHexMap.indexToGrid(idx)));
			//mat.scale(scale);
			GFX->setWorldMatrix(mat);

			shapeInstance->render(rdata);		
		}
	}
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

	ColorI color(0, 0, 100);
	switch(mRebuild.state)
	{
		case RebuildProcess::CollisionStart:
		case RebuildProcess::CollisionProcess:
		case RebuildProcess::CollisionFinish:
			color.set(0, 255, 0); 
			break;
		case RebuildProcess::RenderStart: 
			color.set(100, 0, 0); 
			break;
		case RebuildProcess::RenderProcess: 
			color.set(255, 0, 0); 
			break;
		case RebuildProcess::RenderFinish: 
			color.set(255, 0, 255); 
			break;
	}

	drawer->drawCube(desc, box, color, &mRenderObjToWorld );
}


void HexagonVolume::deleteCollisionObjects()
{
#if 0
	for(U32 i = 0; i < mCollisionObjects.size(); i++)
		mCollisionObjects[i]->deleteObject();
	mCollisionObjects.clear();
#endif
}

void HexagonVolume::createCollisionObjects()
{
#if 0
	this->deleteCollisionObjects();
	for(U32 i = 0; i < mHexagons.size(); i++)
	{
		U32 shapeNr = mHexagons[i].shapeNr;
		if(!mDataBlock->collisionShapeData[shapeNr])
		{
			Con::errorf("HexagonVolume: Datablock is missing collisionShape %i", shapeNr);
			continue;
		}

		HexagonVolumeCollisionShape* obj  = new HexagonVolumeCollisionShape(this->isClientObject());
		obj->onNewDataBlock(mDataBlock->collisionShapeData[shapeNr], false);
		obj->setPosition(mGrid->gridToWorld(mHexagons[i].gridPos));
		if(!obj->registerObject())
		{
			Con::errorf("HexagonVolume: Creating collision object failed!");
			delete obj;
			obj = NULL;
		}
		else
		{
			mCollisionObjects.push_back(obj);						
		}
	}
#endif
}

bool HexagonVolume::startRebuild()
{
	if(!mHexMap.hexArray)
		return false;

	if(this->isServerObject())
	{
		mServerShapeRevision++;
		this->setMaskBits(RebuildMask);
	}

	mRebuild.state = RebuildProcess::CollisionStart;

	return true;
}

#ifdef TODO_OPTIMIZE_NET_UPDATE

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

void HexagonVolume::hexagonsToHexMap()
{
	this->clearHexMap();

	if(mHexagons.empty())
		return;

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
}

void HexagonVolume::hexMapToHexagons()
{
	U32 numHexagons = mHexMap.width * mHexMap.height;
	mHexagons.clear();
	mHexagons.reserve(numHexagons);
	for(U32 idx = 0; idx < numHexagons; idx++)
	{
		if(mHexMap.elevation[idx] == 0)
			continue;

		Point3I mapPos;
		mapPos.y = idx / mHexMap.width;
		mapPos.x = idx - (mapPos.y*mHexMap.width);
		mapPos.z = mHexMap.elevation[idx];

		Point3I gridPos;
		gridPos.x = mHexMap.originGridPos.x + mapPos.x;
		gridPos.y = mHexMap.originGridPos.y + mapPos.y;
		gridPos.z = mHexMap.originGridPos.z + mapPos.z - 1;

		Hexagon hex;
		hex.shapeNr = mHexMap.shapeNr[idx];
		hex.gridPos = gridPos; 

		mHexagons.push_back(hex);
	}
}
#endif

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

void HexagonVolume::rebuildMode2CollisionStart()
{
	mRebuild.idx = 0;
	mRebuild.state = RebuildProcess::CollisionProcess;
}

void HexagonVolume::rebuildMode2CollisionProcess()
{
	U32 idx = mRebuild.idx++;
	U32 numHexagons = mHexMap.width * mHexMap.height;
	if(idx >= numHexagons)
	{
		mRebuild.state = RebuildProcess::CollisionFinish;
		return;
	}

	Con::printf("%s %i: shape #%i elevation %i", 
		this->isGhost() ? "CLNT":"SRVR", 
		idx,
		mHexMap.hexArray[idx].shapeNr,
		mHexMap.hexArray[idx].elevation
	);

	//if(mHexMap.hexArray[idx].elevation == 0)
	//	return;
}

void HexagonVolume::rebuildMode2CollisionFinish()
{
	// Server doesn't need to rebuild render geometry.
	if(this->isServerObject())
		this->rebuildMode2Done();
	else
		mRebuild.state = RebuildProcess::RenderStart;
}

void HexagonVolume::rebuildMode2RenderStart()
{	
	if(mRebuild.shape)
		delete mRebuild.shape;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.idx = 0;

#if TODO
	// No geometry to rebuild?
	if(mHexagons.empty())
	{
		if(mShapeInstance)
			SAFE_DELETE(mShapeInstance);
		this->rebuildMode2Done();
		return;
	}
#endif

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
			this->rebuildMode2Done();
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

	mRebuild.shape = new TSShape();
	mRebuild.shape->revision = mServerShapeRevision;
	mRebuild.shape->createEmptyShape();
	mRebuild.shape->init();
	mRebuild.shape->materialList = new TSMaterialList(mDataBlock->renderShape[0]->materialList);

	mRebuild.state = RebuildProcess::RenderProcess;
}

void HexagonVolume::rebuildMode2RenderProcess()
{
	U32 idx = mRebuild.idx++;
	U32 numHexagons = mHexMap.width * mHexMap.height;
	if(idx >= numHexagons)
	{
		mRebuild.state = RebuildProcess::RenderFinish;
		return;
	}

	if(mHexMap.hexArray[idx].shapeNr == 0)
		return;

	//Con::printf("Have %ix%i map", mHexMap.width, mHexMap.height);

	U32 shapeNr = mHexMap.hexArray[idx].shapeNr;
	if(!mDataBlock->renderShape[shapeNr])
	{
		Con::errorf("HexagonVolume: Datablock is missing render shape %i", shapeNr);
		return;
	}

	const char* shapeNodeName = "mesh";
	const char* shapeMeshName = "mesh2";
	char newMeshName[256];
	dSprintf(newMeshName, sizeof(newMeshName), "hexmap%imesh2", idx);
	if(!mRebuild.shape->addMesh(mDataBlock->renderShape[shapeNr], shapeMeshName, newMeshName))
	{
		Con::errorf("HexagonVolume: Unable to add mesh %s", shapeMeshName);
		return;
	}

	Point3F adjustPos(0,0,0);
	S32 nodeIndex = mDataBlock->renderShape[shapeNr]->findNode(shapeNodeName);
	if(nodeIndex >= 0)
		adjustPos = mDataBlock->renderShape[shapeNr]->defaultTranslations[nodeIndex];

	Point3I gridPos = mHexMap.indexToGrid(idx);
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

void HexagonVolume::rebuildMode2RenderFinish()
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

	this->rebuildMode2Done();

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
}

void HexagonVolume::rebuildMode2Done()
{
	mRebuild.state = RebuildProcess::Ready;
	if(mRebuild.shape)
		delete mRebuild.shape;
	mRebuild.shape = NULL;
	mRebuild.mesh = NULL;
	mRebuild.idx = 0;
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

void HexagonVolume::processTick(const Move* move)
{
   Parent::processTick(move);

	if(!mGrid)
	{
		Vector<SceneObject*> grids;
		this->getContainer()->findObjectList(GridObjectType, &grids);
		if(grids.size() == 0)
			return;
		mGrid = (Grid*)grids[0];
	}

	if(this->isClientObject() && mClientStartRebuild)
	{
		mClientStartRebuild = false;
		this->startRebuild();
	}

	if(mRebuild.state == RebuildProcess::CollisionStart)
		this->rebuildMode2CollisionStart();
	else if(mRebuild.state == RebuildProcess::CollisionProcess)
		this->rebuildMode2CollisionProcess();
	else if(mRebuild.state == RebuildProcess::CollisionFinish)
		this->rebuildMode2CollisionFinish();
	else if(mRebuild.state == RebuildProcess::RenderStart)
		this->rebuildMode2RenderStart();
	else if(mRebuild.state == RebuildProcess::RenderProcess)
		this->rebuildMode2RenderProcess();
	else if(mRebuild.state == RebuildProcess::RenderFinish)
		this->rebuildMode2RenderFinish();
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

   if(stream->writeFlag(mask & InitMask))
   {
		mathWrite(*stream, mHexMap.originGridPos);
		stream->write(mHexMap.width);
		stream->write(mHexMap.height);
   }

   if(stream->writeFlag(mask & RebuildMask))
   {
		stream->write(mServerShapeRevision);
		U32 n = mHexMap.width*mHexMap.height;
		if(stream->writeFlag(n > 0))
		{
			for(U32 i = 0; i < n; i++)
			{
				const HexMap::Hex& hex = mHexMap.hexArray[i];
				if(stream->writeFlag(hex.shapeNr > 0))
				{
					stream->writeInt(hex.elevation, 4);
					stream->writeInt(hex.shapeNr, 2);
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

	// Init
	if(stream->readFlag())
	{
		mathRead(*stream, &mHexMap.originGridPos);
		stream->read(&mHexMap.width);
		stream->read(&mHexMap.height);

		if(mHexMap.hexArray)
		{
			delete[] mHexMap.hexArray;
			mHexMap.hexArray = NULL;
		}
		U32 n = mHexMap.width*mHexMap.height;
		if(n > 0)
		{
			mHexMap.hexArray = new HexMap::Hex[n];
			dMemset(mHexMap.hexArray, 0, n*sizeof(HexMap::Hex));
		}
	}

	// Rebuild
	if(stream->readFlag())
	{
		stream->read(&mServerShapeRevision);
		if(stream->readFlag())
		{
			U32 n = mHexMap.width*mHexMap.height;
			for(U32 i = 0; i < n; i++)
			{
				HexMap::Hex& hex = mHexMap.hexArray[i];
				if(stream->readFlag())
				{
					hex.elevation = stream->readInt(4);
					hex.shapeNr = stream->readInt(2);
				}
				else
				{
					hex.elevation = 0;
					hex.shapeNr = 0;
				}
			}
		}
		mClientStartRebuild = true;
	}
}

bool HexagonVolume::sInit()
{
	Vector<SceneObject*> grids;
	this->getContainer()->findObjectList(GridObjectType, &grids);
	if(grids.size() == 0)
	{
		Con::errorf("HexagonVolume: Init failed: No grid found!");
		return false;
	}

	mGrid = (Grid*)grids[0];

	Box3F worldBox = this->getWorldBox();
	Point3I minGridPos = mGrid->worldToGrid(worldBox.minExtents);
	Point3I maxGridPos = mGrid->worldToGrid(worldBox.maxExtents);

	mHexMap.originGridPos = minGridPos;
	mHexMap.width = maxGridPos.x - minGridPos.x + 1;
	mHexMap.height = maxGridPos.y - minGridPos.y + 1;

	if(mHexMap.hexArray)
	{
		delete[] mHexMap.hexArray;
		mHexMap.hexArray = NULL;
	}
	U32 n = mHexMap.width*mHexMap.height;
	if(n > 0)
	{
		mHexMap.hexArray = new HexMap::Hex[n];
		dMemset(mHexMap.hexArray, 0, n*sizeof(HexMap::Hex));
	}

	this->setMaskBits(InitMask);

	return true;
}

bool HexagonVolume::sAddHexagon(Point3I gridPos, U32 shapeNr)
{
	if(!mHexMap.hexArray)
	{
		Con::errorf("HexagonVolume: addHexagon(): No hex map!");
		return false;
	}

	Point3F worldPos = mGrid->gridToWorld(gridPos);
	if(!this->getWorldBox().isContained(worldPos))
		return false;

	S32 idx = mHexMap.gridToIndex(gridPos);
	if(idx < 0)
		return false;
	if(idx >= mHexMap.width*mHexMap.height)
		return false;

	HexMap::Hex& hex = mHexMap.hexArray[idx];
	if(hex.serverGridPos == gridPos && hex.shapeNr == shapeNr)
		return false;

	hex.serverGridPos = gridPos;
	hex.shapeNr = shapeNr;
	hex.elevation = gridPos.z - mHexMap.originGridPos.z;

	return true;
}

bool HexagonVolume::sRemoveHexagon(Point3I gridPos)
{
	if(!mHexMap.hexArray)
	{
		Con::errorf("HexagonVolume: addHexagon(): No hex map!");
		return false;
	}

	Point3F worldPos = mGrid->gridToWorld(gridPos);
	if(!this->getWorldBox().isContained(worldPos))
		return false;

	S32 idx = mHexMap.gridToIndex(gridPos);
	if(idx < 0)
		return false;
	if(idx >= mHexMap.width*mHexMap.height)
		return false;

	HexMap::Hex& hex = mHexMap.hexArray[idx];
	if(hex.shapeNr > 0)
		return false;

	hex.shapeNr = 0;

	return true;
}

bool HexagonVolume::sRebuild()
{
	if(!mHexMap.hexArray)
		return false;

	return this->startRebuild();
}

//--------------------------------------------------------------------------

DefineEngineMethod(HexagonVolume, init, bool, (),,
   "@brief Initialize volume.\n\n"
)
{
   return object->sInit();
}

DefineEngineMethod(HexagonVolume, addHexagon, bool, (Point3I gridPos, U32 shapeNr),,
   "@brief Add a hexagon to the volume.\n\n"

   "@param Grid position of the new hexagon\n"
	"@param Shape number of the hexagon\n"
)
{
   return object->sAddHexagon(gridPos, shapeNr);
}

DefineEngineMethod(HexagonVolume, removeHexagon, bool, (Point3I pos),,
   "@brief Add a hexagon to the volume.\n\n"

   "@param Position of the new hexagon\n"
)
{
   return object->sRemoveHexagon(pos);
}

DefineEngineMethod(HexagonVolume, rebuild, bool, (),,
   "@brief Rebuild render geometry.\n\n"
)
{
   return object->sRebuild();
}
