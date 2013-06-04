// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _RENDEROBJECTMGR_H_
#define _RENDEROBJECTMGR_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif

//**************************************************************************
// RenderObjectMgr
//**************************************************************************
class RenderObjectMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;
public:
   RenderObjectMgr();
   RenderObjectMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);

   virtual void setOverrideMaterial(BaseMatInstance* overrideMat); 

   // RenderBinMgr
   virtual void render(SceneRenderState * state);

   // ConsoleObject
   static void initPersistFields();
   DECLARE_CONOBJECT(RenderObjectMgr);
protected:
   BaseMatInstance* mOverrideMat;
};

#endif // _RENDEROBJECTMGR_H_