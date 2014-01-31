//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/lighting.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Detail
// RT Lighting
// Visibility
// Fog
// HDR Output
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float3 B               : BINORMAL;
   float2 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float2 out_texCoord    : TEXCOORD0;
   float2 detCoord        : TEXCOORD1;
   float3 wsNormal        : TEXCOORD2;
   float3 outWsPosition   : TEXCOORD3;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float2   detailScale     : register(C8),
                  uniform float4x4 objTrans        : register(C4)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Detail
   OUT.detCoord = IN.texCoord * detailScale;
   
   // RT Lighting
   OUT.wsNormal = mul( objTrans, float4( normalize( IN.normal ), 0.0 ) ).xyz;
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // Visibility
   
   // Fog
   
   // HDR Output
   
   // Forward Shaded Material
   
   return OUT;
}
