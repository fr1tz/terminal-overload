// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _POSTEFFECTMANAGER_H_
#define _POSTEFFECTMANAGER_H_

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif
#ifndef _POSTEFFECTCOMMON_H_
#include "postFx/postEffectCommon.h"
#endif

class PostEffect;
class RenderBinManager;
class SceneRenderState;
class SceneManager;


class PostEffectManager
{
protected:

   friend class PostEffect;

   typedef Vector<PostEffect*> EffectVector;

   typedef Map<String,EffectVector> EffectMap;

   /// A global flag for toggling the post effect system.  It
   /// is tied to the $pref::enablePostEffects preference.
   static bool smRenderEffects;

   EffectVector mEndOfFrameList;
   EffectVector mAfterDiffuseList;
   EffectMap mAfterBinMap;
   EffectMap mBeforeBinMap;

   /// A copy of the last requested back buffer.
   GFXTexHandle mBackBufferCopyTex;

   //GFXTexHandle mBackBufferFloatCopyTex;

   /// The target at the time the last back buffer
   /// was copied.  Used to detect the need to recopy.
   GFXTarget *mLastBackBufferTarget;

   // State for current frame and last frame
   bool mFrameStateSwitch;

   PFXFrameState mFrameState[2];

   bool _handleDeviceEvent( GFXDevice::GFXDeviceEventType evt );

   void _handleBinEvent(   RenderBinManager *bin,                           
                           const SceneRenderState* sceneState,
                           bool isBinStart );  

   ///
   void _onPostRenderPass( SceneManager *sceneGraph, const SceneRenderState *sceneState );

   // Helper method
   void _updateResources();

   ///
   static S32 _effectPrioritySort( PostEffect* const*e1, PostEffect* const*e2 );

   bool _addEffect( PostEffect *effect );

   bool _removeEffect( PostEffect *effect );

public:

   PostEffectManager();

   virtual ~PostEffectManager();

   void renderEffects(  const SceneRenderState *state,
                        const PFXRenderTime effectTiming, 
                        const String &binName = String::EmptyString );

   /// Returns the current back buffer texture taking
   /// a copy of if the target has changed or the buffer
   /// was previously released.
   GFXTextureObject* getBackBufferTex();
   
   /// Releases the current back buffer so that a
   /// new copy is made on the next request.
   void releaseBackBufferTex();

   /*
   bool submitEffect( PostEffect *effect, const PFXRenderTime renderTime = PFXDefaultRenderTime, const GFXRenderBinTypes afterBin = GFXBin_DefaultPostProcessBin )
   {
      return _addEntry( effect, false, renderTime, afterBin );
   }
   */
   
   // State interface
   const PFXFrameState &getFrameState() const { return mFrameState[mFrameStateSwitch]; }
   const PFXFrameState &getLastFrameState() const { return mFrameState[!mFrameStateSwitch]; }

   void setFrameMatrices( const MatrixF &worldToCamera, const MatrixF &cameraToScreen );
   
   // For ManagedSingleton.
   static const char* getSingletonName() { return "PostEffectManager"; }
};

/// Returns the PostEffectManager singleton.
#define PFXMGR ManagedSingleton<PostEffectManager>::instance()

#endif // _POSTEFFECTMANAGER_H_