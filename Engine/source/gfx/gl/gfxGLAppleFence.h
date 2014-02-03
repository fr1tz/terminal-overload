// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLAPPLEFENCE_H_
#define _GFXGLAPPLEFENCE_H_

#include "gfx/gfxFence.h"
#include "gfx/gl/tGL/tGL.h"

class GFXGLAppleFence : public GFXFence
{
public:
   GFXGLAppleFence(GFXDevice* device);
   virtual ~GFXGLAppleFence();
   
   // GFXFence interface
   virtual void issue();
   virtual FenceStatus getStatus() const;
   virtual void block();
   
   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   virtual const String describeSelf() const;
   
private:
   GLuint mHandle;
   bool mIssued;
};

#endif