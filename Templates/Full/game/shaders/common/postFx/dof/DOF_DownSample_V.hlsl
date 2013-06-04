// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../postFx.hlsl"
#include "./../../torque.hlsl"

struct Vert
{
   float4 pos        : POSITION;
   float2 tc         : TEXCOORD0;
   float3 wsEyeRay   : TEXCOORD1;
};

struct Pixel
{  
   float4 position : POSITION;  
   float2 tcColor0 : TEXCOORD0;  
   float2 tcColor1 : TEXCOORD1;  
   float2 tcDepth0 : TEXCOORD2;  
   float2 tcDepth1 : TEXCOORD3;  
   float2 tcDepth2 : TEXCOORD4;  
   float2 tcDepth3 : TEXCOORD5;  
};  

uniform float4    rtParams0;
uniform float2    oneOverTargetSize;  

Pixel main( Vert IN )  
{  
   Pixel OUT; 
   OUT.position = IN.pos;
   
   float2 uv = viewportCoordToRenderTarget( IN.tc, rtParams0 ); 
   //OUT.position = mul( IN.pos, modelView );  
   OUT.tcColor1 = uv + float2( +1.0, -0.0 ) * oneOverTargetSize;  
   OUT.tcColor0 = uv + float2( -1.0, -0.0 ) * oneOverTargetSize;  
   OUT.tcDepth0 = uv + float2( -0.5, -0.0 ) * oneOverTargetSize;    
   OUT.tcDepth1 = uv + float2( -1.5, -0.0 ) * oneOverTargetSize;    
   OUT.tcDepth2 = uv + float2( +1.5, -0.0 ) * oneOverTargetSize;    
   OUT.tcDepth3 = uv + float2( +2.5, -0.0 ) * oneOverTargetSize;    
   return OUT;
}  