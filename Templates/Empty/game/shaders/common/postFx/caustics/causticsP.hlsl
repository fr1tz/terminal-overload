// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

uniform float3    eyePosWorld;
uniform float4    rtParams0;
uniform float4    waterFogPlane;
uniform float     accumTime;

float4 main( PFXVertToPix IN, 
             uniform sampler2D prepassTex :register(S0),
             uniform sampler2D causticsTex0 :register(S1),
             uniform sampler2D causticsTex1 :register(S2),
             uniform float2 targetSize : register(C0) ) : COLOR
{   
   //Sample the pre-pass
   float2 prepassCoord = ( IN.uv0.xy * rtParams0.zw ) + rtParams0.xy;  
   float4 prePass = prepassUncondition( prepassTex, prepassCoord );
   
   //Get depth
   float depth = prePass.w;   
   clip( 0.9999 - depth );
   
   //Get world position
   float3 pos = eyePosWorld + IN.wsEyeRay * depth;
   
   //Use world position X and Y to calculate caustics UV 
   float2 causticsUV0 = (abs(pos.xy * 0.25) % float2(1, 1));
   float2 causticsUV1 = (abs(pos.xy * 0.2) % float2(1, 1));
   
   //Animate uvs
   float timeSin = sin(accumTime);
   causticsUV0.xy += float2(accumTime*0.1, timeSin*0.2);
   causticsUV1.xy -= float2(accumTime*0.15, timeSin*0.15);   
   
   //Sample caustics texture   
   float4 caustics = tex2D(causticsTex0, causticsUV0);   
   caustics *= tex2D(causticsTex1, causticsUV1);
   
   //Use normal Z to modulate caustics  
   float waterDepth = 1 - saturate(pos.z + waterFogPlane.w + 1);
   caustics *= saturate(prePass.z) * pow(1-depth, 64) * waterDepth; 
      
   return caustics;   
}
