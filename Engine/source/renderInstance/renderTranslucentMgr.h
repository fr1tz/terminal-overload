// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RENDER_TRANSLUCENT_MGR_H_
#define _RENDER_TRANSLUCENT_MGR_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

class RenderParticleMgr;

class RenderTranslucentMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

public:

   RenderTranslucentMgr();
   RenderTranslucentMgr( F32 renderOrder, F32 processAddOrder );
   virtual ~RenderTranslucentMgr();

   // RenderBinManager
   void render(SceneRenderState * state);
   void addElement( RenderInst *inst );
   void setupSGData( MeshRenderInst *ri, SceneData &data );

   // ConsoleObject
   DECLARE_CONOBJECT(RenderTranslucentMgr);

protected:
   // This is a stateblock per potential blend type, we create 
   // these as needed.
   enum
   {
      MaxBlend = 256
   };
   GFXStateBlockRef mStateBlocks[MaxBlend];
   
   GFXStateBlockRef _getStateBlock( U8 transFlag );
   RenderParticleMgr *mParticleRenderMgr;;
};


#endif // _RENDER_TRANSLUCENT_MGR_H_
