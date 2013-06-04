// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GFXD3D9STATEBLOCK_H_
#define _GFXD3D9STATEBLOCK_H_

#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif

struct IDirect3DDevice9;
class GFXD3D9StateBlock : public GFXStateBlock
{   
public:
   // 
   // GFXD3D9StateBlock interface
   //

   GFXD3D9StateBlock(const GFXStateBlockDesc& desc, IDirect3DDevice9 *d3dDevice);
   virtual ~GFXD3D9StateBlock();

   /// Called by D3D9 device to active this state block.
   /// @param oldState  The current state, used to make sure we don't set redundant states on the device.  Pass NULL to reset all states.
   void activate(GFXD3D9StateBlock* oldState);


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
   IDirect3DDevice9 *mD3DDevice;  ///< Handle for D3DDevice
   // Cached D3D specific things, these are "calculated" from GFXStateBlock
   U32 mColorMask; 
   U32 mZBias;
   U32 mZSlopeBias;
};

typedef StrongRefPtr<GFXD3D9StateBlock> GFXD3D9StateBlockRef;

#endif