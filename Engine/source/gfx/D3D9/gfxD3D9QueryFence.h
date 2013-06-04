// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFX_D3D9_QUERYFENCE_H_
#define _GFX_D3D9_QUERYFENCE_H_

#include "gfx/gfxFence.h"
#include "gfx/gfxResource.h"

struct IDirect3DQuery9;

class GFXD3D9QueryFence : public GFXFence
{
private:
   mutable IDirect3DQuery9 *mQuery;

public:
   GFXD3D9QueryFence( GFXDevice *device ) : GFXFence( device ), mQuery( NULL ) {};
   virtual ~GFXD3D9QueryFence();

   virtual void issue();
   virtual FenceStatus getStatus() const;
   virtual void block();

   

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   virtual const String describeSelf() const;
};

#endif