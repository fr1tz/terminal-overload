// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#define IN_HLSL
#include "../../shdrConsts.h"
#include "../postFx.hlsl"

//-----------------------------------------------------------------------------
// Data 
//-----------------------------------------------------------------------------
struct VertIn
{
	float4 hpos : POSITION;
	float4 texCoords[8] : TEXCOORD0;
};
 
//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
float4 main(  VertIn IN,
              uniform sampler2D inputTex : register(S0) ) : COLOR
{
   // We calculate the texture coords
   // in the vertex shader as an optimization.
   float4 sample = 0.0f;
   for ( int i = 0; i < 8; i++ )
   {
      sample += tex2D( inputTex, IN.texCoords[i].xy );
      sample += tex2D( inputTex, IN.texCoords[i].zw );
   }
   
	return sample / 16;
}