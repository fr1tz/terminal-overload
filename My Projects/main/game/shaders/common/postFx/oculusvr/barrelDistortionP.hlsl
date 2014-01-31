// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"  
#include "../postFx.hlsl"  
#include "../../torque.hlsl"

uniform sampler2D backBuffer : register(S0);

uniform float3 LensCenter;    // x=Left X, y=Right X, z=Y
uniform float2 ScreenCenter;
uniform float2 Scale;
uniform float2 ScaleIn;
uniform float4 HmdWarpParam;

// Scales input texture coordinates for distortion.
// ScaleIn maps texture coordinates to Scales to ([-1, 1]), although top/bottom will be
// larger due to aspect ratio.
float2 HmdWarp(float2 in01, float2 lensCenter)
{
   float2 theta = (in01 - lensCenter) * ScaleIn; // Scales to [-1, 1]
   float rSq = theta.x * theta.x + theta.y * theta.y;
   float2 theta1 = theta * (HmdWarpParam.x + HmdWarpParam.y * rSq + HmdWarpParam.z * rSq * rSq + HmdWarpParam.w * rSq * rSq * rSq);
   return lensCenter + Scale * theta1;
}

float4 main( PFXVertToPix IN ) : COLOR0  
{
   float2 texCoord;
   float xOffset;
   float2 lensCenter;
   lensCenter.y = LensCenter.z;
   if(IN.uv0.x < 0.5)
   {
      texCoord.x = IN.uv0.x;
      texCoord.y = IN.uv0.y;
      xOffset = 0.0;
      lensCenter.x = LensCenter.x;
   }
   else
   {
      texCoord.x = IN.uv0.x - 0.5;
      texCoord.y = IN.uv0.y;
      xOffset = 0.5;
      lensCenter.x = LensCenter.y;
   }
   
   float2 tc = HmdWarp(texCoord, lensCenter);
   
   float4 color;
   if (any(clamp(tc, ScreenCenter-float2(0.25,0.5), ScreenCenter+float2(0.25, 0.5)) - tc))
   {
      color = float4(0,0,0,0);
   }
   else
   {
      tc.x += xOffset;
      color = tex2D(backBuffer, tc);
   }

   return color;    
}
