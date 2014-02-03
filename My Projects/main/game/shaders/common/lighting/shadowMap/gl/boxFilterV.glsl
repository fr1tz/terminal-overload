// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

attribute vec4 vPosition;
attribute vec2 vTexCoord0;

uniform mat4 modelview;

varying vec2 tex0;

void main()
{
   gl_Position = modelview * vPosition;
   tex0 = vTexCoord0.st;
}