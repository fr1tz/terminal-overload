// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hexagonVolume.h"

#include "platform/platform.h"
#include "collision/boxConvex.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "core/stream/bitStream.h"
#include "core/fileObject.h"
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
   mode = 0;
	objectMask = StaticShapeObjectType;
}

bool HexagonVolumeData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
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

	mGeometryDirty = false;
	mGeometryDirtyTicks = 0;
	mServerObjectCount = 0;
   mDataBlock = NULL;
	mShape = NULL;
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
      scriptOnAdd();
      
   return true;
}

void HexagonVolume::onRemove()
{
   removeFromScene();
   Parent::onRemove();
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
	GameBase* shape = dynamic_cast<ShapeBase*>(obj);
   if(shape)
   {
      for(U32 i = 0; i < mObjects.size(); i++)
      {
         if (shape == mObjects[i] )
         {
            mObjects.erase(i);
            break;
         }
      }
   }

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
   for(U32 i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->prepRenderImage(state);
   }
}

void HexagonVolume::prepRenderImageMode1(SceneRenderState* state)
{
   if(mObjects.size() == 0)
      return;

	TSShapeInstance* shapeInstance = mObjects[0]->getShapeInstance();
	if(!shapeInstance)
		return;

   // Calculate the distance of this object from the camera
   Point3F cameraOffset;
   getRenderTransform().getColumn( 3, &cameraOffset );
   cameraOffset -= state->getDiffuseCameraPosition();
   F32 dist = cameraOffset.len();
   if ( dist < 0.01f )
      dist = 0.01f;

   // Set up the LOD for the shape
	VectorF scale = mObjects[0]->getScale();
   F32 invScale = ( 1.0f / getMax( getMax(scale.x, scale.y), scale.z ) );

   shapeInstance->setDetailFromDistance( state, dist * invScale );

   // Make sure we have a valid level of detail
   if (shapeInstance->getCurrentDetail() < 0 )
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

   for (U32 i = 0; i < mObjects.size(); i++)
	{
		// Set the world matrix to the objects render transform
		MatrixF mat = mObjects[i]->getRenderTransform();
		mat.scale(scale);
		GFX->setWorldMatrix(mat);

		// Animate the the shape
		shapeInstance->animate();

		// Allow the shape to submit the RenderInst(s) for itself
		shapeInstance->render(rdata);		
   }
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

void HexagonVolume::rebuild()
{
	if(!mDataBlock)
		return;

	Point3F scale = this->getScale();
	Box3F box = this->getObjBox();
	box.minExtents.convolve(scale);
	box.maxExtents.convolve(scale);
	MatrixF mat = this->getTransform();
	mat.mul(box);

	if(isServerObject())
	{
		if(mDataBlock->mode < 2)
			return;
		mServerObjectCount = this->getContainer()->countObjectsStrict(
			box,
			(smBaseObjectMask | mDataBlock->objectMask)
		);
		this->setMaskBits(RebuildMask);
	}
	else
	{
		U32 objectCount = this->getContainer()->countObjectsStrict(
			box,
			(smBaseObjectMask | mDataBlock->objectMask)
		);
		Con::printf("HexagonVolume %i: Have %i ghosts, need %i", 
			this->getId(), objectCount, mServerObjectCount);
		if(objectCount != mServerObjectCount)
			return; // Ghosts are missing

		if(mDataBlock->mode == 2)
			this->rebuildMode2();
		else if(mDataBlock->mode == 3)
			this->rebuildMode3();

		mGeometryDirty = false;
		mGeometryDirtyTicks = 0;
	}
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

void HexagonVolume::rebuildMode2()
{
	Point3F scale = this->getScale();
	Box3F box = this->getObjBox();
	box.minExtents.convolve(scale);
	box.maxExtents.convolve(scale);
	MatrixF mat = this->getTransform();
	mat.mul(box);

	mObjects.clear();
	this->getContainer()->findObjects(
		box,
		mDataBlock->objectMask,
		findCallback,
		this
	);

   char newMeshName[256];
	if(mObjects.size() == 0)
		return;
	if(mShape) SAFE_DELETE(mShape);
	mShape = new TSShape();
	mShape->createEmptyShape();
	for(int i = 0; i < mObjects.size(); i++)
	{
		if(mObjects[i]->getShape())
		{
			mShape->materialList = new TSMaterialList(mObjects[i]->getShape()->materialList);
			break;
		}
		return;
	}
	mShape->init();
	TSMesh* mesh = NULL;
	TSShape::smTSAlloc.setWrite();
	//Con::printf("Have %i objects", mObjects.size());
	int numMeshes = 0;
	for(int i = 0; i < mObjects.size(); i++)
	{
		ShapeBase* object = mObjects[i];
		dSprintf(newMeshName, sizeof(newMeshName), "Object%iMesh2", i);
		if(mShape->addMesh(object->getShape(), "Mesh2", newMeshName))
		{
			Point3F pos = object->getPosition() - this->getPosition();
			S32 nodeIndex = object->getShape()->findNode("Mesh");
			if(nodeIndex >= 0)
				pos += object->getShape()->defaultTranslations[nodeIndex];

			if(mesh == NULL)
			{
				//Con::printf("Added initial mesh %s", newMeshName);
				mesh = mShape->findMesh(newMeshName);
				if(mesh)
				{
					mesh->disassemble();
					rebuildMode2MoveMeshVerts(mesh, pos);
					numMeshes++;
				}
				else
				{
					//Con::errorf("Unable to find mesh %s", newMeshName);
				}
			}
			else
			{
				//Con::printf("Added temporary mesh %s", newMeshName);
				TSMesh* tmp = mShape->findMesh(newMeshName);
				if(tmp)
				{
					tmp->disassemble();
					rebuildMode2MoveMeshVerts(tmp, pos);
					rebuildMode2MergeMesh(mesh, tmp);
					mShape->removeMesh(newMeshName);
					//Con::printf("Merged and removed temporary mesh %s", newMeshName);
					numMeshes++;
				}
				else
				{
					//Con::errorf("Unable to find mesh %s", newMeshName);
				}
			}
		}
	}
	//Con::printf("Added %i meshes", numMeshes);
	if(mesh)
	{
		mesh->mVertexData.setReady(false);
		mesh->disassemble();
		mesh->computeBounds();
		mesh->createTangents(mesh->verts, mesh->norms);
		mesh->convertToAlignedMeshData();
	}
	mShape->updateSmallestVisibleDL();
	mShape->init();

	if(mShapeInstance)
		SAFE_DELETE(mShapeInstance);
	mShapeInstance = new TSShapeInstance(mShape, this->isClientObject());
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
	mShape->write(&stream);
	stream.close();
#endif
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

void HexagonVolume::findCallback(SceneObject* obj, void* key)
{
   HexagonVolume* volume = reinterpret_cast<HexagonVolume*>(key);
	U32 volumeMask = smBaseObjectMask | volume->mDataBlock->objectMask;
   U32 objectMask = obj->getTypeMask();

   if((objectMask & volumeMask) == volumeMask)
	{
      ShapeBase* shape = static_cast<ShapeBase*>(obj);
		volume->mObjects.push_back(shape);
		volume->deleteNotify(shape);
   }
}

//--------------------------------------------------------------------------

bool HexagonVolume::clientRebuildCheck()
{
	if(mGeometryDirtyTicks <= 1)
		return true;

	return ((mGeometryDirtyTicks % 10) == 0); 

	if(this->getSceneManager() != NULL)
	{
		GameConnection* conn = GameConnection::getConnectionToServer();
		if(!conn)
			return false;

		MatrixF cameraMatrix;
		if(!conn->getControlCameraTransform(0, &cameraMatrix))
			return false;

		F32 visDist = this->getSceneManager()->getVisibleDistance();
		Point3F cameraPos = cameraMatrix.getPosition();

		//------------------------------------------------------------------
		// Note: This is the same algorithm used in _scopeCallback()
		//       in sceneManager.cpp to check if an object is in scope.
		// {
		F32 difSq = (this->getWorldSphere().center - cameraPos).lenSquared();
		if(difSq < visDist*visDist)
		{
			// Not even close, it's in...
			return true;
		}
		else
		{
			// Check a little more closely...
			F32 realDif = mSqrt(difSq);
			if(realDif - this->getWorldSphere().radius < visDist)
				return true;
			else
				return false;
		}
		// }
		//------------------------------------------------------------------
	}

	// Fallback: Try to rebuild every 10th tick.
	return ((mGeometryDirtyTicks % 10) == 0); 
}

//--------------------------------------------------------------------------

void HexagonVolume::processTick(const Move* move)
{
   Parent::processTick(move);

	if(this->isServerObject())
		return;

	if(mGeometryDirty)
	{
		mGeometryDirtyTicks++;
		if(mServerObjectCount == 0)
		{
			if(mShapeInstance)
			{
				delete mShapeInstance;
				mShapeInstance = NULL;
			}
			if(mShape)
			{
				delete mShape;
				mShape = NULL;
			}
			mGeometryDirty = false;
			mGeometryDirtyTicks = 0;
		}
		else
		{
			if(this->clientRebuildCheck())
				this->rebuild();
		}
	}
}

//--------------------------------------------------------------------------

U32 HexagonVolume::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);

   if(stream->writeFlag(mask & TransformMask))
   {
      stream->writeAffineTransform(mObjToWorld);
   }

   if(stream->writeFlag(mask & RebuildMask))
   {
		stream->write(mServerObjectCount);
   }

   return retMask;
}

void HexagonVolume::unpackUpdate(NetConnection* con, BitStream* stream)
{
   Parent::unpackUpdate(con, stream);

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
		stream->read(&mServerObjectCount);
		mGeometryDirty = true;
		mGeometryDirtyTicks = 0;
	}
}

//--------------------------------------------------------------------------

DefineEngineMethod(HexagonVolume, rebuild, void, (),,
   "@brief Rebuild render geometry.\n\n"
)
{
   object->rebuild();
}