// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../../../../shaders/common/gl/torque.glsl"

uniform vec2 oneOverTargetSize;
uniform vec4 rtParams0;

varying vec2 uv;

void main()
{
	gl_Position = gl_Vertex;   
   uv = viewportCoordToRenderTarget( gl_MultiTexCoord0.st, rtParams0 ); 
}
