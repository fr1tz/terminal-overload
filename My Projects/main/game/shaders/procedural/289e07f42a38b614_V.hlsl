//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/lighting.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Vertex Color
// Base Texture
// RT Lighting
// Visibility
// Fog
// HDR Output
// Forward Shaded Material
// Translucent ZWrite

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float4 diffuse         : COLOR;
   float2 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float4 vertColor       : COLOR;
   float2 out_texCoord    : TEXCOORD0;
   float3 wsNormal        : TEXCOORD1;
   float3 outWsPosition   : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 objTrans        : register(C4)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Diffuse Vertex Color
   OUT.vertColor = IN.diffuse;
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // RT Lighting
   OUT.wsNormal = mul( objTrans, float4( normalize( IN.normal ), 0.0 ) ).xyz;
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // Visibility
   
   // Fog
   
   // HDR Output
   
   // Forward Shaded Material
   
   // Translucent ZWrite
   
   return OUT;
}
