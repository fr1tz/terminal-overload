//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Texture Animation
// Diffuse Vertex Color
// Base Texture
// Bumpmap [Deferred]
// Visibility
// Eye Space Depth (Out)
// GBuffer Conditioner
// Translucent ZWrite

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float4 diffuse         : COLOR;
   float4 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float4 vertColor       : COLOR;
   float2 out_texCoord    : TEXCOORD0;
   float3x3 outViewToTangent : TEXCOORD1;
   float4 wsEyeVec        : TEXCOORD4;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 texMat          : register(C12),
                  uniform float4x4 viewToObj       : register(C4),
                  uniform float4x4 objTrans        : register(C8),
                  uniform float3   eyePosWorld     : register(C16)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Texture Animation
   
   // Diffuse Vertex Color
   OUT.vertColor = IN.diffuse;
   
   // Base Texture
   OUT.out_texCoord = (float2)mul(texMat, IN.texCoord);
   
   // Bumpmap [Deferred]
   float3x3 objToTangentSpace;
   objToTangentSpace[0] = IN.T;
   objToTangentSpace[1] = cross( IN.T, normalize(IN.normal) );
   objToTangentSpace[2] = normalize(IN.normal);
   float3x3 viewToTangent = mul( objToTangentSpace, (float3x3)viewToObj );
   OUT.outViewToTangent = viewToTangent;
   
   // Visibility
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // GBuffer Conditioner
   
   // Translucent ZWrite
   
   return OUT;
}
