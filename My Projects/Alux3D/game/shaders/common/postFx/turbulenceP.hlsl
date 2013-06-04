// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./postFx.hlsl"

uniform float  accumTime;

float4 main( PFXVertToPix IN, uniform sampler2D inputTex : register(S0) ) : COLOR
{
	float reduction = 128;	
	float power = 1.0;
	float speed = 3.0;
	float frequency=8;
	
	float backbuffer_edge_coef=0.98;
	float2 screen_center = float2(0.5, 0.5);	
	float2 cPos = (IN.uv0 - screen_center);
	
	float len = 1.0 - length(cPos);		
	float2 uv = clamp((cPos / len * cos(len * frequency - (accumTime * speed)) * (power / reduction)), 0, 1);
	return tex2D(inputTex, IN.uv0 * backbuffer_edge_coef + uv);

//    float4 color = tex2D(inputTex, IN.uv0 * backbuffer_edge_coef+(sin*right));           
//	return color;

}