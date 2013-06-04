// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _REFLECTIONMATHOOK_H_
#define _REFLECTIONMATHOOK_H_

#ifndef _MATINSTANCEHOOK_H_
#include "materials/matInstanceHook.h"
#endif
#ifndef _MATINSTANCE_H_
#include "materials/matInstance.h"
#endif

class ReflectionMatInstance : public MatInstance
{
   typedef MatInstance Parent;

public:
   ReflectionMatInstance( Material *mat );
   virtual ~ReflectionMatInstance() {}

   virtual bool setupPass( SceneRenderState *state, const SceneData &sgData );
};

class ReflectionMaterialHook : public MatInstanceHook
{
public:

   ReflectionMaterialHook();

   // MatInstanceHook
   virtual ~ReflectionMaterialHook();
   virtual const MatInstanceHookType& getType() const { return Type; }

   /// The material hook type.
   static const MatInstanceHookType Type;

   BaseMatInstance* getReflectMat() const { return mReflectMat; }

   void init( BaseMatInstance *mat );

protected:

   static void _overrideFeatures(   ProcessedMaterial *mat,
                                    U32 stageNum,
                                    MaterialFeatureData &fd, 
                                    const FeatureSet &features );

   /// 
   BaseMatInstance* mReflectMat;


};

#endif // _SHADOWMATHOOK_H_
