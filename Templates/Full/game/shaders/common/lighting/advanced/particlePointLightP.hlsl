// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"

#include "farFrustumQuad.hlsl"
#include "lightingUtils.hlsl"
#include "../../lighting.hlsl"


struct ConvexConnectP
{
   float4 ssPos : TEXCOORD0;
   float3 vsEyeDir : TEXCOORD1;
};

float4 main(   ConvexConnectP IN,
               uniform sampler2D prePassBuffer : register(S0),
               
               uniform float4 lightPosition,
               uniform float4 lightColor,
               uniform float  lightRange,
               
               uniform float4 vsFarPlane,
               uniform float4 rtParams0 ) : COLOR0
{
   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w;
   float2 uvScene = getUVFromSSPos(ssPos, rtParams0);
   
   // Sample/unpack the normal/z data
   float4 prepassSample = prepassUncondition(prePassBuffer, uvScene);
   float3 normal = prepassSample.rgb;
   float depth = prepassSample.a;
   
   // Eye ray - Eye -> Pixel
   float3 eyeRay = getDistanceVectorToPlane(-vsFarPlane.w, IN.vsEyeDir, vsFarPlane);
   float3 viewSpacePos = eyeRay * depth;
      
   // Build light vec, get length, clip pixel if needed
   float3 lightVec = lightPosition.xyz - viewSpacePos;
   float lenLightV = length(lightVec);
   clip(lightRange - lenLightV);

   // Do a very simple falloff instead of real attenuation
   float atten = 1.0 - saturate(lenLightV / lightRange);

   // Normalize lightVec
   lightVec /= lenLightV;

   // N.L * Attenuation
   float Sat_NL_Att = saturate(dot(lightVec, normal)) * atten;     
   
   // Output, no specular
   return lightinfoCondition(lightColor.rgb, Sat_NL_Att, 0.0, 0.0);
}
