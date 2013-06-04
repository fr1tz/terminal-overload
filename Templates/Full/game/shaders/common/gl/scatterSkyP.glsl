// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.glsl"

// Calculates the Mie phase function
float getMiePhase(float fCos, float fCos2, float g, float g2)
{
	return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(abs(1.0 + g2 - 2.0*g*fCos), 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
	//return 1.0;
	return 0.75 + 0.75*fCos2;
}

varying vec4 rayleighColor;
varying vec4 mieColor;
varying vec3 v3Direction;
varying float zPosition;
varying vec3 pos;

uniform samplerCube nightSky;
uniform vec4 nightColor;
uniform vec2 nightInterpAndExposure;
uniform float useCubemap;
uniform vec3 lightDir;
uniform vec3 sunDir;

void main()         
{ 
   float fCos = dot( lightDir, v3Direction ) / length(v3Direction);
   float fCos2 = fCos*fCos;
    
   float g = -0.991;
   float g2 = -0.991 * -0.991;

   float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(abs(1.0 + g2 - 2.0*g*fCos), 1.5);
   
   vec4 color = rayleighColor + fMiePhase * mieColor;
   color.a = color.b;
   
   vec4 nightSkyColor = textureCube(nightSky, -v3Direction);
   nightSkyColor = mix(nightColor, nightSkyColor, useCubemap);

   float fac = dot( normalize( pos ), sunDir );
   fac = max( nightInterpAndExposure.y, pow( clamp( fac, 0.0, 1.0 ), 2 ) );
   gl_FragColor = mix( color, nightSkyColor, nightInterpAndExposure.y );
   
   // Clip based on the camera-relative
   // z position of the vertex, passed through
   // from the vertex position.
   if(zPosition < 0.0)
      discard;

   gl_FragColor.a = 1;
   gl_FragColor = hdrEncode( gl_FragColor );
}
