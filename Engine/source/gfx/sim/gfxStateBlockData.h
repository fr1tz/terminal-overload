// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef __GFXSTATEBLOCKDATA_H_
#define __GFXSTATEBLOCKDATA_H_

#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif
#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif


class GFXSamplerStateData;

/// Allows definition of render state via script, basically wraps a GFXStateBlockDesc
class GFXStateBlockData : public SimObject
{
   typedef SimObject Parent;

   GFXStateBlockDesc mState;
   GFXSamplerStateData* mSamplerStates[TEXTURE_STAGE_COUNT];
public:
   GFXStateBlockData();

   // SimObject
   virtual bool onAdd();
   static void initPersistFields();  

   // GFXStateBlockData
   const GFXStateBlockDesc getState() const { return mState; }
        
   DECLARE_CONOBJECT(GFXStateBlockData);   
};

/// Allows definition of sampler state via script, basically wraps a GFXSamplerStateDesc
class GFXSamplerStateData : public SimObject
{
   typedef SimObject Parent;
   GFXSamplerStateDesc mState;
public:
   // SimObject
   static void initPersistFields();  

   /// Copies the data of this object into desc
   void setSamplerState(GFXSamplerStateDesc& desc);

   DECLARE_CONOBJECT(GFXSamplerStateData);
};


#endif // __GFXSTATEBLOCKDATA_H_
