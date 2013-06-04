// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FOGSTRUCTS_H_
#define _FOGSTRUCTS_H_

/// The aerial fog settings.
struct FogData
{   
   F32 density;
   F32 densityOffset;
   F32 atmosphereHeight;
   ColorF color;

   FogData()
   {
      density = 0.0f;
      densityOffset = 0.0f;
      atmosphereHeight = 0.0f;
      color.set( 0.5f, 0.5f, 0.5f, 1.0f );
   }
};


/// The water fog settings.
struct WaterFogData
{   
   F32 density;
   F32 densityOffset;   
   F32 wetDepth;
   F32 wetDarkening;
   ColorI color;
   PlaneF plane;
   F32 depthGradMax;

   WaterFogData()
   {
      density = 0.0f;
      densityOffset = 0.0f;     
      wetDepth = 0.0f;
      wetDarkening = 0.0f;
      color.set( 0.5f, 0.5f, 0.5f, 1.0f );
      plane.set( 0.0f, 0.0f, 1.0f );
      depthGradMax = 0.0f;
   }
};

#endif // _FOGSTRUCTS_H_