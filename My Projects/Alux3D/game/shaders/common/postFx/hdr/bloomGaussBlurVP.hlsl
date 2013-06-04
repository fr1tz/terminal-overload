// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

uniform sampler2D inputTex : register(S0);
uniform float2 oneOverTargetSize;
uniform float gaussMultiplier;
uniform float gaussMean;
uniform float gaussStdDev;

#define D3DX_PI 3.141592654

float computeGaussianValue( float x, float mean, float std_deviation )
{
    // The gaussian equation is defined as such:
    /*    
      -(x - mean)^2
      -------------
      1.0               2*std_dev^2
      f(x,mean,std_dev) = -------------------- * e^
      sqrt(2*pi*std_dev^2)
      
     */
    float tmp = ( 1.0f / sqrt( 2.0f * D3DX_PI * std_deviation * std_deviation ) );
    float tmp2 = exp( ( -( ( x - mean ) * ( x - mean ) ) ) / ( 2.0f * std_deviation * std_deviation ) );
    return tmp * tmp2;
}

float4 main( PFXVertToPix IN ) : COLOR
{
   float4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
   float offset = 0;
   float weight = 0;
   float x = 0;
   float fI = 0;

   for( int i = 0; i < 9; i++ )
   {
      fI = (float)i;
      offset = (fI - 4.0) * oneOverTargetSize.y;
      x = (fI - 4.0) / 4.0;
      weight = gaussMultiplier * computeGaussianValue( x, gaussMean, gaussStdDev );
      color += (tex2D( inputTex, IN.uv0 + float2( 0.0f, offset ) ) * weight );
   }

   return float4( color.rgb, 1.0f );
}