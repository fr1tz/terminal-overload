// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "Alux3D/shapeRenderVolume.h"

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
#include "T3D/physics/physicsPlugin.h"
#include "T3D/physics/physicsBody.h"
#include "T3D/physics/physicsCollision.h"

bool ShapeRenderVolume::smRenderBounds = false;

// All the objects we care about must be
// derived from ShapeBase and be static!
U32 ShapeRenderVolume::smBaseObjectMask = (ShapeBaseObjectType | StaticObjectType);

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(ShapeRenderVolumeData);

ConsoleDocClass( ShapeRenderVolumeData,
   "@brief Defines shared properties for ShapeRenderVolume objects.\n\n"

   "TODO\n"

   "@see ShapeRenderVolume.\n"
   "@ingroup gameObjects\n"
   "@ingroup Datablocks\n"
);

ShapeRenderVolumeData::ShapeRenderVolumeData()
{
   mode = 0;
	objectMask = StaticShapeObjectType;
}

bool ShapeRenderVolumeData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void ShapeRenderVolumeData::initPersistFields()
{
   addGroup("Operation");

      addField("mode", TypeS32, Offset(mode, ShapeRenderVolumeData),
         "@brief How the render volume operates.\n\n"
         "Mode 0: Call prepRenderImage() method for each object.\n"
			"Mode 1: Grab each object's TSShape and render it.\n"
			"Mode 2: Build single TSShape from objects' TSShapes.\n"
			"Mode 3: Render collision geometry within volume.\n"
		);

		addField( "objectMask", TypeS32, Offset(objectMask, ShapeRenderVolumeData),
			"@brief What kind of objects this volume should render.\n\n"
		);

   endGroup("Operation");

   Parent::initPersistFields();
}


//--------------------------------------------------------------------------
void ShapeRenderVolumeData::packData(BitStream* stream)
{
   Parent::packData(stream);
   stream->write(mode);
	stream->write(objectMask);
}

void ShapeRenderVolumeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   stream->read(&mode);
	stream->read(&objectMask);
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(ShapeRenderVolume);

ConsoleDocClass( ShapeRenderVolume,
   "@brief TODO \n\n"
	"TODO\n"
   "@see ShapeRenderVolumeData\n"
   "@ingroup gameObjects\n"
);

ShapeRenderVolume::ShapeRenderVolume()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   mTypeMask |= StaticShapeObjectType;

   mObjScale.set(1, 1, 1);
   mObjToWorld.identity();
   mWorldToObj.identity();

	mGeometryDirty = false;
	mServerObjectCount = 0;
   mDataBlock = NULL;
	mShape = NULL;
	mShapeInstance = NULL;
}

ShapeRenderVolume::~ShapeRenderVolume()
{

}

//-----------------------------------------------------------------------------
void ShapeRenderVolume::consoleInit()
{
   Con::addVariable( "$ShapeRenderVolume::renderBounds", TypeBool, &smRenderBounds,
      "@brief Makes ShapeRenderVolumes render their bounds.\n\n"
      "Used by the Tools and debug render modes.\n"
      "@ingroup gameObjects" );
}

void ShapeRenderVolume::initPersistFields()
{
   Parent::initPersistFields();
}

//--------------------------------------------------------------------------

bool ShapeRenderVolume::onAdd()
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

void ShapeRenderVolume::onRemove()
{
   removeFromScene();
   Parent::onRemove();
}

bool ShapeRenderVolume::onNewDataBlock( GameBaseData *dptr, bool reload )
{
   mDataBlock = dynamic_cast<ShapeRenderVolumeData*>( dptr );
   if ( !mDataBlock || !Parent::onNewDataBlock( dptr, reload ) )
      return false;

   scriptOnNewDataBlock();
   return true;
}

void ShapeRenderVolume::onDeleteNotify( SimObject *obj )
{
	GameBase* shape = dynamic_cast<ShapeBase*>(obj);
   if(shape)
   {
      for(U32 i = 0; i < mObjects.size(); i++)
      {
         if (shape == mObjects[i] )
         {
            mObjects.erase(i);
				mGeometryDirty = true;
            break;
         }
      }
   }

   Parent::onDeleteNotify( obj );
}

