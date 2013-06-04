// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SINGLELIGHTSHADOWMAP_H_
#define _SINGLELIGHTSHADOWMAP_H_

#ifndef _LIGHTSHADOWMAP_H_
#include "lighting/shadowMap/lightShadowMap.h"
#endif

//
// SingleLightShadowMap, holds the shadow map and various other things for a light.
//
// This represents everything we need to render the shadowmap for one light.
class SingleLightShadowMap : public LightShadowMap
{
public:
   SingleLightShadowMap( LightInfo *light );
   ~SingleLightShadowMap();

   // LightShadowMap
   virtual ShadowType getShadowType() const { return ShadowType_Spot; }
   virtual void _render( RenderPassManager* renderPass, const SceneRenderState *diffuseState );
   virtual void setShaderParameters(GFXShaderConstBuffer* params, LightingShaderConstants* lsc);
};


#endif // _SINGLELIGHTSHADOWMAP_H_