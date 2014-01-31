//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Bumpmap [Deferred]
// Eye Space Depth (Out)
// Visibility
// GBuffer Conditioner
// DXTnm

struct VertData
{
   float3 position        : POSITION;
   float tangentW        : TEXCOORD3;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float2 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float3x3 outViewToTangent : TEXCOORD0;
   float2 out_texCoord    : TEXCOORD3;
   float4 wsEyeVec        : TEXCOORD4;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 viewToObj       : register(C4),
                  uniform float4x4 objTrans        : register(C8),
                  uniform float3   eyePosWorld     : register(C12)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Bumpmap [Deferred]
   float3x3 objToTangentSpace;
   objToTangentSpace[0] = IN.T;
   objToTangentSpace[1] = cross( IN.T, normalize(IN.normal) ) * IN.tangentW;
   objToTangentSpace[2] = normalize(IN.normal);
   float3x3 viewToTangent = mul( objToTangentSpace, (float3x3)viewToObj );
   OUT.outViewToTangent = viewToTangent;
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // Visibility
   
   // GBuffer Conditioner
   
   // DXTnm
   
   return OUT;
}
