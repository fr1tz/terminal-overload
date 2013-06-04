// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _CUSTOMMATERIALDEFINITION_H_
#define _CUSTOMMATERIALDEFINITION_H_

#ifndef _MATERIALDEFINITION_H_
#include "materials/materialDefinition.h"
#endif

class ShaderData;
class GFXStateBlockData;

//**************************************************************************
// Custom Material
//**************************************************************************
class CustomMaterial : public Material
{
   typedef Material Parent;
public:
   enum CustomConsts
   {
      MAX_PASSES = 8,
      NUM_FALLBACK_VERSIONS = 2,
   };
   
   FileName mTexFilename[MAX_TEX_PER_PASS];
   String mSamplerNames[MAX_TEX_PER_PASS];
   String mOutputTarget;
   Material* mFallback;
   bool mForwardLit;

   F32 mVersion;   // 0 = legacy, 1 = DX 8.1, 2 = DX 9.0   
   bool mRefract;   
   ShaderData* mShaderData;

   CustomMaterial();       
   const GFXStateBlockData* getStateBlockData() const;

   //
   // SimObject interface
   //
   virtual bool onAdd();
   virtual void onRemove();

   //
   // ConsoleObject interface
   //
   static void initPersistFields();
   DECLARE_CONOBJECT(CustomMaterial);
protected:
   U32 mMaxTex;
   String mShaderDataName;
   U32 mFlags[MAX_TEX_PER_PASS];   
   GFXStateBlockData* mStateBlockData;

   virtual void _mapMaterial();
};

#endif
