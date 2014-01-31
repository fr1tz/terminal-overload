//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"
#include "shaders/common/terrain/terrain.hlsl"

// Features:
// Vert Position
// Terrain Base Texture
// Terrain Detail Texture 0
// Eye Space Depth (Out)
// GBuffer Conditioner

struct ConnectData
{
   float3 texCoord        : TEXCOORD0;
   float4 detCoord0       : TEXCOORD1;
   float4 wsEyeVec        : TEXCOORD2;
   float3 gbNormal        : TEXCOORD3;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D layerTex        : register(S0),
              uniform float     layerSize       : register(C1),
              uniform float3    detailIdStrengthParallax0 : register(C0),
              uniform float3    vEye            : register(C2),
              uniform float4    oneOverFarplane : register(C3)
)
{
   Fragout OUT;

   // Vert Position
   
   // Terrain Base Texture
   
   // Terrain Detail Texture 0
   float4 layerSample = round( tex2D( layerTex, IN.texCoord.xy ) * 255.0f );
   float detailBlend0 = calcBlend( detailIdStrengthParallax0.x, IN.texCoord.xy, layerSize, layerSample );
   float blendTotal = 0;
   blendTotal = max( blendTotal, detailBlend0 );
   
   // Eye Space Depth (Out)
#ifndef CUBE_SHADOW_MAP
   float eyeSpaceDepth = dot(vEye, (IN.wsEyeVec.xyz / IN.wsEyeVec.w));
#else
   float eyeSpaceDepth = length( IN.wsEyeVec.xyz / IN.wsEyeVec.w ) * oneOverFarplane.x;
#endif
   
   // GBuffer Conditioner
   float4 normal_depth = float4(normalize(IN.gbNormal), eyeSpaceDepth);

   // output buffer format: GFXFormatR16G16B16A16F
   // g-buffer conditioner: float4(normal.X, normal.Y, depth Hi, depth Lo)
   float4 _gbConditionedOutput = float4(sqrt(half(2.0/(1.0 - normal_depth.y))) * half2(normal_depth.xz), 0.0, normal_depth.a);
   
   // Encode depth into hi/lo
   float2 _tempDepth = frac(normal_depth.a * float2(1.0, 65535.0));
   _gbConditionedOutput.zw = _tempDepth.xy - _tempDepth.yy * float2(1.0/65535.0, 0.0);

   OUT.col = _gbConditionedOutput;
   

   return OUT;
}
