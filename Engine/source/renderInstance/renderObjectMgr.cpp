// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#include "renderObjectMgr.h"
#include "console/consoleTypes.h"
#include "scene/sceneObject.h"

IMPLEMENT_CONOBJECT(RenderObjectMgr);

ConsoleDocClass( RenderObjectMgr, 
   "@brief A render bin which uses object callbacks for rendering.\n\n"
   "This render bin gathers object render instances and calls its delegate "
   "method to perform rendering.  It is used infrequently for specialized "
   "scene objects which perform custom rendering.\n\n"
   "@ingroup RenderBin\n" );


RenderObjectMgr::RenderObjectMgr()
: RenderBinManager(RenderPassManager::RIT_Object, 1.0f, 1.0f)
{
   mOverrideMat = NULL;
}

RenderObjectMgr::RenderObjectMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{  
   mOverrideMat = NULL;
}

void RenderObjectMgr::initPersistFields()
{
   Parent::initPersistFields();
}

void RenderObjectMgr::setOverrideMaterial(BaseMatInstance* overrideMat)
{ 
   mOverrideMat = overrideMat; 
}

//-----------------------------------------------------------------------------
// render objects
//-----------------------------------------------------------------------------
void RenderObjectMgr::render( SceneRenderState *state )
{
   PROFILE_SCOPE(RenderObjectMgr_render);

   // Early out if nothing to draw.
   if(!mElementList.size())
      return;

   for( U32 i=0; i<mElementList.size(); i++ )
   {
      ObjectRenderInst *ri = static_cast<ObjectRenderInst*>(mElementList[i].inst);
      if ( ri->renderDelegate )
         ri->renderDelegate( ri, state, mOverrideMat );      
   }
}