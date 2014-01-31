// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


float attenuate( float4 lightColor, float2 attParams, float dist )
{
	// We're summing the results of a scaled constant,
	// linear, and quadratic attenuation.

	#ifdef ACCUMULATE_LUV
		return lightColor.w * ( 1.0 - dot( attParams, float2( dist, dist * dist ) ) );
	#else
		return 1.0 - dot( attParams, float2( dist, dist * dist ) );
	#endif
}

float3 getDistanceVectorToPlane( float3 origin, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float num = dot( plane, float4( origin, 1.0 ) );
   float t = -num / denum;

   return direction.xyz * t;
}

float3 getDistanceVectorToPlane( float negFarPlaneDotEye, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float t = negFarPlaneDotEye / denum;

   return direction.xyz * t;
}
