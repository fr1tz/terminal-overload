// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SCENEDATA_H_
#define _SCENEDATA_H_

#ifndef _SCENERENDERSTATE_H_
#include "scene/sceneRenderState.h"
#endif
#ifndef _LIGHTMANAGER_H_
#include "lighting/lightManager.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif

class GFXTexHandle;
class GFXCubemap;


struct SceneData
{
   /// The special bin types.
   enum BinType
   {
      /// A normal render bin that isn't one of 
      /// the special bins we care about.
      RegularBin = 0,

      /// The glow render bin.
      /// @see RenderGlowMgr
      GlowBin,

      /// The prepass render bin.
      /// @RenderPrePassMgr
      PrePassBin,
   };

   /// This defines when we're rendering a special bin 
   /// type that the material or lighting system needs
   /// to know about.
   BinType binType;

   // textures
   GFXTextureObject *lightmap;
   GFXTextureObject *backBuffTex;
   GFXTextureObject *reflectTex;
   GFXTextureObject *miscTex;
   
   /// The current lights to use in rendering
   /// in order of the light importance.
   LightInfo* lights[8];

   ///
   ColorF ambientLightColor;

   // fog      
   F32 fogDensity;
   F32 fogDensityOffset;
   F32 fogHeightFalloff;
   ColorF fogColor;
  
   // misc
   const MatrixF *objTrans;
   GFXCubemap *cubemap;
   F32 visibility;

   /// Enables wireframe rendering for the object.
   bool wireframe;

   /// A generic hint value passed from the game
   /// code down to the material for use by shader 
   /// features.
   void *materialHint;

   /// Constructor.
   SceneData() 
   { 
      dMemset( this, 0, sizeof( SceneData ) );
      objTrans = &MatrixF::Identity;
      visibility = 1.0f;
   }

   /// Initializes the data with the scene state setting
   /// common scene wide parameters.
   inline void init( const SceneRenderState *state, BinType type = RegularBin )
   {
      dMemset( this, 0, sizeof( SceneData ) );
      setFogParams( state->getSceneManager()->getFogData() );
      wireframe = GFXDevice::getWireframe();
      binType = type;
      objTrans = &MatrixF::Identity;
      visibility = 1.0f;
      ambientLightColor = state->getAmbientLightColor();
   }

   inline void setFogParams( const FogData &data )
   {
      fogDensity = data.density;
      fogDensityOffset = data.densityOffset;
      if ( !mIsZero( data.atmosphereHeight ) )
         fogHeightFalloff = 1.0f / data.atmosphereHeight;
      else
         fogHeightFalloff = 0.0f;

      fogColor = data.color;
   }
};

#endif // _SCENEDATA_H_
