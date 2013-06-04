// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

uniform mat4 modelview;

varying vec2 tex0;

void main()
{
   gl_Position = modelview * gl_Vertex;
   tex0 = gl_MultiTexCoord0.st;
}