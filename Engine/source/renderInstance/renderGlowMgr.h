// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RENDERGLOWMGR_H_
#define _RENDERGLOWMGR_H_

#ifndef _TEXTARGETBIN_MGR_H_
#include "renderInstance/renderTexTargetBinManager.h"
#endif
#include <renderInstance/renderParticleMgr.h>


class PostEffect;


///
class RenderGlowMgr : public RenderTexTargetBinManager
{  
   typedef RenderTexTargetBinManager Parent;

public:

   RenderGlowMgr();
   virtual ~RenderGlowMgr();

   /// Returns the glow post effect.
   PostEffect* getGlowEffect();

   /// Returns true if the glow post effect is
   /// enabled and the glow buffer should be updated.
   bool isGlowEnabled();

   // RenderBinManager
   virtual void addElement( RenderInst *inst );
   virtual void render( SceneRenderState *state );

   // ConsoleObject
   DECLARE_CONOBJECT( RenderGlowMgr );

protected:

   class GlowMaterialHook : public MatInstanceHook
   {
   public:

      GlowMaterialHook( BaseMatInstance *matInst );
      virtual ~GlowMaterialHook();

      virtual BaseMatInstance *getMatInstance() { return mGlowMatInst; }

      virtual const MatInstanceHookType& getType() const { return Type; }

      /// Our material hook type.
      static const MatInstanceHookType Type;

   protected:

      static void _overrideFeatures(   ProcessedMaterial *mat,
                                       U32 stageNum,
                                       MaterialFeatureData &fd, 
                                       const FeatureSet &features );

      BaseMatInstance *mGlowMatInst; 
   };

   SimObjectPtr<PostEffect> mGlowEffect;
   RenderParticleMgr *mParticleRenderMgr;
};


#endif // _RENDERGLOWMGR_H_
