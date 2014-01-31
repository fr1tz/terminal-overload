//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Diffuse Color
// Reflect Cube
// Visibility
// Fog
// HDR Output
// Translucent
// Hardware Instancing
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3 reflectVec      : TEXCOORD1;
   float visibility      : TEXCOORD2;
   float3 wsPosition      : TEXCOORD3;
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
              uniform float4    fogColor        : register(C1),
              uniform float3    eyePosWorld     : register(C2),
              uniform float3    fogData         : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   float4 diffuseColor = tex2D(diffuseMap, IN.texCoord);
   OUT.col = diffuseColor;
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Reflect Cube
   OUT.col.rgb = lerp( OUT.col.rgb, (texCUBE( cubeMap, IN.reflectVec )).rgb, (diffuseColor).a );
   
   // Visibility
   OUT.col.a *= IN.visibility;
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Translucent
   
   // Hardware Instancing
   
   // Forward Shaded Material
   

   return OUT;
}
