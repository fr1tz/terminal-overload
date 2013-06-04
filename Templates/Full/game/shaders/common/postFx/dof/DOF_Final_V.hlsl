// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../postFx.hlsl"
#include "./../../torque.hlsl"

uniform float4 rtParams0;
uniform float4 rtParams1;
uniform float4 rtParams2;
uniform float4 rtParams3;
uniform float2 oneOverTargetSize;  
                     
PFXVertToPix main( PFXVert IN )
{
   PFXVertToPix OUT;
           
   /*
   OUT.hpos = IN.pos;
   OUT.uv0 = IN.uv;
   OUT.uv1 = IN.uv;
   OUT.uv2 = IN.uv;
   OUT.uv3 = IN.uv;   
   */
      
   /*
   OUT.hpos = IN.pos;
   OUT.uv0 = IN.uv + rtParams0.xy;
   OUT.uv1 = IN.uv + rtParams1.xy;
   OUT.uv2 = IN.uv + rtParams2.xy;
   OUT.uv3 = IN.uv + rtParams3.xy;  
   */
   
   
   /*
   OUT.hpos = IN.pos;
   OUT.uv0 = IN.uv * rtParams0.zw;
   OUT.uv1 = IN.uv * rtParams1.zw;
   OUT.uv2 = IN.uv * rtParams2.zw;
   OUT.uv3 = IN.uv * rtParams3.zw;  
   */
   
   
   OUT.hpos = IN.pos;
   OUT.uv0 = viewportCoordToRenderTarget( IN.uv, rtParams0 ); 
   OUT.uv1 = viewportCoordToRenderTarget( IN.uv, rtParams1 ); // + float2( -5, 1 ) * oneOverTargetSize; 
   OUT.uv2 = viewportCoordToRenderTarget( IN.uv, rtParams2 ); 
   OUT.uv3 = viewportCoordToRenderTarget( IN.uv, rtParams3 ); 
   

   OUT.wsEyeRay = IN.wsEyeRay;
   
   return OUT;
}
