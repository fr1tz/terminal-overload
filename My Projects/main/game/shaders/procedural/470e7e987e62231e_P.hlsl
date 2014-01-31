//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/foliage.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Foliage Feature
// Vert Position
// Base Texture
// Diffuse Color
// Visibility
// Translucent
// Forward Shaded Material

struct ConnectData
{
   float foliageFade     : TEXCOORD0;
   float2 texCoord        : TEXCOORD1;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float     visibility      : register(C0),
              uniform sampler2D diffuseMap      : register(S0),
              uniform float4    diffuseMaterialColor : register(C1)
)
{
   Fragout OUT;

   // Foliage Feature
   visibility *= IN.foliageFade;
   
   // Vert Position
   
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
