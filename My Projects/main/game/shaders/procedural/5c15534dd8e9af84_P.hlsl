//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Bumpmap [Deferred]
// Visibility

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3x3 worldToTangent  : TEXCOORD1;
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
              uniform sampler2D bumpMap         : register(S1),
              uniform float     visibility      : register(C0)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Bumpmap [Deferred]
   float4 bumpNormal = tex2D(bumpMap, IN.texCoord);
   bumpNormal.xyz = bumpNormal.xyz * 2.0 - 1.0;
   float3 wsNormal = normalize( mul( bumpNormal.xyz, IN.worldToTangent ) );
   
   // Visibility
   fizzle( IN.vpos, visibility );
   

   return OUT;
}
