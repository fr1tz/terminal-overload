// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shaders/common/postFx/postFx.hlsl"

uniform sampler2D diffuseMap : register(S0);

struct VertToPix
{
	float4 hpos       : POSITION;
	float2 uv        : TEXCOORD0;
};

static float offset[3] = { 0.0, 1.3846153846, 3.2307692308 };
static float weight[3] = { 0.2270270270, 0.3162162162, 0.0702702703 };  

uniform float2 oneOverTargetSize;

float4 main( VertToPix IN ) : COLOR
{	
	float4 OUT = tex2D( diffuseMap, IN.uv ) * weight[0];
			        
	for ( int i=1; i < 3; i++ )
	{
		float2 sample = (BLUR_DIR * offset[i]) * oneOverTargetSize;
		OUT += tex2D( diffuseMap, IN.uv + sample ) * weight[i];  
		OUT += tex2D( diffuseMap, IN.uv - sample ) * weight[i];  
	}
					   
	return OUT;
}
