// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "Alux3D/metaShapeRenderer.h"

#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "core/stream/bitStream.h"
#include "materials/sceneData.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "renderInstance/renderPassManager.h"

IMPLEMENT_CO_NETOBJECT_V1(MetaShapeRenderer);

ConsoleDocClass( MetaShapeRenderer, 
   "@brief Scene object that renders the MetaShape objects within its bounds.\n\n"
   "TODO" );

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
MetaShapeRenderer::MetaShapeRenderer()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set( Ghostable | ScopeAlways );

   // Set it as a "static" object
   mTypeMask |= StaticObjectType | StaticShapeObjectType;

	mUpdatePolyList = true;
}

MetaShapeRenderer::~MetaShapeRenderer()
{
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void MetaShapeRenderer::initPersistFields()
{
   // SceneObject already handles exposing the transform
   Parent::initPersistFields();
}

bool MetaShapeRenderer::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   // Set up a 1x1x1 bounding box
   mObjBox.set( Point3F( -0.5f, -0.5f, -0.5f ),
                Point3F(  0.5f,  0.5f,  0.5f ) );

   resetWorldBox();

   // Add this object to the scene
   addToScene();

   return true;
}

void MetaShapeRenderer::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void MetaShapeRenderer::setTransform(const MatrixF & mat)
{
   // Let SceneObject handle all of the matrix manipulation
   Parent::setTransform( mat );

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits( TransformMask );
}

U32 MetaShapeRenderer::packUpdate( NetConnection *conn, U32 mask, BitStream *stream )
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate( conn, mask, stream );

   // Write our transform information
   if ( stream->writeFlag( mask & TransformMask ) )
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
   }

   return retMask;
}

void MetaShapeRenderer::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if ( stream->readFlag() )  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform( mObjToWorld );

		mUpdatePolyList = true;
   }
}

//-----------------------------------------------------------------------------
// Object Rendering
//-----------------------------------------------------------------------------
void MetaShapeRenderer::createGeometry()
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
		ShapeBaseObjectType,
		&mPolyList
	);

	mUpdatePolyList = false;

   static const Point3F cubePoints[8] = 
   {
      Point3F( 1.0f, -1.0f, -1.0f), Point3F( 1.0f, -1.0f,  1.0f),
      Point3F( 1.0f,  1.0f, -1.0f), Point3F( 1.0f,  1.0f,  1.0f),
      Point3F(-1.0f, -1.0f, -1.0f), Point3F(-1.0f,  1.0f, -1.0f),
      Point3F(-1.0f, -1.0f,  1.0f), Point3F(-1.0f,  1.0f,  1.0f)
   };

   static const Point3F cubeNormals[6] = 
   {
      Point3F( 1.0f,  0.0f,  0.0f), Point3F(-1.0f,  0.0f,  0.0f),
      Point3F( 0.0f,  1.0f,  0.0f), Point3F( 0.0f, -1.0f,  0.0f),
      Point3F( 0.0f,  0.0f,  1.0f), Point3F( 0.0f,  0.0f, -1.0f)
   };

   static const ColorI cubeColors[3] = 
   {
      ColorI( 0, 0, 100, 100),
      ColorI( 0, 0, 100, 100),
      ColorI( 0, 0, 100, 100)
   };

   static const U32 cubeFaces[36][3] = 
   {
      { 3, 0, 0 }, { 0, 0, 0 }, { 1, 0, 0 },
      { 2, 0, 0 }, { 0, 0, 0 }, { 3, 0, 0 },
      { 7, 1, 0 }, { 4, 1, 0 }, { 5, 1, 0 },
      { 6, 1, 0 }, { 4, 1, 0 }, { 7, 1, 0 },
      { 3, 2, 1 }, { 5, 2, 1 }, { 2, 2, 1 },
      { 7, 2, 1 }, { 5, 2, 1 }, { 3, 2, 1 },
      { 1, 3, 1 }, { 4, 3, 1 }, { 6, 3, 1 },
      { 0, 3, 1 }, { 4, 3, 1 }, { 1, 3, 1 },
      { 3, 4, 2 }, { 6, 4, 2 }, { 7, 4, 2 },
      { 1, 4, 2 }, { 6, 4, 2 }, { 3, 4, 2 },
      { 2, 5, 2 }, { 4, 5, 2 }, { 0, 5, 2 },
      { 5, 5, 2 }, { 4, 5, 2 }, { 2, 5, 2 }
   };

   // Fill the vertex buffer
   VertexType *pVert = NULL;

   mVertexBuffer.set( GFX, 36, GFXBufferTypeStatic );
   pVert = mVertexBuffer.lock();

   Point3F halfSize = getObjBox().getExtents() * 0.5f;

   for (U32 i = 0; i < 36; i++)
   {
      const U32& vdx = cubeFaces[i][0];
      const U32& ndx = cubeFaces[i][1];
      const U32& cdx = cubeFaces[i][2];

      pVert[i].point  = cubePoints[vdx] * halfSize;
      pVert[i].normal = cubeNormals[ndx];
      pVert[i].color  = cubeColors[cdx];
   }

   mVertexBuffer.unlock();

   // Set up our normal and reflection StateBlocks
   GFXStateBlockDesc desc;

   // The normal StateBlock only needs a default StateBlock
   mNormalSB = GFX->createStateBlock( desc );

   // The reflection needs its culling reversed
   desc.cullDefined = true;
   desc.cullMode = GFXCullCW;
   mReflectSB = GFX->createStateBlock( desc );
}

void MetaShapeRenderer::prepRenderImage( SceneRenderState *state )
{
   // Do a little prep work if needed
   if ( mVertexBuffer.isNull() )
      createGeometry();

	if(mUpdatePolyList)
		this->createGeometry();

   // Allocate an ObjectRenderInst so that we can submit it to the RenderPassManager
   ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();

   // Now bind our rendering function so that it will get called
   ri->renderDelegate.bind( this, &MetaShapeRenderer::render );

   // Set our RenderInst as a standard object render
   ri->type = RenderPassManager::RIT_Object;

   // Set our sorting keys to a default value
   ri->defaultKey = 0;
   ri->defaultKey2 = 0;

   // Submit our RenderInst to the RenderPassManager
   state->getRenderPass()->addInst( ri );
}

void MetaShapeRenderer::render( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat )
{
   if ( overrideMat )
      return;

	PROFILE_SCOPE(MetaShapeRenderer_Render);

	mPolyList.render();

   if ( mVertexBuffer.isNull() )
      return;

   // Set up a GFX debug event (this helps with debugging rendering events in external tools)
   GFXDEBUGEVENT_SCOPE( MetaShapeRenderer_Render, ColorI::RED );

   // GFXTransformSaver is a handy helper class that restores
   // the current GFX matrices to their original values when
   // it goes out of scope at the end of the function
   GFXTransformSaver saver;

   // Calculate our object to world transform matrix
   MatrixF objectToWorld = getRenderTransform();
   objectToWorld.scale( getScale() );

   // Apply our object transform
   GFX->multWorld( objectToWorld );

   // Deal with reflect pass otherwise
   // set the normal StateBlock
   if ( state->isReflectPass() )
      GFX->setStateBlock( mReflectSB );
   else
      GFX->setStateBlock( mNormalSB );

   // Set up the "generic" shaders
   // These handle rendering on GFX layers that don't support
   // fixed function. Otherwise they disable shaders.
   GFX->setupGenericShaders( GFXDevice::GSModColorTexture );

   // Set the vertex buffer
   GFX->setVertexBuffer( mVertexBuffer );

   // Draw our triangles
   GFX->drawPrimitive( GFXTriangleList, 0, 12 );
}