// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../hlslStructs.h"

struct ConvexConnectV
{
   float4 hpos : POSITION;
   float4 wsEyeDir : TEXCOORD0;
   float4 ssPos : TEXCOORD1;
   float4 vsEyeDir : TEXCOORD2;
};

ConvexConnectV main( VertexIn_P IN,
                     uniform float4x4 modelview,
                     uniform float4x4 objTrans,
                     uniform float4x4 worldViewOnly,
                     uniform float3 eyePosWorld )
{
   ConvexConnectV OUT;

   OUT.hpos = mul( modelview, IN.pos );
   OUT.wsEyeDir = mul( objTrans, IN.pos ) - float4( eyePosWorld, 0.0 );
   OUT.vsEyeDir = mul( worldViewOnly, IN.pos );
   OUT.ssPos = OUT.hpos;

   return OUT;
}
