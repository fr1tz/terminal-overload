//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Visibility
// Fog
// HDR Output
// Forward Shaded Material

struct ConnectData
{
   float2 vpos            : VPOS;
   float3 wsPosition      : TEXCOORD0;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float4    diffuseMaterialColor : register(C0),
              uniform float     visibility      : register(C1),
              uniform float4    fogColor        : register(C2),
              uniform float3    eyePosWorld     : register(C3),
              uniform float3    fogData         : register(C4)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Forward Shaded Material
   

   return OUT;
}
