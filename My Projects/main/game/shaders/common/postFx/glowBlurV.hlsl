// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./postFx.hlsl"
#include "./../torque.hlsl"


uniform float2 texSize0;

struct VertToPix
{
   float4 hpos       : POSITION;

   float2 uv0        : TEXCOORD0;
   float2 uv1        : TEXCOORD1;
   float2 uv2        : TEXCOORD2;
   float2 uv3        : TEXCOORD3;

   float2 uv4        : TEXCOORD4;
   float2 uv5        : TEXCOORD5;
   float2 uv6        : TEXCOORD6;
   float2 uv7        : TEXCOORD7;
};

VertToPix main( PFXVert IN )
{
   VertToPix OUT;
   
   OUT.hpos = IN.pos;
   
   float2 uv = IN.uv + (0.5f / texSize0);

   OUT.uv0 = uv + ( ( BLUR_DIR * 3.5f ) / texSize0 );
   OUT.uv1 = uv + ( ( BLUR_DIR * 2.5f ) / texSize0 );
   OUT.uv2 = uv + ( ( BLUR_DIR * 1.5f ) / texSize0 );
   OUT.uv3 = uv + ( ( BLUR_DIR * 0.5f ) / texSize0 );

   OUT.uv4 = uv - ( ( BLUR_DIR * 3.5f ) / texSize0 );
   OUT.uv5 = uv - ( ( BLUR_DIR * 2.5f ) / texSize0 );
   OUT.uv6 = uv - ( ( BLUR_DIR * 1.5f ) / texSize0 );
   OUT.uv7 = uv - ( ( BLUR_DIR * 0.5f ) / texSize0 );
   
   return OUT;
}
