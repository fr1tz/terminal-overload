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
// Diffuse Color
// Reflect Cube
// Visibility
// HDR Output
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
   float3 reflectVec      : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 texMat          : register(C8),
                  uniform float4x4 objTrans        : register(C4),
                  uniform float3   eyePosWorld     : register(C12)
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
   
   // Diffuse Color
   
   // Reflect Cube
   float3 cubeVertPos = mul((float3x3)objTrans, IN.position).xyz;
   float3 cubeNormal = normalize( mul(objTrans, normalize(IN.normal)).xyz );
   float3 cubePos = float3( objTrans[0][3], objTrans[1][3], objTrans[2][3] );
   float3 eyeToVert = cubeVertPos - ( eyePosWorld - cubePos );
   OUT.reflectVec = reflect(eyeToVert, cubeNormal);
   
   // Visibility
   
   // HDR Output
   
   // Translucent ZWrite
   
   return OUT;
}
