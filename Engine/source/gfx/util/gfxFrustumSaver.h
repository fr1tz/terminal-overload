// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef TORQUE_GFX_UTIL_GFXFRUSTUMSAVER_H_
#define TORQUE_GFX_UTIL_GFXFRUSTUMSAVER_H_

#include "platform/types.h"

#ifndef _MATHUTIL_FRUSTUM_H_
#include "math/util/frustum.h"
#endif

class GFXFrustumSaver
{
public:
   /// Saves the current frustum state.
   GFXFrustumSaver();
   
   /// Restores the saved frustum state.
   ~GFXFrustumSaver();
   
private:
   Frustum mFrustum;
};

#endif
