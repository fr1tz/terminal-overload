//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Detail
// Bumpmap [Deferred]
// Visibility
// HDR Output
// DXTnm
// Hardware Instancing

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float2 detCoord        : TEXCOORD1;
   float3x3 worldToTangent  : TEXCOORD2;
   float visibility      : TEXCOORD5;
   float2 vpos            : VPOS;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D diffuseMap      : register(S0),
              uniform sampler2D detailMap       : register(S1),
              uniform sampler2D bumpMap         : register(S2)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   OUT.col = tex2D(diffuseMap, IN.texCoord);
   
   // Detail
   OUT.col += ( tex2D(detailMap, IN.detCoord) * 2.0 ) - 1.0;
   
   // Bumpmap [Deferred]
   float4 bumpNormal = float4( tex2D(bumpMap, IN.texCoord).ag * 2.0 - 1.0, 0.0, 0.0 ); // DXTnm
   bumpNormal.z = sqrt( 1.0 - dot( bumpNormal.xy, bumpNormal.xy ) ); // DXTnm
   float3 wsNormal = normalize( mul( bumpNormal.xyz, IN.worldToTangent ) );
   
   // Visibility
   fizzle( IN.vpos, IN.visibility );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // DXTnm
   
   // Hardware Instancing
   

   return OUT;
}
