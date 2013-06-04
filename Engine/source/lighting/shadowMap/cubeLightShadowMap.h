// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CUBELIGHTSHADOWMAP_H_
#define _CUBELIGHTSHADOWMAP_H_

#ifndef _LIGHTSHADOWMAP_H_
#include "lighting/shadowMap/lightShadowMap.h"
#endif
#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif


class CubeLightShadowMap : public LightShadowMap
{
   typedef LightShadowMap Parent;

public:

   CubeLightShadowMap( LightInfo *light );

   // LightShadowMap
   virtual bool hasShadowTex() const { return mCubemap.isValid(); }
   virtual ShadowType getShadowType() const { return ShadowType_CubeMap; }
   virtual void _render( RenderPassManager* renderPass, const SceneRenderState *diffuseState );
   virtual void setShaderParameters( GFXShaderConstBuffer* params, LightingShaderConstants* lsc );
   virtual void releaseTextures();
   virtual bool setTextureStage( U32 currTexFlag, LightingShaderConstants* lsc );

protected:   

   /// The shadow cubemap.
   GFXCubemapHandle mCubemap;

};

#endif // _CUBELIGHTSHADOWMAP_H_
