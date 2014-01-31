//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Visibility
// Eye Space Depth (Out)
// Hardware Instancing

struct ConnectData
{
   float visibility      : TEXCOORD0;
   float2 vpos            : VPOS;
   float4 wsEyeVec        : TEXCOORD1;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float3    vEye            : register(C0),
              uniform float4    oneOverFarplane : register(C1)
)
{
   Fragout OUT;

   // Vert Position
   
   // Visibility
   fizzle( IN.vpos, IN.visibility );
   
   // Eye Space Depth (Out)
#ifndef CUBE_SHADOW_MAP
   float eyeSpaceDepth = dot(vEye, (IN.wsEyeVec.xyz / IN.wsEyeVec.w));
#else
   float eyeSpaceDepth = length( IN.wsEyeVec.xyz / IN.wsEyeVec.w ) * oneOverFarplane.x;
#endif
   OUT.col = float4(eyeSpaceDepth.rrr,1);
   
   // Hardware Instancing
   

   return OUT;
}
