//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Diffuse Color
// Bumpmap [Deferred]
// Visibility
// Fog
// HDR Output
// Hardware Instancing
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3x3 worldToTangent  : TEXCOORD1;
   float visibility      : TEXCOORD4;
   float2 vpos            : VPOS;
   float3 wsPosition      : TEXCOORD5;
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
              uniform float4    diffuseMaterialColor : register(C0),
              uniform sampler2D bumpMap         : register(S1),
              uniform float4    fogColor        : register(C1),
              uniform float3    eyePosWorld     : register(C2),
              uniform float3    fogData         : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Bumpmap [Deferred]
   float4 bumpNormal = tex2D(bumpMap, IN.texCoord);
   bumpNormal.xyz = bumpNormal.xyz * 2.0 - 1.0;
   float3 wsNormal = normalize( mul( bumpNormal.xyz, IN.worldToTangent ) );
   
   // Visibility
   fizzle( IN.vpos, IN.visibility );
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Hardware Instancing
   
   // Forward Shaded Material
   

   return OUT;
}
