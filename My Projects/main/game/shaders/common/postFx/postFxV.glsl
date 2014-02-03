// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "./../gl/torque.glsl"

attribute vec4 vPosition;
attribute vec2 vTexCoord0;
attribute vec3 vTexCoord1;

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
   gl_Position = vPosition;
   
   uv0 = viewportCoordToRenderTarget( vTexCoord0, rtParams0 ); 
   uv1 = viewportCoordToRenderTarget( vTexCoord0, rtParams1 ); 
   uv2 = viewportCoordToRenderTarget( vTexCoord0, rtParams2 ); 
   uv3 = viewportCoordToRenderTarget( vTexCoord0, rtParams3 ); 
   
   wsEyeRay = vTexCoord1;
}
