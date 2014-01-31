// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../postFx.hlsl"
#include "./../../torque.hlsl"


uniform float2 texSize0;
uniform float4 rtParams0;
uniform float2 oneOverTargetSize; 

struct VertToPix
{
   float4 hpos       : POSITION;      

   float4 uv0        : TEXCOORD0;
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
   
   IN.uv = viewportCoordToRenderTarget( IN.uv, rtParams0 );
   
   //float4 step = float4( 3.5, 2.5, 1.5, 0.5 );
   //float4 step = float4( 4.0, 3.0, 2.0, 1.0 );
   float4 step = float4( 9.0, 5.0, 2.5, 0.5 );
   
   // I don't know why this offset is necessary, but it is.
   //IN.uv = IN.uv * oneOverTargetSize;

   OUT.uv0.xy = IN.uv + ( ( BLUR_DIR * step.x ) / texSize0 );
   OUT.uv1 = IN.uv + ( ( BLUR_DIR * step.y ) / texSize0 );
   OUT.uv2 = IN.uv + ( ( BLUR_DIR * step.z ) / texSize0 );
   OUT.uv3 = IN.uv + ( ( BLUR_DIR * step.w ) / texSize0 );

   OUT.uv4 = IN.uv - ( ( BLUR_DIR * step.x ) / texSize0 );
   OUT.uv5 = IN.uv - ( ( BLUR_DIR * step.y ) / texSize0 );
   OUT.uv6 = IN.uv - ( ( BLUR_DIR * step.z ) / texSize0 );
   OUT.uv7 = IN.uv - ( ( BLUR_DIR * step.w ) / texSize0 );   
   
   OUT.uv0.zw = IN.uv;
   
   /*
   OUT.uv0 = viewportCoordToRenderTarget( OUT.uv0, rtParams0 );
   OUT.uv1 = viewportCoordToRenderTarget( OUT.uv1, rtParams0 );
   OUT.uv2 = viewportCoordToRenderTarget( OUT.uv2, rtParams0 );
   OUT.uv3 = viewportCoordToRenderTarget( OUT.uv3, rtParams0 );
   
   OUT.uv4 = viewportCoordToRenderTarget( OUT.uv4, rtParams0 );
   OUT.uv5 = viewportCoordToRenderTarget( OUT.uv5, rtParams0 );
   OUT.uv6 = viewportCoordToRenderTarget( OUT.uv6, rtParams0 );
   OUT.uv7 = viewportCoordToRenderTarget( OUT.uv7, rtParams0 );
   */
   
   return OUT;
}
