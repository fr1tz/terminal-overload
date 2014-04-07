// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

in vec4 vPosition;
in vec2 vTexCoord0;

uniform mat4 modelview;

out vec2 tex0;

void main()
{
   gl_Position = modelview * vPosition;
   tex0 = vTexCoord0.st;
}