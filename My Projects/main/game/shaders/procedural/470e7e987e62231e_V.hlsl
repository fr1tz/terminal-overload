//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/foliage.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Foliage Feature
// Vert Position
// Base Texture
// Diffuse Color
// Visibility
// Translucent
// Forward Shaded Material

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
   float2 out_texCoord    : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float3   eyePosWorld     : register(C4),
                  uniform float4x4 modelview       : register(C0)
)
{
   ConnectData OUT;

   // Foliage Feature
   float3 T;
   foliageProcessVert( IN.position, IN.diffuse, IN.texCoord, IN.normal, T, eyePosWorld );
   OUT.foliageFade = IN.diffuse.a;
   
   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Diffuse Color
   
   // Visibility
   
   // Translucent
   
   // Forward Shaded Material
   
   return OUT;
}