void ShapeRenderVolume::inspectPostApply()
{
   Parent::inspectPostApply();
}

//------------------------------------------------------------------------------

void ShapeRenderVolume::setTransform(const MatrixF & mat)
{
   Parent::setTransform(mat);

   if (isServerObject()) {
      MatrixF base(true);
      base.scale(Point3F(1.0/mObjScale.x,
                         1.0/mObjScale.y,
                         1.0/mObjScale.z));
      base.mul(mWorldToObj);
      setMaskBits(TransformMask | ScaleMask);
		this->rebuild();
   }
}

void ShapeRenderVolume::prepRenderImage(SceneRenderState* state)
{
	if(smRenderBounds || isSelected())
	{
		ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
		ri->renderDelegate.bind(this, &ShapeRenderVolume::renderObjectBounds);
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

void ShapeRenderVolume::prepRenderImageMode0(SceneRenderState* state)
{
   for(U32 i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->prepRenderImage(state);
   }
}

void ShapeRenderVolume::prepRenderImageMode1(SceneRenderState* state)
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

void ShapeRenderVolume::prepRenderImageMode2(SceneRenderState* state)
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

void ShapeRenderVolume::prepRenderImageMode3(SceneRenderState* state)
{
   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &ShapeRenderVolume::renderObjectMode3);
   ri->type = RenderPassManager::RIT_Editor;      
   ri->translucentSort = true;
   ri->defaultKey = 1;
   state->getRenderPass()->addInst(ri);
}

void ShapeRenderVolume::renderObjectMode3(ObjectRenderInst* ri,
	SceneRenderState* state, BaseMatInstance* overrideMat)
{
   if(overrideMat)
      return;

	mPolyList.render();

	if(!smRenderBounds && !isSelected())
		return;
}

void ShapeRenderVolume::renderObjectBounds(ObjectRenderInst*  ri,
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

void ShapeRenderVolume::rebuild()
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
		mServerObjectCount = this->getContainer()->countObjects(
			box,
			(smBaseObjectMask | mDataBlock->objectMask)
		);
		this->setMaskBits(RebuildMask);
	}
	else
	{
		U32 objectCount = this->getContainer()->countObjects(
			box,
			(smBaseObjectMask | mDataBlock->objectMask)
		);
		Con::printf("Have %i need %i", objectCount, mServerObjectCount);
		if(objectCount != mServerObjectCount)
			return; // Ghosts are missing

		if(mDataBlock->mode == 2)
			this->rebuildMode2();
		else if(mDataBlock->mode == 3)
			this->rebuildMode3();

		mGeometryDirty = false;
	}
}

void ShapeRenderVolume::rebuildMode2MoveMeshVerts(TSMesh* mesh, Point3F vec)
{
	// Note: Mesh must be disassembled!
	for(int i = 0; i < mesh->verts.size(); i++)
		mesh->verts[i] += vec;
}

void ShapeRenderVolume::rebuildMode2MergeMesh(TSMesh* dest, TSMesh* src)
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

void ShapeRenderVolume::rebuildMode2()
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
      Con::errorf("ShapeRenderVolume::rebuildShape() - Could not open file");
      return;
   }
	mShape->write(&stream);
	stream.close();
#endif
}

void ShapeRenderVolume::rebuildMode3()
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

void ShapeRenderVolume::findCallback(SceneObject* obj, void* key)
{
   ShapeRenderVolume* volume = reinterpret_cast<ShapeRenderVolume*>(key);
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

void ShapeRenderVolume::processTick(const Move* move)
{
   Parent::processTick(move);

	if(this->isServerObject())
		return;

	if(mGeometryDirty)
		this->rebuild();
}

//--------------------------------------------------------------------------

U32 ShapeRenderVolume::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
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

void ShapeRenderVolume::unpackUpdate(NetConnection* con, BitStream* stream)
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
	}
}
