//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Visibility
// Eye Space Depth (Out)
// GBuffer Conditioner
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
   float visibility      : TEXCOORD0;
   float4 wsEyeVec        : TEXCOORD1;
   float3 gbNormal        : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 viewProj        : register(C0),
                  uniform float3   eyePosWorld     : register(C4),
                  uniform float4x4 worldToCamera   : register(C5)
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
   
   // Visibility
   OUT.visibility = IN.inst_visibility; // Instancing!
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // GBuffer Conditioner
   float4x4 worldViewOnly = mul( worldToCamera, objTrans ); // Instancing!
   OUT.gbNormal = mul(worldViewOnly, float4( normalize(IN.normal), 0.0 ) ).xyz;
   
   // Hardware Instancing
   
   return OUT;
}
