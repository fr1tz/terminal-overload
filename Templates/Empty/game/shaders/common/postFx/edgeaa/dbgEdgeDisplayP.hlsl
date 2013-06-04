// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

float4 main( PFXVertToPix IN, 
             uniform sampler2D edgeBuffer :register(S0) ) : COLOR0
{
   return float4( tex2D( edgeBuffer, IN.uv0 ).rrr, 1.0 );
}