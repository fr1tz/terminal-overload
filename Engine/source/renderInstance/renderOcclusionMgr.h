// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _RENDEROCCLUSIONMGR_H_
#define _RENDEROCCLUSIONMGR_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif

class Material;
class BaseMatInstance;


//**************************************************************************
// RenderOcclusionMgr
//**************************************************************************
class RenderOcclusionMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;
public:
   RenderOcclusionMgr();
   RenderOcclusionMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);

   // RenderOcclusionMgr
   virtual void init();
   virtual void render(SceneRenderState * state);

   // ConsoleObject
   static void consoleInit();
   static void initPersistFields();
   DECLARE_CONOBJECT(RenderOcclusionMgr);

protected:
   GFXStateBlockRef mRenderSB;
   GFXStateBlockRef mTestSB;

   /// The material for rendering occluders.
   SimObjectPtr<Material> mMaterial;
   BaseMatInstance *mMatInstance;

   static bool smDebugRender;

   GFXVertexBufferHandle<GFXVertexP> mBoxBuff;
   GFXVertexBufferHandle<GFXVertexP> mSphereBuff;
   U32 mSpherePrimCount;
};

#endif // _RENDEROCCLUSIONMGR_H_