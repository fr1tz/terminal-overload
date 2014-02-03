// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./postFx.hlsl"

uniform float  accumTime;
uniform float2 projectionOffset;
uniform float4 targetViewport;

float4 main( PFXVertToPix IN, uniform sampler2D inputTex : register(S0) ) : COLOR
{
	float speed = 2.0;
	float distortion = 6.0;
	
	float y = IN.uv0.y + (cos((IN.uv0.y+projectionOffset.y) * distortion + accumTime * speed) * 0.01);
   float x = IN.uv0.x + (sin((IN.uv0.x+projectionOffset.x) * distortion + accumTime * speed) * 0.01);

   // Clamp the calculated uv values to be within the target's viewport
	y = clamp(y, targetViewport.y, targetViewport.w);
	x = clamp(x, targetViewport.x, targetViewport.z);
	
    return tex2D (inputTex, float2(x, y));
}
