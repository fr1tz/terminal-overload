//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Reflect Cube
// HDR Output

struct ConnectData
{
   float3 reflectVec      : TEXCOORD0;
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
              uniform samplerCUBE cubeMap         : register(S0)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Reflect Cube
   OUT.col *= texCUBE( cubeMap, IN.reflectVec );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   

   return OUT;
}
