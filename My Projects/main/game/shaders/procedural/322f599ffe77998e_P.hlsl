//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Reflect Cube
// Fog
// HDR Output
// Forward Shaded Material

struct ConnectData
{
   float3 reflectVec      : TEXCOORD0;
   float3 wsPosition      : TEXCOORD1;
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
              uniform samplerCUBE cubeMap         : register(S0),
              uniform float4    fogColor        : register(C1),
              uniform float3    eyePosWorld     : register(C2),
              uniform float3    fogData         : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Reflect Cube
   OUT.col *= texCUBE( cubeMap, IN.reflectVec );
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Forward Shaded Material
   

   return OUT;
}
