// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

struct Vertex
{
   float4 pos : POSITION;
   float4 color : COLOR0;
   float2 uv0 : TEXCOORD0;
};

struct Conn
{
   float4 hpos : POSITION;
   float4 color : TEXCOORD0;
   float2 uv0 : TEXCOORD1;
	float4 pos : TEXCOORD2;
};


uniform float4x4 modelViewProj;
uniform float4x4 fsModelViewProj;

Conn main( Vertex In )
{
   Conn Out;

   Out.hpos = mul( modelViewProj, In.pos );
	Out.pos = mul( fsModelViewProj, In.pos );
	Out.color = In.color;
	Out.uv0 = In.uv0;
	
   return Out;
}

