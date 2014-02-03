// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BARRELDISTORTIONPOSTEFFECT_H_
#define _BARRELDISTORTIONPOSTEFFECT_H_

#include "postFx/postEffect.h"

class BarrelDistortionPostEffect : public PostEffect
{
   typedef PostEffect Parent;

protected:
   GFXShaderConstHandle *mHmdWarpParamSC;
   GFXShaderConstHandle *mHmdChromaAbSC;
   GFXShaderConstHandle *mScaleSC;
   GFXShaderConstHandle *mScaleInSC;
   GFXShaderConstHandle *mLensCenterSC;
   GFXShaderConstHandle *mScreenCenterSC;

   // Oculus VR HMD index to reference
   S32 mHMDIndex;

   // Oculus VR sensor index to reference
   S32 mSensorIndex;

   // Used to increase the size of the window into the world at the
   // expense of apparent resolution.
   F32 mScaleOutput;

protected:
   virtual void _setupConstants( const SceneRenderState *state );

public:
   BarrelDistortionPostEffect();
   virtual ~BarrelDistortionPostEffect();

   DECLARE_CONOBJECT(BarrelDistortionPostEffect);

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();

   virtual void process(   const SceneRenderState *state, 
                           GFXTexHandle &inOutTex,
                           const RectI *inTexViewport = NULL );
};

#endif   // _BARRELDISTORTIONPOSTEFFECT_H_
