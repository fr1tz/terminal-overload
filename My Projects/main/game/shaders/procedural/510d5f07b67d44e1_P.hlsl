//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Vertex Color
// Base Texture
// Visibility
// Translucent ZWrite

struct ConnectData
{
   float4 vertColor       : COLOR;
   float2 texCoord        : TEXCOORD0;
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
              uniform float     visibility      : register(C0)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Vertex Color
   OUT.col = IN.vertColor;
   
   // Base Texture
   OUT.col *= tex2D(diffuseMap, IN.texCoord);
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // Translucent ZWrite
   

   return OUT;
}
