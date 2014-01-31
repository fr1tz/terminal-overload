// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

struct CloudVert
{
   float4 pos        : POSITION;
   float3 normal     : NORMAL;
   float3 binormal   : BINORMAL;
   float3 tangent    : TANGENT;
   float2 uv0        : TEXCOORD0;
};

struct ConnectData
{
   float4 hpos : POSITION;
   float2 texCoord : TEXCOORD0;
};

uniform float4x4  modelview;
uniform float     accumTime;
uniform float     texScale;
uniform float2    texDirection;
uniform float2    texOffset;

ConnectData main( CloudVert IN )
{   
   ConnectData OUT;
   
   OUT.hpos = mul(modelview, IN.pos);
   
   float2 uv = IN.uv0;
   uv += texOffset;
   uv *= texScale;
   uv += accumTime * texDirection;

   OUT.texCoord = uv;   
   
   return OUT;
}