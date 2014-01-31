//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Paraboloid Vert Transform
// Visibility
// Depth (Out)
// Hardware Instancing

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
   float2 posXY           : TEXCOORD0;
   float visibility      : TEXCOORD1;
   float depth           : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float2   atlasScale      : register(C0),
                  uniform float4x4 worldToCamera   : register(C1),
                  uniform float4   lightParams     : register(C5),
                  uniform float2   atlasXOffset    : register(C6)
)
{
   ConnectData OUT;

   // Paraboloid Vert Transform
   float4x4 objTrans = { // Instancing!
      IN.inst_objectTrans[0],
      IN.inst_objectTrans[1],
      IN.inst_objectTrans[2],
      IN.inst_objectTrans[3] };
   float4x4 worldViewOnly = mul( worldToCamera, objTrans ); // Instancing!
   OUT.hpos = mul(worldViewOnly, float4(IN.position.xyz,1)).xzyw;
   float L = length(OUT.hpos.xyz);
   OUT.hpos /= L;
   OUT.hpos.z = OUT.hpos.z + 1.0;
   OUT.hpos.xy /= OUT.hpos.z;
   OUT.hpos.z = L / lightParams.x;
   OUT.hpos.w = 1.0;
   OUT.posXY = OUT.hpos.xy;
   OUT.hpos.xy *= atlasScale.xy;
   OUT.hpos.xy += atlasXOffset;
   
   // Visibility
   OUT.visibility = IN.inst_visibility; // Instancing!
   
   // Depth (Out)
   OUT.depth = OUT.hpos.z / OUT.hpos.w;
   
   // Hardware Instancing
   
   return OUT;
}
