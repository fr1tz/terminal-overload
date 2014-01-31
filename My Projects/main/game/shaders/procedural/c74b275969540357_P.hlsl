//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Paraboloid Vert Transform
// Visibility
// Depth (Out)

struct ConnectData
{
   float2 posXY           : TEXCOORD0;
   float2 vpos            : VPOS;
   float depth           : TEXCOORD1;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float     visibility      : register(C0)
)
{
   Fragout OUT;

   // Paraboloid Vert Transform
   clip( 1.0 - abs(IN.posXY.x) );
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // Depth (Out)
   OUT.col = float4( IN.depth, 0, 0, 1 );
   

   return OUT;
}
