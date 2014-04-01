// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//*****************************************************************************
// Glow shader
//*****************************************************************************

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord0;

uniform mat4 modelview;
uniform vec2 offset0, offset1, offset2, offset3;

out vec2 texc0, texc1, texc2, texc3;

void main()
{
   gl_Position = modelview * vPosition;
   
   vec2 tc = vTexCoord0.st;
   tc.y = 1.0 - tc.y;
   
   texc0 = tc + offset0;
   texc1 = tc + offset1;
   texc2 = tc + offset2;
   texc3 = tc + offset3;
   gl_Position.y *= -1;
}