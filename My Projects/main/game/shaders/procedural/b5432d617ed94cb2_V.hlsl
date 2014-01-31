//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Texture Animation
// Base Texture
// Diffuse Color
// Visibility
// Fog
// HDR Output
// Translucent
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
   float tangentW        : TEXCOORD3;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float4 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float2 out_texCoord    : TEXCOORD0;
   float3 outWsPosition   : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 texMat          : register(C8),
                  uniform float4x4 objTrans        : register(C4)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Texture Animation
   
   // Base Texture
   OUT.out_texCoord = (float2)mul(texMat, IN.texCoord);
   
   // Diffuse Color
   
   // Visibility
   
   // Fog
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // HDR Output
   
   // Translucent
   
   // Forward Shaded Material
   
   return OUT;
}
