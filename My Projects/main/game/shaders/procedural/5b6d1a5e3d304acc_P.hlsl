//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Detail
// Diffuse Color
// Bumpmap [Deferred]
// Visibility
// Translucent
// DXTnm
// Forward Shaded Material

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float2 detCoord        : TEXCOORD1;
   float3x3 worldToTangent  : TEXCOORD2;
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
              uniform sampler2D detailMap       : register(S1),
              uniform float4    diffuseMaterialColor : register(C0),
              uniform sampler2D bumpMap         : register(S2),
              uniform float     visibility      : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Detail
   OUT.col += ( tex2D(detailMap, IN.detCoord) * 2.0 ) - 1.0;
   
   // Diffuse Color
   OUT.col *= diffuseMaterialColor;
   
   // Bumpmap [Deferred]
   float4 bumpNormal = float4( tex2D(bumpMap, IN.texCoord).ag * 2.0 - 1.0, 0.0, 0.0 ); // DXTnm
   bumpNormal.z = sqrt( 1.0 - dot( bumpNormal.xy, bumpNormal.xy ) ); // DXTnm
   float3 wsNormal = normalize( mul( bumpNormal.xyz, IN.worldToTangent ) );
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Translucent
   
   // DXTnm
   
   // Forward Shaded Material
   

   return OUT;
}
