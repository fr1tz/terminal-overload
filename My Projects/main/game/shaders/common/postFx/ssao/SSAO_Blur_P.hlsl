// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"
//#include "./../postFx.hlsl"

uniform sampler2D occludeMap : register(S0);
uniform sampler2D prepassMap : register(S1);

struct VertToPix
{
   float4 hpos       : POSITION;

   float4 uv0        : TEXCOORD0;
   float2 uv1        : TEXCOORD1;
   float2 uv2        : TEXCOORD2;
   float2 uv3        : TEXCOORD3;

   float2 uv4        : TEXCOORD4;
   float2 uv5        : TEXCOORD5;
   float2 uv6        : TEXCOORD6;
   float2 uv7        : TEXCOORD7;   
};


uniform float blurDepthTol;
uniform float blurNormalTol;


void sample( float2 uv, float weight, float4 centerTap, inout int usedCount, inout float occlusion, inout float total )
{
   //return;
   float4 tap = prepassUncondition( prepassMap, uv );   
   
   if ( abs( tap.a - centerTap.a ) < blurDepthTol )
   {
      if ( dot( tap.xyz, centerTap.xyz ) > blurNormalTol )
      {
         usedCount++;
         total += weight;
         occlusion += tex2D( occludeMap, uv ).r * weight;
      }
   }   
}

float4 main( VertToPix IN ) : COLOR
{   
   //float4 centerTap;
   float4 centerTap = prepassUncondition( prepassMap, IN.uv0.zw );
   
   //return centerTap;
   
   //float centerOcclude = tex2D( occludeMap, IN.uv0.zw ).r;
   //return float4( centerOcclude.rrr, 1 );

   float4 kernel = float4( 0.175, 0.275, 0.375, 0.475 ); //25f;

   float occlusion = 0;
   int usedCount = 0;
   float total = 0.0;
         
   sample( IN.uv0.xy, kernel.x, centerTap, usedCount, occlusion, total );
   sample( IN.uv1, kernel.y, centerTap, usedCount, occlusion, total );
   sample( IN.uv2, kernel.z, centerTap, usedCount, occlusion, total );
   sample( IN.uv3, kernel.w, centerTap, usedCount, occlusion, total );
   
   sample( IN.uv4, kernel.x, centerTap, usedCount, occlusion, total );
   sample( IN.uv5, kernel.y, centerTap, usedCount, occlusion, total );
   sample( IN.uv6, kernel.z, centerTap, usedCount, occlusion, total );
   sample( IN.uv7, kernel.w, centerTap, usedCount, occlusion, total );   
   
   occlusion += tex2D( occludeMap, IN.uv0.zw ).r * 0.5;
   total += 0.5;
   //occlusion /= 3.0;
   
   //occlusion /= (float)usedCount / 8.0;
   occlusion /= total;
   
   return float4( occlusion.rrr, 1 );   
   
   
   //return float4( 0,0,0,occlusion );
   
   //float3 color = tex2D( colorMap, IN.uv0.zw );
      
   //return float4( color, occlusion );
}