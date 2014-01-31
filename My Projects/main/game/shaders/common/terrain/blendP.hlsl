// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "terrain.hlsl"

struct ConnectData
{
   float4 hpos : POSITION;
   float2 layerCoord : TEXCOORD0;
   float2 texCoord : TEXCOORD1;
};

float4 main(   ConnectData IN,
               uniform sampler2D layerTex : register(S0),
               uniform sampler2D textureMap : register(S1),
               uniform float texId,
               uniform float layerSize ) : COLOR
{
   float4 layerSample = round( tex2D( layerTex, IN.layerCoord ) * 255.0f );

   float blend = calcBlend( texId, IN.layerCoord, layerSize, layerSample );

   clip( blend - 0.0001 );

   return float4( tex2D( textureMap, IN.texCoord ).rgb, blend );
}
