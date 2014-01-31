//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Detail
// Diffuse Color
// Visibility
// HDR Output
// Hardware Instancing

struct ConnectData
{
   float2 detCoord        : TEXCOORD0;
   float visibility      : TEXCOORD1;
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
              uniform sampler2D detailMap       : register(S0),
              uniform float4    diffuseMaterialColor : register(C0)
)
{
   Fragout OUT;

   // Vert Position
   
   // Detail
   OUT.col = ( tex2D(detailMap, IN.detCoord) * 2.0 ) - 1.0;
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Visibility
   fizzle( IN.vpos, IN.visibility );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Hardware Instancing
   

   return OUT;
}
