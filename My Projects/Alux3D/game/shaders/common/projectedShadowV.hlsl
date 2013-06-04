// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

struct Vert
{
	float3 position	: POSITION;
    float3 normal          : NORMAL;
    float3 T               : TANGENT;
    float4 color      : COLOR0;
    float2 texCoord        : TEXCOORD0;
};

struct Conn
{
	float4 position : POSITION;
   float4 color : COLOR0;
	float2 texCoord	: TEXCOORD0;
	float fade : TEXCOORD1;
};

uniform float4x4 modelview;
uniform float shadowLength;
uniform float3 shadowCasterPosition;

Conn main( Vert In )
{
    Conn Out;

    // Decals are in world space.
    Out.position = mul( modelview, float4( In.position.xyz, 1.0 ) );
 
    Out.color = In.color;
    Out.texCoord = In.texCoord;
 
    float fromCasterDist = length( In.position.xyz - shadowCasterPosition ) - shadowLength;   
    Out.fade = 1.0 - saturate( fromCasterDist / shadowLength );
    
   return Out;
}
