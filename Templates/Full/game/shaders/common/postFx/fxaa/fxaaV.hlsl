// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../../torque.hlsl"
#include "./../postFX.hlsl"

struct VertToPix
{
   float4 hpos       : POSITION;
   float2 uv0        : TEXCOORD0;
};

uniform float4 rtParams0;
                    
VertToPix main( PFXVert IN )
{
   VertToPix OUT;
   
   OUT.hpos = IN.pos;
   OUT.uv0 = viewportCoordToRenderTarget( IN.uv, rtParams0 ); 
   
   return OUT;
}
