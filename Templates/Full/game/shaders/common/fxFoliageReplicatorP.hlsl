// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shdrConsts.h"

//-----------------------------------------------------------------------------
// Structures                                                                  
//-----------------------------------------------------------------------------
struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float4 lum				  : COLOR0;
   float4 groundAlphaCoeff : COLOR1;
   float2 alphaLookup	  : TEXCOORD1;
};

struct Fragout
{
   float4 col : COLOR0;
};

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D diffuseMap : register(S0),
              uniform sampler2D alphaMap : register(S1),
              uniform float4 groundAlpha,
              uniform float4 ambient )
{
   Fragout OUT;

	float4 alpha = tex2D(alphaMap, IN.alphaLookup);
   OUT.col = float4( ambient.rgb * IN.lum.rgb, 1.0 ) * tex2D(diffuseMap, IN.texCoord);
   OUT.col.a = OUT.col.a * min(alpha, groundAlpha + IN.groundAlphaCoeff.x).x;
   
   return OUT;
}
