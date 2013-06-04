// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PARABOLOIDLIGHTSHADOWMAP_H_
#define _PARABOLOIDLIGHTSHADOWMAP_H_

#ifndef _LIGHTSHADOWMAP_H_
#include "lighting/shadowMap/lightShadowMap.h"
#endif


class ParaboloidLightShadowMap : public LightShadowMap
{
   typedef LightShadowMap Parent;
public:
   ParaboloidLightShadowMap( LightInfo *light );
   ~ParaboloidLightShadowMap();

   // LightShadowMap
   virtual ShadowType getShadowType() const;
   virtual void _render( RenderPassManager* renderPass, const SceneRenderState *diffuseState );
   virtual void setShaderParameters(GFXShaderConstBuffer* params, LightingShaderConstants* lsc);

protected:
   Point2F mShadowMapScale;
   Point2F mShadowMapOffset;
};

#endif