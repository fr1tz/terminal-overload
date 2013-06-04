// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/sceneSpace.h"

#include "core/stream/bitStream.h"
#include "console/engineAPI.h"
#include "math/mathIO.h"
#include "math/mOrientedBox.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/gfxTransformSaver.h"
#include "renderInstance/renderPassManager.h"
#include "materials/materialDefinition.h"
#include "materials/baseMatInstance.h"
#include "scene/sceneRenderState.h"


extern bool gEditingMission;


//-----------------------------------------------------------------------------

SceneSpace::SceneSpace()
   : mEditorRenderMaterial( NULL )
{
   mNetFlags.set( Ghostable | ScopeAlways );
   mTypeMask |= StaticObjectType;

   // Except when their rendering is otherwise suppressed, we do not want
   // spaces to get culled away when in the editor.
   mObjectFlags |= DisableCullingInEditorFlag;
}

//-----------------------------------------------------------------------------

SceneSpace::~SceneSpace()
{
   SAFE_DELETE( mEditorRenderMaterial );
}

//-----------------------------------------------------------------------------

bool SceneSpace::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   addToScene();
   return true;
}

//-----------------------------------------------------------------------------

void SceneSpace::onRemove()
{
   removeFromScene();
   Parent::onRemove();
}

//-----------------------------------------------------------------------------

void SceneSpace::setTransform(const MatrixF & mat)
{  
   Parent::setTransform( mat );

   if( isServerObject() )
      setMaskBits( TransformMask );
}

//-----------------------------------------------------------------------------

void SceneSpace::onEditorEnable()
{
   // If we haven't created a material for editor rendering yet,
   // try so now.

   if( isClientObject() && !mEditorRenderMaterial )
      mEditorRenderMaterial = _createEditorRenderMaterial();
}

//-----------------------------------------------------------------------------

void SceneSpace::onEditorDisable()
{
   SAFE_DELETE( mEditorRenderMaterial );
}

//-----------------------------------------------------------------------------

BaseMatInstance* SceneSpace::_createEditorRenderMaterial()
{
   String materialName = String::ToString( "Editor%sMaterial", getClassName() );
   
   Material* material;
   if( !Sim::findObject( materialName, material ) )
      return NULL;

   return material->createMatInstance();
}

//-----------------------------------------------------------------------------

void SceneSpace::prepRenderImage( SceneRenderState* state )
{
   if( !gEditingMission )
      return;

   if( !state->isDiffusePass() )
      return;

   ObjectRenderInst* ri = state->getRenderPass()->allocInst< ObjectRenderInst >();
   ri->renderDelegate.bind( this, &SceneSpace::_renderObject );
   ri->type = RenderPassManager::RIT_Editor;
   ri->defaultKey = 0;
   ri->defaultKey2 = 0;
   state->getRenderPass()->addInst( ri );
}

//-----------------------------------------------------------------------------

void SceneSpace::_renderObject( ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat )
{
   if( overrideMat )
      return;

   if( !mEditorRenderMaterial )
   {
      // We have no material for rendering so just render
      // a plain box.

      GFXTransformSaver saver;

      MatrixF mat = getRenderTransform();
      mat.scale( getScale() );

      GFX->multWorld( mat );

      GFXStateBlockDesc desc;
      desc.setZReadWrite( true, false );
      desc.setBlend( true );
      desc.setCullMode( GFXCullNone );

      GFXDrawUtil *drawer = GFX->getDrawUtil();
      drawer->drawCube( desc, mObjBox, _getDefaultEditorSolidColor() );

      // Render black wireframe.

      desc.setFillModeWireframe();
      drawer->drawCube( desc, mObjBox, _getDefaultEditorWireframeColor() );
   }
   else
   {
      //RDTODO
   }
}

//-----------------------------------------------------------------------------

U32 SceneSpace::packUpdate( NetConnection* connection, U32 mask, BitStream* stream )
{
   U32 retMask = Parent::packUpdate( connection, mask, stream );

   if( stream->writeFlag( mask & TransformMask ) ) 
   {
      mathWrite( *stream, mObjToWorld );
      mathWrite( *stream, mObjScale );
   }

   return retMask;
}

//-----------------------------------------------------------------------------

void SceneSpace::unpackUpdate( NetConnection* connection, BitStream* stream )
{
   Parent::unpackUpdate( connection, stream );

   if( stream->readFlag() )  // TransformMask
   {
      mathRead( *stream, &mObjToWorld );
      mathRead( *stream, &mObjScale );

      setTransform( mObjToWorld );
   }
}
