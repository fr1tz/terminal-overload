//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Features:
// Vert Position
// Terrain Base Texture
// Eye Space Depth (Out)
// GBuffer Conditioner

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
   float4 wsEyeVec        : TEXCOORD1;
   float3 gbNormal        : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float    oneOverTerrainSize : register(C12),
                  uniform float    squareSize      : register(C13),
                  uniform float4x4 objTrans        : register(C4),
                  uniform float3   eyePosWorld     : register(C14),
                  uniform float4x4 worldViewOnly   : register(C8)
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
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // GBuffer Conditioner
   OUT.gbNormal = mul(worldViewOnly, float4( normalize(IN.normal), 0.0 ) ).xyz;
   
   return OUT;
}
