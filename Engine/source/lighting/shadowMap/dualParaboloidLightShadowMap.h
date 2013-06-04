// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _DUALPARABOLOIDLIGHTSHADOWMAP_H_
#define _DUALPARABOLOIDLIGHTSHADOWMAP_H_

#ifndef _PARABOLOIDLIGHTSHADOWMAP_H_
#include "lighting/shadowMap/paraboloidLightShadowMap.h"
#endif

class DualParaboloidLightShadowMap : public ParaboloidLightShadowMap
{
   typedef ParaboloidLightShadowMap Parent;

public:
   DualParaboloidLightShadowMap( LightInfo *light );

   virtual void _render( RenderPassManager* renderPass, const SceneRenderState *diffuseState );
};

#endif // _DUALPARABOLOIDLIGHTSHADOWMAP_H_