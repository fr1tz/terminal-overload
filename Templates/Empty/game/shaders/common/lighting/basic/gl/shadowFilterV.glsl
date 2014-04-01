// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../../../../shaders/common/gl/torque.glsl"

in vec4 vPosition;
in vec2 vTexCoord0;

uniform vec4 rtParams0;

out vec2 uv;

void main()
{
   gl_Position = vPosition;   
   uv = viewportCoordToRenderTarget( vTexCoord0.st, rtParams0 ); 
   gl_Position.y *= -1; //correct ssp
}
