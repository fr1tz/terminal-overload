// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

in vec4 vPosition;
in vec2 vTexCoord0;

uniform mat4x4 modelview;

out vec4 hpos;
out vec2 uv0;


void main()
{
   hpos = vec4( modelview * vPosition );
   gl_Position = hpos;

   uv0 = vTexCoord0.st;
   gl_Position.y *= -1;
}
