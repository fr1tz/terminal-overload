//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Detail
// Diffuse Color
// Visibility
// Fog
// HDR Output
// Hardware Instancing
// Forward Shaded Material

struct ConnectData
{
   float2 detCoord        : TEXCOORD0;
   float visibility      : TEXCOORD1;
   float2 vpos            : VPOS;
   float3 wsPosition      : TEXCOORD2;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D detailMap       : register(S0),
              uniform float4    diffuseMaterialColor : register(C0),
              uniform float4    fogColor        : register(C1),
              uniform float3    eyePosWorld     : register(C2),
              uniform float3    fogData         : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Detail
   OUT.col = ( tex2D(detailMap, IN.detCoord) * 2.0 ) - 1.0;
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
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
