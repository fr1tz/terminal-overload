// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADOWMAPMANAGER_H_
#define _SHADOWMAPMANAGER_H_

#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif
#ifndef _SHADOWMANAGER_H_
#include "lighting/shadowManager.h"
#endif
#ifndef _GFXENUMS_H_
#include "gfx/gfxEnums.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _MPOINT4_H_
#include "math/mPoint4.h"
#endif

class LightShadowMap;
class ShadowMapPass;
class LightInfo;

class SceneManager;
class SceneRenderState;


class ShadowMapManager : public ShadowManager
{
   typedef ShadowManager Parent;

   friend class ShadowMapPass;

public:

   ShadowMapManager();
   virtual ~ShadowMapManager();

   /// Sets the current shadowmap (used in setLightInfo/setTextureStage calls)
   void setLightShadowMap( LightShadowMap *lm ) { mCurrentShadowMap = lm; }
   
   /// Looks up the shadow map for the light then sets it.
   void setLightShadowMapForLight( LightInfo *light );

   /// Return the current shadow map
   LightShadowMap* getCurrentShadowMap() const { return mCurrentShadowMap; }

   ShadowMapPass* getShadowMapPass() const { return mShadowMapPass; }

   // Shadow manager
   virtual void activate();
   virtual void deactivate();

   GFXTextureObject* getTapRotationTex();

   /// The shadow map deactivation signal.
   static Signal<void(void)> smShadowDeactivateSignal;

   static void updateShadowDisable();

protected:

   void _onTextureEvent( GFXTexCallbackCode code );

   void _onPreRender( SceneManager *sg, const SceneRenderState* state );

   ShadowMapPass *mShadowMapPass;
   LightShadowMap *mCurrentShadowMap;

   ///
   GFXTexHandle mTapRotationTex;

   bool mIsActive;

public:
   // For ManagedSingleton.
   static const char* getSingletonName() { return "ShadowMapManager"; }   
};


/// Returns the ShadowMapManager singleton.
#define SHADOWMGR ManagedSingleton<ShadowMapManager>::instance()

GFX_DeclareTextureProfile( ShadowMapTexProfile );

#endif // _SHADOWMAPMANAGER_H_