// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslStructs.h"

struct VertOut
{
   float4 hpos : POSITION;
   float4 offscreenPos : TEXCOORD0;
   float4 backbufferPos : TEXCOORD1;
};

uniform float4 screenRect; // point, extent

VertOut main( float4 uvCoord : COLOR )
{
   VertOut OUT;
   
   OUT.hpos = float4(uvCoord.xy, 1.0, 1.0);
   OUT.hpos.xy *= screenRect.zw;
   OUT.hpos.xy += screenRect.xy;
   
   OUT.backbufferPos = OUT.hpos;
   OUT.offscreenPos = OUT.hpos;
   
   return OUT;
}

