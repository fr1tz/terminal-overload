// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gfx/util/gfxFrustumSaver.h"
#include "gfx/gfxDevice.h"

GFXFrustumSaver::GFXFrustumSaver()
{
   mFrustum = GFX->getFrustum();
}

GFXFrustumSaver::~GFXFrustumSaver()
{   
   GFX->setFrustum( mFrustum );   
}
