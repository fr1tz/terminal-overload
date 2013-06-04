// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.hlsl"

struct ConnectData
{
   float4 hpos : POSITION;
   float2 texCoord : TEXCOORD0;
};

uniform sampler2D diffuseMap        : register(S0);

float4 main( ConnectData IN ) : COLOR
{
   float4 col = tex2D( diffuseMap, IN.texCoord );
   return hdrEncode( col );
}