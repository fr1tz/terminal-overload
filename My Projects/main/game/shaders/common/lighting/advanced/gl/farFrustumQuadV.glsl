// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "farFrustumQuad.glsl"

uniform vec4 renderTargetParams;

varying vec4 hpos;
varying vec2 uv0;
varying vec3 wsEyeRay;


void main()
{
   // Expand the SS coordinate (stored in uv0)
   hpos = vec4( gl_MultiTexCoord0.st * 2.0 - 1.0, 1.0, 1.0 );
   gl_Position = hpos;
   
   // Get a RT-corrected UV from the SS coord
   uv0 = getUVFromSSPos( hpos.xyz, renderTargetParams );
   
   // Interpolators will generate eye ray from far-frustum corners
   wsEyeRay = gl_Vertex.xyz;
}
