// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.glsl"
#include "hlslCompat.glsl"


// Conn
varying vec4  rayleighColor;
#define IN_rayleighColor rayleighColor
varying vec4  mieColor;
#define IN_mieColor mieColor
varying vec3  v3Direction;
#define IN_v3Direction v3Direction
varying float zPosition;
#define IN_zPosition zPosition
varying vec3  pos;
#define IN_pos pos

uniform samplerCube nightSky ;
uniform vec4 nightColor;
uniform vec2 nightInterpAndExposure;
uniform float useCubemap;
uniform vec3 lightDir;
uniform vec3 sunDir;

void main()
{ 

   float fCos = dot( lightDir, IN_v3Direction ) / length(IN_v3Direction);
   float fCos2 = fCos*fCos;
    
   float g = -0.991;
   float g2 = -0.991 * -0.991;

   float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(abs(1.0 + g2 - 2.0*g*fCos), 1.5);
   
   vec4 color = IN_rayleighColor + fMiePhase * IN_mieColor;
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
