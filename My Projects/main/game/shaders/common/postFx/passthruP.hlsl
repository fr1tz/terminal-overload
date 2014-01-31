// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./postFx.hlsl"

uniform sampler2D inputTex : register(S0);

float4 main( PFXVertToPix IN ) : COLOR
{
   return tex2D( inputTex, IN.uv0 );   
}