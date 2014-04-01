// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "farFrustumQuad.glsl"

in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec2 vTexCoord0;

uniform vec4 rtParams0;
out vec4 hpos;
out vec2 uv0;
out vec3 wsEyeRay;
out vec3 vsEyeRay;

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
