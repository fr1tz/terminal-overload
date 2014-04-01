// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLSTATEBLOCK_H_
#define _GFXGLSTATEBLOCK_H_

#include "gfx/gfxStateBlock.h"

class GFXGLStateBlock : public GFXStateBlock
{   
public:
   // 
   // GFXGLStateBlock interface
   //
   GFXGLStateBlock(const GFXStateBlockDesc& desc);
   virtual ~GFXGLStateBlock();

   /// Called by OpenGL device to active this state block.
   /// @param oldState  The current state, used to make sure we don't set redundant states on the device.  Pass NULL to reset all states.
   void activate(const GFXGLStateBlock* oldState);


   // 
   // GFXStateBlock interface
   //

   /// Returns the hash value of the desc that created this block
   virtual U32 getHashValue() const;

   /// Returns a GFXStateBlockDesc that this block represents
   virtual const GFXStateBlockDesc& getDesc() const;   

   //
   // GFXResource
   //
   virtual void zombify() { }
   /// When called the resource should restore all device sensitive information destroyed by zombify()
   virtual void resurrect() { }
private:
   GFXStateBlockDesc mDesc;
   U32 mCachedHashValue;
   U32 mSamplerObjects[TEXTURE_STAGE_COUNT];
};

typedef StrongRefPtr<GFXGLStateBlock> GFXGLStateBlockRef;

#endif