//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/terrain/terrain.hlsl"
#include "shaders/common/lighting.hlsl"
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Terrain Base Texture
// Terrain Lightmap Texture
// Terrain Detail Texture 0
// RT Lighting
// Fog
// HDR Output
// Forward Shaded Material

struct ConnectData
{
   float3 texCoord        : TEXCOORD0;
   float4 detCoord0       : TEXCOORD1;
   float3 wsNormal        : TEXCOORD2;
   float3 wsPosition      : TEXCOORD3;
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D baseTexMap      : register(S0),
              uniform sampler2D lightMapTex     : register(S1),
              uniform sampler2D layerTex        : register(S2),
              uniform float     layerSize       : register(C16),
              uniform float3    detailIdStrengthParallax0 : register(C0),
              uniform sampler2D detailMap0      : register(S3),
              uniform float3    eyePosWorld     : register(C17),
              uniform float4    inLightPos[3] : register(C1),
              uniform float4    inLightInvRadiusSq : register(C4),
              uniform float4    inLightColor[4] : register(C5),
              uniform float4    inLightSpotDir[3] : register(C9),
              uniform float4    inLightSpotAngle : register(C12),
              uniform float4    inLightSpotFalloff : register(C13),
              uniform float     specularPower   : register(C14),
              uniform float4    specularColor   : register(C15),
              uniform float4    ambient         : register(C18),
              uniform float4    fogColor        : register(C19),
              uniform float3    fogData         : register(C20)
)
{
   Fragout OUT;

   // Vert Position
   
   // Terrain Base Texture
   float4 baseColor = tex2D( baseTexMap, IN.texCoord.xy );
   OUT.col = baseColor;
   
   // Terrain Lightmap Texture
   float4 lightMask = 1;
   lightMask[0] = tex2D( lightMapTex, IN.texCoord.xy ).r;
   
   // Terrain Detail Texture 0
   float4 layerSample = round( tex2D( layerTex, IN.texCoord.xy ) * 255.0f );
   float detailBlend0 = calcBlend( detailIdStrengthParallax0.x, IN.texCoord.xy, layerSize, layerSample );
   float blendTotal = 0;
   blendTotal = max( blendTotal, detailBlend0 );
   float4 detailColor;
   if ( detailBlend0 > 0.0f )
   {
      detailColor = ( tex2D( detailMap0, IN.detCoord0.xy ) * 2.0 ) - 1.0;
      detailColor *= detailIdStrengthParallax0.y * IN.detCoord0.w;
      OUT.col = lerp( OUT.col, baseColor + detailColor, detailBlend0 );
   }
   
   // RT Lighting
   IN.wsNormal = normalize( half3( IN.wsNormal ) );
   float3 wsView = normalize( eyePosWorld - IN.wsPosition );
   float4 rtShading; float4 specular;
   compute4Lights( wsView, IN.wsPosition, IN.wsNormal, lightMask,
      inLightPos, inLightInvRadiusSq, inLightColor, inLightSpotDir, inLightSpotAngle, inLightSpotFalloff, specularPower, specularColor,
      rtShading, specular );
   OUT.col *= float4( rtShading.rgb + ambient.rgb, 1 );
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Forward Shaded Material
   

   return OUT;
}
