//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Bumpmap [Deferred]
// Visibility
// Fog
// HDR Output
// DXTnm
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3x3 worldToTangent  : TEXCOORD1;
   float2 vpos            : VPOS;
   float3 wsPosition      : TEXCOORD4;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D diffuseMap      : register(S0),
              uniform sampler2D bumpMap         : register(S1),
              uniform float     visibility      : register(C0),
              uniform float4    fogColor        : register(C1),
              uniform float3    eyePosWorld     : register(C2),
              uniform float3    fogData         : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Bumpmap [Deferred]
   float4 bumpNormal = float4( tex2D(bumpMap, IN.texCoord).ag * 2.0 - 1.0, 0.0, 0.0 ); // DXTnm
   bumpNormal.z = sqrt( 1.0 - dot( bumpNormal.xy, bumpNormal.xy ) ); // DXTnm
   float3 wsNormal = normalize( mul( bumpNormal.xyz, IN.worldToTangent ) );
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // DXTnm
   
   // Forward Shaded Material
   

   return OUT;
}
