
#include "shaders/common/postFx/postFx.hlsl"
#include "shaders/common/torque.hlsl"

uniform sampler2D backBuffer : register(s0);
uniform float distCoeff;
uniform float cubeDistort;
uniform float3 colorDistort;
uniform float4 keepColor;

float4 main( PFXVertToPix IN ) : COLOR0
{
   float4 outColor = tex2D(backBuffer, IN.uv0);

   float v = (outColor[0] + outColor[1] + outColor[2]) / 3;
   outColor[0] = v;
   outColor[1] = 0;
   outColor[2] = 0;

   return float4(outColor.rgb, 1);
}
