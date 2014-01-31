//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Texture Animation
// Base Texture
// Diffuse Color
// Visibility
// Translucent
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
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
              uniform float     visibility      : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Texture Animation
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Translucent
   
   // Forward Shaded Material
   

   return OUT;
}
