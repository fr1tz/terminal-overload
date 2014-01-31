//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Visibility
// Forward Shaded Material
// Translucent

struct ConnectData
{
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
              uniform float     visibility      : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Forward Shaded Material
   
   // Translucent
   

   return OUT;
}
