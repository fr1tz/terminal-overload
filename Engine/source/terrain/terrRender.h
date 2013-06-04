// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRRENDER_H_
#define _TERRRENDER_H_

#ifndef _TERRDATA_H_
#include "terrain/terrData.h"
#endif

enum TerrConstants 
{
   MaxClipPlanes       = 8, ///< left, right, top, bottom - don't need far tho...
   //MaxTerrainMaterials = 256,

   MaxTerrainLights = 64,
   MaxVisibleLights = 31,
   ClipPlaneMask    = (1 << MaxClipPlanes) - 1,
   FarSphereMask    = 0x80000000,
   FogPlaneBoxMask  = 0x40000000,
};

class SceneRenderState;


// Allows a lighting system to plug into terrain rendering
class TerrainLightingPlugin
{
public:
   virtual ~TerrainLightingPlugin() {}
   
   virtual void setupLightStage(LightManager * lm, LightInfo* light, SceneData& sgData, BaseMatInstance* basemat, BaseMatInstance** dmat) = 0;
   virtual void cleanupLights(LightManager * lm) {}
};


/// A special texture profile used for the terrain layer id map.
GFX_DeclareTextureProfile( TerrainLayerTexProfile );

#endif // _TERRRENDER_H_
