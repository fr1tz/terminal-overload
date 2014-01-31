// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _METASHAPERENDERER_H_
#define _METASHAPERENDERER_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _CONCRETEPOLYLIST_H_
#include "collision/concretePolyList.h"
#endif

class BaseMatInstance;

class MetaShapeRenderer : public SceneObject
{
   typedef SceneObject Parent;

   enum MaskBits 
   {
      TransformMask = Parent::NextFreeMask << 0,
      NextFreeMask  = Parent::NextFreeMask << 1
   };

   //--------------------------------------------------------------------------
   // Rendering variables
   //--------------------------------------------------------------------------
   // Define our vertex format here so we don't have to
   // change it in multiple spots later
   typedef GFXVertexPCN VertexType;

   // The handles for our StateBlocks
   GFXStateBlockRef mNormalSB;
   GFXStateBlockRef mReflectSB;

   // The GFX vertex and primitive buffers
   GFXVertexBufferHandle< VertexType > mVertexBuffer;

	ConcretePolyList mPolyList;
	bool mUpdatePolyList;

public:
   MetaShapeRenderer();
   virtual ~MetaShapeRenderer();

   // Declare this object as a ConsoleObject so that we can
   // instantiate it into the world and network it
   DECLARE_CONOBJECT(MetaShapeRenderer);

   //--------------------------------------------------------------------------
   // Object Editing
   // Since there is always a server and a client object in Torque and we
   // actually edit the server object we need to implement some basic
   // networking functions
   //--------------------------------------------------------------------------
   // Set up any fields that we want to be editable (like position)
   static void initPersistFields();

   // Handle when we are added to the scene and removed from the scene
   bool onAdd();
   void onRemove();

   // Override this so that we can dirty the network flag when it is called
   void setTransform( const MatrixF &mat );

   // This function handles sending the relevant data from the server
   // object to the client object
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   // This function handles receiving relevant data from the server
   // object and applying it to the client object
   void unpackUpdate( NetConnection *conn, BitStream *stream );

   //--------------------------------------------------------------------------
   // Object Rendering
   // Torque utilizes a "batch" rendering system. This means that it builds a
   // list of objects that need to render (via RenderInst's) and then renders
   // them all in one batch. This allows it to optimized on things like
   // minimizing texture, state, and shader switching by grouping objects that
   // use the same Materials. For this example, however, we are just going to
   // get this object added to the list of objects that handle their own
   // rendering.
   //--------------------------------------------------------------------------
   // Create the geometry for rendering
   void createGeometry();

   // This is the function that allows this object to submit itself for rendering
   void prepRenderImage( SceneRenderState *state );

   // This is the function that actually gets called to do the rendering
   // Note that there is no longer a predefined name for this function.
   // Instead, when we submit our ObjectRenderInst in prepRenderImage(),
   // we bind this function as our rendering delegate function
   void render( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat );
};

#endif // _METASHAPERENDERER_H_