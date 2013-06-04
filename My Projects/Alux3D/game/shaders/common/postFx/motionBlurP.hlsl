// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./postFx.hlsl"
#include "../torque.hlsl"
#include "shadergen:/autogenConditioners.h"

uniform float4x4 matPrevScreenToWorld;
uniform float4x4 matWorldToScreen;

// Passed in from setShaderConsts()
uniform float velocityMultiplier;

uniform sampler2D backBuffer  : register(S0);
uniform sampler2D prepassTex  : register(S1);

float4 main(PFXVertToPix IN) : COLOR0
{
   float samples = 5;
   
   // First get the prepass texture for uv channel 0
   float4 prepass = prepassUncondition( prepassTex, IN.uv0 );
   
   // Next extract the depth
   float depth = prepass.a;
   
   // Create the screen position
   float4 screenPos = float4(IN.uv0.x*2-1, IN.uv0.y*2-1, depth*2-1, 1);

   // Calculate the world position
   float4 D = mul(screenPos, matWorldToScreen);
   float4 worldPos = D / D.w;
   
   // Now calculate the previous screen position
   float4 previousPos = mul( worldPos, matPrevScreenToWorld );
   previousPos /= previousPos.w;
	
   // Calculate the XY velocity
   float2 velocity = ((screenPos - previousPos) / velocityMultiplier).xy;
   
   // Generate the motion blur
   float4 color = tex2D(backBuffer, IN.uv0);
	IN.uv0 += velocity;
	
   for(int i = 1; i<samples; ++i, IN.uv0 += velocity)
   {
      float4 currentColor = tex2D(backBuffer, IN.uv0);
      color += currentColor;
   }
   
   return color / samples;
}