// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "../../torque.hlsl"
#include "shadergen:/autogenConditioners.h"


uniform sampler2D inputTex : register(S0);
uniform float brightPassThreshold;

float4 main( PFXVertToPix IN ) : COLOR
{
   float4 sample = hdrDecode( tex2D( inputTex, IN.uv0 ) );
   
   // Determine the brightness of this particular pixel.
   float lum = hdrLuminance( sample.rgb );

   // Write the colour to the bright-pass render target
   return ( float4( lum.rrr, 1 ) );
}
