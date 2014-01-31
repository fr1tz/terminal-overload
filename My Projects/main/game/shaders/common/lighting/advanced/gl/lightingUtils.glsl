// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


float attenuate( vec4 lightColor, vec2 attParams, float dist )
{
	// We're summing the results of a scaled constant,
	// linear, and quadratic attenuation.

	#ifdef ACCUMULATE_LUV
		return lightColor.w * ( 1.0 - dot( attParams, vec2( dist, dist * dist ) ) );
	#else
		return 1.0 - dot( attParams, vec2( dist, dist * dist ) );
	#endif
}

// Calculate the specular coefficent
//
//	pxlToLight - Normalized vector representing direction from the pixel being lit, to the light source, in world space
//	normal - Normalized surface normal
//	pxlToEye - Normalized vector representing direction from pixel being lit, to the camera, in world space
//	specPwr - Specular exponent
//	specularScale - A scalar on the specular output used in RGB accumulation.
//
float calcSpecular( vec3 pxlToLight, vec3 normal, vec3 pxlToEye, float specPwr, float specularScale )
{
#ifdef PHONG_SPECULAR 
   // (R.V)^c
   float specVal = dot( normalize( -reflect( pxlToLight, normal ) ), pxlToEye );
#else
   // (N.H)^c   [Blinn-Phong, TGEA style, default]
   float specVal = dot( normal, normalize( pxlToLight + pxlToEye ) );
#endif

#ifdef ACCUMULATE_LUV
   return pow( max( specVal, 0.00001f ), specPwr );
#else
   // If this is RGB accumulation, than there is no facility for the luminance
   // of the light to play in to the specular intensity. In LUV, the luminance
   // of the light color gets rolled into N.L * Attenuation
   return specularScale * pow( max( specVal, 0.00001f ), specPwr );
#endif
}

vec3 getDistanceVectorToPlane( vec3 origin, vec3 direction, vec4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float num = dot( plane, vec4( origin, 1.0 ) );
   float t = -num / denum;

   return direction.xyz * t;
}

vec3 getDistanceVectorToPlane( float negFarPlaneDotEye, vec3 direction, vec4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float t = negFarPlaneDotEye / denum;

   return direction.xyz * t;
}