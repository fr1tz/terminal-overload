//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Texture Animation
// Diffuse Vertex Color
// Base Texture
// Diffuse Color
// Reflect Cube
// Visibility
// Translucent ZWrite

struct ConnectData
{
   float4 vertColor       : COLOR;
   float2 texCoord        : TEXCOORD0;
   float3 reflectVec      : TEXCOORD1;
   float2 vpos            : VPOS;
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
              uniform float     visibility      : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Texture Animation
   
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
   fizzle( IN.vpos, visibility );
   
   // Translucent ZWrite
   

   return OUT;
}
