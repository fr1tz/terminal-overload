// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/controls/guiMaterialCtrl.h"

#include "materials/baseMatInstance.h"
#include "materials/materialManager.h"
#include "materials/sceneData.h"
#include "core/util/safeDelete.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDevice.h"
#include "math/util/matrixSet.h"
#include "scene/sceneRenderState.h"

IMPLEMENT_CONOBJECT( GuiMaterialCtrl );

ConsoleDocClass( GuiMaterialCtrl,
   "@brief Container for GuiMaterialPreview\n\n"
   "Editor use only.\n\n"
   "@internal"
);

GuiMaterialCtrl::GuiMaterialCtrl()
   : mMaterialInst( NULL )
{
}

void GuiMaterialCtrl::initPersistFields()
{
   addGroup( "Material" );
   addProtectedField( "materialName", TypeStringFilename, Offset( mMaterialName, GuiMaterialCtrl ), &GuiMaterialCtrl::_setMaterial, &defaultProtectedGetFn, "" );
   endGroup( "Material" );

   Parent::initPersistFields();
}

bool GuiMaterialCtrl::onWake()
{
   if ( !Parent::onWake() )
      return false;

   setActive( true );
   setMaterial( mMaterialName );

   return true;
}

void GuiMaterialCtrl::onSleep()
{
   SAFE_DELETE( mMaterialInst );

   Parent::onSleep();
}

bool GuiMaterialCtrl::_setMaterial( void *object, const char *index, const char *data )
{
   static_cast<GuiMaterialCtrl *>( object )->setMaterial( data );

   // Return false to keep the caller from setting the field.
   return false;
}

bool GuiMaterialCtrl::setMaterial( const String &materialName )
{
   SAFE_DELETE( mMaterialInst );
   mMaterialName = materialName;

   if ( mMaterialName.isNotEmpty() && isAwake() )
      mMaterialInst = MATMGR->createMatInstance( mMaterialName, getGFXVertexFormat<GFXVertexPCT>() );

   return true;
}

void GuiMaterialCtrl::inspectPostApply()
{
   Parent::inspectPostApply();
}

void GuiMaterialCtrl::onRender( Point2I offset, const RectI &updateRect )
{
   Parent::onRender( offset, updateRect );

   if ( !mMaterialInst )
      return;

   // Draw a quad with the material assigned
   GFXVertexBufferHandle<GFXVertexPCT> verts( GFX, 4, GFXBufferTypeVolatile );
   verts.lock();

   F32 screenLeft   = updateRect.point.x;
   F32 screenRight  = (updateRect.point.x + updateRect.extent.x);
   F32 screenTop    = updateRect.point.y;
   F32 screenBottom = (updateRect.point.y + updateRect.extent.y);

   const F32 fillConv = GFX->getFillConventionOffset();
   verts[0].point.set( screenLeft  - fillConv, screenTop    - fillConv, 0.f );
   verts[1].point.set( screenRight - fillConv, screenTop    - fillConv, 0.f );
   verts[2].point.set( screenLeft  - fillConv, screenBottom - fillConv, 0.f );
   verts[3].point.set( screenRight - fillConv, screenBottom - fillConv, 0.f );

   verts[0].color = verts[1].color = verts[2].color = verts[3].color = ColorI( 255, 255, 255, 255 );

   verts[0].texCoord.set( 0.0f, 0.0f );
   verts[1].texCoord.set( 1.0f, 0.0f );
   verts[2].texCoord.set( 0.0f, 1.0f );
   verts[3].texCoord.set( 1.0f, 1.0f );

   verts.unlock();

   GFX->setVertexBuffer( verts );

   MatrixSet matSet;
   matSet.setWorld(GFX->getWorldMatrix());
   matSet.setView(GFX->getViewMatrix());
   matSet.setProjection(GFX->getProjectionMatrix());
   
   MatrixF cameraMatrix( true );
   F32 left, right, top, bottom, nearPlane, farPlane;
   bool isOrtho;
   GFX->getFrustum( &left, &right, &bottom, &top, &nearPlane, &farPlane, &isOrtho );
   Frustum frust( isOrtho, left, right, top, bottom, nearPlane, farPlane, cameraMatrix );

   SceneRenderState state
   (
      gClientSceneGraph,
      SPT_Diffuse,
      SceneCameraState( GFX->getViewport(), frust, GFX->getWorldMatrix(), GFX->getProjectionMatrix() ),
      gClientSceneGraph->getDefaultRenderPass(),
      false
   );

   SceneData sgData;
   sgData.init( &state );
   sgData.wireframe = false; // Don't wireframe this.

   while( mMaterialInst->setupPass( &state, sgData ) )
   {
      mMaterialInst->setSceneInfo( &state, sgData );
      mMaterialInst->setTransforms( matSet, &state );
      GFX->setupGenericShaders();
      GFX->drawPrimitive( GFXTriangleStrip, 0, 2 );
   }

   // Clean up
   GFX->setShader( NULL );
   GFX->setTexture( 0, NULL );
}

ConsoleMethod( GuiMaterialCtrl, setMaterial, bool, 3, 3, "( string materialName )"
               "Set the material to be displayed in the control." )
{
   return object->setMaterial( argv[2] );
}
