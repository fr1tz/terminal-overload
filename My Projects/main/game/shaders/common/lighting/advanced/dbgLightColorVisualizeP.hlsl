// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"
#include "../../postfx/postFx.hlsl"


float4 main( PFXVertToPix IN, 
             uniform sampler2D lightPrePassTex : register(S0) ) : COLOR0
{   
   float3 lightcolor;   
   float nl_Att, specular;   
   lightinfoUncondition( tex2D( lightPrePassTex, IN.uv0 ), lightcolor, nl_Att, specular );   
   return float4( lightcolor, 1.0 );   
}
