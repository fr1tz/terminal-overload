//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Visibility
// HDR Output

struct ConnectData
{
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
              uniform float4    diffuseMaterialColor : register(C0),
              uniform float     visibility      : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   

   return OUT;
}
