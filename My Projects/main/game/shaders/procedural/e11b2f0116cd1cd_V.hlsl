//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/lighting.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Terrain Base Texture
// Terrain Lightmap Texture
// RT Lighting
// Fog
// HDR Output
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float tcTangentZ      : TEXCOORD0;
   float tcEmpty         : TEXCOORD1;
};


struct ConnectData
{
   float4 hpos            : POSITION;
   float3 outTexCoord     : TEXCOORD0;
   float3 wsNormal        : TEXCOORD1;
   float3 outWsPosition   : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float    oneOverTerrainSize : register(C8),
                  uniform float    squareSize      : register(C9),
                  uniform float4x4 objTrans        : register(C4)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Terrain Base Texture
   float3 texCoord = IN.position.xyz * float3( oneOverTerrainSize, oneOverTerrainSize, -oneOverTerrainSize );
   OUT.outTexCoord.xy = texCoord.xy;
   OUT.outTexCoord.z = 0;
   float3 T = normalize( float3( squareSize, 0, IN.tcTangentZ ) );
   
   // Terrain Lightmap Texture
   
   // RT Lighting
   OUT.wsNormal = mul( objTrans, float4( normalize( IN.normal ), 0.0 ) ).xyz;
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // Fog
   
   // HDR Output
   
   // Forward Shaded Material
   
   return OUT;
}
