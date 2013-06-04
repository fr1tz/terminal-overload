// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../hlslStructs.h"

struct ConvexConnectV
{
   float4 hpos : POSITION;
   float4 ssPos : TEXCOORD0;
   float3 vsEyeDir : TEXCOORD1;
};

ConvexConnectV main( VertexIn_P IN,
                     uniform float4x4 viewProj,
                     uniform float4x4 view,
                     uniform float3 particlePosWorld,
                     uniform float  lightRange )
{
   ConvexConnectV OUT;
   
   float4 vPosWorld = IN.pos + float4(particlePosWorld, 0.0) + float4(IN.pos.xyz, 0.0) * lightRange;
   OUT.hpos = mul(viewProj, vPosWorld);
   OUT.vsEyeDir = mul(view, vPosWorld);
   OUT.ssPos = OUT.hpos;

   return OUT;
}
