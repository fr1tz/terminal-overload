// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"  
#include "../postFx.hlsl"  
#include "../../torque.hlsl"

uniform sampler2D backBuffer : register(S0);

uniform float2 LensXOffsets;

float4 main( PFXVertToPix IN ) : COLOR0  
{
   float2 texCoord;
   float xOffset;
   float2 lensCenter;
   lensCenter.y = 0.5;
   if(IN.uv0.x < 0.5)
   {
      texCoord.x = IN.uv0.x;
      texCoord.y = IN.uv0.y;
      xOffset = 0.0;
      lensCenter.x = LensXOffsets.x;
   }
   else
   {
      texCoord.x = IN.uv0.x - 0.5;
      texCoord.y = IN.uv0.y;
      xOffset = 0.5;
      lensCenter.x = LensXOffsets.y;
   }

   texCoord.x *= 2.0;
   texCoord.x += lensCenter.x;
   texCoord.x *= 0.5;
   texCoord.x += 0.25;
   
   float4 color = tex2D(backBuffer, texCoord);

   return color;    
}
