// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


struct PFXVert
{
   float4 pos        : POSITION;
   float2 uv         : TEXCOORD0;
   float3 wsEyeRay   : TEXCOORD1;
};

struct PFXVertToPix
{
   float4 hpos       : POSITION;
   float2 uv0        : TEXCOORD0;
   float2 uv1        : TEXCOORD1;
   float2 uv2        : TEXCOORD2;
   float2 uv3        : TEXCOORD3;
   float3 wsEyeRay   : TEXCOORD4;
};
