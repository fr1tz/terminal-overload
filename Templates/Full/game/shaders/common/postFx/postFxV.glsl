// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../gl/torque.glsl"

in vec4 vPosition;
in vec2 vTexCoord0;
in vec3 vTexCoord1;

uniform vec4 rtParams0;
uniform vec4 rtParams1;
uniform vec4 rtParams2;
uniform vec4 rtParams3;

out vec2 uv0;
out vec2 uv1;
out vec2 uv2;
out vec2 uv3;
out vec3 wsEyeRay;                 


void main()
{
   gl_Position = vPosition;
   
   uv0 = viewportCoordToRenderTarget( vTexCoord0, rtParams0 ); 
   uv1 = viewportCoordToRenderTarget( vTexCoord0, rtParams1 ); 
   uv2 = viewportCoordToRenderTarget( vTexCoord0, rtParams2 ); 
   uv3 = viewportCoordToRenderTarget( vTexCoord0, rtParams3 ); 
   
   wsEyeRay = vTexCoord1;
}
