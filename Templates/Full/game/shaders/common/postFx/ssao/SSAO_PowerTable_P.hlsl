// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../postFx.hlsl"

float4 main( PFXVertToPix IN ) : COLOR
{  
   float power = pow( max( IN.uv0.x, 0 ), 0.1 );   
   return float4( power, 0, 0, 1 );   
}