//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Vertex Color
// Base Texture
// Diffuse Color
// Reflect Cube
// Visibility
// Fog
// HDR Output
// Translucent
// Forward Shaded Material

struct ConnectData
{
   float4 vertColor       : COLOR;
   float2 texCoord        : TEXCOORD0;
   float3 reflectVec      : TEXCOORD1;
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
              uniform sampler2D diffuseMap      : register(S0),
              uniform float4    diffuseMaterialColor : register(C0),
              uniform samplerCUBE cubeMap         : register(S1),
              uniform float     visibility      : register(C1),
              uniform float4    fogColor        : register(C2),
              uniform float3    eyePosWorld     : register(C3),
              uniform float3    fogData         : register(C4)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Vertex Color
   OUT.col = IN.vertColor;
   
   // Base Texture
   float4 diffuseColor = tex2D(diffuseMap, IN.texCoord);
   OUT.col *= diffuseColor;
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Reflect Cube
   OUT.col.rgb = lerp( OUT.col.rgb, (texCUBE( cubeMap, IN.reflectVec )).rgb, (diffuseColor).a );
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Translucent
   
   // Forward Shaded Material
   

   return OUT;
}
