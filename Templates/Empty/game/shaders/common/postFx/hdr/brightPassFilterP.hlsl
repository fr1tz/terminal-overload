// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "shadergen:/autogenConditioners.h"
#include "../../torque.hlsl"


uniform sampler2D inputTex : register(S0);
uniform sampler2D luminanceTex  : register(S1);
uniform float2 oneOverTargetSize;
uniform float brightPassThreshold;
uniform float g_fMiddleGray;

static const float3 LUMINANCE_VECTOR = float3(0.3125f, 0.6154f, 0.0721f);


static float2 gTapOffsets[4] = 
{
   { -0.5, 0.5 },  { 0.5, -0.5 },
   { -0.5, -0.5 }, { 0.5, 0.5 }
};

float4 main( PFXVertToPix IN ) : COLOR
{
   float4 average = { 0.0f, 0.0f, 0.0f, 0.0f };      

   // Combine and average 4 samples from the source HDR texture.
   for( int i = 0; i < 4; i++ )
      average += hdrDecode( tex2D( inputTex, IN.uv0 + ( gTapOffsets[i] * oneOverTargetSize ) ) );
   average *= 0.25f;

   // Determine the brightness of this particular pixel.   
   float adaptedLum = tex2D( luminanceTex, float2( 0.5f, 0.5f ) ).r;
   float lum = (g_fMiddleGray / (adaptedLum + 0.0001)) * hdrLuminance( average.rgb );
   //float lum = hdrLuminance( average.rgb );
   
   // Determine whether this pixel passes the test...
   if ( lum < brightPassThreshold )
      average = float4( 0.0f, 0.0f, 0.0f, 1.0f );

   // Write the colour to the bright-pass render target
   return hdrEncode( average );
}
