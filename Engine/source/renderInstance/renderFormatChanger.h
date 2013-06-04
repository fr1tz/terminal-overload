// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RENDERFORMATCHANGER_H_
#define _RENDERFORMATCHANGER_H_

#ifndef _RENDERPASSSTATETOKEN_H_
#include "renderInstance/renderPassStateToken.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

class PostEffect;


class RenderFormatToken : public RenderPassStateToken
{
   typedef RenderPassStateToken Parent;

public:
   enum FormatTokenState
   {
      FTSDisabled,
      FTSWaiting,
      FTSActive,
      FTSComplete,
   };

   const static U32 TargetChainLength = 1;

protected:

   FormatTokenState mFCState;
   GFXFormat mColorFormat;
   GFXFormat mDepthFormat;
   bool mTargetUpdatePending;
   U32 mTargetChainIdx;
   Point2I mTargetSize;
   S32 mTargetAALevel;
   SimObjectPtr<PostEffect> mCopyPostEffect;
   SimObjectPtr<PostEffect> mResolvePostEffect;

   NamedTexTarget mTarget;

   GFXTexHandle mTargetColorTexture[TargetChainLength];
   GFXTexHandle mTargetDepthStencilTexture[TargetChainLength];
   GFXTextureTargetRef mTargetChain[TargetChainLength];

   GFXTexHandle mStoredPassZTarget;
   
   void _updateTargets();
   void _teardownTargets();

   void _onTextureEvent( GFXTexCallbackCode code );
   virtual bool _handleGFXEvent(GFXDevice::GFXDeviceEventType event);

   static bool _setFmt( void *object, const char *index, const char *data );
   static const char* _getCopyPostEffect( void* object, const char* data );
   static const char* _getResolvePostEffect( void* object, const char* data );
   static bool _setCopyPostEffect( void* object, const char* index, const char* data );
   static bool _setResolvePostEffect( void* object, const char* index, const char* data );
   
public:

   DECLARE_CONOBJECT(RenderFormatToken);
   static void initPersistFields();
   virtual bool onAdd();
   virtual void onRemove();

   RenderFormatToken();
   virtual ~RenderFormatToken();

   virtual void process(SceneRenderState *state, RenderPassStateBin *callingBin);
   virtual void reset();
   virtual void enable(bool enabled = true);
   virtual bool isEnabled() const;
};

#endif // _RENDERFORMATCHANGER_H_
