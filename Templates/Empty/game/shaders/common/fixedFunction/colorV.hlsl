// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

struct Appdata
{
	float4 position   : POSITION;
	float4 color      : COLOR;
};
struct Conn
{
   float4 HPOS             : POSITION;
   float4 color            : COLOR;
};
Conn main( Appdata In, uniform float4x4 modelview : register(C0) )
{
   Conn Out;
   Out.HPOS = mul(modelview, In.position);
   Out.color = In.color;
   return Out;
}