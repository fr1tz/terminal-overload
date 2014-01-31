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
// Fog
// HDR Output
// Hardware Instancing
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
   float tangentW        : TEXCOORD3;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float2 texCoord        : TEXCOORD0;
   float4 inst_objectTrans[4] : TEXCOORD4;
   float inst_visibility : TEXCOORD8;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float2 detCoord        : TEXCOORD0;
   float visibility      : TEXCOORD1;
   float3 outWsPosition   : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 viewProj        : register(C1),
                  uniform float2   detailScale     : register(C0)
)
{
   ConnectData OUT;

   // Vert Position
   float4x4 objTrans = { // Instancing!
      IN.inst_objectTrans[0],
      IN.inst_objectTrans[1],
      IN.inst_objectTrans[2],
      IN.inst_objectTrans[3] };
   float4x4 modelview = mul( viewProj, objTrans ); // Instancing!
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Detail
   OUT.detCoord = IN.texCoord * detailScale;
   
   // Diffuse Color
   
   // Visibility
   OUT.visibility = IN.inst_visibility; // Instancing!
   
   // Fog
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // HDR Output
   
   // Hardware Instancing
   
   // Forward Shaded Material
   
   return OUT;
}
