//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Diffuse Color
// Vert Lit
// Visibility
// Translucent
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float4 vertColor       : COLOR;
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
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Vert Lit
   float4 finalVertColor = -1.0f * log(1.0f - IN.vertColor);
   OUT.col = 1.0 - exp(-1.0 * OUT.col * finalVertColor);
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Translucent
   
   // Forward Shaded Material
   

   return OUT;
}
