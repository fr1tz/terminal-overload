// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "farFrustumQuad.glsl"

attribute vec4 vPosition;
attribute vec3 vNormal;
attribute vec3 vTangent;
attribute vec2 vTexCoord0;

uniform vec4 rtParams0;
varying vec4 hpos;
varying vec2 uv0;
varying vec3 wsEyeRay;
varying vec3 vsEyeRay;

void main()
{   
   hpos = vec4( vTexCoord0, 0, 1 );   

   // Get a RT-corrected UV from the SS coord
   uv0 = getUVFromSSPos( hpos.xyz, rtParams0 );
   gl_Position = hpos;   
   
   // Interpolators will generate eye rays the 
   // from far-frustum corners.
   wsEyeRay = vTangent;
   vsEyeRay = vNormal;
   
   correctSSP(gl_Position);
}
