// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

float4 main( float4 color_in : COLOR0, uniform sampler2D diffuseMap : register(S0) ) : COLOR0
{
   return color_in;
}