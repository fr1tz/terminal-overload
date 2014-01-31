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

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3 reflectVec      : TEXCOORD1;
   float visibility      : TEXCOORD2;
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
              uniform samplerCUBE cubeMap         : register(S1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Base Texture
   float4 diffuseColor = tex2D(diffuseMap, IN.texCoord);
   OUT.col = diffuseColor;
   
   // Reflect Cube
   OUT.col.rgb = lerp( OUT.col.rgb, (texCUBE( cubeMap, IN.reflectVec )).rgb, (diffuseColor).a );
   
   // Visibility
   fizzle( IN.vpos, IN.visibility );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Translucent ZWrite
   
   // Hardware Instancing
   

   return OUT;
}
