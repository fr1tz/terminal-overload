// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../gl/torque.glsl"


uniform vec4 rtParams0;
uniform vec4 rtParams1;
uniform vec4 rtParams2;
uniform vec4 rtParams3;

varying vec2 uv0;
varying vec2 uv1;
varying vec2 uv2;
varying vec2 uv3;
varying vec3 wsEyeRay;                 


void main()
{
   gl_Position = gl_Vertex;
   
   uv0 = viewportCoordToRenderTarget( gl_MultiTexCoord0.st, rtParams0 ); 
   uv1 = viewportCoordToRenderTarget( gl_MultiTexCoord0.st, rtParams1 ); 
   uv2 = viewportCoordToRenderTarget( gl_MultiTexCoord0.st, rtParams2 ); 
   uv3 = viewportCoordToRenderTarget( gl_MultiTexCoord0.st, rtParams3 ); 
   
   wsEyeRay = gl_MultiTexCoord1.xyz;
}
