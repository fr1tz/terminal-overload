// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"  
#include "./postFx.hlsl"  
#include "../torque.hlsl"

uniform sampler2D backBuffer : register(S0);
uniform sampler1D colorCorrectionTex : register( s1 );

uniform float OneOverGamma;


float4 main( PFXVertToPix IN ) : COLOR0  
{
    float4 color = tex2D(backBuffer, IN.uv0.xy);

   // Apply the color correction.
   color.r = tex1D( colorCorrectionTex, color.r ).r;
   color.g = tex1D( colorCorrectionTex, color.g ).g;
   color.b = tex1D( colorCorrectionTex, color.b ).b;

   // Apply gamma correction
    color.rgb = pow( abs(color.rgb), OneOverGamma );

    return color;    
}