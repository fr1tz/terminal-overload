//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/foliage.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Foliage Feature
// Vert Position
// Visibility
// Eye Space Depth (Out)
// GBuffer Conditioner

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float4 diffuse         : COLOR;
   float4 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float foliageFade     : TEXCOORD0;
   float4 hpos            : POSITION;
   float4 wsEyeVec        : TEXCOORD1;
   float3 gbNormal        : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float3   eyePosWorld     : register(C12),
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 objTrans        : register(C4),
                  uniform float4x4 worldViewOnly   : register(C8)
)
{
   ConnectData OUT;

   // Foliage Feature
   float3 T;
   foliageProcessVert( IN.position, IN.diffuse, IN.texCoord, IN.normal, T, eyePosWorld );
   OUT.foliageFade = IN.diffuse.a;
   
   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Visibility
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // GBuffer Conditioner
   OUT.gbNormal = mul(worldViewOnly, float4( normalize(IN.normal), 0.0 ) ).xyz;
   
   return OUT;
}
