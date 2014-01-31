//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Reflect Cube
// Visibility
// HDR Output
// Translucent ZWrite
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
   float2 out_texCoord    : TEXCOORD0;
   float3 reflectVec      : TEXCOORD1;
   float visibility      : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 viewProj        : register(C0),
                  uniform float3   eyePosWorld     : register(C4)
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
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Reflect Cube
   float3 cubeVertPos = mul((float3x3)objTrans, IN.position).xyz;
   float3 cubeNormal = normalize( mul(objTrans, normalize(IN.normal)).xyz );
   float3 cubePos = float3( objTrans[0][3], objTrans[1][3], objTrans[2][3] );
   float3 eyeToVert = cubeVertPos - ( eyePosWorld - cubePos );
   OUT.reflectVec = reflect(eyeToVert, cubeNormal);
   
   // Visibility
   OUT.visibility = IN.inst_visibility; // Instancing!
   
   // HDR Output
   
   // Translucent ZWrite
   
   // Hardware Instancing
   
   return OUT;
}
