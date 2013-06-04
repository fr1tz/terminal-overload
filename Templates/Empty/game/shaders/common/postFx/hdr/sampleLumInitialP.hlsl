// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../torque.hlsl"
#include "../postFx.hlsl"

uniform sampler2D inputTex : register( S0 );
uniform float2 texSize0;

uniform float g_fMinLuminace;

static float2 gTapOffsets[9] = 
{
   { -1.0, -1.0 }, { 0.0, -1.0 }, { 1.0, -1.0 },
   { -1.0, 0.0 },  { 0.0, 0.0 },  { 1.0, 0.0 },
   { -1.0, 1.0 },  { 0.0, 1.0 },  { 1.0, 1.0 }
};


float4 main( PFXVertToPix IN ) : COLOR
{
   float2 tsize = 1.0 / texSize0;

   float3 sample;
   float average = 0.0;
     
   for ( int i = 0; i < 9; i++ )
   {
      // Decode the hdr value.
      sample = hdrDecode( tex2D( inputTex, IN.uv0 + ( gTapOffsets[i] * tsize ) ).rgb );

      // Get the luminance and add it to the average.
      float lum = max( hdrLuminance( sample ), g_fMinLuminace );
      average += log( lum );
   }

   average = exp( average / 9.0 );

   return float4( average, 0.0, 0.0, 1.0 );
}
