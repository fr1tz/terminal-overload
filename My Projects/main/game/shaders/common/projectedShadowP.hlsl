// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

struct Conn
{
   float2 texCoord : TEXCOORD0;
   float4 color : COLOR0;
   float fade : TEXCOORD1;
};

uniform sampler2D inputTex : register(S0);
uniform float4 ambient;

float4 main( Conn IN ) : COLOR0
{
   float shadow = tex2D( inputTex, IN.texCoord ).a * IN.color.a;           
   return ( ambient * shadow ) + ( 1 - shadow );
}
