// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

float4 main( const float2 inPosition : POSITION ) : POSITION
{
   return float4( inPosition, 0, 1 );
}