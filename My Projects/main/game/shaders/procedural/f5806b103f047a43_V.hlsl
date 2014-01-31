//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Diffuse Vertex Color
// Diffuse Color
// Visibility
// Fog
// HDR Output
// Translucent
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
   float4 diffuse         : COLOR;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float4 vertColor       : COLOR;
   float3 outWsPosition   : TEXCOORD0;
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
   
   // Diffuse Color
   
   // Visibility
   
   // Fog
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // HDR Output
   
   // Translucent
   
   // Forward Shaded Material
   
   return OUT;
}
