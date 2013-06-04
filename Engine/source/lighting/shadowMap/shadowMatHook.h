// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADOWMATHOOK_H_
#define _SHADOWMATHOOK_H_

#ifndef _MATINSTANCEHOOK_H_
#include "materials/matInstanceHook.h"
#endif
#ifndef _MATINSTANCE_H_
#include "materials/matInstance.h"
#endif

// TODO: Move ShadowType enum to somewhere 
// with less dependancies.
#ifndef _SHADOWMAPPASS_H_
#include "lighting/shadowMap/shadowMapPass.h"
#endif

class ShadowMatInstance : public MatInstance
{
   typedef MatInstance Parent;

   bool mLightmappedMaterial;
public:
   ShadowMatInstance( Material *mat );
   virtual ~ShadowMatInstance() {}

   virtual bool setupPass( SceneRenderState *state, const SceneData &sgData );
};

class ShadowMaterialHook : public MatInstanceHook
{
public:

   ShadowMaterialHook();

   // MatInstanceHook
   virtual ~ShadowMaterialHook();
   virtual const MatInstanceHookType& getType() const { return Type; }

   /// The material hook type.
   static const MatInstanceHookType Type;

   BaseMatInstance* getShadowMat( ShadowType type ) const;

   void init( BaseMatInstance *mat );

protected:

   static void _overrideFeatures(   ProcessedMaterial *mat,
                                    U32 stageNum,
                                    MaterialFeatureData &fd, 
                                    const FeatureSet &features );

   /// 
   BaseMatInstance* mShadowMat[ShadowType_Count];


};

#endif // _SHADOWMATHOOK_H_
