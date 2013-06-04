// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

float4 main( PFXVertToPix IN, 
             uniform sampler2D edgeBuffer : register(S0),
             uniform sampler2D backBuffer : register(S1),
             uniform float2 targetSize : register(C0) ) : COLOR0
{
   float2 pixelSize = 1.0 / targetSize;

   // Sample edge buffer, bail if not on an edge
   float edgeSample = tex2D(edgeBuffer, IN.uv0).r;
   clip(edgeSample - 1e-6);
   
   // Ok we're on an edge, so multi-tap sample, average, and return
   float2 offsets[9] = {
      float2( 0.0,  0.0),
      float2(-1.0, -1.0),
      float2( 0.0, -1.0),
      float2( 1.0, -1.0),
      float2( 1.0,  0.0),
      float2( 1.0,  1.0),
      float2( 0.0,  1.0),
      float2(-1.0,  1.0),
      float2(-1.0,  0.0),
   };
      
   float4 accumColor = 0;
   for(int i = 0; i < 9; i++)
   {
      // Multiply the intensity of the edge, by the UV, so that things which maybe
      // aren't quite full edges get sub-pixel sampling to reduce artifacts
      
      // Scaling offsets by 0.5 to reduce the range bluriness from extending to
      // far outward from the edge.
      
      float2 offsetUV = IN.uv1 + edgeSample * ( offsets[i] * 0.5 ) * pixelSize;//rtWidthHeightInvWidthNegHeight.zw;
      //offsetUV *= 0.999;
      accumColor+= tex2D(backBuffer, offsetUV);
   }
   accumColor /= 9.0;
   
   return accumColor;
}
